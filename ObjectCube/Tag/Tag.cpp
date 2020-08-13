/*
 *  Tag.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 25.10.2009.
 *  Copyright 2009 Reykjavik University. All rights reserved.
 *
 */

#include "Tag.h"

#include <memory>

#include "TagFactory.h"
#include "../DataAccess/Factories/TagDataAccessFactory.h"
#include "../Converters/TagConverter.h"
#include "../DataAccess/Root/TagDataAccess.h"
#include "../LayerShared/SharedDefinitions.h"
#include "../LayerShared/Exception.h"
#include "../Language.h"


//taka út
#include <iostream>

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

Tag::Tag()
{
	init_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

Tag::~Tag()
{

}
//____________________________________________________________________________________________________________________________________________________________________________________

void Tag::init_()
{
	id_ = INVALID_VALUE;
	tagSetId_ = INVALID_VALUE;
	typeId_ = UNKNOWN;
}
//____________________________________________________________________________________________________________________________________________________________________________________

Tag* Tag::fetch_( int id )
{
	unique_ptr<TagDataAccess> dataAccess( TagDataAccessFactory::create() );
	std::shared_ptr<Tag> tag( TagConverter::dataAccessToLogic( dataAccess->fetch( id ) ) );  //Creates the correct type (new)
	
	tag->fetchImp_();
	
	unique_ptr<Tag> tagToReturn( TagFactory::create( tag->getTypeId() ) );
	*tagToReturn.get() = *tag.get();
	return tagToReturn.release();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void Tag::create_()
{
	unique_ptr<TagDataAccess> dataAccess( TagConverter::logicToDataAccess( this ) );
	*this = *TagConverter::dataAccessToLogic( dataAccess->create() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void Tag::delete_()
{
	unique_ptr<TagDataAccess> dataAccess( TagDataAccessFactory::create() ); //The existence of the tag on objects is checked here rather than using State to limit dependence
	
	if( inUse() )
	{
		throw Exception( "Tag::delete_","This tag has been attached to objects an cannot be deleted without removing it from those objects first.", getId() );
	}
	dataAccess->remove( getId() ); 
}
//____________________________________________________________________________________________________________________________________________________________________________________

const string Tag::valueAsString() const
{
	return valueAsString_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

const string Tag::valueAsString_() const
{
	throw Exception( "Tag::valueAsString_", "This function is not, and should not, be implemented for this abstract class!" );
}
//____________________________________________________________________________________________________________________________________________________________________________________

const string Tag::typeAsString() const
{
	return Language::asString( "TagType", getTypeId() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

const string Tag::typeAsString( int tagTypeId )
{
	return Language::asString( "TagType", tagTypeId );
}
//____________________________________________________________________________________________________________________________________________________________________________________

int Tag::inUse() const
{
	unique_ptr<TagDataAccess> dataAccess( TagDataAccessFactory::create() );
	return dataAccess->inUse( getId() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

bool Tag::operator==( Tag const& x) const
{
	return	getId() == x.getId();
}
//____________________________________________________________________________________________________________________________________________________________________________________

bool Tag::operator!=( Tag const& x) const
{
	return !( getId() == x.getId() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

bool Tag::operator < ( const Tag& x ) const
{ 
	return getId() < x.getId(); 
}
//____________________________________________________________________________________________________________________________________________________________________________________++

Tag& Tag::operator=( const Tag& tag  )
{
	*this = tag;
	return *this;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void Tag::assignValues_( const Tag& tag )
{
	setId_( tag.getId() );
	setTypeId_( tag.getTypeId() );
	setTagSetId_( tag.getTagSetId() );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

bool Tag::compareByValueAsString( Tag* tag1, Tag* tag2 )
{
	return true;
}










