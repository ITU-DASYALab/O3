/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/

#include "ObjectTagDataAccess.h"

#include "BoundingBoxDataAccess.h"

#include "../../LayerShared/Exception.h"
#include "../../LayerShared/SharedDefinitions.h"


using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

ObjectTagDataAccess::ObjectTagDataAccess()
:	boundingBox_( 0 ),
	confirmed_( false ),
	tagId_( INVALID_VALUE ),
    objectId_( INVALID_VALUE )
{
}
//____________________________________________________________________________________________________________________________________________________________________________________

ObjectTagDataAccess::ObjectTagDataAccess( const ObjectTagDataAccess& objectTag ) //Copy constructor
:	boundingBox_( 0 ),
	confirmed_( false ),
	tagId_( INVALID_VALUE ),
    objectId_( INVALID_VALUE )
{
	copyValues_( objectTag );
}
//____________________________________________________________________________________________________________________________________________________________________________________

ObjectTagDataAccess& ObjectTagDataAccess::operator=( const ObjectTagDataAccess& objectTag )
{
	cleanup_();
	copyValues_( objectTag );
	return *this;}
//____________________________________________________________________________________________________________________________________________________________________________________

ObjectTagDataAccess::~ObjectTagDataAccess()
{ 
	cleanup_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void ObjectTagDataAccess::cleanup_()
{
	if( boundingBox_ )
	{
		delete boundingBox_;
		boundingBox_ = 0;
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________

void ObjectTagDataAccess::copyValues_( const ObjectTagDataAccess& objectTag )
{
    objectId_ = objectTag.objectId_;
	tagId_ = objectTag.tagId_;
	confirmed_ = objectTag.confirmed_;
	if( objectTag.hasBoundingBox() )
	{
		boundingBox_ = new BoundingBoxDataAccess();
		*boundingBox_ = *objectTag.boundingBox_;
	}	
}
//____________________________________________________________________________________________________________________________________________________________________________________

BoundingBoxDataAccess* ObjectTagDataAccess::getBoundingBox() const
{
	if( !boundingBox_ )
	{
		throw Exception( "ObjectTagDataAccess::getBoundingBox", "Attempt to get a non-existing bounding box!" );
	}
	return boundingBox_;
}
//____________________________________________________________________________________________________________________________________________________________________________________

bool ObjectTagDataAccess::hasBoundingBox() const
{
	return boundingBox_ == 0 ? false : true;
}
//____________________________________________________________________________________________________________________________________________________________________________________

