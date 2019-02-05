/*
 *  Random_Plugin.cpp
 *  Random_Plugin
 *
 *  Created by Bjorn Thor Jonsson
 *  Copyright 2012 Reykjavik University. All rights reserved.
 *
 */

#include <iostream>
#include <fstream>
#include <iomanip>
#include <cassert>
#include <sstream>
#include <stdlib.h>

#include "Random_Plugin.h"

#include "../ObjectCube/Plugin/PluginServer.h"
#include "../ObjectCube/Plugin/PluginObject.h"

#define EXPORT __attribute__((visibility("default")))

using namespace std;

//Moving those into a settings file may (or may not) be a good idea
const int MAX_RANDOM_NUMBER = 100;

Random_Plugin::Random_Plugin( const int id )
:	ProcessObjectPlugin( id )
{
	m_log = std::unique_ptr<Utils::Log>( new Utils::Log("oc_plugin_random.log") );
	m_log->writeEnter() << __PRETTY_FUNCTION__ << std::endl;

    srand ( time(NULL) );
}

//A neccessary part of all plugins
PluginReply Random_Plugin::process( const PluginObject& /*object*/, const vector<BoundingBox>& /*boundingBoxes*/ ) { return {}; }
void Random_Plugin::renameTag( const string& /*tagSetName*/, const string& /*oldTagName*/, const string& /*newTagName*/ ) {}
void Random_Plugin::mergeTags(	const string& /*tagSetName*/, const string& /*oldTagName*/, const string& /*newTagName*/ ) {}
void Random_Plugin::confirmTagging( int /*objectId*/, const string& /*tagSetName*/, const BoundingBox& /*boundingBox*/, const string& /*tag*/ ) {}
void Random_Plugin::deleteTagging(	int /*objectId*/,const string& /*tagSetName*/, const BoundingBox& /*boundingBox*/, const string& /*tag*/ ) {}
void Random_Plugin::updateTagging(	int /*objectId*/, const string& /*tagSetName*/, const BoundingBox& /*boundingBox*/, const string& /*oldTag*/, const string& /*newTag*/) {}
void Random_Plugin::taggingNotification( int /*objectId*/, const string& /*tagSetName*/, const BoundingBox& /*boundingBox*/, const string& /*tag*/ ) {}

string Random_Plugin::intToString( int value )
{
  stringstream strStream;
  strStream << value;
  return strStream.str();
}

PluginReply Random_Plugin::process( const PluginObject& object )
{
	m_log->writeEnter() << __PRETTY_FUNCTION__ << std::endl;

	PluginReply reply( object.getId() );
	
	int res1 = ( rand() % MAX_RANDOM_NUMBER ) + 1;
	int res2 = ( rand() % MAX_RANDOM_NUMBER ) + 1;
	
	m_log->writeInfo() << object.getName() << ":" << res1 << " " << res2 << std::endl;

	reply.addTagging( toTagging_( "Random.Number.1", intToString( res1 ) ) );
	reply.addTagging( toTagging_( "Random.Number.2", intToString( res2 ) ) );
	
	m_log->writeInfo() << reply.getTaggingSize() << std::endl;

	return reply;
}

PluginTagging Random_Plugin::toTagging_( const string& tagSetName, const string& tag )
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
	//std::cout << "----Trying to register plugin (in plugin code)" << std::endl;
	pluginServer.addProcessObjectPlugin( new Random_Plugin( id ) );
}
