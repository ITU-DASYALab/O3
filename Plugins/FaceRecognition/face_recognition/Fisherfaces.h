#ifndef __FISHERFACES_H__
#define __FISHERFACES_H__

#include <iostream>
#include <vector>
#include <float.h>
#include <opencv2/opencv.hpp>

#include "ImageList.h"
#include "RecImage.h"
#include "LDA.h";

#include "../common/common.h"
#include "Recognizer.h"

using namespace std;
using namespace cv;

class Fisherfaces: public Recognizer {
private:
	PCA pca;
	LDA lda;
	int flags;
	//ImageList X;
	vector<Mat> pcaProjTrFaces;
	vector<Mat> ldaProjTrFaces;
	Mat eigenvectors;

public:
	Fisherfaces(){};
	Fisherfaces(ImageList X, int flags=0);
	~Fisherfaces();
	void init(ImageList X, int flags);
	Mat project(Mat &m);
	vector<RecognizerResult> recognize(const Mat& instance);
	Mat getEigenvectors();
	Mat getEigenvalues();
};

#endif
