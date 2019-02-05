/*
 *  TimeRangeFilter.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 3.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "TimeRangeFilter.h"

#include <sstream>
#include <iomanip>

#include "../LayerShared/SharedDefinitions.h"
#include "../LayerShared/Exception.h"
#include "../LayerShared/TimeSupport.h"

using namespace ObjectCube;


//____________________________________________________________________________________________________________________________________________________________________________________

TimeRangeFilter::TimeRangeFilter()
{
	init_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

TimeRangeFilter::TimeRangeFilter( int tagSetId )
: Filter( tagSetId )
{
	init_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

TimeRangeFilter::TimeRangeFilter( int hoursFrom, int hoursTo, int tagSetId ) 
: Filter( tagSetId )
{
	init_();
	
	setHoursFrom( hoursFrom );
	setHoursTo( hoursTo );
}
//____________________________________________________________________________________________________________________________________________________________________________________

TimeRangeFilter::~TimeRangeFilter()
{
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TimeRangeFilter::init_()
{
	setTypeId_( Filter::TIME_RANGE_FILTER );
	
	hoursFrom_ = INVALID_VALUE;
	minutesFrom_ = INVALID_VALUE;
	secondsFrom_ = INVALID_VALUE;
	millisecondsFrom_ = INVALID_VALUE;
	
	hoursTo_ = INVALID_VALUE;
	minutesTo_ = INVALID_VALUE;
	secondsTo_ = INVALID_VALUE;
	millisecondsTo_ = INVALID_VALUE;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TimeRangeFilter::setHoursFrom( int hours )
{
	hoursFrom_ = hours;
	setNullStatus_( getHoursFrom() == INVALID_VALUE || getHoursTo() == INVALID_VALUE );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TimeRangeFilter::setMinutesFrom( int minutes )
{
	minutesFrom_ = minutes;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TimeRangeFilter::setSecondsFrom( int seconds )
{
	secondsFrom_ = seconds;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TimeRangeFilter::setMillisecondsFrom( int milliseconds )
{
	millisecondsFrom_ = milliseconds;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TimeRangeFilter::setHoursTo( int hours )
{
	hoursTo_ = hours;
	setNullStatus_( getHoursFrom() == INVALID_VALUE || getHoursTo() == INVALID_VALUE );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TimeRangeFilter::setMinutesTo( int minutes )
{
	minutesTo_ = minutes;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TimeRangeFilter::setSecondsTo( int seconds )
{
	secondsTo_ = seconds;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TimeRangeFilter::setMillisecondsTo( int milliseconds )
{
	millisecondsTo_ = milliseconds;
}
//____________________________________________________________________________________________________________________________________________________________________________________

Filter& TimeRangeFilter::operator=( const Filter& filter )
{
	assignValues_( filter );
	const TimeRangeFilter* trFilter = dynamic_cast<const TimeRangeFilter*>( &filter );
	
	setHoursFrom( trFilter->getHoursFrom() );
	setMinutesFrom( trFilter->getMinutesFrom() );
	setSecondsFrom( trFilter->getSecondsFrom() );
	setMillisecondsFrom( trFilter->getMillisecondsFrom() );
	
	setHoursTo( trFilter->getHoursTo() );
	setMinutesTo( trFilter->getMinutesTo() );
	setSecondsTo( trFilter->getSecondsTo() );
	setMillisecondsTo( trFilter->getMillisecondsTo() );
	
	return *this;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TimeRangeFilter::fillInAndValidateValues()
{
	
	if( getHoursFrom() == INVALID_VALUE || getHoursTo() == INVALID_VALUE )
	{
		throw Exception( "TimeRangeFilter::fillInAndValidateTime_", "Hours to and from have not been set!" );
	}
	
	if( getMinutesFrom() == INVALID_VALUE )
	{
		setMinutesFrom( 0 );
	}
	if( getSecondsFrom() == INVALID_VALUE )
	{
		setSecondsFrom( 0 );
	}
	if( getMillisecondsFrom() == INVALID_VALUE )
	{
		setMillisecondsFrom( 0 );
	}
	
	if( getMinutesTo() == INVALID_VALUE )
	{
		setMinutesTo( 59 );
	}
	if( getSecondsTo() == INVALID_VALUE )
	{
		setSecondsTo( 59 );
	}
	if( getMillisecondsTo() == INVALID_VALUE )
	{
		setMillisecondsTo( 999 );
	}
	
	//Validation
	if( !TimeSupport::validTime( getHoursFrom(), getMinutesFrom(), getSecondsFrom(), getMillisecondsFrom() ) )
	{
		stringstream stringStream;
		stringStream << "Time from is not valid, hours: " << getHoursFrom() << " minutes: " << getMinutesFrom() << " seconds: " << getSecondsFrom() << " milliseconds: " << getMillisecondsFrom();
		throw Exception( "TimeRangeFilter::fillInAndValidateTime_", stringStream.str() );
	}
	
	if( !TimeSupport::validTime( getHoursTo(), getMinutesTo(), getSecondsTo(), getMillisecondsTo() ) )
	{
		stringstream stringStream;
		stringStream << "Time to is not valid, hours: " << getHoursTo() << " minutes: " << getMinutesTo() << " seconds: " << getSecondsTo() << " milliseconds: " << getMillisecondsTo();
		throw Exception( "TimeRangeFilter::fillInAndValidateTime_", stringStream.str() );
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________


