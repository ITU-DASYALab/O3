/*
   File name: FaceRecTest.h
   Date:      2011-07-14 13:27
   Author:    Kristján Rúnarsson
*/

#ifndef __FACERECTEST_H__
#define __FACERECTEST_H__

#include "Recognizer.h"

void msgAlgorithm(string algorithm)
{
	cout << endl << "-------------------" << endl;
	cout << "Using " << algorithm << endl;
	cout << "-------------------" << endl;
}

void msgTestHeader(){
	cout << endl;
	cout << "Identification results for each subject test image:" << endl;
	cout << "---------------------------------------------------" << endl;
}

void msgTestResult(string subjectFaceImage, RecognizerResult res, string actualName, bool isCorrectlyRec)
{
	cout  << "File: " << subjectFaceImage << ", recognized ID: " << res.subjectName[0] << ", actual ID: " << actualName;

	if(isCorrectlyRec)
	{
		cout << " --> true";
	}
	else
	{
		cout << " --> false";
	}

	cout << ",   distance: " << res.distance<< endl;
}

void msgSummary(int numCorrect, int numIncorrect, int numTestFiles)
{
	cout << endl;
	cout << "Summary:" << endl;
	cout << "--------" << endl;
	cout << "True:    " << numCorrect << endl;
	cout << "False:  " << numIncorrect << endl;
	cout << "Correct: " << ((float)numCorrect/(float)numTestFiles)*100.0 << "%" << endl;
}

void msgSubjBySubj(vector<int> &corrPerId)
{
	cout << endl;
	cout << "Total correct identifications for each subject:" << endl;
	cout << "-----------------------------------------------" << endl;

	int tot=0;
	for(int i=0; i<40; i++)
	{
		cout << "Correct for subject s" << i+1 << ": " << corrPerId[i] << endl;
		tot += corrPerId[i];
	}

	cout << "-----------------------------------------------" << endl;
	cout << "Total: " << tot << endl;
	cout << "-----------------------------------------------" << endl;
}

#endif
