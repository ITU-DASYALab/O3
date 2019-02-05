/*
 *  Random_Plugin.h
 *  Random_Plugin
 *
 *  Created by Bjorn Thor Jonsson
 *  Copyright 2012 Reykjavik University. All rights reserved.
 *
 */

#ifndef Random_Plugin_
#define Random_Plugin_

/* The classes below are exported */
#pragma GCC visibility push(default)

#include <map>
#include <set>
#include <string>
#include "../ObjectCube/Plugin/ProcessObjectPlugin.h"
#include "../ObjectCube/Utils/Log.h"

using namespace std;
using namespace ObjectCube;

class Random_Plugin : public ProcessObjectPlugin
{
public:
	Random_Plugin( const int id );
	virtual ~Random_Plugin() {;}
	
	virtual PluginReply process( const PluginObject& object );
	virtual PluginReply process( const PluginObject& object, const vector<BoundingBox>& boundingBoxes );
	virtual void renameTag( const string& tagSetName, const string& oldTagName, const string& newTagName );
	virtual void mergeTags(	const string& tagSetName, const string& oldTagName, const string& newTagName );
	virtual void confirmTagging( int objectId, const string& tagSetName, const BoundingBox& boundingBox, const string& tag );
	virtual void deleteTagging(	int objectId,const string& tagSetName, const BoundingBox& boundingBox, const string& tag );
	virtual void updateTagging(	int objectId, const string& tagSetName, const BoundingBox& boundingBox, const string& oldTag, const string& newTag);
	virtual void taggingNotification( int objectId, const string& tagSetName, const BoundingBox& boundingBox, const string& tag );
	
private:
	string intToString( int value );
	PluginTagging toTagging_( const string& tagSetName, const string& tag );

	std::unique_ptr<Utils::Log> m_log;
};

#pragma GCC visibility pop
#endif
