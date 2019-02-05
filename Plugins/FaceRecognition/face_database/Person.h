/*
   File name: Person.h
   Date:      2011-07-27 15:35
   Author:    Kristján Rúnarsson
*/

#ifndef __PERSON_H__
#define __PERSON_H__

#include <stdexcept>
#include <iostream>
#include <vector>
#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>

class Face;

using namespace std;
using namespace cv;

class Person {

	private:

		bool persisted;

		int personSeqNum;
		string realName;

		Mat trainingFaces;
		string faceRecImgDir;

		vector<Face> faces;

		Person(int personSeqNum, string realName);
 
		void insert();
		void update();

		void persistFaces();

	public:
		Person();
		Person(string realName);

		void persist();

		void addFace(Face &face);
		void removeFace(Face &face);

		string getRealName();
		void setRealName(string realName);
		int getPersonSeqNum();
		vector<Face> &getFaces();
		void setFaces(vector<Face> faces);

		bool isUnknown();

		static Person personFromSeq(int personSeqNum);
		static Person personByRealName(string realName);

		static bool exists(string realName);

		static void deletePerson(Person &person);
		static void trainingFaceLists(vector<string> &realNames, Mat &trainingFaces);
		static void trainingNameAndFaceLists(vector<string> &names, vector<string> &paths);
		static int getNameSeq();
};

#endif
