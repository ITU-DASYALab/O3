#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <algorithm>

#include "RecImage.h"

/*
RecImage::RecImage(const RecImage &r)
{
	this->path=r.path;
	this->subjectName=r.subjectName;
	this->data=r.data.clone();
}

RecImage &RecImage::operator=(const RecImage &r)
{
	this->path=r.path;
	this->subjectName=r.subjectName;
	this->data=r.data.clone();
	return *this;
}
*/

RecImage::RecImage(const string path, const string subjectName)
{
	this->path=path;
	this->subjectName=subjectName;
}

/* Read the image from the filesystem into an OpenCV matrix.*/
void RecImage::load()
{
	data = imread(path, CV_LOAD_IMAGE_GRAYSCALE);
}

/* Returns the path to the original image in the file system. */
string RecImage::getPath()
{
	return path;
}

/* Returns the image unmodified as a OpenCV matrix.*/
Mat RecImage::getData()
{
	return data;
}

/* Reuturns the name corresponding with to the face in this image.*/
string RecImage::getSubjectName()
{
	return subjectName;
}
