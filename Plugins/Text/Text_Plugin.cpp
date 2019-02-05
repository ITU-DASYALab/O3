/*
 *  Text_Plugin.cp
 *  Text_Plugin
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

#include "Text_Plugin.h"

#include "../../ObjectCube/Plugin/PluginServer.h"
#include "../../ObjectCube/Plugin/PluginObject.h"
#include "../../ObjectCube/LayerShared/StringSupport.h"


#define EXPORT __attribute__((visibility("default")))

using namespace std;



Text_Plugin::Text_Plugin( const int id )
:	ProcessObjectPlugin( id )
{
	
}


//A neccessary part of all plugins
// See "ObjectCube Plug-in API" on google docs for details.

PluginReply Text_Plugin::process( const PluginObject& object, const vector<BoundingBox>& boundingBoxes ) {}
void Text_Plugin::renameTag( const string& tagSetName, const string& oldTagName, const string& newTagName ) {}
void Text_Plugin::mergeTags(	const string& tagSetName, const string& oldTagName, const string& newTagName ) {}
void Text_Plugin::confirmTagging( int objectId, const string& tagSetName, const BoundingBox& boundingBox, const string& tag ) {}
void Text_Plugin::deleteTagging(	int objectId,const string& tagSetName, const BoundingBox& boundingBox, const string& tag ) {}
void Text_Plugin::updateTagging(	int objectId, const string& tagSetName, const BoundingBox& boundingBox, const string& oldTag, const string& newTag) {}
void Text_Plugin::taggingNotification( int objectId, const string& tagSetName, const BoundingBox& boundingBox, const string& tag ) {}


PluginReply Text_Plugin::process( const PluginObject& object )
{
	PluginReply reply( object.getId() );
	try 
	{
		string fileType = StringSupport::split(object.getName(), '.')[1];

		if (fileType != "txt"){
			return reply;
		}
		//Do your analysis, object.getBinaryData() returns the object data (use object.getDataSizeInBytes() to get the size)
		//The tagSetName is the value in the "name" column in the plugin_tag_set table.
		
		//Insert tagging, using the toTagging_ function or other methods:  reply.addTagging( toTagging_( tagSetName, tag ) )

		reply.addTagging( toTagging_( "Text.Text", object.getBinaryData() ) );
	}
	catch(...)
	{
		std::cerr << "Unknown error in Text_Plugin::process" << std::endl;
	}
	
	return reply;
}

										  
PluginTagging Text_Plugin::toTagging_( const string& tagSetName, const string& tag )
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
	pluginServer.addProcessObjectPlugin( new Text_Plugin( id ) );
}

										  


