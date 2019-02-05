/*
 *  DateSupport.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 3.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "DateSupport.h"

#include <sstream>
#include <iomanip>
#include <ctime>

#include "Exception.h"

using namespace ObjectCube;
using namespace std;

//____________________________________________________________________________________________________________________________________________________________________________________

int DateSupport::minimumYear_ = 1900;  //Due to tm struct: http://www.cplusplus.com/reference/clibrary/ctime/tm/
int DateSupport::daysInMonth_[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
//____________________________________________________________________________________________________________________________________________________________________________________

int DateSupport::getMinimumYear()
{
	return minimumYear_;
}
//____________________________________________________________________________________________________________________________________________________________________________________

bool DateSupport::validDate( int year, int month, int dayOfMonth )  
{
	if( year < minimumYear_ )
	{
		return false;
	}
	if( month < 1 || month > 12 )
	{
		return false;
	}
	try //lasetDayOfMonth can throw exceptions.  This function should not.
	{
		if( dayOfMonth < 1 || dayOfMonth > DateSupport::lastDayOfMonth( year, month ) )
		{
			return false;
		}
	}
	catch (...) 
	{
		return false;
	}
	
	return true;
}
//____________________________________________________________________________________________________________________________________________________________________________________

string DateSupport::toString( int year, int month, int dayOfMonth )
{
	stringstream stringStream, ssYear, ssMonth, ssDayOfMonth;
	
	//Creating correct sized and zero filled versions
	ssYear << setw(4) << setfill('0') << right << year;
	ssMonth << setw(2) << setfill('0') << right << month;
	ssDayOfMonth << setw(2) << setfill('0') << right << dayOfMonth;
	
	stringStream << ssYear.str() << "-" << ssMonth.str() << "-" << ssDayOfMonth.str();
	return stringStream.str();
}
//____________________________________________________________________________________________________________________________________________________________________________________

// http://en.wikipedia.org/wiki/Leap_year#Gregorian_calendar

bool DateSupport::isALeapYear( int year )
{
	if( year <= 0 )
	{
		throw Exception( "DateSupport::isALeapYear", "A non-positive number in year", year );
	}
	if( !(year % 400) || ( !(year % 4) && year % 100 ) )
	{
		return true;
	}
	return false;
}
//____________________________________________________________________________________________________________________________________________________________________________________

int DateSupport::lastDayOfMonth( int year, int month )
{
	if( year <= 0 )
	{
		throw Exception( "DateSupport::lastDayOfMonth", "A non-positive number in year", year );
	}
	if( month < 1 || month > 12 )
	{
		throw Exception( "DateSupport::lastDayOfMonth", "Illegal month", month );
	}
	return daysInMonth_[month - 1] + ( month == 2 && DateSupport::isALeapYear( year ) ? 1 : 0 );
}
//____________________________________________________________________________________________________________________________________________________________________________________

// The algorithm is from: http://www.faqs.org/faqs/calendars/faq/part1/index.html (section 2.6)
// This only supports Gregorian dates

int DateSupport::dayOfWeek( int year, int month, int day )
{
	int a = ( 14 - month ) / 12;
	int y = year - a;
	int m = month + 12 * a - 2;
	return ( day + y + y/4 - y/100 + y/400 + (31*m)/12 ) % 7;
}
//____________________________________________________________________________________________________________________________________________________________________________________

bool DateSupport::weekend( int year, int month, int day )
{
	if( DateSupport::dayOfWeek( year, month, day ) == SATURDAY || DateSupport::dayOfWeek( year, month, day ) == SUNDAY )
	{
		return true;
	}
	return false;
}
//____________________________________________________________________________________________________________________________________________________________________________________

// Uses the ISO8601 standard.
// Weeks start on monday
// http://en.wikipedia.org/wiki/Seven-day_week#Week_numbering
// 1 Gregorian calendar year = 52 weeks + 1 day (2 days in a leap year).  The range is therefore 1-53.

int DateSupport::weekOfYear( int year, int month, int day )
{
	int firstDayOfYear = DateSupport::dayOfWeek( year, 1, 1 );
	
	if( ( firstDayOfYear > THURSDAY || firstDayOfYear == SUNDAY ) 
		&& month == 1 && day < 4 )  //The last week of the year before
	{
		return DateSupport::weekOfYear( year - 1, 12, 31 );
	}
	
	int daysInFirstWeek = 8 - firstDayOfYear;
	return 1.99 + ( DateSupport::daysBetween( year, 1, 1, year, month, day ) - daysInFirstWeek ) / 7;
}
//____________________________________________________________________________________________________________________________________________________________________________________

int DateSupport::daysBetween( int yearFrom, int monthFrom, int dayFrom, int yearTo, int monthTo, int dayTo )
{
	tm dateFrom = { 0, 0, 0, dayFrom, monthFrom - 1, yearFrom - minimumYear_, 0, 0};
	tm dateTo = { 0, 0, 0, dayTo, monthTo - 1, yearTo - minimumYear_, 0, 0 }; 
	
	time_t timeFrom = mktime( &dateFrom );
	time_t timeTo = mktime( &dateTo );
		
	if( timeFrom == -1 || timeTo == -1 )
	{
		throw Exception( "DateSupport::daysBetween", "Invalid date in input!" );
	}
	
	return difftime( timeTo, timeFrom ) / 86400;
}
//____________________________________________________________________________________________________________________________________________________________________________________

int DateSupport::quarter( int year, int month, int day )
{
	if( DateSupport::daysBetween( year, month, day, year, 4, 1 ) > 0 )
	{
		return 1;
	}
	if( DateSupport::daysBetween( year, month, day, year, 7, 1 ) > 0 )
	{
		return 2;
	}
	if( DateSupport::daysBetween( year, month, day, year, 10, 1 ) > 0 )
	{
		return 3;
	}
	return 4;
}
//____________________________________________________________________________________________________________________________________________________________________________________





























