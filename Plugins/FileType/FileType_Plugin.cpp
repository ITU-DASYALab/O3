/*
 *  FileType_Plugin.cp
 *  FileType_Plugin
 *
 *  Created by Grímur Tómasson on 15.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cassert>

#include "FileType_Plugin.h"

#include "../../ObjectCube/Plugin/PluginServer.h"
#include "../../ObjectCube/Plugin/PluginObject.h"
#include "../../ObjectCube/LayerShared/StringSupport.h"


#define EXPORT __attribute__((visibility("default")))

using namespace std;



FileType_Plugin::FileType_Plugin( const int id )
:	ProcessObjectPlugin( id )
{
	
}


//A neccessary part of all plugins
// See "ObjectCube Plug-in API" on google docs for details.

PluginReply FileType_Plugin::process( const PluginObject& object, const vector<BoundingBox>& boundingBoxes ) {}
void FileType_Plugin::renameTag( const string& tagSetName, const string& oldTagName, const string& newTagName ) {}
void FileType_Plugin::mergeTags(	const string& tagSetName, const string& oldTagName, const string& newTagName ) {}
void FileType_Plugin::confirmTagging( int objectId, const string& tagSetName, const BoundingBox& boundingBox, const string& tag ) {}
void FileType_Plugin::deleteTagging(	int objectId,const string& tagSetName, const BoundingBox& boundingBox, const string& tag ) {}
void FileType_Plugin::updateTagging(	int objectId, const string& tagSetName, const BoundingBox& boundingBox, const string& oldTag, const string& newTag) {}
void FileType_Plugin::taggingNotification( int objectId, const string& tagSetName, const BoundingBox& boundingBox, const string& tag ) {}


PluginReply FileType_Plugin::process( const PluginObject& object )
{
	PluginReply reply( object.getId() );
	try 
	{
		string fileType = object.getName().substr(object.getName().find_last_of('.')+1);

		//Do your analysis, object.getBinaryData() returns the object data (use object.getDataSizeInBytes() to get the size)
		//The tagSetName is the value in the "name" column in the plugin_tag_set table.
		
		//Insert tagging, using the toTagging_ function or other methods:  reply.addTagging( toTagging_( tagSetName, tag ) )

		reply.addTagging( toTagging_( "FileType", fileType ) );
	}
	catch(...)
	{
		std::cerr << "Unknown error in FileType_Plugin::process" << std::endl;
	}
	
	return reply;
}

										  
PluginTagging FileType_Plugin::toTagging_( const string& tagSetName, const string& tag )
{
	//In this case, all tagging applies to the whole image
	Coordinate2D upperLeftCorner( 0.0, 100.0 );
	Coordinate2D lowerRightCorner( 100.0, 0.0 );
	BoundingBox boundingBox( upperLeftCorner, lowerRightCorner );
	
	return PluginTagging( tagSetName, tag, boundingBox, true ); //All taggings from this plugin are confirmed (true) and for the whole image
}
										  

//A neccessary part of all plugins
extern "C" EXPORT double getPluginInterfaceVersion()
{
	return PLUGIN_INTERFACE_VERSION;
}


//A neccessary part of all plugins
extern "C" EXPORT void registerPlugin( const int id, PluginServer& pluginServer )
{
	//std::cout << "----Trying to register plugin (in plugin code)" << std::endl;
	pluginServer.addProcessObjectPlugin( new FileType_Plugin( id ) );
}

										  


