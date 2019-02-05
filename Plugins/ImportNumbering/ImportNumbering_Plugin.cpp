/*
 *  ImportNumbering_Plugin.cpp
 *  ImportNumbering_Plugin
 *
 *  Created by Olafur Waage
 *  Copyright 2013 Reykjavik University. All rights reserved.
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cassert>
#include <sstream>
#include <stdlib.h>

#include "ImportNumbering_Plugin.h"

#include "../ObjectCube/Plugin/PluginServer.h"
#include "../ObjectCube/Plugin/PluginObject.h"

#define EXPORT __attribute__((visibility("default")))

using namespace std;

ImportNumbering_Plugin::ImportNumbering_Plugin( const int id )
:	ProcessObjectPlugin( id )
{
	m_log = std::unique_ptr<Utils::Log>( new Utils::Log("oc_plugin_import_numbering.log") );
	m_log->writeEnter() << __PRETTY_FUNCTION__ << std::endl;
}

//A neccessary part of all plugins
PluginReply ImportNumbering_Plugin::process( const PluginObject& /*object*/, const vector<BoundingBox>& /*boundingBoxes*/ ) { return {}; }
void ImportNumbering_Plugin::renameTag( const string& /*tagSetName*/, const string& /*oldTagName*/, const string& /*newTagName*/ ) {}
void ImportNumbering_Plugin::mergeTags(	const string& /*tagSetName*/, const string& /*oldTagName*/, const string& /*newTagName*/ ) {}
void ImportNumbering_Plugin::confirmTagging( int /*objectId*/, const string& /*tagSetName*/, const BoundingBox& /*boundingBox*/, const string& /*tag*/ ) {}
void ImportNumbering_Plugin::deleteTagging(	int /*objectId*/,const string& /*tagSetName*/, const BoundingBox& /*boundingBox*/, const string& /*tag*/ ) {}
void ImportNumbering_Plugin::updateTagging(	int /*objectId*/, const string& /*tagSetName*/, const BoundingBox& /*boundingBox*/, const string& /*oldTag*/, const string& /*newTag*/) {}
void ImportNumbering_Plugin::taggingNotification( int /*objectId*/, const string& /*tagSetName*/, const BoundingBox& /*boundingBox*/, const string& /*tag*/ ) {}

PluginReply ImportNumbering_Plugin::process( const PluginObject& object )
{
	m_log->writeEnter() << __PRETTY_FUNCTION__ << std::endl;

	PluginReply reply( object.getId() );

	reply.addTagging( toTagging_( "Import.Number", "1" ) );
	
	m_log->writeInfo() << reply.getTaggingSize() << std::endl;

	return reply;
}

PluginTagging ImportNumbering_Plugin::toTagging_( const string& tagSetName, const string& tag )
{
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
	pluginServer.addProcessObjectPlugin( new ImportNumbering_Plugin( id ) );
}
