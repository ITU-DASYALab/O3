#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stdexcept>
#include "ImageList.h"
#include "../common/common.h"

using namespace std;
using namespace cv;

/*
ImageList::ImageList(ImageList &il){
	this->imageVector = il.imageVector;
	this->imageMatrix = il.imageMatrix.clone();
	this->uniqueSubjectNames = uniqueSubjectNames;
	this->allSubjectNames = allSubjectNames;
	this->imgVectorSize = il.imgVectorSize;
}

ImageList &ImageList::operator=(ImageList &il){
	this->imageVector = il.imageVector;
	this->imageMatrix = il.imageMatrix.clone();
	this->uniqueSubjectNames = uniqueSubjectNames;
	this->allSubjectNames = allSubjectNames;
	this->imgVectorSize = il.imgVectorSize;
	return *this;
}
*/

ImageList::ImageList(vector<string> names, vector<string> paths)
{

	if(names.empty() || paths.empty())
	{
		stringstream msg;
		msg << EXWHERE << endl << "The name and path lists cannot be emtpy" << endl; 
		cerr << msg << endl;
		throw runtime_error(msg.str());	
	}

	for(unsigned int i=0; i<names.size(); i++){
		RecImage ri;
		ri.path = paths[i];
		ri.subjectName = names[i];

		imageVector.push_back(ri);
	}

	for(unsigned int i=0; i<names.size(); i++)
	{
		imageVector[i].load();
	}

	imgVectorSize = imageVector[0].getData().cols * imageVector[0].getData().rows;

	extractSubjectNames();

	vectorToMatrix(imageVector,imageMatrix);
}

/* This constructor is intended for test cases only. It takes a vector of N class
 * names and a matrix with N columns where each column 'i' contains a recognition 
 * image corresponding to class (subject) name 'i' in the class names vector.  */
ImageList::ImageList(vector<string> names, Mat matrix)
{
	if(names.empty() || matrix.empty())
	{
		stringstream msg;
		msg << EXWHERE << endl << "The name and image matrix cannot be emtpy" << endl; 
		cerr << msg << endl;
		throw runtime_error(msg.str());	
	}

	for(int i=0; i<matrix.cols; i++){
		RecImage ri;
		ri.path = "/nopath";
		ri.subjectName = names[i];
		ri.data = matrix.col(i);
		imageVector.push_back(ri);
	}

	imgVectorSize = imageVector[0].getData().cols * imageVector[0].getData().rows;

	extractSubjectNames();

	ImageList::vectorToMatrix(imageVector,imageMatrix);
}

/* Reads a list of images from a CSV file an packages them into a
 * vector of RecImage objects. The CSV file should contain two columns:
 *
 *     <class/subjectname>;<path-to-image>
 */
ImageList::ImageList(const string fileName)
{
	std::ifstream file(fileName.c_str(), ifstream::in);

	if(!file) {
		stringstream msg;
		msg << EXWHERE << endl << "Unable to open file: " << fileName << endl;
		cerr << msg << endl;
		throw runtime_error(msg.str());
	}

	std::string line, path, trueSubjectID;
	while (std::getline(file, line)) {
		std::stringstream liness(line);
		std::getline(liness, trueSubjectID, ';');
		std::getline(liness, path);

		path.erase(std::remove(path.begin(), path.end(), '\r'), path.end());
		path.erase(std::remove(path.begin(), path.end(), '\n'), path.end());
		path.erase(std::remove(path.begin(), path.end(), ' '), path.end());

		
		RecImage img(path, trueSubjectID);

		imageVector.push_back(img);
	}

	for(std::vector<RecImage>::iterator it = imageVector.begin(); it != imageVector.end(); ++it)
	{
		it->load();
	}

	imgVectorSize = imageVector[0].getData().cols * imageVector[0].getData().rows;

	extractSubjectNames();

	vectorToMatrix(imageVector,imageMatrix);
}

/* Returns the full list of images listed in the CSV file as an OpenCV matrix.*/
Mat ImageList::getImages()
{
	return imageMatrix;
}

/* Get all images corresponding to a certain subject name as an OpenCV matrix. */ 
Mat ImageList::getImageMatrixForName(string name)
{
	vector<RecImage> iVec;

	for(std::vector<RecImage>::iterator it = imageVector.begin(); it != imageVector.end(); ++it)
	{
		if(it->getSubjectName().compare(name) == 0)
		{
			iVec.push_back(*it);
		}
	}

	Mat iMat;
	vectorToMatrix(iVec, iMat);
	return iMat;
}

/* Returns the list of all subject names, that is to say, the global subject name list
 * with duplicates. This list corresponds index number for index number with columns
 * in the training image matrix.*/
vector<string> ImageList::getAllSubjectNames(){
	return allSubjectNames;
}

/* Returns the list of unique subject names, that is to say, the global subject name list
 * with all duplicates removed. */
vector<string> ImageList::getUniqueSubjectNames(){
	return uniqueSubjectNames;
}

/* Extracts both the full and unique subject names list. The former is needed for mapping
 * columns in the image matrix to subject names. The latter is useful in the fisherfaces
 * traingin phase. */
void ImageList::extractSubjectNames(){
	
	for(std::vector<RecImage>::iterator it = imageVector.begin(); it != imageVector.end(); ++it)
	{
		uniqueSubjectNames.push_back(it->getSubjectName());
		allSubjectNames.push_back(it->getSubjectName());
	}

	sort(uniqueSubjectNames.begin(), uniqueSubjectNames.end());

	vector<string>::iterator newEnd = unique(uniqueSubjectNames.begin(), uniqueSubjectNames.end()); 

	uniqueSubjectNames.resize(distance(uniqueSubjectNames.begin(), newEnd));
}

unsigned int ImageList::size()
{
	return imageVector.size();
}

/* Given the index number of a recognition face this method will look up the subject name
 * corresponding to that recognition image in the list of all subject names. */
string ImageList::getSubjectNameByIndex(int index)
{
	return imageVector[index].getSubjectName();
}

/* Given the index number of a recognition face this method will look up the path
 * corresponding to a recognition image.*/
string ImageList::getPathByIndex(int index)
{
	return imageVector[index].getPath();
}

/* Given the index number of a recognition face this method will look return the 
 * corresponding raw recognition image.*/
Mat ImageList::getImageByIndex(int index)
{
	return imageVector[index].getData();
}


/* Given a name this method looks up the index of a subject in the list of unique
 * subject names. */
int ImageList::getUniqueIndexBySubjectName(string name)
{
	vector<string> names = getUniqueSubjectNames();

	vector<string>::iterator location = find(names.begin(), names.end(), name);
	return distance(names.begin(),location);
}

/* Utility function that converts a vector of RecImage objects into an OpenCV matrix.*/
void ImageList::vectorToMatrix(vector<RecImage> &imageVector, Mat &matrix)
{
	int imgVectorSize = imageVector[0].getData().cols * imageVector[0].getData().rows;

	Mat tmpMatrix = Mat(imgVectorSize, imageVector.size(), CV_32FC1);

	for(unsigned int i = 0; i < imageVector.size(); i++)
	{
		Mat recMatCol = tmpMatrix.col(i);
		Mat floatImage;
		imageVector[i].getData().convertTo(floatImage, CV_32FC1);
		floatImage.reshape(1, imgVectorSize).copyTo(recMatCol);
	}
	matrix = tmpMatrix.clone();
}

