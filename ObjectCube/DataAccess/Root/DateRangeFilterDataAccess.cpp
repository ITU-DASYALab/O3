/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/

#include "DateRangeFilterDataAccess.h"

#include "../../LayerShared/SharedDefinitions.h"
#include "../../LayerShared/Exception.h"
#include "../../LayerShared/FilterCommon.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

DateRangeFilterDataAccess::DateRangeFilterDataAccess()
{
	setTypeId( FilterCommon::DATE_RANGE_FILTER );
	
	yearFrom_ = INVALID_VALUE;
	monthFrom_ = INVALID_VALUE;
	dayOfMonthFrom_ = INVALID_VALUE;
	
	yearTo_ = INVALID_VALUE;
	monthTo_ = INVALID_VALUE;
	dayOfMonthTo_ = INVALID_VALUE;
}
//____________________________________________________________________________________________________________________________________________________________________________________

DateRangeFilterDataAccess::~DateRangeFilterDataAccess()
{
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DateRangeFilterDataAccess::setYearFrom( int year )
{
	yearFrom_ = year;
	setNullStatus( getYearFrom() == INVALID_VALUE );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DateRangeFilterDataAccess::setMonthFrom( int month )
{
	monthFrom_ = month;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DateRangeFilterDataAccess::setDayOfMonthFrom( int dayOfMonth )
{
	dayOfMonthFrom_ = dayOfMonth;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DateRangeFilterDataAccess::setYearTo( int year )
{
	yearTo_ = year;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DateRangeFilterDataAccess::setMonthTo( int month )
{
	monthTo_ = month;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DateRangeFilterDataAccess::setDayOfMonthTo( int dayOfMonth )
{
	dayOfMonthTo_ = dayOfMonth;
}
//____________________________________________________________________________________________________________________________________________________________________________________

string DateRangeFilterDataAccess::getSelectionPredicate_()
{	
	throw Exception( "DateRangeFilterDataAccess::getSelectionPredicate_", "This is only implemented in DB specific classes" );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

string DateRangeFilterDataAccess::getFiltrationPredicate_()
{
	throw Exception( "DateRangeFilterDataAccess::getFiltrationPredicate_", "This is only implemented in DB specific classes" );		
}
//____________________________________________________________________________________________________________________________________________________________________________________


