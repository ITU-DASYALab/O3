/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/

#include "ObjectTag.h"

#include "Hub.h"

#include "Tag/Tag.h"
#include "TagSet/TagSet.h"
#include "LayerShared/Exception.h"
#include "LayerShared/SharedDefinitions.h"

#include "DataAccess/Factories/ObjectTagDataAccessFactory.h"
#include "DataAccess/Root/ObjectTagDataAccess.h"
#include "Converters/ObjectTagConverter.h"

#include "Plugin/PluginServer.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

ObjectTag::ObjectTag( Tag* tag )
:	tag_( 0 ),
	objectId_( INVALID_VALUE ),
	confirmed_( true ),
	boundingBox_()
{
	tag_ = tag;
}
//____________________________________________________________________________________________________________________________________________________________________________________

ObjectTag::ObjectTag( const Tag* tag )
:	tag_( 0 ),
	objectId_( INVALID_VALUE ),
	confirmed_( true ),
	boundingBox_()
{
	tag_ = const_cast<Tag*>( tag );
}
//____________________________________________________________________________________________________________________________________________________________________________________

ObjectTag::ObjectTag( Tag* tag, BoundingBox boundingBox )
:	tag_( 0 ),
	objectId_( INVALID_VALUE ),
	confirmed_( true ),
	boundingBox_( boundingBox )
{
	tag_ = tag;
	//boundingBox_ = boundingBox;
}
//____________________________________________________________________________________________________________________________________________________________________________________

ObjectTag::ObjectTag( const Tag* tag, BoundingBox boundingBox )
:	tag_( 0 ),
	objectId_( INVALID_VALUE ),
	confirmed_( true ),
	boundingBox_( boundingBox)
{
	tag_ = const_cast<Tag*>( tag );
	//boundingBox_ = boundingBox_;
}
//____________________________________________________________________________________________________________________________________________________________________________________

ObjectTag::ObjectTag( const ObjectTag& objectTag )
:	tag_( 0 ),
	objectId_( INVALID_VALUE ),
	confirmed_(true),
	boundingBox_()
{
	copyValues_( objectTag );
}
//____________________________________________________________________________________________________________________________________________________________________________________

ObjectTag& ObjectTag::operator=( const ObjectTag& objectTag )
{
	copyValues_( objectTag );
	return *this;
}
//____________________________________________________________________________________________________________________________________________________________________________________

ObjectTag::~ObjectTag()
{
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void ObjectTag::copyValues_( const ObjectTag& objectTag )
{
	tag_ = objectTag.tag_;
	objectId_ = objectTag.objectId_;
	confirmed_ = objectTag.confirmed_;
	boundingBox_ = objectTag.boundingBox_;
}
//____________________________________________________________________________________________________________________________________________________________________________________

BoundingBox ObjectTag::getBoundingBox() const 
{
	/*
	if( !boundingBox_ )
	{
		throw Exception( "ObjectTag::getBoundingBox", "Attempt to get a non-existing bounding box!" );
	}
	*/
	return boundingBox_;
}
//____________________________________________________________________________________________________________________________________________________________________________________
/*
bool ObjectTag::hasBoundingBox() const
{
	return boundingBox_ == 0 ? false : true;
}
*/
//____________________________________________________________________________________________________________________________________________________________________________________

bool ObjectTag::operator==( const ObjectTag& x ) const
{
	
	return	getTag()->getId() == x.getTag()->getId() && boundingBox_ == x.getBoundingBox() && confirmed_ == x.getConfirmed();
}
//____________________________________________________________________________________________________________________________________________________________________________________

bool ObjectTag::operator!=( ObjectTag const& x ) const
{
	return !( getTag()->getId() == x.getTag()->getId() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

bool ObjectTag::operator < ( const ObjectTag& x ) const
{ 
	return getTag()->getId() < x.getTag()->getId(); 
}
//____________________________________________________________________________________________________________________________________________________________________________________

bool ObjectTag::operator()( const ObjectTag& x ) const
{
	return operator==( x );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void ObjectTag::confirmTagging()
{
	setConfirmed( true );
	unique_ptr<ObjectTagDataAccess> dataAccess( ObjectTagConverter::logicToDataAccess( *this ) );
	dataAccess->modify();
	
	//Let plug-ins know
	string tagSetName = Hub::getHub()->getTagSet( getTag()->getTagSetId() )->getName();
	string tagValue = getTag()->valueAsString();
	std::shared_ptr<PluginServer> pluginServer = Hub::getHub()->getPluginServer();
	pluginServer->getProcessObjectServer().confirmTagging( getObjectId_(), tagSetName, getBoundingBox(), tagValue );
}
//____________________________________________________________________________________________________________________________________________________________________________________





































