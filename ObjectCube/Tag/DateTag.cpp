/*
 *  DateTag.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 10.4.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "DateTag.h"

#include <sstream>

#include "../DataAccess/Root/DateTagDataAccess.h"
#include "../DataAccess/Factories/DateTagDataAccessFactory.h"
#include "../Converters/TagConverter.h"
#include "../LayerShared/Exception.h"
#include "../LayerShared/SharedDefinitions.h"
#include "../LayerShared/DateSupport.h"

#include <memory>

using namespace ObjectCube;


//____________________________________________________________________________________________________________________________________________________________________________________

DateTag::DateTag() 
: Tag()
{
	init_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

DateTag::DateTag( int year, int month, int dayOfMonth )
: Tag()
{
	init_();
	setYear( year );
	setMonth( month );
	setDayOfMonth( dayOfMonth );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DateTag::init_()
{
	setYear( INVALID_VALUE );
	setMonth( INVALID_VALUE );
	setDayOfMonth( INVALID_VALUE );
	setTypeId_( Tag::DATE);
	setNull_( true );
}
//____________________________________________________________________________________________________________________________________________________________________________________

DateTag::~DateTag()
{
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DateTag::fetchImp_()  //Reconsider this design
{
	unique_ptr<DateTagDataAccess> dataAccess( DateTagDataAccessFactory::create() );
	
	if( getId() > 0 )
	{
		std::shared_ptr<Tag> tag( TagConverter::dataAccessToLogic( dataAccess->fetch( getId() ) ) );
		*this = *dynamic_cast<DateTag*>( tag.get() ) ;
		return;
	}
	else if( getTagSetId() > 0 && !isNull() )  //The value itself has no limitations, here we demand it has been set (not null)
	{
		std::shared_ptr<Tag> tag( TagConverter::dataAccessToLogic( dataAccess->fetch( getTagSetId(), getYear(), getMonth(), getDayOfMonth() ) ) );
		*this = *dynamic_cast<DateTag*>( tag.get() );
		return;
	}
	throw Exception( "DateTag::fetch_()", "Unsupported use of fetch_()" );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DateTag::create_()
{
	unique_ptr<DateTagDataAccess> dataAccess( dynamic_cast<DateTagDataAccess*>( TagConverter::logicToDataAccess( this ).release() ) );
	std::shared_ptr<Tag> tag( TagConverter::dataAccessToLogic( dataAccess->create() ) );
	*this = *dynamic_cast<DateTag*>( tag.get() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DateTag::delete_()
{
	unique_ptr<DateTagDataAccess> dataAccess( DateTagDataAccessFactory::create() ); //The existence of the tag on objects is checked here rather than using State to limit dependence
	
	if( inUse() )
	{
		throw Exception( "DateTag::delete_","This tag has been attached to objects an cannot be deleted without removing it from those objects first.", getId() );
	}
	dataAccess->remove( getId() ); //delete is taken
}
//____________________________________________________________________________________________________________________________________________________________________________________

const string DateTag::valueAsString_() const
{
	return DateSupport::toString( getYear(), getMonth(), getDayOfMonth() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

DateTag* DateTag::fetch( int id )
{
	DateTag* tag = new DateTag();
	tag->setId_( id );
	tag->fetchImp_();
	return tag;
}
//____________________________________________________________________________________________________________________________________________________________________________________

DateTag* DateTag::fetch( int tagSetId, int year, int month, int dayOfMonth  )
{
	DateTag* tag = new DateTag();
	
	tag->setTagSetId_( tagSetId );
	tag->setYear( year );
	tag->setMonth( month );
	tag->setDayOfMonth( dayOfMonth );
	
	tag->fetchImp_();
	return tag;
}
//____________________________________________________________________________________________________________________________________________________________________________________

Tag& DateTag::operator=( const Tag& tag )
{
	assignValues_( tag );
	const DateTag* dTag = dynamic_cast<const DateTag*>( &tag );
	setYear( dTag->getYear() );
	setMonth( dTag->getMonth() );
	setDayOfMonth( dTag->getDayOfMonth() );
	return *this;
}
//____________________________________________________________________________________________________________________________________________________________________________________

bool DateTag::compare( const DateTag* a, const DateTag* b )
{
    if( a->getYear() != b->getYear() )
    {
        return a->getYear() < b->getYear();
    }

    if( a->getMonth() != b->getMonth() )
    {
        return a->getMonth() < b->getMonth();
    }

    if( a->getDayOfMonth() != b->getDayOfMonth() )
    {
        return a->getDayOfMonth() < b->getDayOfMonth();
    }

    return true;
}

//____________________________________________________________________________________________________________________________________________________________________________________
