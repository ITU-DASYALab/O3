/*
 *  /*
 *  AlphanumericalTag.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 20.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "RGBTag.h"

#include "../DataAccess/Root/RGBTagDataAccess.h"
#include "../DataAccess/Factories/RGBTagDataAccessFactory.h"
#include "../Converters/TagConverter.h"
#include "../LayerShared/Exception.h"

#include <memory>
#include <iostream>
using namespace ObjectCube;
using namespace std;

//____________________________________________________________________________________________________________________________________________________________________________________

RGBTag::RGBTag() 
: Tag()
{
	init_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

RGBTag::RGBTag( const string& name )
: Tag()
{
	init_();
	setName( name );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void RGBTag::init_()
{
	setName( "NOT INITIALIZED!" );
	setTypeId_( Tag::RGB );
}
//____________________________________________________________________________________________________________________________________________________________________________________

RGBTag::~RGBTag()
{
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void RGBTag::setName( string name ) 
{ 
	name_ = name; 
}
//____________________________________________________________________________________________________________________________________________________________________________________

void RGBTag::fetchImp_()  //Reconsider this design
{
	unique_ptr<RGBTagDataAccess> dataAccess( RGBTagDataAccessFactory::create() );

	if( getId() > 0 )
	{
		std::shared_ptr<Tag> tag( TagConverter::dataAccessToLogic( dataAccess->fetch( getId() ) ) );
		*this = *dynamic_cast<RGBTag*>( tag.get() );
		return;
	}
	else if( getTagSetId() > 0 && getName().length() > 0 )
	{
		std::shared_ptr<Tag> tag( TagConverter::dataAccessToLogic( dataAccess->fetch( getTagSetId(), getName() ) ) );
		*this = *dynamic_cast<RGBTag*>( tag.get() );
		return;
	}
	throw Exception( "RGBTag::fetch_()", "Unsupported use of fetch_()" );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void RGBTag::create_()
{
	unique_ptr<RGBTagDataAccess> dataAccess( dynamic_cast<RGBTagDataAccess*>( TagConverter::logicToDataAccess( this ).release() ) );
	std::shared_ptr<Tag> tag( TagConverter::dataAccessToLogic( dataAccess->create() ) );
	*this = *dynamic_cast<RGBTag*>( tag.get() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void RGBTag::delete_()
{
	unique_ptr<RGBTagDataAccess> dataAccess( RGBTagDataAccessFactory::create() ); //The existence of the tag on objects is checked here rather than using State to limit dependence
	
	if( inUse() )
	{
		throw Exception( "RGBTag::delete_","This tag has been attached to objects an cannot be deleted without removing it from those objects first.", getId() );
	}
	dataAccess->remove( getId() ); //delete is taken
}
//____________________________________________________________________________________________________________________________________________________________________________________

const string RGBTag::valueAsString_() const
{
	return getName();
}
//____________________________________________________________________________________________________________________________________________________________________________________

RGBTag* RGBTag::fetch( int id )
{
	RGBTag* tag = new RGBTag();
	tag->setId_( id );
	tag->fetchImp_();
	return tag;
}
//____________________________________________________________________________________________________________________________________________________________________________________

RGBTag* RGBTag::fetch( int tagSetId, const string& name )
{
	RGBTag* tag = new RGBTag();
	tag->setTagSetId_( tagSetId );
	tag->setName( name );
	tag->fetchImp_();
	return tag;
}
//____________________________________________________________________________________________________________________________________________________________________________________

Tag& RGBTag::operator=( const Tag& tag )
{
	assignValues_( tag );
	setName( dynamic_cast<const RGBTag*>( &tag )->getName() );
	return *this;
}
//____________________________________________________________________________________________________________________________________________________________________________________