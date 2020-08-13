/*
 *  TimeTag.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 9.4.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "TimeTag.h"

#include <sstream>

#include "../DataAccess/Root/TimeTagDataAccess.h"
#include "../DataAccess/Factories/TimeTagDataAccessFactory.h"
#include "../Converters/TagConverter.h"
#include "../LayerShared/Exception.h"
#include "../LayerShared/SharedDefinitions.h"

#include <memory>

using namespace ObjectCube;


//____________________________________________________________________________________________________________________________________________________________________________________

TimeTag::TimeTag() 
: Tag()
{
	init_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

TimeTag::TimeTag( int hours, int minutes, int seconds, int milliseconds )
: Tag()
{
	init_();
	setHours( hours );
	setMinutes( minutes );
	setSeconds( seconds );
	setMilliseconds( milliseconds );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TimeTag::init_()
{
	setHours( INVALID_VALUE );
	setMinutes( INVALID_VALUE );
	setSeconds( INVALID_VALUE );
	setMilliseconds( INVALID_VALUE );
	setTypeId_( Tag::TIME );
	setNull_( true );
}
//____________________________________________________________________________________________________________________________________________________________________________________

TimeTag::~TimeTag()
{
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TimeTag::fetchImp_()  
{
	unique_ptr<TimeTagDataAccess> dataAccess( TimeTagDataAccessFactory::create() );
	
	if( getId() > 0 )
	{
		std::shared_ptr<Tag> tag( TagConverter::dataAccessToLogic( dataAccess->fetch( getId() ) ) );
		*this = *dynamic_cast<TimeTag*>( tag.get() ) ;
		return;
	}
	else if( getTagSetId() > 0 && !isNull() )  //The value itself has no limitations, here we demand it has been set (not null)
	{
		std::shared_ptr<Tag> tag( TagConverter::dataAccessToLogic( dataAccess->fetch( getTagSetId(), getHours(), getMinutes(), getSeconds(), getMilliseconds() ) ) );
		*this = *dynamic_cast<TimeTag*>( tag.get() );
		return;
	}
	throw Exception( "TimeTag::fetch_()", "Unsupported use of fetch_()" );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TimeTag::create_()
{
	unique_ptr<TimeTagDataAccess> dataAccess( dynamic_cast<TimeTagDataAccess*>( TagConverter::logicToDataAccess( this ).release() ) );
	std::shared_ptr<Tag> tag( TagConverter::dataAccessToLogic( dataAccess->create() ) ); 
	*this = *dynamic_cast<TimeTag*>( tag.get() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TimeTag::delete_()
{
	unique_ptr<TimeTagDataAccess> dataAccess( TimeTagDataAccessFactory::create() ); //The existence of the tag on objects is checked here rather than using State to limit dependence
	
	if( inUse() )
	{
		throw Exception( "TimeTag::delete_","This tag has been attached to objects an cannot be deleted without removing it from those objects first.", getId() );
	}
	dataAccess->remove( getId() ); //delete is taken
}
//____________________________________________________________________________________________________________________________________________________________________________________

const string TimeTag::valueAsString_() const
{
	stringstream stringStream;
	stringStream << getHours() << ":" << getMinutes() << ":" << getSeconds() << "." << getMilliseconds();
	return stringStream.str();
}
//____________________________________________________________________________________________________________________________________________________________________________________

TimeTag* TimeTag::fetch( int id )
{
	TimeTag* tag = new TimeTag();
	tag->setId_( id );
	tag->fetchImp_();
	return tag;
}
//____________________________________________________________________________________________________________________________________________________________________________________

TimeTag* TimeTag::fetch( int tagSetId, int hours, int minutes, int seconds, int milliseconds  )
{
	TimeTag* tag = new TimeTag();
	
	tag->setTagSetId_( tagSetId );
	tag->setHours( hours );
	tag->setMinutes( minutes );
	tag->setSeconds( seconds );
	tag->setMilliseconds( milliseconds );
	
	tag->fetchImp_();
	return tag;
}
//____________________________________________________________________________________________________________________________________________________________________________________

Tag& TimeTag::operator=( const Tag& tag )
{
	assignValues_( tag );
	const TimeTag* tTag = dynamic_cast<const TimeTag*>( &tag );
	setHours( tTag->getHours() );
	setMinutes( tTag->getMinutes() );
	setSeconds( tTag->getSeconds() );
	setMilliseconds( tTag->getMilliseconds() );
	return *this;
}
//____________________________________________________________________________________________________________________________________________________________________________________

bool TimeTag::compare( const TimeTag* a, const TimeTag* b )
{
    if( a->getHours() != b->getHours() )
    {
        return a->getHours() < b->getHours();
    }

    if( a->getMinutes() != b->getMinutes() )
    {
        return a->getMinutes() < b->getMinutes();
    }

    if( a->getSeconds() != b->getSeconds() )
    {
        return a->getSeconds() < b->getSeconds();
    }

    if( a->getMilliseconds() != b->getMilliseconds() )
    {
        return a->getMilliseconds() < b->getMilliseconds();
    }

    return true;
}

//____________________________________________________________________________________________________________________________________________________________________________________
