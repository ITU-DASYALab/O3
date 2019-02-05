/*
 * File name: Person.cpp
 * Date:			2011-07-27 15:34
 * Author:		Kristján Rúnarsson
 */

#include <iostream>
#include <string>
#include <sstream>
#include "Person.h"
#include "Face.h"
#include "MySQLite.h"

#define EXWHERE string(__PRETTY_FUNCTION__) 

Person::Person()
{
	this->realName = "Unknown";
	this->personSeqNum = -1; 
	this->persisted = false;
}

// Public constructor to create new unpersisted objects only.
Person::Person(string realName)
{
	this->realName = realName;
	this->personSeqNum = -1; 
	this->persisted = false;
}

Person::Person(int personSeqNum, string realName)
{
	this->realName = realName;
	this->personSeqNum = personSeqNum;
	this->persisted = true;
}

void Person::persist(){
	if(!persisted)
	{
		//cout << "person(" << realName << "):insert" << endl;
		insert();
	}
	else
	{
		//cout << "person:(" << realName << ")update" << endl;
		update();
	}
}

void Person::insert()
{
	MySQLite db;

	db.beginTransaction();

	try{
		personSeqNum = db.getCurrentId("person", "personSeqNum")+1;

		stringstream insert;
		insert << "INSERT INTO person (personSeqNum, realName) VALUES (";
		insert << personSeqNum << ","; 
		insert << "'" << realName << "')";

		db.getTable(insert.str());

		persistFaces();
	}
	catch(runtime_error e)
	{
		db.rollbackTransaction();
		stringstream msg;
		msg << EXWHERE << "Unable to insert data for '" << realName << "', cause: " << endl;
		msg << e.what();
		throw runtime_error(msg.str());
	}

	db.commitTransaction();

	persisted = true;
}

void Person::update()
{
	MySQLite db;

	db.beginTransaction();

	try{
		stringstream update;
		update << "UPDATE person SET ";
		update << "realName = '" << realName << "' ";
		update << "WHERE " ;
		update << "personSeqNum = " << personSeqNum << " "; 
		
		//cout << update.str() << endl;

		db.getTable(update.str());

		persistFaces();
	}
	catch(runtime_error e)
	{
		db.rollbackTransaction();
		stringstream msg;
		msg << EXWHERE << "Unable to update data for '" << realName << "', cause: " << endl;
		msg << e.what();
		throw runtime_error(msg.str());
	}

	db.commitTransaction();

	persisted = true;
}

void Person::persistFaces()
{
	for(unsigned int i=0; i<faces.size(); i++)
	{
		faces[i].setPersonSeqNum(this->personSeqNum);

		if(!faces[i].isPersisted())
		{
			faces[i].insertNoTrans();
		}
		else
		{
			faces[i].updateNoTrans();
		}
	}
}

void Person::addFace(Face &face)
{
	face.setPersonSeqNum(this->personSeqNum);
	faces.push_back(face);
}

void Person::removeFace(Face &face)
{
	for(unsigned int i=0; i<faces.size(); i++)
	{
		if(faces[i].getFaceSeqNum()==face.getFaceSeqNum())
		{
			faces.erase(faces.begin()+i);
			break;
		}
	}
}

string Person::getRealName()
{
	return realName;
}

void Person::setRealName(string realName)
{
	this->realName = realName;
}

int Person::getPersonSeqNum()
{
	return personSeqNum;
}

bool Person::isUnknown()
{
	return realName.compare("Unknown") == 0;
}

vector<Face> &Person::getFaces()
{
	return faces;
}

void Person::setFaces(vector<Face> faces)
{
	this->faces = faces;
}

Person Person::personFromSeq(int personSeqNum)
{
	MySQLite db;
	stringstream select;
	select << "SELECT realName,personSeqNum FROM person WHERE personSeqNum=" << personSeqNum;

	char** table = db.getTable(select.str());

	if(db.noOfRows() != 2){
		stringstream msg;
		msg << "No person with the sequence number '" << personSeqNum << "' exists in the database.";
		throw runtime_error(msg.str());
	}

	Person p(personSeqNum, table[2]);

	p.setFaces(Face::facesForPersonSeqNum(personSeqNum));

	return p;
}

Person Person::personByRealName(string realName)
{
	MySQLite db;
	stringstream select;
	select << "SELECT realName,personSeqNum FROM person WHERE realName='" << realName << "'";

	char** table = db.getTable(select.str());

	if(db.noOfRows() != 2){
		stringstream msg;
		msg << "No person with the name '" << realName << "' exists in the database.";
		throw runtime_error(msg.str());
	}

	int personSeqNum = atoi(table[3]);
	Person p(personSeqNum, realName);

	p.setFaces(Face::facesForPersonSeqNum(personSeqNum));

	return p;
}

 bool Person::exists(string realName)
 {
	MySQLite db;
	stringstream select;
	select << "SELECT realName,personSeqNum FROM person WHERE realName='" << realName << "'";

	/*char** table =*/ db.getTable(select.str());

	if(db.noOfRows() > 1){
		return true;
	}

	return false;
}


/* The OpenCV PCA analyzer takes a matrix of vectors as one of it's constructor
 * parameters. This matrix contains as many columns as there are training images
 * while the number of rows is: trImage.rows*trImage.cols. This function retrievs.
 * all face recognition images designated as training images form the database and
 * arranges them into such a matrix as descibed above. It also sets a vector of 
 * strings that maps column numbers in the training face matrix to real names.
 */
void Person::trainingFaceLists(vector<string> &realNames, Mat &trainingFaces)
{
	MySQLite db;

	stringstream select;
	select << "SELECT p.realName, f.recImagePath FROM person p, face f ";
	select << "WHERE p.personSeqNum=f.personSeqNum AND training=1";

	//cout << select.str() << endl;

	char** table = db.getTable(select.str());

	if(db.noOfRows() <= 1){
		return;
	}

	int offset = db.noOfColumns();
	string tmpRealName = table[offset+0];
	string tmpTrImagePath = table[offset+1];

	Mat tmpTrImage=imread(tmpTrImagePath, CV_32FC1);

	// Calculate the length of an image after it has been rehaped into a vector.
	int trImageVectorSize = tmpTrImage.cols * tmpTrImage.rows;

	// Create the matrix that holds the training faces.
	trainingFaces=Mat(trImageVectorSize, db.noOfRows()-1, CV_32FC1);

	for(int i=1; i < db.noOfRows(); i++, offset += db.noOfColumns())
	{
		if(i < 1)
		{
			tmpRealName = table[offset+0];
			tmpTrImagePath = table[offset+1];
			tmpTrImage = imread(tmpTrImagePath, CV_LOAD_IMAGE_GRAYSCALE);
		}

		realNames.push_back(tmpRealName);

		// The PCA object requires the training images to be in float format.
		Mat tmpTrImageFloat;
		tmpTrImage.convertTo(tmpTrImageFloat, CV_32FC1);

		Mat tmpTrImgVector = trainingFaces.col(i-1);
		tmpTrImageFloat.reshape(1, trImageVectorSize).copyTo(trainingFaces);
	}
}

//----------------------

void Person::trainingNameAndFaceLists(vector<string> &names, vector<string> &paths)
{
	MySQLite db;

	stringstream select;
	select << "SELECT p.realName, f.recImagePath FROM person p, face f ";
	select << "WHERE p.personSeqNum=f.personSeqNum AND training=1";

	//cout << select.str() << endl;

	char** table = db.getTable(select.str());

	if(db.noOfRows() <= 1){
		return;
	}

	int offset = db.noOfColumns();
	string tmpRealName = table[offset+0];
	string tmpTrImagePath = table[offset+1];

	/*Mat tmpTrImage=*/imread(tmpTrImagePath, CV_32FC1);

	// Calculate the length of an image after it has been rehaped into a vector.
	//int trImageVectorSize = tmpTrImage.cols * tmpTrImage.rows;

	for(int i=1; i < db.noOfRows(); i++, offset += db.noOfColumns())
	{
		tmpRealName = table[offset+0];
		tmpTrImagePath = table[offset+1];

		names.push_back(tmpRealName);
		paths.push_back(tmpTrImagePath);
	}
}

//----------------------

void Person::deletePerson(Person &person)
{
	MySQLite db;

	stringstream del;
	del << "delete from person where personSeqNum=" << person.getPersonSeqNum();

	db.getTable(del.str());
}

int Person::getNameSeq()
{
	MySQLite db;

	db.beginTransaction();

	int newSeqNum = -1;
	try
	{
		stringstream select;
		select << "select * from personNameSeq;";
	
		char** result =  db.getTable(select.str());

		int oldSeqNum = atoi(result[1]);

		newSeqNum = oldSeqNum + 1;

		stringstream update;
		update << "UPDATE personNameSeq SET seqNum="<< newSeqNum << " WHERE seqNum=" << oldSeqNum ;

		//cout << update.str() << endl;
		db.getTable(update.str());
	}
	catch(runtime_error e)
	{
		db.rollbackTransaction();
		throw e;
	}

	db.commitTransaction();

	return newSeqNum;
}


