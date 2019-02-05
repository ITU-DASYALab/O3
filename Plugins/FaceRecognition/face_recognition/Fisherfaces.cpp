#include "Fisherfaces.h"
#include <stdexcept>

Fisherfaces::Fisherfaces(ImageList X, int flags)
{
	if(X.size()<1)
	{
		throw runtime_error("The training image set cannot be empty.");
	}

	init(X, flags);
}

void Fisherfaces::init(ImageList X, int flags)
{
	if(X.size() < 2)
	{
		throw runtime_error("The training image list must at least two columns.");
	}

	this->flags = flags;
	this->imageList = X;

	// Here:
	//  n: is the number of samples (training images).
	//  c: is the number of classes (persons in the training set).
	int n = imageList.size();
	int c = imageList.getUniqueSubjectNames().size();


	if(flags & PRINT_DEBUG)
	{
		cout << EXWHERE << "n=" << n << endl;
		cout << EXWHERE << "c=" << c << endl;
	}

	// PCA projection.
	//----------------

	Mat trFaceMat = imageList.getImages().clone();

	this->pca = PCA(trFaceMat, Mat(),CV_PCA_DATA_AS_COL, n-c);

	for(int i = 0; i < n; i++) {
		this->pcaProjTrFaces.push_back(pca.project(trFaceMat.col(i)));
	}

	// LDA projection.
	//----------------

	Mat pcaProjTrFaceMat = Mat::zeros(this->pcaProjTrFaces[0].rows, n, CV_32FC1);

	vector<string> subjectNames = imageList.getAllSubjectNames();

	for(int i=0; i<n; i++){
		Mat matCol = pcaProjTrFaceMat.col(i);
		pcaProjTrFaces[i].copyTo(matCol);
	}

	ImageList pcaProjTrFaceList(subjectNames, pcaProjTrFaceMat);

	lda = LDA(pcaProjTrFaceList); //, PRINT_DEBUG);

	if(flags & PRINT_DEBUG)
	{
		cout << EXWHERE << " lda.eigenvectors (rows.cols): " << lda.eigenvectors.rows << "," << lda.eigenvectors.cols << endl;
		cout << EXWHERE << " pca.eigenvectors (rows.cols): " << pca.eigenvectors.rows << "," << pca.eigenvectors.cols << endl;
	}

	// The step: $W_{opt}=W_{fld}^TW_{pca}^T$ The pca guy should return eigenvectors 
	// as rows not columns which essentially means it returns $W_{pca}^T$.
	this->eigenvectors = pca.eigenvectors.t() * lda.eigenvectors;

	if(flags & PRINT_DEBUG)
	{
		cout << EXWHERE << " fisherfaces.eigenvectors (rows.cols): " << eigenvectors.rows << "," << eigenvectors.cols << endl;
	}

	for(int i = 0; i < n; i++) {
		Mat column = trFaceMat.col(i);
		this->ldaProjTrFaces.push_back(this->project(column));
	}
}

Fisherfaces::~Fisherfaces() { }

Mat Fisherfaces::project(Mat &m)
{
	return eigenvectors.t() * m;
}

/* This method takes a matrix representing a recognition image for an unknown 
 * face, reshapes it into a vector and projects it into face-space. The projected 
 * unknown face is compared to all traing images and the identity corresponding
 * to the training face that has the shortest euclidean distance to the unknown 
 * face is returned.
 */
vector<RecognizerResult> Fisherfaces::recognize(const Mat &unknown) 
{
	Mat unknownVec;
	unknown.reshape(1, unknown.rows*unknown.cols).convertTo(unknownVec, CV_32FC1);

	Mat unkLdaProjected = this->project(unknownVec);

	vector<RecognizerResult> res = nearestNeighbor(ldaProjTrFaces, unkLdaProjected);
	return res;
}

// Returns a matrix containing the eigenfaces.
Mat Fisherfaces::getEigenvectors()
{
	return this->eigenvectors;
}

// Returns a matrix containing the eigenvalues.
Mat Fisherfaces::getEigenvalues()
{
	return pca.eigenvalues;
}
