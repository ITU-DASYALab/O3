/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2011. All rights reserved.
 **********************************************************************/

#include "PluginTagging.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

PluginTagging::PluginTagging()
:	tagSetName_(),
	tag_(),
	boundingBox_(),
	confirmed_( true )
{

}
//____________________________________________________________________________________________________________________________________________________________________________________

PluginTagging::PluginTagging( string tagSetName, string tag, BoundingBox boundingBox, bool confirmed )
:	tagSetName_(),
	tag_(),
	boundingBox_(),
	confirmed_( true )
{
	tagSetName_ = tagSetName;
	tag_ = tag;
	boundingBox_ = boundingBox;
	confirmed_ = confirmed;
}
//____________________________________________________________________________________________________________________________________________________________________________________



