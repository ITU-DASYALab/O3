/*
 *  Your_Plugin.cp
 *  Your_Plugin
 *
 *  Created by Grímur Tómasson on 15.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cassert>

#include "Your_Plugin.h"

#include "../ObjectCube/Plugin/PluginServer.h"
#include "../ObjectCube/Plugin/PluginObject.h"

#define EXPORT __attribute__((visibility("default")))

using namespace std;



Your_Plugin::Your_Plugin( const int id )
:	ProcessObjectPlugin( id )
{
	
}


//A neccessary part of all plugins
// See "ObjectCube Plug-in API" on google docs for details.

PluginReply Your_Plugin::process( const PluginObject& object, const vector<BoundingBox>& boundingBoxes ) {}
void Your_Plugin::renameTag( const string& tagSetName, const string& oldTagName, const string& newTagName ) {}
void Your_Plugin::mergeTags(	const string& tagSetName, const string& oldTagName, const string& newTagName ) {}
void Your_Plugin::confirmTagging( int objectId, const string& tagSetName, const BoundingBox& boundingBox, const string& tag ) {}
void Your_Plugin::deleteTagging(	int objectId,const string& tagSetName, const BoundingBox& boundingBox, const string& tag ) {}
void Your_Plugin::updateTagging(	int objectId, const string& tagSetName, const BoundingBox& boundingBox, const string& oldTag, const string& newTag) {}
void Your_Plugin::taggingNotification( int objectId, const string& tagSetName, const BoundingBox& boundingBox, const string& tag ) {}


PluginReply Your_Plugin::process( const PluginObject& object )
{
	PluginReply reply( object.getId() );
	try 
	{
		//Do your analysis, object.getBinaryData() returns the object data (use object.getDataSizeInBytes() to get the size)
			//The tagSetName is the value in the "name" column in the plugin_tag_set table.
		
			//Insert tagging, using the toTagging_ function or other methods:  reply.addTagging( toTagging_( tagSetName, tag ) )
	}
	/*
	catch ( app specific errors) 
	{
		std::cerr << "Error caught: " << e << std::endl;
	}
	 */
	catch(...)
	{
		std::cerr << "Unknown error in Your_Plugin::process" << std::endl;
	}
	
	return reply;
}

										  
PluginTagging Your_Plugin::toTagging_( const string& tagSetName, const string& tag )
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
	pluginServer.addProcessObjectPlugin( new Your_Plugin( id ) );
}

										  


