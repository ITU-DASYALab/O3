#ifndef __IMAGELIST_H__
#define __IMAGELIST_H__

#include <opencv2/opencv.hpp>

#include <string>

#include "ImageList.h"
#include "RecImage.h"

// Test lists consist of the subject ID of the person of whom a face image is and the
// path to that image.
class ImageList
{
	private:
		vector<RecImage> imageVector;
		Mat imageMatrix;
		vector<string> uniqueSubjectNames, allSubjectNames;
		int imgVectorSize;
		void extractSubjectNames();

	public:
		//ImageList(ImageList &il);
		//ImageList &operator=(ImageList &il);
		ImageList(){};
		ImageList(vector<string> names, vector<string> paths);
		ImageList(vector<string> names, Mat images);
		ImageList(const string fileName );
		Mat getImages();
		Mat getImageMatrixForName(string name);
		vector<string> getAllSubjectNames();
		vector<string> getUniqueSubjectNames();
		string getSubjectNameByIndex(int index);
		string getPathByIndex(int index);
		Mat getImageByIndex(int index);
		int getUniqueIndexBySubjectName(string name);
		unsigned int size();
		void vectorToMatrix(vector<RecImage> &imageVector, Mat &matrix);
};

#endif
