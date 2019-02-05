/*
 *  EXIF_Plugin.h
 *  EXIF_Plugin
 *
 *  Created by Gr’mur T—masson on 15.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef EXIF_Plugin_
#define EXIF_Plugin_

/* The classes below are exported */
#pragma GCC visibility push(default)

#include <map>
#include <set>
#include <string>
#include "../../ObjectCube/Plugin/ProcessObjectPlugin.h"

using namespace std;
using namespace ObjectCube;

class EXIF_Plugin : public ProcessObjectPlugin
{
public:
	EXIF_Plugin( const int id );
	virtual ~EXIF_Plugin() {;}
	
	virtual PluginReply process( const PluginObject& object );
	virtual PluginReply process( const PluginObject& object, const vector<BoundingBox>& boundingBoxes );
	virtual void renameTag( const string& tagSetName, const string& oldTagName, const string& newTagName );
	virtual void mergeTags(	const string& tagSetName, const string& oldTagName, const string& newTagName );
	virtual void confirmTagging( int objectId, const string& tagSetName, const BoundingBox& boundingBox, const string& tag );
	virtual void deleteTagging(	int objectId,const string& tagSetName, const BoundingBox& boundingBox, const string& tag );
	virtual void updateTagging(	int objectId, const string& tagSetName, const BoundingBox& boundingBox, const string& oldTag, const string& newTag);
	virtual void taggingNotification( int objectId, const string& tagSetName, const BoundingBox& boundingBox, const string& tag );
	
private:
	void init_();
	void processMetaDatum_( const Exiv2::Metadatum& metaDatum, PluginReply& reply );
	PluginTagging toTagging_( const string& tagSetName, const string& tag );
	
	std::string extractDate_( const std::string& value );
	std::string extractTime_( const std::string& value );

	set<string> tagsToProcess_;
	set<string> extractDateAndTime_;
	
	enum FORMAT_TYPE
	{
		LABEL = 1,
		DATE = 2,
		TIME = 3
	};
};

#pragma GCC visibility pop
#endif
