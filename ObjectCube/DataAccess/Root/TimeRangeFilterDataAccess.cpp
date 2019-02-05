/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/

#include "TimeRangeFilterDataAccess.h"

#include "../../LayerShared/SharedDefinitions.h"
#include "../../LayerShared/Exception.h"
#include "../../LayerShared/FilterCommon.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

TimeRangeFilterDataAccess::TimeRangeFilterDataAccess()
{
	setTypeId( FilterCommon::TIME_RANGE_FILTER );
	
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

TimeRangeFilterDataAccess::~TimeRangeFilterDataAccess()
{
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TimeRangeFilterDataAccess::setHoursFrom( int hours )
{
	hoursFrom_ = hours;
	setNullStatus( getHoursFrom() == INVALID_VALUE || getHoursTo() == INVALID_VALUE );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TimeRangeFilterDataAccess::setMinutesFrom( int minutes )
{
	minutesFrom_ = minutes;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TimeRangeFilterDataAccess::setSecondsFrom( int seconds )
{
	secondsFrom_ = seconds;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TimeRangeFilterDataAccess::setMillisecondsFrom( int milliseconds )
{
	millisecondsFrom_ = milliseconds;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TimeRangeFilterDataAccess::setHoursTo( int hours )
{
	hoursTo_ = hours;
	setNullStatus( getHoursFrom() == INVALID_VALUE || getHoursTo() == INVALID_VALUE );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TimeRangeFilterDataAccess::setMinutesTo( int minutes )
{
	minutesTo_ = minutes;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TimeRangeFilterDataAccess::setSecondsTo( int seconds )
{
	secondsTo_ = seconds;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TimeRangeFilterDataAccess::setMillisecondsTo( int milliseconds )
{
	millisecondsTo_ = milliseconds;
}
//____________________________________________________________________________________________________________________________________________________________________________________

string TimeRangeFilterDataAccess::getSelectionPredicate_()
{
	throw Exception( "TimeRangeFilterDataAccess::getSelectionPredicate_", "This is only implemented in DB specific classes" );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

string TimeRangeFilterDataAccess::getFiltrationPredicate_()
{
	throw Exception( "TimeRangeFilterDataAccess::getFiltrationPredicate_", "This is only implemented in DB specific classes" );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

