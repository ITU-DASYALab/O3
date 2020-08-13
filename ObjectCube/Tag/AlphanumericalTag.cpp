/*
 *  AlphanumericalTag.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 20.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "AlphanumericalTag.h"

#include "../DataAccess/Root/AlphanumericalTagDataAccess.h"
#include "../DataAccess/Factories/AlphanumericalTagDataAccessFactory.h"
#include "../Converters/TagConverter.h"
#include "../LayerShared/Exception.h"

#include <memory>

using namespace ObjectCube;


//____________________________________________________________________________________________________________________________________________________________________________________

AlphanumericalTag::AlphanumericalTag() 
: Tag()
{
	init_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

AlphanumericalTag::AlphanumericalTag( const string& name )
: Tag()
{
	init_();
	setName( name );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void AlphanumericalTag::init_()
{
	setName( "NOT INITIALIZED!" );
	setTypeId_( Tag::ALPHANUMERICAL );
}
//____________________________________________________________________________________________________________________________________________________________________________________

AlphanumericalTag::~AlphanumericalTag()
{
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void AlphanumericalTag::setName( string name ) 
{ 
	name_ = name; 
}
//____________________________________________________________________________________________________________________________________________________________________________________

void AlphanumericalTag::fetchImp_()  //Reconsider this design
{
	unique_ptr<AlphanumericalTagDataAccess> dataAccess( AlphanumericalTagDataAccessFactory::create() );

	if( getId() > 0 )
	{
		std::shared_ptr<Tag> tag( TagConverter::dataAccessToLogic( dataAccess->fetch( getId() ) ) );
		*this = *dynamic_cast<AlphanumericalTag*>( tag.get() );
		return;
	}
	else if( getTagSetId() > 0 && getName().length() > 0 )
	{
		std::shared_ptr<Tag> tag( TagConverter::dataAccessToLogic( dataAccess->fetch( getTagSetId(), getName() ) ) );
		*this = *dynamic_cast<AlphanumericalTag*>( tag.get() );
		return;
	}
	throw Exception( "AlphanumericalTag::fetch_()", "Unsupported use of fetch_()" );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void AlphanumericalTag::create_()
{
	unique_ptr<AlphanumericalTagDataAccess> dataAccess( dynamic_cast<AlphanumericalTagDataAccess*>( TagConverter::logicToDataAccess( this ).release() ) );
	std::shared_ptr<Tag> tag( TagConverter::dataAccessToLogic( dataAccess->create() ) );
	*this = *dynamic_cast<AlphanumericalTag*>( tag.get() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void AlphanumericalTag::delete_()
{
	unique_ptr<AlphanumericalTagDataAccess> dataAccess( AlphanumericalTagDataAccessFactory::create() ); //The existence of the tag on objects is checked here rather than using State to limit dependence
	
	if( inUse() )
	{
		throw Exception( "AlphanumericalTag::delete_","This tag has been attached to objects an cannot be deleted without removing it from those objects first.", getId() );
	}
	dataAccess->remove( getId() ); //delete is taken
}
//____________________________________________________________________________________________________________________________________________________________________________________

const string AlphanumericalTag::valueAsString_() const
{
	return getName();
}
//____________________________________________________________________________________________________________________________________________________________________________________

AlphanumericalTag* AlphanumericalTag::fetch( int id )
{
	AlphanumericalTag* tag = new AlphanumericalTag();
	tag->setId_( id );
	tag->fetchImp_();
	return tag;
}
//____________________________________________________________________________________________________________________________________________________________________________________

AlphanumericalTag* AlphanumericalTag::fetch( int tagSetId, const string& name )
{
	AlphanumericalTag* tag = new AlphanumericalTag();
	tag->setTagSetId_( tagSetId );
	tag->setName( name );
	tag->fetchImp_();
	return tag;
}
//____________________________________________________________________________________________________________________________________________________________________________________

Tag& AlphanumericalTag::operator=( const Tag& tag )
{
	assignValues_( tag );
	setName( dynamic_cast<const AlphanumericalTag*>( &tag )->getName() );
	return *this;
}
//____________________________________________________________________________________________________________________________________________________________________________________



