#include <cv.h>
#include <highgui.h>
#include <float.h>

#include <iostream>
#include <string>

#include "LDA.h"

using namespace cv;


int main(int argc, char *argv[]) {
	Mat X(11, 2, CV_32FC1);

	//X = np.array([[2,3],[3,4],[4,5],[5,6],[5,7],[2,1],[3, 2],[4 ,2],[4 ,3],[6, 4],[7,6]]).T
	X.at<float>(0,0) = 2; 
	X.at<float>(0,1) = 3;

	X.at<float>(1,0) = 3;
	X.at<float>(1,1) = 4;

	X.at<float>(2,0) = 4;
	X.at<float>(2,1) = 5;

	X.at<float>(3,0) = 5;
	X.at<float>(3,1) = 6;

	X.at<float>(4,0) = 5;
	X.at<float>(4,1) = 7;

	X.at<float>(5,0) = 2;
	X.at<float>(5,1) = 1;

	X.at<float>(6,0) = 3;
	X.at<float>(6,1) = 2;

	X.at<float>(7,0) = 4;
	X.at<float>(7,1) = 2;

	X.at<float>(8,0) = 4;
	X.at<float>(8,1) = 3;

	X.at<float>(9,0) = 6;
	X.at<float>(9,1) = 4;

	X.at<float>(10,0) = 7;
	X.at<float>(10,1) = 6;


	cout << X << endl;

	Mat XT(2, 11, CV_32FC1);

	transpose(X,XT);
	cout << XT << endl;
	cout << "XT.cols=" << XT.cols << " XT.rows=" << XT.rows << endl;

	//y = np.array([ 0,0,0,0,0,1,1,1,1,1,1])
	Mat y(1, 11, CV_32FC1);
	y.at<float>(0,0) = 0;
	y.at<float>(0,1) = 0;
	y.at<float>(0,2) = 0;
	y.at<float>(0,3) = 1;
	y.at<float>(0,4) = 1;
	y.at<float>(0,5) = 1;
	y.at<float>(0,6) = 2;
	y.at<float>(0,7) = 2;
	y.at<float>(0,8) = 2;
	y.at<float>(0,9) = 2;
	y.at<float>(0,10) = 2;

	cout << y << endl;

	cout << endl;
	
	PCA pca(XT, Mat(), CV_PCA_DATA_AS_COL, XT.rows-1);

	cout << "PCA eigenvalues:" << endl;
	cout << pca.eigenvalues << endl;

	cout << "PCA eigenvectors:" << endl;
	cout << pca.eigenvectors << endl;

	cout << endl;

	LDA lda(XT,y, 3);

	cout << "LCA eigenvalues:" << endl;
	cout << lda.getEigenvalues() << endl;

	cout << "LCA eigenvectors:" << endl;
	cout << lda.getEigenvectors() << endl;

}
