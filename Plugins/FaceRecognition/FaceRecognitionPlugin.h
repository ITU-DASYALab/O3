/*
 *  FaceRecognitionPlugin.h
 *  FaceRecognitionPlugin
 *
 *  Created by Grmur Tmasson on 15.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef FaceRecognitionPlugin_
#define FaceRecognitionPlugin_

/* The classes below are exported */
#pragma GCC visibility push(default)

#include <map>
#include <set>
#include <string>
#include <memory>
#include "../ObjectCube/Plugin/ProcessObjectPlugin.h"
#include "../ObjectCube/Utils/Log.h"

#include "face_detection/FaceDetector.h"
#include "face_recognition/Eigenfaces.h"

using namespace std;
using namespace ObjectCube;

class Face;

class FaceRecognitionPlugin : public ProcessObjectPlugin
{
public:
	FaceRecognitionPlugin( const int id );
	~FaceRecognitionPlugin();
	
	virtual PluginReply process( const PluginObject& object );
	virtual PluginReply process( const PluginObject& object, const vector<BoundingBox>& boundingBoxes );
	virtual void renameTag( const string& tagSetName, const string& oldTagName, const string& newTagName );
	virtual void mergeTags(	const string& tagSetName, const string& oldTagName, const string& newTagName );
	virtual void confirmTagging( int objectId, const string& tagSetName, const BoundingBox& boundingBox, const string& tag );
	virtual void confirmTagging( const PluginObject &object, const string& tagSetName, const BoundingBox& boundingBox, const string& tag );
	virtual void deleteTagging(	int objectId,const string& tagSetName, const BoundingBox& boundingBox, const string& tag );
	virtual void updateTagging(	int objectId, const string& tagSetName, const BoundingBox& boundingBox, const string& oldTag, const string& newTag);
	virtual void taggingNotification( int objectId, const string& tagSetName, const BoundingBox& boundingBox, const string& tag );
	
private:

	FaceDetector *faceDet;
	Eigenfaces *faceRec;

	void train();

	std::unique_ptr<Utils::Log> m_log;

	string recImagePath, databasePath;
	PluginReply process( char* imgBuffer, long imgByteSize, vector<BoundingBox>& boundingBoxes );
	PluginTagging toTagging_( const string& tagSetName, const string& tag, Mat &origImg, Rect faceRoi, Face& face, vector<string> suggestedTags  );
	Mat decodeImage(const char *imgBuffer, long size);
	string newUnknownName();
	void processRoi(const PluginObject &object, Rect &faceRect, Mat &imgDecoded, RegionOfInterest &face, PluginReply &reply);
};

#pragma GCC visibility pop
#endif
