/*
 *  FaceRecognitionPlugin.cp
 *  FaceRecognitionPlugin
 *
 *  Created by Grímur Tómasson on 15.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cassert>
#include <exception>
#include <stdexcept>
#include <math.h>

#include "FaceRecognitionPlugin.h"
#include "face_database/Person.h"
#include "face_database/Face.h"


#include "../ObjectCube/Plugin/PluginServer.h"
#include "../ObjectCube/Plugin/PluginObject.h"
#include "../ObjectCube/LayerShared/Parameters.h"
#include "../ObjectCube/Utils/PathSearch.h"

#include <syslog.h>

#define EXPORT __attribute__((visibility("default")))

vector<string> split(const char* str,const char* delim);



FaceRecognitionPlugin::FaceRecognitionPlugin( const int id )
:	ProcessObjectPlugin( id )
{
	m_log = std::unique_ptr<Utils::Log>( new Utils::Log("oc_plugin_facerec.log") );
	m_log->writeEnter() << __PRETTY_FUNCTION__ << std::endl;

	try
	{
		Parameters *params = Parameters::getParameters();
	
		params->add("casFaceFrontalName", Utils::findFullPath("ObjectCube/plugin/FaceRecognition/haarcascade_frontalface_alt.xml"));
		params->add("casRightEyeName", Utils::findFullPath("ObjectCube/plugin/FaceRecognition/haarcascade_righteye_2splits.xml"));
		params->add("casLeftEyeName", Utils::findFullPath("ObjectCube/plugin/FaceRecognition/haarcascade_lefteye_2splits.xml"));
		params->add("recImagePath", Utils::findFullPath("ObjectCube/plugin/FaceRecognition/face_rec_images"));
		params->add("databasePath", Utils::findFullPath("ObjectCube/plugin/FaceRecognition/faceDatabase.sqlite"));
		faceDet = new FaceDetector(params->getValue("casFaceFrontalName"), params->getValue("casRightEyeName"), params->getValue("casLeftEyeName"));
	
		faceRec = NULL;
		
		this->train();

		m_log->writeInfo() << "Construction done" << std::endl;
	}
	catch(...)
	{
		m_log->writeError() << "Unknown error in FaceRecognitionPlugin constructor" << std::endl;
		throw;
	}
}

void FaceRecognitionPlugin::train()
{
	m_log->writeEnter() << __PRETTY_FUNCTION__ << std::endl;

	vector<string> trNames;
	vector<string> trImgPaths;

	// Gets names and recognition image paths from database.
	Person::trainingNameAndFaceLists(trNames, trImgPaths);

	if(trNames.size() < 2)
	{
		return;
	}
	
	ImageList trainingImageList(trNames, trImgPaths);

	delete faceRec;

	faceRec = new Eigenfaces(trainingImageList, 0); //, PRINT_DEBUG);
}

FaceRecognitionPlugin::~FaceRecognitionPlugin() 
{
/*
	delete(faceDet);
	delete(faceRec);
	//MySQLite::closeDB();
*/
}



//A neccessary part of all plugins
// See "ObjectCube Plug-in API" on google docs for details.

void FaceRecognitionPlugin::renameTag( const string& /*tagSetName*/, const string& /*oldTagName*/, const string& /*newTagName*/ ) {}
void FaceRecognitionPlugin::mergeTags(const string& /*tagSetName*/, const string& /*oldTagName*/, const string& /*newTagName*/ ) {}

void FaceRecognitionPlugin::confirmTagging( int /*objectId*/, const string& /*tagSetName*/, const BoundingBox& /*boundingBox*/, const string& /*tag*/ ) {}

void FaceRecognitionPlugin::confirmTagging( const PluginObject &object, const string& /*tagSetName*/, const BoundingBox& boundingBox, const string& tag )
{
	m_log->writeEnter() << __PRETTY_FUNCTION__ << std::endl;
	int objectId = object.getId();

	try 
	{
		// Does the face exist?
		if(!Face::exists(objectId, boundingBox.getUpperLeftCorner(), boundingBox.getLowerRightCorner()))
		{

			// If the face does not exist we process the incoming ROI.
			vector<BoundingBox> boundingBoxes;
			boundingBoxes.push_back(boundingBox);

			// Process assumes that the face does not already exist, it runs the face through the recognizer, which always returns some identity.
			// The face is then associated with that identity.
			PluginReply pluginReply = process( object, boundingBoxes );
		}

		Face incomingFace = Face::faceByObjectIdAndRoi(objectId,  boundingBox.getUpperLeftCorner(), boundingBox.getLowerRightCorner());

		// If the face does exist it must be associated with somebody, Who is it?

		Person currentPerson = Person::personFromSeq(incomingFace.getPersonSeqNum());

		Person incomingPerson;

		if(!Person::exists(tag))
		{

			m_log->writeInfo() << "Person with tag=" << tag << " does not exist. Creating new one ..." << std::endl;

			incomingPerson = Person(tag);
		}
		else
		{

			m_log->writeInfo() << "Person with tag=" << tag << " exists, retrieving ..." << std::endl;

			incomingPerson = Person::personByRealName(tag);
		}

		// This person is confirmed and becomes training face.
		incomingFace.setConfirmed(true);
		incomingFace.setTraining(true);

		// If the incoming person and the person currently associated with the face are the same
		// there is nothing more to do.
		if(currentPerson.getPersonSeqNum() == incomingPerson.getPersonSeqNum())
		{
			incomingFace.persist();
			this->train();
			return;
		}

		currentPerson.removeFace(incomingFace);

		// If the person this face was previously associated with has no more faces we
		// delete that person. Otherwise we save it's new status.
		if(currentPerson.getFaces().size()<=0)
		{
			Person::deletePerson(currentPerson);
		}
		else
		{
			currentPerson.persist();
		}

		incomingPerson.addFace(incomingFace);

		incomingPerson.persist();

		// Retrain the recognizer because we just promoted a face to training status.
		this->train();

	}
	catch(...)
	{
		m_log->writeError() << "Unknown error in FaceRecognitionPlugin::confirmTagging" << std::endl;
		throw;
	}
}



void FaceRecognitionPlugin::deleteTagging(int objectId, const string& /*tagSetName*/, const BoundingBox& boundingBox, const string& /*tag*/ )
{
	m_log->writeEnter() << __PRETTY_FUNCTION__ << std::endl;
	try 
	{
		Parameters *params = Parameters::getParameters();
		string recPath = params->getValue("recImagePath");

		Face face = Face::faceByObjectIdAndRoi(objectId,  boundingBox.getUpperLeftCorner(), boundingBox.getLowerRightCorner());
		Person p = Person::personFromSeq(face.getPersonSeqNum());

		Face::deleteByNameAndRoi(recPath, objectId, boundingBox.getUpperLeftCorner(), boundingBox.getLowerRightCorner());
		
		if(p.getFaces().size()<=1)
		{
			Person::deletePerson(p);
		}
	}
	catch(...)
	{
		m_log->writeError() << "Unknown error in FaceRecognitionPlugin::deleteTagging" << std::endl;
		throw;
	}
}



void FaceRecognitionPlugin::updateTagging(int /*objectId*/, const string& /*tagSetName*/, const BoundingBox& /*boundingBox*/, const string& /*oldTag*/, const string& /*newTag*/)
{
	m_log->writeEnter() << __PRETTY_FUNCTION__ << std::endl;
}



Mat FaceRecognitionPlugin::decodeImage(const char *imgBuffer, long imgByteSize)
{
	m_log->writeEnter() << __PRETTY_FUNCTION__ << std::endl;
	vector<char> data;

	for(long i=0; i<imgByteSize; i++)
	{
		data.push_back(imgBuffer[i]);
	}

	Mat imgRaw(data);

	return imdecode(imgRaw, CV_LOAD_IMAGE_COLOR);
}


string FaceRecognitionPlugin::newUnknownName()
{
	m_log->writeEnter() << __PRETTY_FUNCTION__ << std::endl;
	stringstream name;
	name << "Unknown" << Person::getNameSeq();
	return name.str();
}


void FaceRecognitionPlugin::processRoi(const PluginObject &object, Rect &faceRect, Mat &imgDecoded, RegionOfInterest &face, PluginReply &reply)
{
	m_log->writeEnter() << __PRETTY_FUNCTION__ << std::endl;
	//Rect faceRect = faces[i]->getAbsoluteRect();
	
	Mat processedFace;
	//FaceDetector::extractFace(imgDecoded, processedFace, *faces[i], Size(100,120));
	FaceDetector::extractFace(imgDecoded, processedFace, face, Size(100,120));

	vector<RecognizerResult> recRes;

	Person p;

	if(faceRec == NULL)
	{
		RecognizerResult r;
		r.subjectName = newUnknownName();	
		r.distance = 1;
		recRes.push_back(r);
		p = Person(r.subjectName);
	}
	else
	{
		recRes = faceRec->recognize(processedFace);
		p = Person::personByRealName(recRes[0].subjectName);
	}

	Face f(object.getName(), Point(faceRect.x,faceRect.y), Point(faceRect.x+faceRect.width,faceRect.y+faceRect.height), processedFace, object.getId());
    
    //HACK for expediency
    f.upperLeftX = ( (double) faceRect.x / imgDecoded.cols ) * 100;
	f.upperLeftY = ( (double) faceRect.y / imgDecoded.rows ) * 100;
	f.lowerRightX = ( ( (double) faceRect.x + faceRect.width ) / imgDecoded.cols ) * 100;
	f.lowerRightY = ( ( (double) faceRect.y + faceRect.height ) / imgDecoded.rows ) * 100;
    //Round 
    f.upperLeftX = floorf( f.upperLeftX * 100 + 0.5) / 100;
    f.upperLeftY = floorf( f.upperLeftY * 100 + 0.5) / 100;
    f.lowerRightX = floorf( f.lowerRightX * 100 + 0.5) / 100;
    f.lowerRightY = floorf( f.lowerRightY * 100 + 0.5) / 100;
    
	p.addFace(f);

	p.persist();

	std::stringstream ss;

	// Original image name.
	ss << f.getOrigImgName() << ",";

	
	// Name of the rec image for this face.
	// int faceCount = p.getFaces().size()-1;
	vector <Face> faceList = p.getFaces();
	ss << faceList[faceList.size()-1].getRecImgPath() << ",";

	// Were both eyes found?
	int rightEyeCount = (face.getSubRegions()[0])->getSubRegions().size();
	int leftEyeCount = (face.getSubRegions()[1])->getSubRegions().size();

	if(rightEyeCount > 0 && leftEyeCount > 0)
	{
		ss << "1" << ",";
	}
	else
	{
		ss << "0" << ",";
	}

	// Best matches.
	for(unsigned int i=0; i<recRes.size(); i++)
	{
		ss << recRes[i].subjectName << ",";
		ss << recRes[i].distance;
		if(i<recRes.size()-1)
		{
			ss << ",";
		}
		else
		{
			ss << endl;
		}
	}

	m_log->writeDebug() << ss.str();

	// Insert tagging, using the toTagging_ function or other methods:  reply.addTagging( toTagging_( tagSetName, tag ) )
	// The arguments 'tagSetName' and 'tag" must jive with ObjectCube_DB_creation_script_monetdb.txt.
	//stringstream tag;
	//reply.addTagging(toTagging_("FaceRec.Person", tag.str(), faceRect));

	vector<string> allSuggestedTags;
	for(unsigned int i=0; i<recRes.size(); i++)
	{
		allSuggestedTags.push_back(recRes[i].subjectName);	
	}

	reply.addTagging(toTagging_("FaceRec.Person", p.getRealName(), imgDecoded, faceRect, f, allSuggestedTags));
}



PluginReply FaceRecognitionPlugin::process( const PluginObject& object, const vector<BoundingBox>& boundingBoxes ) 
{
	m_log->writeEnter() << __PRETTY_FUNCTION__ << std::endl;
	PluginReply reply( object.getId() );

	try 
	{
		//Do your analysis, object.getBinaryData() returns the object data (use object.getDataSizeInBytes() to get the size)
		const char *imgBuffer = object.getBinaryData();
		long imgByteSize = object.getDataSizeInBytes();
	
		Mat imgDecoded = this->decodeImage(imgBuffer, imgByteSize);
	
		/* Create a root ROI.*/
		RegionOfInterest roiRoot(object.getName(), imgDecoded.cols, imgDecoded.rows);

		for(unsigned int i=0; i<boundingBoxes.size(); i++)
		{
			double upperLeftX = boundingBoxes[i].getUpperLeftCorner().getX();
			double upperLeftY = boundingBoxes[i].getUpperLeftCorner().getY();
	
			double lowerRightX = boundingBoxes[i].getLowerRightCorner().getX();
			double lowerRightY = boundingBoxes[i].getLowerRightCorner().getY();

			double width = lowerRightX - upperLeftX;
			double height = lowerRightY - upperLeftY;
	
			RegionOfInterest face("face", upperLeftX, upperLeftY, width, height);
			roiRoot.addSubRegion(face);

		}
	
		faceDet->detectEyes(imgDecoded, roiRoot);

		vector<RegionOfInterest*> &faces = roiRoot.getSubRegions();

		if(faces.size() < 1)
		{
			return reply;
		}

		for(unsigned int i=0; i<faces.size(); i++)
		{
			Rect faceRect = faces[i]->getAbsoluteRect();
			this->processRoi(object, faceRect, imgDecoded, *faces[i], reply);
		}
	}
	catch(...)
	{
		m_log->writeError() << "Unknown error in FaceRecognitionPlugin::process( const PluginObject& object, const vector<BoundingBox>& boundingBoxes )" << std::endl;
		throw;
	}

	return reply;
}

void FaceRecognitionPlugin::taggingNotification( int /*objectId*/, const string& /*tagSetName*/, const BoundingBox& /*boundingBox*/, const string& /*tag*/ )
{

}



PluginReply FaceRecognitionPlugin::process( const PluginObject& object )
{
	m_log->writeEnter() << __PRETTY_FUNCTION__ << std::endl;
	PluginReply reply( object.getId() );
	Rect r;

	try 
	{
		//Do your analysis, object.getBinaryData() returns the object data (use object.getDataSizeInBytes() to get the size)
		const char *imgBuffer = object.getBinaryData();
		long imgByteSize = object.getDataSizeInBytes();

		Mat imgDecoded = this->decodeImage(imgBuffer, imgByteSize);

		RegionOfInterest roiRoot(object.getName(), imgDecoded.cols, imgDecoded.rows);

		faceDet->detectFaces(imgDecoded, roiRoot);
		faceDet->detectEyes(imgDecoded, roiRoot);

		vector<RegionOfInterest*> &faces = roiRoot.getSubRegions();

		for(unsigned int i=0; i<faces.size(); i++)
		{
			Rect faceRect = faces[i]->getAbsoluteRect();
			this->processRoi(object, faceRect, imgDecoded, *faces[i], reply);
		}
	}
	catch(...)
	{
		m_log->writeError() << "Unknown error in FaceRecognitionPlugin::process( const PluginObject& object )" << std::endl;
		throw;
	}
	
	return reply;
}

										  
//PluginTagging FaceRecognitionPlugin::toTagging_( const string& tagSetName, const string& tag, Rect faceRoi, vector<string> suggestedTags )
PluginTagging FaceRecognitionPlugin::toTagging_( const string& tagSetName, const string& tag, Mat& /*origImg*/, Rect /*faceRoi*/, Face& face, vector<string> suggestedTags  )
{
	m_log->writeEnter() << __PRETTY_FUNCTION__ << std::endl;
	//In this case, all tagging applies to the whole image
	
	Coordinate2D upperLeftCorner( face.upperLeftX, face.upperLeftY );
	Coordinate2D lowerRightCorner( face.lowerRightX, face.lowerRightY );
	
	//Coordinate2D upperLeftCorner( (float)faceRoi.x, (float)faceRoi.y );
	//Coordinate2D lowerRightCorner( (float)(faceRoi.x + faceRoi.width), (float)(faceRoi.y+faceRoi.height) );

	BoundingBox boundingBox( upperLeftCorner, lowerRightCorner );
	
	PluginTagging retval( tagSetName, tag, boundingBox, false ); //All taggings from this plugin are confirmed (true) and for the whole image

	retval.setSuggestedTags(suggestedTags);

	return retval;
}


//A neccessary part of all plugins
extern "C" EXPORT double getPluginInterfaceVersion()
{
	return PLUGIN_INTERFACE_VERSION;
}


//A neccessary part of all plugins
extern "C" EXPORT void registerPlugin( const int id, PluginServer& pluginServer )
{
	pluginServer.addProcessObjectPlugin( new FaceRecognitionPlugin( id ) );
}

