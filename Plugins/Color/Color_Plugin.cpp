/***********************************************************************
 ** Reykjavik University
 ** Gr�mur T�masson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/

#include <iostream>
#include <math.h>

#include "Color_Plugin.h"

#include "../../ObjectCube/Plugin/PluginServer.h"
#include "../../ObjectCube/Plugin/PluginObject.h"

#include "ColorProcessing.h"

#define EXPORT __attribute__((visibility("default")))

//Moving those into a settings file is a good idea
const double MAX_SAMPLE_SIZE_PERCENTAGE = 1;
const int MINIMUM_SAMPLES_PIXELS_PER_AXIS = 100;

Color_Plugin::Color_Plugin( const int id )
: ProcessObjectPlugin( id )
{
	std::cout << "Color_Plugin::Color_Plugin" << std::endl;
}

PluginReply Color_Plugin::process( const PluginObject& object )
{
	PluginReply reply( object.getId() );

	ColorProcessing colorProcessing( MAX_SAMPLE_SIZE_PERCENTAGE, MINIMUM_SAMPLES_PIXELS_PER_AXIS );
	colorProcessing.processImage( reply, object.getBinaryData(), object.getDataSizeInBytes() );
	return reply;
}

PluginReply Color_Plugin::process( const PluginObject& /*object*/, const vector<BoundingBox>& /*boundingBoxes*/ ) { return {}; }
void Color_Plugin::renameTag( const string& /*tagSetName*/, const string& /*oldTagName*/, const string& /*newTagName*/ ) {}
void Color_Plugin::mergeTags(	const string& /*tagSetName*/, const string& /*oldTagName*/, const string& /*newTagName*/ ) {}
void Color_Plugin::confirmTagging( int /*objectId*/, const string& /*tagSetName*/, const BoundingBox& /*boundingBox*/, const string& /*tag*/ ) {}
void Color_Plugin::deleteTagging(	int /*objectId*/,const string& /*tagSetName*/, const BoundingBox& /*boundingBox*/, const string& /*tag*/ ) {}
void Color_Plugin::updateTagging(	int /*objectId*/, const string& /*tagSetName*/, const BoundingBox& /*boundingBox*/, const string& /*oldTag*/, const string& /*newTag*/) {}
void Color_Plugin::taggingNotification( int /*objectId*/, const string& /*tagSetName*/, const BoundingBox& /*boundingBox*/, const string& /*tag*/ ) {}

//A neccessary part of all plugins
extern "C" EXPORT double getPluginInterfaceVersion()
{
	return PLUGIN_INTERFACE_VERSION;
}

//A neccessary part of all plugins
extern "C" EXPORT void registerPlugin( const int id, PluginServer& pluginServer )
{
	//std::cout << "----Trying to register plugin (in plugin code)" << std::endl;
	pluginServer.addProcessObjectPlugin( new Color_Plugin( id ) );
}
