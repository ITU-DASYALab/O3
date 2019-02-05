#ifndef __RECOGNISER_H__
#define __RECOGNISER_H__

#include "ImageList.h"
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

struct RecognizerResult {
	string subjectName;
	double distance;
};

class Recognizer {
	private:

	protected:
		ImageList imageList;

	public:
		virtual vector<RecognizerResult> recognize(const Mat& unknown)=0;  

		vector<RecognizerResult> nearestNeighbor(const vector<Mat> &projTrFaces, const Mat &unkProjected, unsigned int retain=5);
};


#endif
