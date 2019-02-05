#include "Eigenfaces.h"
#include <stdexcept>
/* Implements an eigenfaces based face recognser.
 *     Parameters:
 *       imageList - The list of training images, there must be two or more of them.
 *       components - The number of principal components to retain during PCA analysis.
 *       flags - So far only PRINT_DEBUG is implemented.
 */
Eigenfaces::Eigenfaces(ImageList &imageList, int components, int flags)
{
	if(imageList.size()<1)
	{
		throw runtime_error("The training image set cannot be empty.");
	}

	init(imageList, components, flags);
}

void Eigenfaces::init(ImageList &imageList, int components, int flags)
{
	if(imageList.size() < 2)
	{
		throw runtime_error("The training image list must at least two columns.");
	}

	this->flags = flags;

	int numSamples = imageList.size(); 
	this->imageList = imageList;

	// Get a deep copy.
	trFaces = imageList.getImages().clone();
	//Mat trFaces = imageList.getImages();

	this->pca = new PCA(trFaces, Mat(),CV_PCA_DATA_AS_COL, components);

	for(int sampleIdx = 0; sampleIdx < numSamples; sampleIdx++) {
		this->projTrFaces.push_back(pca->project(trFaces.col(sampleIdx)));
	}

	if(flags & PRINT_DEBUG)
	{
		cout << EXWHERE << "Number of training faces: " << imageList.size() << endl;
		cout << EXWHERE << "Eigenvectors (rows,cols): " << pca->eigenvectors.rows << "," << pca->eigenvectors.cols << endl;
	}
}

Eigenfaces::~Eigenfaces()
{
	delete pca;
}

/* This method takes a matrix representing a recognition image for an unknown 
 * face, reshapes it into a vector and projects it into face-space. The projected 
 * unknown face is compared to all traing images and the identity corresponding
 * to the training face that has the shortest euclidean distance to the unknown 
 * face is returned.
 */
vector<RecognizerResult> Eigenfaces::recognize(const Mat& unknown) 
{

	Mat unkProjected = pca->project(unknown.reshape(1, unknown.rows*unknown.cols));

	vector<RecognizerResult> res = nearestNeighbor(projTrFaces, unkProjected);
	
	return res;
}

// Returns the vector containing the average face.
Mat Eigenfaces::getAverage()
{
	return pca->mean;
}


// Returns a matrix containing the eigenfaces.
Mat Eigenfaces::getEigenvectors()
{
	return pca->eigenvectors;
}

// Returns a matrix containing the eigenvalues.
Mat Eigenfaces::getEigenvalues()
{
	return pca->eigenvalues;
}
