#ifndef __FACE_H__
#define __FACE_H__


#include <opencv2/opencv.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
#include "../../../ObjectCube/Boundaries/Coordinate2D.h"

using namespace std;
using namespace cv;
using namespace ObjectCube;

class Face {

	friend class Person;

	private:
		
		bool persisted;

		Mat recImage;
		Point upperLeft,lowerRight;
		int faceSeqNum, personSeqNum, objectCubeID;
		string recImageRoot, origImagePath, recImagePath;
		bool confirmed, training;

		Face(int faceSeqNum, string origImagePath, Point upperLeft, Point lowerRight, Mat recImage, int objectCubeID);
		void init(bool persisted, int faceSeqNum, string origImagePath, Point upperLeft, Point lowerRight, Mat recImage, int objectCubeID);

		void insert();
		void insertNoTrans();
		void update();
		void updateNoTrans();

	public:
    
    double upperLeftX;
    double upperLeftY;
    double lowerRightX;
    double lowerRightY;
		
		Face();
		Face(string origImagePath, Point upperLeft, Point lowerRight, Mat recImage, int objectCubeID);

		void persist();
		bool isPersisted();

		void setUpperLeft(Point p);
		Point getUpperLeft();

		void setLowerRight(Point p);
		Point getLowerRight();

		int getFaceSeqNum();
		int getPersonSeqNum();

		void setPersonSeqNum(int personSeqNum);
		string getOrigImgName();

		void setOrigImgName(string origImageName);
		string getRecImgPath();

		void setRecImgPath(string recImagePath);

		void setConfirmed(bool b);
		void setTraining(bool b);

		void setObjectCubeID(int id);
		int getObjectCubeID();

		bool isConfirmed();
		bool isTraining();

		static void deleteByNameAndRoi(string recPath, int objectId, Coordinate2D upperLeft, Coordinate2D lowerRight);

		static bool exists(int objectId, Coordinate2D upperLeft, Coordinate2D lowerRight);
		static Face faceByObjectIdAndRoi(int objectId, Coordinate2D upperLeft, Coordinate2D lowerRight);

		static vector<Face> facesForPersonSeqNum(int personSeqNum);
};

#endif
