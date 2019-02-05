#ifndef __RECIMAGE_H__
#define __RECIMAGE_H__

#include <opencv2/opencv.hpp>

#include <string>
using namespace std;
using namespace cv;

class ImageList;

class RecImage{

	private:
		string path;
		string subjectName;
		Mat data;

		void load();

	public:
		//RecImage(const RecImage &r);
		//RecImage &operator=(const RecImage &r);
		RecImage(){};
		RecImage(const string path, const string subjectName);
		string getPath();
		Mat getData();
		string getSubjectName();

	friend class ImageList;

};

#endif
