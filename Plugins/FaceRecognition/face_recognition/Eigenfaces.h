#ifndef __EIGENFACES_H__
#define __EIGENFACES_H__

#include <iostream>
#include <vector>
#include <float.h>
#include <opencv2/opencv.hpp>

#include "ImageList.h"
#include "RecImage.h"

#include "../common/common.h"
#include "Recognizer.h"

using namespace std;
using namespace cv;

class Eigenfaces: public Recognizer {
private:
	int flags;
	PCA *pca;
	Mat trFaces;
	vector<Mat> projTrFaces;

public:
	Eigenfaces(){};
	Eigenfaces(ImageList &imageList, int components, int flags=0);
	virtual ~Eigenfaces();
	void init(ImageList &imageList, int components, int flags);
	vector<RecognizerResult> recognize(const Mat& instance);
	Mat getAverage();
	Mat getEigenvectors();
	Mat getEigenvalues();
};

#endif
