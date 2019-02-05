/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/

#include "ObjectTagConverter.h"

#include "../DataAccess/Root/ObjectTagDataAccess.h"
#include "../DataAccess/Factories/ObjectTagDataAccessFactory.h"
#include "BoundingBoxConverter.h"
#include "../Hub.h"
#include "../Tag/Tag.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

ObjectTag ObjectTagConverter::dataAccessToLogic( ObjectTagDataAccess* objectTagDA )
{
	ObjectTag objectTag( const_cast<Tag*>( Hub::getHub()->getTag( objectTagDA->getTagId() ) ) );
	objectTag.setObjectId_( objectTagDA->getObjectId() );
	objectTag.setConfirmed( objectTagDA->getConfirmed() );
	objectTag.boundingBox_ = BoundingBoxConverter::dataAccessToLogic( *objectTagDA->getBoundingBox() );
	
	return objectTag;
}
//____________________________________________________________________________________________________________________________________________________________________________________

ObjectTagDataAccess* ObjectTagConverter::logicToDataAccess( const ObjectTag& objectTag )
{
	ObjectTagDataAccess* objectTagDA = ObjectTagDataAccessFactory::create(); //new ObjectTagDataAccess();
	objectTagDA->setTagId( objectTag.getTag()->getId() );
	objectTagDA->setObjectId( objectTag.getObjectId_() );
	objectTagDA->setConfirmed( objectTag.getConfirmed() );
	objectTagDA->setBoundingBox( new BoundingBoxDataAccess( BoundingBoxConverter::logicToDataAccess( objectTag.getBoundingBox() ) ) );
	
	return objectTagDA;
}
//____________________________________________________________________________________________________________________________________________________________________________________

vector<ObjectTag> ObjectTagConverter::dataAccessToLogic( vector<ObjectTagDataAccess*> objectTagsDA )
{
	vector<ObjectTag> objectTags;
	for( vector<ObjectTagDataAccess*>::iterator itr = objectTagsDA.begin(); itr != objectTagsDA.end(); ++itr )
	{
		objectTags.push_back( ObjectTagConverter::dataAccessToLogic( *itr ) );
	}
	return objectTags;
}
//____________________________________________________________________________________________________________________________________________________________________________________

vector<ObjectTagDataAccess*> ObjectTagConverter::logicToDataAccess( const vector<ObjectTag>& objectTags )
{
	vector<ObjectTagDataAccess*> objectTagsDA;
	for( vector<ObjectTag>::const_iterator itr = objectTags.begin(); itr != objectTags.end(); ++itr )
	{
		objectTagsDA.push_back( ObjectTagConverter::logicToDataAccess( *itr ) );
	}
	return objectTagsDA;	
}
 //____________________________________________________________________________________________________________________________________________________________________________________


