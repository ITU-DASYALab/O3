/*
 *  DateRangeFilter.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 3.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "DateRangeFilter.h"

#include <sstream>
#include <iomanip>
#include <time.h>

#include "../LayerShared/SharedDefinitions.h"
#include "../LayerShared/Exception.h"
#include "../LayerShared/DateSupport.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

DateRangeFilter::DateRangeFilter()
{
	init_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

DateRangeFilter::DateRangeFilter( int tagSetId )
: Filter( tagSetId )
{
	init_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

DateRangeFilter::DateRangeFilter( int yearFrom, int tagSetId )  // yearFrom-01-01 - current date
: Filter( tagSetId )
{
	init_();	
	
	setYearFrom( yearFrom );
}
//____________________________________________________________________________________________________________________________________________________________________________________

DateRangeFilter::DateRangeFilter( int yearFrom, int yearTo, int tagSetId ) // yearFrom-01-01 - yearTo-12-lastDayOfMonth
: Filter( tagSetId )
{
	init_();
	
	setYearFrom( yearFrom );
	
	setYearTo( yearTo );
}
//____________________________________________________________________________________________________________________________________________________________________________________

DateRangeFilter::DateRangeFilter( int yearFrom, int monthFrom, int yearTo, int monthTo, int tagSetId ) // yearFrom-monthFrom-01 - yearTo-monthTo-lastDayOfMonth
: Filter( tagSetId )
{
	init_();
	
	setYearFrom( yearFrom );
	setMonthFrom( monthFrom );
	
	setYearTo( yearTo );
	setMonthTo( monthTo );
}
//____________________________________________________________________________________________________________________________________________________________________________________

DateRangeFilter::DateRangeFilter( int yearFrom, int monthFrom, int dayOfMonthFrom, int yearTo, int monthTo, int dayOfMonthTo, int tagSetId )
: Filter( tagSetId )
{
	init_();
	
	setYearFrom( yearFrom );
	setMonthFrom( monthFrom );
	setDayOfMonthFrom( dayOfMonthFrom );
	
	setYearTo( yearTo );
	setMonthTo( monthTo );	
	setDayOfMonthTo( dayOfMonthTo );
}
//____________________________________________________________________________________________________________________________________________________________________________________

DateRangeFilter::~DateRangeFilter()
{
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DateRangeFilter::init_()
{
	setTypeId_( Filter::DATE_RANGE_FILTER );

	yearFrom_ = INVALID_VALUE;
	monthFrom_ = INVALID_VALUE;
	dayOfMonthFrom_ = INVALID_VALUE;
	
	yearTo_ = INVALID_VALUE;
	monthTo_ = INVALID_VALUE;
	dayOfMonthTo_ = INVALID_VALUE;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DateRangeFilter::setYearFrom( int year )
{
	yearFrom_ = year;
	setNullStatus_( getYearFrom() == INVALID_VALUE );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DateRangeFilter::setMonthFrom( int month )
{
	monthFrom_ = month;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DateRangeFilter::setDayOfMonthFrom( int dayOfMonth )
{
	dayOfMonthFrom_ = dayOfMonth;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DateRangeFilter::setYearTo( int year )
{
	yearTo_ = year;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DateRangeFilter::setMonthTo( int month )
{
	monthTo_ = month;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DateRangeFilter::setDayOfMonthTo( int dayOfMonth )
{
	dayOfMonthTo_ = dayOfMonth;
}
//____________________________________________________________________________________________________________________________________________________________________________________

Filter& DateRangeFilter::operator=( const Filter& filter )
{
	assignValues_( filter );
	const DateRangeFilter* drFilter = dynamic_cast<const DateRangeFilter*>( &filter );
	
	setYearFrom( drFilter->getYearFrom() );
	setMonthFrom( drFilter->getMonthFrom() );
	setDayOfMonthFrom( drFilter->getDayOfMonthFrom() );
	
	setYearTo( drFilter->getYearTo() );
	setMonthTo( drFilter->getMonthTo() );
	setDayOfMonthTo( drFilter->getDayOfMonthTo() );
	
	return *this;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DateRangeFilter::fillInAndValidateValues()
{
	if( getYearFrom() == INVALID_VALUE )
	{
		throw Exception( "DateRangeFilter::fillInAndValidateDates_", "Year from was not set!" );
	}
	
	if( getMonthFrom() == INVALID_VALUE )
	{
		setMonthFrom( 1 );  //January
	}
	if( getDayOfMonthFrom() == INVALID_VALUE )
	{
		setDayOfMonthFrom( 1 ); //First day of month
	}
	
	time_t rawtime;
	tm* timeinfo;
	
	time( &rawtime );
	timeinfo = localtime( &rawtime );	
	
	if( getYearTo() == INVALID_VALUE )
	{
		setYearTo( timeinfo->tm_year + DateSupport::getMinimumYear() ); 
	}
	
	if( getMonthTo() == INVALID_VALUE )
	{
		setMonthTo( 12 ); //December
	}
	if( getDayOfMonthTo() == INVALID_VALUE )
	{  //Set it to the last day of the month
		setDayOfMonthTo( DateSupport::lastDayOfMonth( getYearTo(), getMonthTo() ) );
	}
	
	//Validation
	if( !DateSupport::validDate( getYearFrom(), getMonthFrom(), getDayOfMonthFrom() ) )
	{
		stringstream stringStream;
		stringStream << "Date from is not valid, year: " << getYearFrom() << " month: " << getMonthFrom() << " dayOfMonth: " << getDayOfMonthFrom();
		throw Exception( "DateRangeFilter::fillInAndValidateDates_", stringStream.str() );
	}
	
	if( !DateSupport::validDate( getYearTo(), getMonthTo(), getDayOfMonthTo() ) )
	{
		stringstream stringStream;
		stringStream << "Date to is not valid, year: " << getYearTo() << " month: " << getMonthTo() << " dayOfMonth: " << getDayOfMonthTo();
		throw Exception( "DateRangeFilter::fillInAndValidateDates_", stringStream.str() );
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________




