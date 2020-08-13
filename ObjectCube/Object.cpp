/*
 *  Photo.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 25.10.2009.
 *  Copyright 2009 Reykjavik University. All rights reserved.
 *
 */

//Declaration
#include "Object.h"
//External
#include <memory>
#include <iostream>
//Data access
#include "DataAccess/Factories/ObjectDataAccessFactory.h"
#include "DataAccess/Root/ObjectDataAccess.h"
#include "Converters/ObjectConverter.h"
#include "Converters/ObjectTagConverter.h"
//Other local
#include "Hub.h"
#include "TagSet/TagSet.h" //Due to enum, consider another placement for it 
#include "LayerShared/SharedDefinitions.h"
#include "LayerShared/Exception.h"
#include "LayerShared/MemoryManagement.h"
#include "LayerShared/DebugInfo.h"
#include "Tag/Tag.h"
#include "Tag/TagFactory.h"
#include "Tag/AlphanumericalTag.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

Object::Object()
{
	init_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

Object::Object( const string& name )
{
	init_();
	name_ = name;
}
//____________________________________________________________________________________________________________________________________________________________________________________

Object::~Object()
{

}
//____________________________________________________________________________________________________________________________________________________________________________________

void Object::init_()
{
	id_ = INVALID_VALUE;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void Object::validateCreate_()
{
	if( getName().length() < 1 )
	{
		throw Exception("Object::validateCreate_","No objects can be created without a name");
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________

Object& Object::create()
{
	DebugInfo::getDebugInfo()->pushTimer( "Object", "create" );
	DebugInfo::getDebugInfo()->pushTimer( "Object", "create", "add to DB" );
	unique_ptr<ObjectDataAccess> dataAccess( 	ObjectConverter::logicToDataAccess( this ) );
	*this = ObjectConverter::dataAccessToLogic( dataAccess->create() );
	DebugInfo::getDebugInfo()->popTimer();
	
	DebugInfo::getDebugInfo()->pushTimer( "Object", "create", "add uncategorized" );
	Hub* hub = Hub::getHub();
	if( !hasUserTags() ) //Uncategorized
	{
		const Tag* tag = hub->getUncategorizedTag();
		ObjectTag uncatTag( tag );
		uncatTag.setObjectId_( getId() );
		tags_.push_back( uncatTag );
	}
	DebugInfo::getDebugInfo()->popTimer();
	
	DebugInfo::getDebugInfo()->pushTimer( "Object", "create", "add tags to DB" );
	vector<ObjectTag>::iterator itr;
	for( itr = tags_.begin(); itr != tags_.end(); itr++ )
	{
		unique_ptr<ObjectTagDataAccess> objectTagDA( ObjectTagConverter::logicToDataAccess( *itr ) );
		dataAccess->addTag( objectTagDA.get() );
	}
	DebugInfo::getDebugInfo()->popTimer();
	
	DebugInfo::getDebugInfo()->pushTimer( "Object", "create", "add object to Hub" );
	hub->addObject( *this );
	DebugInfo::getDebugInfo()->popTimer();
	updateFileType();
	DebugInfo::getDebugInfo()->popTimer();
	
	return *this;
}
//____________________________________________________________________________________________________________________________________________________________________________________

Object& Object::create( const string& path )
{
	name_ = path;
	return create();
}
//____________________________________________________________________________________________________________________________________________________________________________________

Object Object::fetch( int id )
{
	DebugInfo::getDebugInfo()->output("Object", "fetch(id)", "Start" );
	
	unique_ptr<ObjectDataAccess> dataAccess( ObjectDataAccessFactory::create() );
	Object object = ObjectConverter::dataAccessToLogic( dataAccess->fetch( id ) );
//	Hub* hub = Hub::getHub();
//	object.setTags_( hub->getTags( dataAccess->getTagIds() ) );
	DebugInfo::getDebugInfo()->output("Object", "fetch(id)", "Done" );
	return object;
}
//____________________________________________________________________________________________________________________________________________________________________________________

Object Object::fetch( const string& qualifiedName )
{
	DebugInfo::getDebugInfo()->output("Object", "fetch(name)", "Start" );
	
	unique_ptr<ObjectDataAccess> dataAccess( ObjectDataAccessFactory::create() );
	Object object = ObjectConverter::dataAccessToLogic( dataAccess->fetch( qualifiedName ) );
//	Hub* hub = Hub::getHub();
//	object.setTags_( hub->getTags( dataAccess->getTagIds() ) );
	DebugInfo::getDebugInfo()->output("Object", "fetch(name)", "Done" );
	return object;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void Object::update()
{
	unique_ptr<ObjectDataAccess> dataAccess( 	ObjectConverter::logicToDataAccess( this ) );
	cout << "Object::update() Thumbnail = " <<  thumbnail_ << endl;
	cout << "Object::update() fileType = " << fileType_ << endl;
	dataAccess->setName(name_);
	dataAccess->setThumbnail(thumbnail_);
	dataAccess->setFileType(fileType_);
	dataAccess->update();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void Object::updateFileType()
{
	unique_ptr<ObjectDataAccess> dataAccess( 	ObjectConverter::logicToDataAccess( this ) );
	dataAccess->updateFileTypeFromPluginResult();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void Object::erase()
{
	unique_ptr<ObjectDataAccess> dataAccess( 	ObjectConverter::logicToDataAccess( this ) );
	dataAccess->erase();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void Object::addTag( ObjectTag& tag )
{
	if( tag.getTag()->getId() == INVALID_VALUE )
	{
		throw Exception( "Object::addTag", "Invalid value in tag id" );
	}
	if( hasTag( tag.getTag()->getId() ) )  //Trying to add the same tag twice is not an error
	{
		return;
	}
	
	tag.setObjectId_( getId() );
	
	unique_ptr<ObjectDataAccess> dataAccess( ObjectDataAccessFactory::create() );
	unique_ptr<ObjectTagDataAccess> objectTagDA( ObjectTagConverter::logicToDataAccess( tag ) );
	dataAccess->addTag( objectTagDA.get() );
	
	Hub* hub = Hub::getHub();
	if( hub->getParentTagSetsAccessType( tag.getTag() ) == TagSet::USER && hasTag( hub->getUncategorizedTag()->getId() ) )
	{
		//ObjectTag oTag = ObjectTag( const_cast<Tag*>( hub->getUncategorizedTag() ) ); 
        ObjectTag oTag = getTag( hub->getUncategorizedTag()->getId() );
		oTag.setObjectId_( getId() );
		removeTag( oTag );
	}
	
	tags_.push_back(  tag );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void Object::removeTag( ObjectTag& tag )
{
	unique_ptr<ObjectDataAccess> dataAccess( ObjectDataAccessFactory::create() );
	unique_ptr<ObjectTagDataAccess> objectTagDA( ObjectTagConverter::logicToDataAccess( tag ) );
	dataAccess->removeTag( objectTagDA.get() );
	
	vector<ObjectTag>::iterator itr = find_if( tags_.begin(), tags_.end(), tag );
	if( itr == tags_.end() )
	{
		throw Exception( "Object::removeTag", "The object was not tagged with the tag in question!" );
	}
	 
	tags_.erase( itr );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void Object::updateTagging( ObjectTag& tagging, const Tag* tag )
{
    removeTag( tagging );
    ObjectTag newTag( tag, tagging.getBoundingBox() );
    addTag( newTag );
    newTag.confirmTagging();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void Object::pluginProcess()
{
    Hub* hub = Hub::getHub();
    hub->addObject( *const_cast<Object*>(this) );
}
//____________________________________________________________________________________________________________________________________________________________________________________
bool Object::hasUserTags()
{
	Hub* hub = Hub::getHub();
	
	vector<ObjectTag>::iterator itr;
	for( itr = tags_.begin(); itr != tags_.end(); itr++ )
	{
		if( hub->getParentTagSetsAccessType( (*itr).getTag() ) == TagSet::USER )
		{
			return true;
		}
	}
	return false;
}
//____________________________________________________________________________________________________________________________________________________________________________________

const ObjectTag Object::getTag( int id ) const
{
	vector<ObjectTag>::const_iterator itr;
	for( itr = tags_.begin(); itr != tags_.end(); itr++ )
	{
		if( (*itr).getTag()->getId() == id )
		{
			return *itr;
		}
	}
	throw Exception("Object::getTag(id)", "Tag requested is not attached to this object.", id);
}
//____________________________________________________________________________________________________________________________________________________________________________________

bool Object::hasTag( int id )
{
	try 
	{
		getTag( id );  //If it does not throw an error the tag was found
		return true;
	}
	catch (...) {}
	return false;
}
//____________________________________________________________________________________________________________________________________________________________________________________















