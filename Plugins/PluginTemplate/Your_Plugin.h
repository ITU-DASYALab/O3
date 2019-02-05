/*
 *  Your_Plugin.h
 *  Your_Plugin
 *
 *  Created by Gr’mur T—masson on 15.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef Your_Plugin_
#define Your_Plugin_

/* The classes below are exported */
#pragma GCC visibility push(default)

#include <map>
#include <set>
#include <string>
#include "../ObjectCube/Plugin/ProcessObjectPlugin.h"

using namespace std;
using namespace ObjectCube;

class Your_Plugin : public ProcessObjectPlugin
{
public:
	Your_Plugin( const int id );
	virtual ~Your_Plugin() {;}
	
	virtual PluginReply process( const PluginObject& object );
	virtual PluginReply process( const PluginObject& object, const vector<BoundingBox>& boundingBoxes );
	virtual void renameTag( const string& tagSetName, const string& oldTagName, const string& newTagName );
	virtual void mergeTags(	const string& tagSetName, const string& oldTagName, const string& newTagName );
	virtual void confirmTagging( int objectId, const string& tagSetName, const BoundingBox& boundingBox, const string& tag );
	virtual void deleteTagging(	int objectId,const string& tagSetName, const BoundingBox& boundingBox, const string& tag );
	virtual void updateTagging(	int objectId, const string& tagSetName, const BoundingBox& boundingBox, const string& oldTag, const string& newTag);
	virtual void taggingNotification( int objectId, const string& tagSetName, const BoundingBox& boundingBox, const string& tag );
	
private:
	PluginTagging toTagging_( const string& tagSetName, const string& tag );
		
};

#pragma GCC visibility pop
#endif
