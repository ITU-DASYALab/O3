/*
 *  NumericalTag.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 27.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "NumericalTag.h"

#include <sstream>

#include "../DataAccess/Root/NumericalTagDataAccess.h"
#include "../DataAccess/Factories/NumericalTagDataAccessFactory.h"
#include "../Converters/TagConverter.h"
#include "../LayerShared/Exception.h"
#include "../LayerShared/SharedDefinitions.h"

#include <memory>

using namespace ObjectCube;


//____________________________________________________________________________________________________________________________________________________________________________________

NumericalTag::NumericalTag() 
: Tag()
{
	init_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

NumericalTag::NumericalTag( long number )
: Tag()
{
	init_();
	setNumber( number );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void NumericalTag::init_()
{
	setNumber( INVALID_VALUE );
	setTypeId_( Tag::NUMERICAL );
	setNull_( true );
}
//____________________________________________________________________________________________________________________________________________________________________________________

NumericalTag::~NumericalTag()
{
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void NumericalTag::fetchImp_()  
{
	unique_ptr<NumericalTagDataAccess> dataAccess( NumericalTagDataAccessFactory::create() );
	
	if( getId() > 0 )
	{
		std::shared_ptr<Tag> tag( TagConverter::dataAccessToLogic( dataAccess->fetch( getId() ) ) );
		*this = *dynamic_cast<NumericalTag*>( tag.get() ) ;
		return;
	}
	else if( getTagSetId() > 0 && !isNull() )  //The number itself has no value limitations, here we demand it has been set (not null)
	{
		std::shared_ptr<Tag> tag( TagConverter::dataAccessToLogic( dataAccess->fetch( getTagSetId(), getNumber() ) ) );
		*this = *dynamic_cast<NumericalTag*>( tag.get() );
		return;
	}
	throw Exception( "NumericalTag::fetch_()", "Unsupported use of fetch_()" );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void NumericalTag::create_()
{
	unique_ptr<NumericalTagDataAccess> dataAccess( dynamic_cast<NumericalTagDataAccess*>( TagConverter::logicToDataAccess( this ).release() ) );
	std::shared_ptr<Tag> tag( TagConverter::dataAccessToLogic( dataAccess->create() ) );
	*this = *dynamic_cast<NumericalTag*>( tag.get() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void NumericalTag::delete_()
{
	unique_ptr<NumericalTagDataAccess> dataAccess( NumericalTagDataAccessFactory::create() ); //The existence of the tag on objects is checked here rather than using State to limit dependence
	
	if( inUse() )
	{
		throw Exception( "NumericalTag::delete_","This tag has been attached to objects an cannot be deleted without removing it from those objects first.", getId() );
	}
	dataAccess->remove( getId() ); 
}
//____________________________________________________________________________________________________________________________________________________________________________________

const string NumericalTag::valueAsString_() const
{
	stringstream stringStream;
	stringStream << number_;
	return stringStream.str();
}
//____________________________________________________________________________________________________________________________________________________________________________________

NumericalTag* NumericalTag::fetch( int id )
{
	NumericalTag* tag = new NumericalTag();
	tag->setId_( id );
	tag->fetchImp_();
	return tag;
}
//____________________________________________________________________________________________________________________________________________________________________________________

NumericalTag* NumericalTag::fetch( int tagSetId, long number )
{
	NumericalTag* tag = new NumericalTag();
	tag->setTagSetId_( tagSetId );
	tag->setNumber( number );
	tag->fetchImp_();
	return tag;
}
//____________________________________________________________________________________________________________________________________________________________________________________

Tag& NumericalTag::operator=( const Tag& tag )
{
	assignValues_( tag );
	setNumber( dynamic_cast<const NumericalTag*> ( &tag )->getNumber() );
	return *this;
}
//____________________________________________________________________________________________________________________________________________________________________________________
