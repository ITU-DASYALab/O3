/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2011. All rights reserved.
 **********************************************************************/

#include "PluginTaggingProcessed.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

PluginTaggingProcessed::PluginTaggingProcessed()
:	objectId_(),
	tagSetId_()
{

}
//____________________________________________________________________________________________________________________________________________________________________________________

PluginTaggingProcessed::PluginTaggingProcessed( int objectId, int tagSetId, const PluginTagging& pluginTagging )
:	objectId_( objectId ),
	tagSetId_( tagSetId ),
	PluginTagging( pluginTagging )
{
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

bool PluginTaggingProcessed::operator < ( const PluginTaggingProcessed& b ) const
{
	return getTag() < b.getTag();
}
//____________________________________________________________________________________________________________________________________________________________________________________

bool PluginTaggingProcessed::operator==( PluginTaggingProcessed const& x) const
{
	return	getObjectId() == x.getObjectId() &&
			getTagSetId() == x.getTagSetId() &&
			getTagSetName() == x.getTagSetName() &&
			getTag() == x.getTag() &&
			getBoundingBox() == x.getBoundingBox() &&
			getConfirmed() == x.getConfirmed();	
}
//____________________________________________________________________________________________________________________________________________________________________________________
