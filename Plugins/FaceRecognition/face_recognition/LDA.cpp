#include "LDA.h"

#include "../common/common.h"
/*Implements LDA as described by Belhumeur et. al. in their paper :
 *Eigenfaces vs. Fisherfaces: Recognition Using Class Specific Linear Projection
 */
LDA::LDA(ImageList imageList, int flags)
{
	init(imageList, flags);
}

void LDA::init(ImageList imageList, int flags)
{
	this->flags = flags;

	Mat X = imageList.getImages();

	vector<string> classNames = imageList.getUniqueSubjectNames();
	int d = X.rows;					// Length of the training image vectors.
	int c = classNames.size();		// Number of classes (individuals/persons);
	int numComp = c-1;  			// Number of components to be retained.

	if(flags & PRINT_DEBUG)
	{
		cout << EXWHERE << "d=" << d << endl;
		cout << EXWHERE << "c=" << c << endl;
		cout << EXWHERE << "numComp=" << numComp << endl;
	}

	Mat Sw = Mat::zeros(d, d, CV_32FC1); // Within class scatter.
	Mat Sb = Mat::zeros(d, d, CV_32FC1); // Between class scatter.

	// Calculate $mu$ mean of all samples.
	Mat mu(d,1, CV_32FC1);

	for(int i=0; i<d; i++){
		Scalar tmpMean = mean(X.row(i));
		mu.at<float>(i, 0) = tmpMean.val[0]; 
	}

	for(int i=0; i<c; i++){

		// For each class extract the test image vectors.
		Mat Xi = imageList.getImageMatrixForName(classNames[i]);;

		// For these calculate the class meani $mu_i$.
		Mat mu_i(Xi.rows, 1, CV_32FC1);
		for(int j=0; j<Xi.rows; j++){
			mu_i.at<float>(0,j) = mean(Xi.row(j)).val[0];
		}
		
		// Between class scatter.
		// $S_b = \Sigma^c_{i-1} N_i (\mu_i-\mu)(\mu_i-\mu)^T$
		//
		// Where:
		//     c: Number of classes.
		//     \mu: mean image of all samples.
		//     \mu: mean image of current class.
		//

		Sb = Sb + (Xi.cols * ((mu_i - mu) * (mu_i - mu).t()));;

		// Within class scatter.
		// $S_w = \Sigma^c_{i-1} \Sigma_{x_k \in X_i} (x_k-\mu_i)(x_k-\mu_i)^T$
		//
		// Where:
		//     c: Number of classes.
		//     \mu: mean image of current class.
		//
		//Sw = Sw + ((Xi - classMeanMat) * (Xi - classMeanMat).t());
		Mat Sw_mark = Mat::zeros(d, d, CV_32FC1); // Within class scatter.

		for(int j=0; j<Xi.cols; j++)
		{
			Mat xk_sub = Xi.col(j) - mu_i; 	
			Sw_mark = Sw_mark + (xk_sub * xk_sub.t());
		}
		
		Sw = Sw + Sw_mark;
	}

	//Mat Sr =  Sw.inv().mul(Sb);
	Mat Sr =  Sw.inv() * Sb;

	// The eigenvectors, called $W_{fld}=\{w_1, w_2, ... w_m\}$, in the paper by Belnumer et. al.
	// this matrix is a column vector of eigenvalues but OpenCV eigen() returns the eigenvectors 
	// as rows.
	//eigen(Sr, eigenvalues, eigenvectors);

	my_eigen(Sr, eigenvalues, eigenvectors);


/*
	for(int k=0; k < eigenvectors.cols; k++)
	{
		Mat vec = eigenvectors.row(k);
		normalize(vec, vec);
	}
*/

	if(flags & PRINT_DEBUG)
	{
		cout << EXWHERE <<  "Sw (rows,cols): " << Sw.rows << "," << Sw.cols << endl;
		//cout << EXWHERE <<  "Sw: " << Sw << endl;
		cout << EXWHERE <<  "Sb (rows,cols): " << Sb.rows << "," << Sb.cols << endl;
		//cout << EXWHERE <<  "Sb: " << Sb << endl;
		cout << EXWHERE <<  "Sr (rows,cols): " << Sr.rows << "," << Sr.cols << endl;
		//cout << EXWHERE <<  "Sr: " << Sr << endl;
		cout << EXWHERE <<  "eigenvectors (rows,cols): " << eigenvectors.rows << "," << eigenvectors.cols << endl;
		//cout << EXWHERE <<  "eigenvectors: " << eigenvectors << endl;
		cout << EXWHERE <<  "eigenvalues (rows,cols): " << eigenvalues.rows << "," << eigenvalues.cols << endl;
		//cout << EXWHERE <<  "eigenvalues: " << eigenvalues << endl;
	}

	// The upper bound on 'm' is c-1 so we drop all except those eigenvectors. 
	//this->eigenvectors = eigenvectors.rowRange(0,numComp);
	this->eigenvectors = eigenvectors.colRange(0,numComp);
	this->eigenvalues = eigenvalues.rowRange(0,numComp);

	cout << EXWHERE <<  "eigenvectors (rows,cols): " << eigenvectors.rows << "," << eigenvectors.cols << endl;
}

void LDA::my_eigen(Mat &source, Mat &eigenvals, Mat &eigenvecs)
{
	
	// Convert the opencv column matrix into an armadillo matrix.
	arma::cx_mat sourceArma(source.rows, source.cols);
	
	for(int i=0; i<source.rows; i++)
	{
		for(int j=0; j<source.cols; j++)
		{
			sourceArma.at(i,j) = source.at<float>(i,j);	
		}
	}

	// Obtain eigenvectors and eigenvalues.
	arma::cx_mat eigenvectorsArma;
	arma::cx_vec eigenvaluesArma;

	arma::eig_gen(eigenvaluesArma, eigenvectorsArma, sourceArma, 'r');

	// Convert the complex eigenvalue vector to a normal vector.
	arma::colvec eigenvaluesArmaReal(eigenvaluesArma.n_elem);

	for(unsigned int i=0; i < eigenvaluesArma.n_elem; i++)
	{
		eigenvaluesArmaReal.at(i) = eigenvaluesArma.at(i).real();
	}

	// Obtain index numbers the eigenvalues would have if they were sorted in desending order.
	arma::uvec index = sort_index(eigenvaluesArmaReal, 1);

	// Sort eigenvectors by largest eigenvalue in descending order.
	arma::cx_mat eigenvectorsArmaSorted(eigenvectorsArma.n_rows, eigenvectorsArma.n_cols);

	for(unsigned int i=0; i < eigenvaluesArma.n_elem; i++)
	{
		// If an eigenvalue had index N in the unsorted eigenvalues vector it gets index M in
		// the sorted one. Thus we take the column N which corresponds to that eigenvalue and 
		// make it into column M. This way we are guaranteed to retain the X largest components.
		eigenvectorsArmaSorted.col(index.at(i)) = eigenvectorsArma.col(i);
	}

	
	// Transfer the processed eigenvectors into an OpenCV matrix.
	eigenvecs = Mat::zeros((int)eigenvectorsArma.n_rows, (int)eigenvectorsArma.n_cols, CV_32FC1);

	for(unsigned int i=0; i<eigenvectorsArma.n_rows; i++)
	{
		for(unsigned int j=0; j<eigenvectorsArma.n_cols; j++)
		{
			eigenvecs.at<float>(i,j) = (float)eigenvectorsArmaSorted.at(i,j).real();
		}
	}

	// Because the openCV eigen function returned eigenvectors as rows and the rest of the code still expects it
	// we transpose the eigenvalue matrix.
	//eigenvecs = eigenvecs.t();


	// Sort the eigenvalues.
	arma::vec eigenvaluesArmaSorted = sort(eigenvaluesArmaReal, 1);

	// Convert the sorted eigenvalue vector into an OpenCV matrix.
	eigenvals = Mat::zeros((int)eigenvaluesArma.n_elem, 1, CV_32FC1);
	for(unsigned int i=0; i<eigenvaluesArma.n_elem; i++)
	{
		eigenvals.at<float>(i,0) = (float)eigenvaluesArmaSorted.at(i);
	}

}


Mat LDA::project(Mat X)
{
	return eigenvectors.t()*X;
}
