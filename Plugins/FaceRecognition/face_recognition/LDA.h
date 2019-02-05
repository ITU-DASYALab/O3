#ifndef __LDA_H__
#define __LDA_H__

#include <cv.h>
#include <highgui.h>
#include <float.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <armadillo>

#include "ImageList.h"

using namespace cv;

class LDA
{
	private:
		int flags;

		void init(ImageList imageList, int flags);
		void my_eigen(Mat &source, Mat &eigenvals, Mat &eigenvecs);

	public:
		Mat eigenvectors;
		Mat eigenvalues;

		LDA(){};
		LDA(ImageList imageList, int flags=0);
		Mat project(Mat X);
};

#endif
