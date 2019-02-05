/*
 * File name: face_detector.cpp
 * Date:      2011-06-18 13:53
 * Author:    Kristján Rúnarsson
 */
/**
 * Display video from webcam and detect faces
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
//#include <opencv2/imgproc/imgproc.hpp>
//#include <opencv2/imgproc/imgproc_c.h>
//#include <opencv2/objdetect/objdetect.hpp>
//#include <opencv2/highgui/highgui.hpp>

#include <opencv2/opencv.hpp>

#include <iostream>
#include <sstream>
 
using namespace cv;
using namespace std;

// Constructor flags
#define SAVE_ROI		1 // Debugging, Save the region of interest clips to disk.
#define TIME_DETECTION	2 // Debugging, Time the execution of eye and face cascades.


// Face extraction flags
#define NO_MASK 1
#define NO_ROTATION 2
#define NO_NORMALIZATION 4
#define MARK_OPTIMAL_NASAL 8

/* Member variables:
 *
 *   scaleFactor  - Specifies how much the image size is reduced at each image scale.
 *   minNeighbors - Speficifes how many neighbors should each candiate rectangle have i
 *                  to retain it.
 *   flags        - This parameter is not used for new cascade and have the same meaning for old 
 *                  cascade as in function cvHaarDetectObjects. Here *old* haar classifier was
 *                  trained by the haartraining application whereas a *new* cascade classifier 
 *                  was trained by the traincascade application.
 *   minWidth     - The minimum possible object width. Objects smaller than that are ignored.
 *   minHeight    - The minimum possible object height. Objects smaller than that are ignored.
 */
 
#include "RegionOfInterest.h"

struct CascadeParams {
	float scaleFactor;
	float minNeighbors;
	int flags;
	float minWidth;
	int minHeight;
};

struct MaskParams {
	double optNasalRootPos;
	Scalar color;

	MaskParams(){
		optNasalRootPos = 0.4;
		//color = CV_RGB(255,165,0);
		//color = CV_RGB(255, 165, 0);
		color = CV_RGB(190, 190, 190);
	}
};

class FaceDetector{
	private:
		CascadeClassifier casFaceFrontal, casLeftEye, casRightEye;
		CascadeParams eyeCasPars, faceFrontCasPars;
		int haarFlags, flags;
		double faceTime, eyeTime;
		Mat *originalImage; 
		Mat scaledSearchImage;
		float upScale, downScale;
		float eyeRoiPropUpperBound, eyeRoiPropLowerBound, eyeRoiPropWidth;
		
		void setEyeSearchRois(Rect &leftRoi, Rect &rightRoi, Rect face);

		void getSaveName(const char *prefix, int index, const char* fileType, string &destination);
		
		void detect(CascadeClassifier &cascade, Mat &image, vector<Rect> &resRois, 
			CascadeParams casPars);

	public:

		FaceDetector(string trFileFace, string trFileRightEye, string trFileLeftEye);
		void setScale(int scale);
		void setFlags(int flags);
		void detectFaces(Mat &originalImage, RegionOfInterest &faceList);
		
		void markFaces(Mat &image, RegionOfInterest &root, CvScalar color);
		void detectEyes(Mat &originalImage, RegionOfInterest &faceList);
		void markEyes(Mat &originalImage, RegionOfInterest &root, CvScalar leftColor, CvScalar rightColor);

		double getFaceTime();
		double getEyeTime();
	
		static void extractFace(Mat &original, Mat& face, RegionOfInterest &roi, Size recSize, int flags=0, int interpolation = INTER_AREA);
		static void extractFace(Mat &original, Mat& face, RegionOfInterest &roi, Size recSize, MaskParams mp, int flags=0, int interpolation = INTER_AREA);

};
