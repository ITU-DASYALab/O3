/*
 *  ObjectConverter.cpp
 *  Prada
 *
 *  Created by Grímur Tómasson on 6.2.2010.
 *  Copyright 2010 RU. All rights reserved.
 *
 */
#include <iostream>
#include "ObjectConverter.h"

#include "../DataAccess/Factories/ObjectDataAccessFactory.h"
#include "../DataAccess/Root/ObjectDataAccess.h"
#include "ObjectTagConverter.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

Object ObjectConverter::dataAccessToLogic( ObjectDataAccess* objectDA )
{
	Object object;
	object.setId_( objectDA->getId() );
	object.setName( objectDA->getName() );
	object.setThumbnail( objectDA->getThumbnail() );
	object.setFileType( objectDA->getFileType() );
	object.tags_ = ObjectTagConverter::dataAccessToLogic( objectDA->getTagInfo() );
	//object.tags_ = TagConverter::dataAccessToLogic( objectDA->getAllTags() );
	return object;
}
//____________________________________________________________________________________________________________________________________________________________________________________

ObjectDataAccess* ObjectConverter::logicToDataAccess( const Object* object )
{
	ObjectDataAccess* objectDA = ObjectDataAccessFactory::create();
	objectDA->setId( object->getId() );
	objectDA->setName( object->getName() );
	objectDA->setThumbnail( object->getThumbnail() );
	objectDA->setFileType( object->getFileType() );
	objectDA->setTagInfo( ObjectTagConverter::logicToDataAccess( object->tags_ ) );
	/*
	vector<int> tagIds;
	for( vector<Tag*>::const_iterator itr = object->tags_.begin(); itr != object->tags_.end(); ++itr )
	{
		tagIds.push_back( (*itr)->getId() );
	}
	objectDA->setTagIds( tagIds );
	 */
	//objectDA->setTags( TagConverter::logicToDataAccess( object->tags_ ) );
	return objectDA;
}
//____________________________________________________________________________________________________________________________________________________________________________________

vector<Object> ObjectConverter::dataAccessToLogic( vector<ObjectDataAccess*> objectsDA )
{
	vector<Object> objects;
	for( vector<ObjectDataAccess*>::iterator itr = objectsDA.begin(); itr != objectsDA.end(); ++itr )
	{
		objects.push_back( ObjectConverter::dataAccessToLogic( *itr ) );
	}
	return objects;
}
//____________________________________________________________________________________________________________________________________________________________________________________

vector<ObjectDataAccess*> ObjectConverter::logicToDataAccess( const vector<Object>& objects )
{
	vector<ObjectDataAccess*> objectsDA;
	for( vector<Object>::const_iterator itr = objects.begin(); itr != objects.end(); ++itr )
	{
		objectsDA.push_back( ObjectConverter::logicToDataAccess( &(*itr) ) );
	}
	return objectsDA;
}
//____________________________________________________________________________________________________________________________________________________________________________________

