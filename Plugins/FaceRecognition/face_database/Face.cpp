/*
 * File name: Face.cpp
 * Date:		2011-07-27 15:34
 * Author:		Kristján Rúnarsson
 */

#include <iostream>
#include <string>
#include <sstream>
#include <cstdio>
#include <errno.h>
#include <unistd.h>
#include <stdexcept>

#include <sys/types.h>
#include <sys/stat.h>

#include "MySQLite.h"
#include "../../../ObjectCube/LayerShared/Parameters.h"

#include "Face.h"

#define EXWHERE string(__PRETTY_FUNCTION__) + " - "

using namespace ObjectCube;

Face::Face()
{
}

// Public constructor to create new unpersisted objects only.
Face::Face(string origImagePath, Point upperLeft, Point lowerRight, Mat recImage, int objectCubeID)
{
	
	MySQLite db;
	this->init(false, -1, origImagePath, upperLeft, lowerRight,recImage, objectCubeID);
}

// Private constructor for use in static methods when retrieving faces that are known to have been
// peristed already.
Face::Face(int faceSeqNum, string origImagePath, Point upperLeft, Point lowerRight, Mat recImage, int objectCubeID)
{
	this->init(true, faceSeqNum, origImagePath, upperLeft, lowerRight, recImage, objectCubeID);
}




void Face::init(bool persisted, int faceSeqNum, string origImagePath, Point upperLeft, Point lowerRight, Mat recImage, int objectCubeID)
{

	this->persisted = persisted;

	Parameters *params = Parameters::getParameters();

	//this->recImageRoot = "/Users/kristjanr/tmp/ObjectCube/face_rec_images"; // Root directory of recognition image library.
	this->recImageRoot = params->getValue("recImagePath");

	if (access(recImageRoot.c_str(), R_OK|W_OK|F_OK) != 0)
	{
		throw runtime_error( EXWHERE + "The directory " + recImageRoot + " is not accessible: " + strerror(errno));
	}

	this->recImage = recImage.clone();
	this->faceSeqNum = faceSeqNum; // Globally uniqe ID.
	this->personSeqNum = 0;  // FK that links persons to faces.
	this->origImagePath = origImagePath;
	this->upperLeft = upperLeft;
	this->lowerRight = lowerRight;

	this->confirmed = false;
	this->training = false;
	this->objectCubeID = objectCubeID;


	stringstream recPath;
	recPath << recImageRoot << "/seq_num_not_set.png";
	this->recImagePath = recPath.str();   // Path to the pre processed recognition image that corresponds to this face.
}

void Face::persist(){
	if(!persisted)
	{
		//cout << "face:insert" << endl;
		insert();
	}
	else
	{
		//cout << "face:update" << endl;
		update();
	}
}

void Face::insert()
{
	MySQLite db;

	db.beginTransaction();
	try{
		insertNoTrans();
	}
	catch(runtime_error e)
	{
		db.rollbackTransaction();

		stringstream msg;
		msg << EXWHERE << "Unable to insert face, cause: ";
		msg << e.what();
		throw runtime_error(msg.str());
	}

	db.commitTransaction();
}

void Face::insertNoTrans()
{

	MySQLite db;

	this->faceSeqNum = db.getCurrentId( "face", "faceSeqNum" )+1;

	stringstream recPath;
	recPath << recImageRoot << "/" << faceSeqNum << ".png";

	this->recImagePath = recPath.str();   // Path to the pre processed recognition image that corresponds to this face.
	//cout << "recImagePath=" << this->recImagePath << endl;

	stringstream insert;
	insert << "INSERT INTO face VALUES(";
	insert << faceSeqNum << ",";
	insert << personSeqNum << ",";
	insert << "'" << origImagePath << "',";
	insert << upperLeft.x << ",";
	insert << upperLeft.y << ",";
	insert << lowerRight.x << ",";
	insert << lowerRight.y << ",";
	insert << confirmed << ",";
	insert << training << ",";
	insert << "'" << recImagePath << "',";
	insert << objectCubeID;
    
    insert << "," << upperLeftX << "," << upperLeftY << "," << lowerRightX << "," << lowerRightY; 
    
    
    insert << ")";

	//cout << insert.str() << endl;

	db.getTable(insert.str());

	//  - If insert was successful write matrix to disk.
	if(db.getCurrentId("face", "faceSeqNum") != faceSeqNum){
		stringstream msg;
		msg << EXWHERE << "Unable to insert face, cause because insert failed.";
		throw runtime_error(msg.str());
	}

	imwrite(recImagePath, recImage);

	if (access(recImagePath.c_str(), R_OK|W_OK|F_OK) != 0)
	{
		stringstream msg;
		msg << EXWHERE << "Could not write the recognition file '" << recImagePath << "': " << strerror(errno);
		throw runtime_error(msg.str());
	}

	this->persisted = true;
}

void Face::update()
{
	MySQLite db;

	db.beginTransaction();
	try{
		updateNoTrans();
	}
	catch(runtime_error e)
	{
		db.rollbackTransaction();

		stringstream msg;
		msg << EXWHERE << "Unable to insert face, cause: ";
		msg << e.what();
		throw runtime_error(msg.str());
	}

	db.commitTransaction();
}

void Face::updateNoTrans()
{
	
	//cout << "face.updateNoTrans()" << endl;

	stringstream update;
	update << "UPDATE face SET ";
	update << "faceSeqNum = " << faceSeqNum << ", ";
	update << "personSeqNum = " << personSeqNum << ", "; 
	update << "origImagePath = '" << origImagePath << "', ";
	update << "uLeftX = " << upperLeft.x << ", ";
	update << "uLeftY = " << upperLeft.y << ", ";
	update << "lRightX = " << lowerRight.x << ", ";
	update << "lRightY = " << lowerRight.y << ", ";
	update << "confirmed = " << confirmed << ", ";
	update << "training = " << training << ", ";
	update << "recImagePath = '" << recImagePath << "', ";
	update << "objectCubeID = " << objectCubeID << ", ";
    
    update << "upper_left_x = '" << upperLeftX << "', ";
    update << "upper_left_y = '" << upperLeftY << "', ";
    update << "lower_right_x = '" << lowerRightX << "', ";
    update << "lower_right_y = '" << lowerRightY << "', ";
    
	update << "WHERE " ;
	update << "faceSeqNum = " << faceSeqNum << ";";

	//cout << update.str() << endl;

	MySQLite db;

	try{
		db.getTable(update.str());
	}
	catch(runtime_error e)
	{
		stringstream msg;
		msg << "Unable to update face, cause: ";
		msg << e.what();
		throw runtime_error(msg.str());
	}
}

bool Face::isPersisted()
{
	return persisted;
}


void Face::setUpperLeft(Point p)
{
	this->upperLeft = p;
}

Point Face::getUpperLeft()
{
	return upperLeft;
}

void Face::setLowerRight(Point p)
{
	this->lowerRight = p;
}

Point Face::getLowerRight()
{
	return lowerRight;
}

int Face::getFaceSeqNum()
{
	return faceSeqNum;
}

int Face::getPersonSeqNum()
{
	return personSeqNum;
}

void Face::setPersonSeqNum(int personSeqNum)
{
	this->personSeqNum = personSeqNum;
}

string Face::getOrigImgName()
{
	return origImagePath;
}

void Face::setOrigImgName(string origImagePath)
{
	this->origImagePath = origImagePath;
}

string Face::getRecImgPath()
{
	return this->recImagePath;
}

void Face::setRecImgPath(string recImagePath)
{
	this->recImagePath = recImagePath;
}

void Face::setConfirmed(bool b)
{
	confirmed = b;
}

void Face::setTraining(bool b)
{
	training = b;
}

void Face::setObjectCubeID(int id)
{
	this->objectCubeID = id;
}

int Face::getObjectCubeID()
{
	return objectCubeID;
}

bool Face::isConfirmed()
{
	return confirmed;
}

bool Face::isTraining()
{
	return training;
}

void Face::deleteByNameAndRoi(string recPath, int objectId, Coordinate2D upperLeft, Coordinate2D lowerRight)
{
	//Face f = Face::faceByNameAndRoi(realName, upperLeft, lowerRight);
	Face f = faceByObjectIdAndRoi( objectId, upperLeft, lowerRight);


	// Let's be a bit paranoid!
	// ------------------------

	if(recPath.compare("") == 0){
		return;
	}

	if(f.getRecImgPath().compare("") == 0){
		return;
	}

	// Don't delete the root directory.
	if( (recPath.find_first_of("/") == 0) && (f.getRecImgPath().length() == 1 ) ) {
		return;
	}

	if ( f.getRecImgPath().find_last_of("png") != f.getRecImgPath().length() -1 ){
		return;
	}

	// Just in case the object contains garbage we check against the global
	// recognition image path.
	if (f.getRecImgPath().find_first_of(recPath) != 0)
	{
		return;
	}

	MySQLite db;

	stringstream del;
	del << "DELETE FROM face WHERE faceSeqNum=" << f.getFaceSeqNum();

	//cout << del.str() << endl;
	
	db.getTable(del.str());

	//cout << "I'll remove: " << f.getRecImgPath().c_str() << endl;
	remove(f.getRecImgPath().c_str());
}

//-----------------------------------
bool Face::exists(int objectId, Coordinate2D upperLeft, Coordinate2D lowerRight)
{
	MySQLite db;

	stringstream select;
	select << "SELECT f.faceSeqNum, f.personSeqNum, f.origImagePath, f.uLeftX, f.uLeftY," << 
		" f.lRightX, f.lRightY, f.confirmed, f.training, f.recImagePath, f.objectCubeID" <<
		" FROM face f WHERE " << 
		"f.objectCubeID=" << objectId <<
    " and f.upper_left_x = " << upperLeft.getX() << " and f.upper_left_y = " << upperLeft.getY() << 
    " and f.lower_right_x=" << lowerRight.getX() << " and f.lower_right_y=" << lowerRight.getY();
		//" and f.uLeftX = " << upperLeft.getX() << " and f.uLeftY = " << upperLeft.getY() << 
		//" and f.lRightX=" << lowerRight.getX() << " and f.lRightY=" << lowerRight.getY();

	//cout << select.str() << endl;

	/*char **table = */db.getTable(select.str());

	/*int lineOffset = */db.noOfColumns();


	if(db.noOfRows() > 1){
		return true;
	}

	return false;

}
//-----------------------------------

//-----------------------------------
Face Face::faceByObjectIdAndRoi(int objectId, Coordinate2D upperLeft, Coordinate2D lowerRight)
{
	MySQLite db;

	stringstream select;
	select << "SELECT f.faceSeqNum, f.personSeqNum, f.origImagePath, f.uLeftX, f.uLeftY," << 
		" f.lRightX, f.lRightY, f.confirmed, f.training, f.recImagePath, f.objectCubeID, f.upper_left_x, f.upper_left_y, f.lower_right_x, f.lower_right_y" <<
		" FROM face f WHERE " << 
		"f.objectCubeID=" << objectId <<
    " and f.upper_left_x = " << upperLeft.getX() << " and f.upper_left_y = " << upperLeft.getY() << 
    " and f.lower_right_x=" << lowerRight.getX() << " and f.lower_right_y=" << lowerRight.getY();
	//	" and f.uLeftX = " << upperLeft.getX() << " and f.uLeftY = " << upperLeft.getY() << 
	//	" and f.lRightX=" << lowerRight.getX() << " and f.lRightY=" << lowerRight.getY();

	//cout << select.str() << endl;

	char **table = db.getTable(select.str());

	int lineOffset = db.noOfColumns();


	if(db.noOfRows() < 2){
		stringstream msg;
		msg << "Face not found for: objectId=" << objectId << ", boundingBox=(" <<
		upperLeft.getX() <<  "," << upperLeft.getY() << "," << 
		lowerRight.getX() << "," << lowerRight.getY() << ")"; 

		throw runtime_error(msg.str());
	}

	int faceSeqNum = atoi(table[0+lineOffset]);
	//cout << "faceSeqNum: " << table[0+lineOffset] << endl;

	int personSeqNum = atoi(table[1+lineOffset]);
	//cout << "personSeqNum: " << table[1+lineOffset] << endl;

	string origImagePath = table[2+lineOffset];
	//cout << "origImagePath: " << table[2+lineOffset] << endl;

	Point uLeftPoint(atoi(table[3+lineOffset]), atoi(table[4+lineOffset]));
	//cout << "upperLeft: " << table[3+lineOffset] << endl;

	Point lRightPoint(atoi(table[5+lineOffset]), atoi(table[6+lineOffset]));
	//cout << "lowerRight: " << table[5+lineOffset] << endl;

	bool confirmed = (bool) atoi(table[7+lineOffset]);
	//cout << "confirmed: " << table[7+lineOffset] << endl;

	bool training = (bool) atoi(table[8+lineOffset]);
	//cout << "training: " << table[8+lineOffset] << endl;

	string recImagePath = table[9+lineOffset];
	//cout << "recImagePath: " << table[9+lineOffset] << endl;

	int objectCubeID = atoi(table[10+lineOffset]);
	//cout << "personSeqNum: " << table[1+lineOffset] << endl;

	Mat recImage = imread(recImagePath);

	if(recImage.empty())
	{
		stringstream msg;
		msg << "Unable to load recogntion image for image: " << recImagePath;
		throw runtime_error(msg.str());
	}


	Face f(faceSeqNum, origImagePath, uLeftPoint, lRightPoint, recImage, objectCubeID);
	f.setConfirmed(confirmed);
	f.setTraining(training);
	f.setPersonSeqNum(personSeqNum);
	f.setRecImgPath(recImagePath);
    
    f.upperLeftX = atoi(table[lineOffset + 11]);
    f.upperLeftY = atoi(table[lineOffset + 12]);
    f.lowerRightX = atoi(table[lineOffset + 13]);
    f.lowerRightY = atoi(table[lineOffset + 14]);
		
	return f;
}

//-----------------------------------

vector<Face> Face::facesForPersonSeqNum(int personSeqNum)
{
	MySQLite db;

	vector<Face> faces;

	stringstream select;
	select << "SELECT * FROM face WHERE personSeqNum=" <<  personSeqNum;

	char **table = db.getTable(select.str());

	if(db.noOfRows() < 2){
		stringstream msg;
		msg << "Faces not found for: personSeqNum=" << personSeqNum;

		throw runtime_error(msg.str());
	}

	int lineOffset = db.noOfColumns();
	for(int i=1; i<db.noOfRows(); i++, lineOffset += db.noOfColumns()){

		int faceSeqNum = atoi(table[0+lineOffset]);
		//cout << "faceSeqNum: " << table[0+lineOffset] << endl;

		int personSeqNum = atoi(table[1+lineOffset]);
		//cout << "personSeqNum: " << table[1+lineOffset] << endl;

		string origImagePath = table[2+lineOffset];
		//cout << "origImagePath: " << table[2+lineOffset] << endl;

		Point upperLeft(atoi(table[3+lineOffset]), atoi(table[4+lineOffset]));
		//cout << "upperLeft: " << table[3+lineOffset] << endl;

		Point lowerRight(atoi(table[5+lineOffset]), atoi(table[6+lineOffset]));
		//cout << "lowerRight: " << table[5+lineOffset] << endl;

		bool confirmed = (bool) atoi(table[7+lineOffset]);
		//cout << "confirmed: " << table[7+lineOffset] << endl;

		bool training = (bool) atoi(table[8+lineOffset]);
		//cout << "training: " << table[8+lineOffset] << endl;

		string recImagePath = table[9+lineOffset];
		//cout << "recImagePath: " << table[9+lineOffset] << endl;
		
		int objectCubeID = atoi(table[10+lineOffset]);
		//cout << "personSeqNum: " << table[1+lineOffset] << endl;

		//cout << "----" << endl;

		Mat recImage = imread(recImagePath);

		if(recImage.empty())
		{
			stringstream msg;
			msg << "Unable to load recogntion image for image: " << recImagePath;
			throw runtime_error(msg.str());
		}
	
		Face f(faceSeqNum, origImagePath, upperLeft, lowerRight, recImage, objectCubeID);
		f.setConfirmed(confirmed);
		f.setTraining(training);
		f.setPersonSeqNum(personSeqNum);
		f.setRecImgPath(recImagePath);
        
        f.upperLeftX = atoi(table[lineOffset + 11]);
        f.upperLeftY = atoi(table[lineOffset + 12]);
        f.lowerRightX = atoi(table[lineOffset + 13]);
        f.lowerRightY = atoi(table[lineOffset + 14]);

		
		faces.push_back(f);
	}

	return faces;
}

/*
Face Face::faceFromFaceSeqNum(int faceSeqNum)
{
}

Face Face::faceFromRoi(string origImagePath, Point upperLeft, Point lowerRight)
{
}
*/
