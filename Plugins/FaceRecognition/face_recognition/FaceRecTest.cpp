#include <cv.h>
#include <highgui.h>

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

#include "Eigenfaces.h"
#include "Fisherfaces.h"
#include "FaceRecTest.h"
#include "../common/common.h"

using namespace std;
using namespace cv;

// Scale every value in a matrix so that it is in the 0-255 range. Thanks to
// the guys at stackoverflow for this one:
//
//     http://stackoverflow.com/questions/4974709/pca-svm-using-c-syntax-in-opencv-2-2
//
Mat toGrayscale(const Mat& mat) {
	Mat gMat(mat.rows, mat.cols, CV_8UC1);

	double min, max;
	minMaxLoc(mat, &min, &max);

	for(int row = 0; row < mat.rows; row++) {
		for(int col = 0; col < mat.cols; col++) {
			gMat.at<uchar>(row, col) = 255 * ((mat.at<float>(row, col) - min) / (max - min));
		}
	}

	return gMat;
}


void usage()
{
	cout << "eigenfacetest [-vs] [-t list of training images] [-r list of test images]" << endl;
	cout << " -v: Verbose mode." << endl;
	cout << " -f: Use fisherfaces, default is eigenfaces." << endl;
	cout << " -s: The projected face vectors can be retrieved and rendered" << endl;
	cout << "     as images. This option shows the average face and a " << endl;
	cout << "     few of the eigenfaces." << endl;
	cout << " -r: A list of test files with faces to try and recognize." << endl ;
	cout << " -t: A List of training files with faces to... well... train on." << endl;
	cout << " -h: This text." << endl;
	exit(1);
}

void unableToLoad()
{
	cerr << "Unable to load face images. The program expects a set of face images in a subdirectory" << endl;
	cerr << "of the execution directory named 'att_faces'. This face database can be freely downloaded " << endl; 
	cerr << "from the Cambridge University Copmputer Lab's website:" << endl;
	cerr << "     http://www.cl.cam.ac.uk/research/dtg/attarchive/facedatabase.html" << endl;
	exit(1);
}

int main(int argc, char *argv[]) {
	string trainingList = "./train_original.txt";
	string testList = "./test_original.txt";


	bool isVerbose=false, doShow=false, useFisher=false;
	char c;
	while ( (c = getopt(argc, argv, ":ast:r:vf")) != -1) {
		switch (c) {
			case 's':
				doShow = true;
				break;
			case 'v':
				isVerbose = true;
				break;
			case 'f':
				useFisher = true;
				break;
			case 'r':
				testList = optarg;
				break;
			case 't':
				trainingList = optarg;
				break;
			case 'h':
				usage();
				break;
			case '?':
				cout << "Invalid option: '-" << (char)optopt << "'" << endl;
				usage();
				break;
			case ':':
				cout << "Missing argument value for: '-" << (char)optopt << "'" << endl;
				usage();
				break;
			default:
				cerr << "getopt returned character code 0%o" << c << endl;
				usage();
		}
	}


	ImageList testImageList(testList);
	ImageList trainImageList(trainingList);

	cout << endl;
	cout << "There are " << trainImageList.size() << " training files and " << testImageList.size() << " test files." << endl;


	if(testImageList.size()<1 || trainImageList.size()<1)
	{
		unableToLoad();
	}


	// On instantiating the FaceRecognizer object automatically processes
	// the training images and projects them.

	
	Recognizer * rec;
	if(useFisher)
	{
		msgAlgorithm("Fisherfaces");
		rec = new Fisherfaces(trainImageList, PRINT_DEBUG);
	}
	else
	{
		int n = trainImageList.size();
		int c = trainImageList.getUniqueSubjectNames().size();
		msgAlgorithm("Eigenfaces");

		rec = new Eigenfaces(trainImageList, n-c);

		//rec = new Eigenfaces(trainImageList, 0);
	}


	if(isVerbose){
		msgTestHeader();
	}


	// This vector keeps track of how many times each face is correctly recognized
	// The index numbers stand for the ID number of a subject in the test set.
	vector<int> corrPerId;
	for(int i=0; i<40; i++)
	{
		corrPerId.push_back(0);
	}

	int correct=0, incorrect=0;
	for(unsigned int i=0; i<testImageList.size(); i++)
	{
		// Look up the true subject ID of the current test subject.
		Mat currentUnknownImage = testImageList.getImages().col(i);

		// Compare a face from the list of test faces with the set of training faces stored in
		// the recognizer and try to find the closest match.
		//string recAs = foo.recognize(currentUnknownImage);

		vector<RecognizerResult> recAs;

		recAs = rec->recognize(currentUnknownImage);

		// The recognizer returns the subject ID of the subject he thinks this is. If a subject is correctly 
		// recognized the subject ID returned by the recognizer should be the same as the subject ID from the 
		// test file so we must look up the ID from the test file.
		bool isCorrectlyRec;
		if(recAs[0].subjectName.compare(testImageList.getSubjectNameByIndex(i))==0)
		{
			isCorrectlyRec = true;
			correct++; // Track total correct recognitions for all subjects.
			corrPerId[testImageList.getUniqueIndexBySubjectName(recAs[0].subjectName)]++; // Track total correct recognitions for this subject
		} 
		else
		{
			isCorrectlyRec = false;
			incorrect++; // Total false recognitions for all subjects.
		}

		
		if(isVerbose) {
			string actualName = testImageList.getSubjectNameByIndex(i);
			string recognizedName = recAs[0].subjectName.c_str();
			string path = testImageList.getPathByIndex(i);
			msgTestResult(path, recAs[0], actualName, isCorrectlyRec);
		}

		if(isCorrectlyRec)
		{
			cout << recAs[0].distance << ",true" << endl;
		}
		else
		{
			cout << recAs[0].distance << ",false" << endl;
		}
	}

	if(isVerbose){
		msgSubjBySubj(corrPerId);
	}

	msgSummary(correct, incorrect, testImageList.size());

	delete rec;

}
