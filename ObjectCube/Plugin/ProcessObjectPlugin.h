/*
 *  ProcessObjectPlugin.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 15.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_PROCESS_OBJECT_PLUGIN_
#define ObjectCube_PROCESS_OBJECT_PLUGIN_

#include <map>
#include <string>
#include <vector>

#include "PluginCommon.h"
#include "PluginReply.h"

using namespace std;

namespace ObjectCube
{
	class PluginObject;
	
	class ProcessObjectPlugin : public PluginCommon  // An interface for Object Cube plugins
	{
	public:
		
		ProcessObjectPlugin( int id ) { setId( id ); }
		virtual ~ProcessObjectPlugin() {;}
		
		
		//Plugin interface functions
		virtual PluginReply process(	const PluginObject& object ) = 0;
		
		virtual PluginReply process(	const PluginObject& object, 
										const vector<BoundingBox>& boundingBoxes ) = 0;
		
		virtual void renameTag(			const string& tagSetName,
										const string& oldTagName,
										const string& newTagName ) = 0;
		
		virtual void mergeTags(			const string& tagSetName,
										const string& oldTagName,
										const string& newTagName ) = 0;
		
		virtual void confirmTagging(	int objectId,
										const string& tagSetName,
										const BoundingBox& boundingBox,
										const string& tag ) = 0;
		
		virtual void deleteTagging(		int objectId,
										const string& tagSetName,
										const BoundingBox& boundingBox,
										const string& tag ) = 0;
		
		virtual void updateTagging(		int objectId,
										const string& tagSetName,
										const BoundingBox& boundingBox,
										const string& oldTag,
										const string& newTag) = 0;
		
		virtual void taggingNotification( int objectId,
										 const string& tagSetName,
										 const BoundingBox& boundingBox,
										 const string& tag ) = 0;
		
		void setId( int id) { setId_( id ); }
		void setName( const string& name) { setName_( name ); }
		
	private:
		virtual void makeAbstract() {;}

	};

}

#endif