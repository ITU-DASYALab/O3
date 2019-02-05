/*
 *  DateSupportTest.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 4.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "DateSupportTest.h"

#include <cppunit/extensions/HelperMacros.h>
#include <iostream>

#include "../LayerShared/DateSupport.h"
#include "../Hub.h"
#include "../LayerShared/Exception.h"


using namespace ObjectCube;

CPPUNIT_TEST_SUITE_REGISTRATION( DateSupportTest );

//____________________________________________________________________________________________________________________________________________________________________________________

//  Canned tests --------------------------------------------------------------------------------------------------------------------

void DateSupportTest::testValidDateCanned()
{
	cerr << "\nDateSupportTest::testValidDateCanned = ";
	
	CPPUNIT_ASSERT( DateSupport::validDate( 2000, 2, 29 ) == true );
	CPPUNIT_ASSERT( DateSupport::validDate( 2010, 5, 4 ) == true );
	CPPUNIT_ASSERT( DateSupport::validDate( 2010, 4, 31 ) == false );
	CPPUNIT_ASSERT( DateSupport::validDate( 2010, 9, 31 ) == false );
	CPPUNIT_ASSERT( DateSupport::validDate( 2010, 13, 31 ) == false );
	CPPUNIT_ASSERT( DateSupport::validDate( 2010, 0, 31 ) == false );
	CPPUNIT_ASSERT( DateSupport::validDate( 2010, -1, 31 ) == false );
	CPPUNIT_ASSERT( DateSupport::validDate( 2010, 5, -1 ) == false );
	CPPUNIT_ASSERT( DateSupport::validDate( 2010, 5, 0 ) == false );
	CPPUNIT_ASSERT( DateSupport::validDate( 2010, 5, 32 ) == false );
	CPPUNIT_ASSERT( DateSupport::validDate( 0, 5, 4 ) == false );
	CPPUNIT_ASSERT( DateSupport::validDate( -1, 5, 4 ) == false );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DateSupportTest::testIsALeapYear()
{
	cerr << "\nDateSupportTest::testIsALeapYear = ";
	
	//http://en.wikipedia.org/wiki/Leap_year#Gregorian_calendar
	
	CPPUNIT_ASSERT( DateSupport::isALeapYear( 2000 ) == true );
	CPPUNIT_ASSERT( DateSupport::isALeapYear( 2010 ) == false );
	CPPUNIT_ASSERT( DateSupport::isALeapYear( 1900 ) == false );
	CPPUNIT_ASSERT( DateSupport::isALeapYear( 2008 ) == true);
	CPPUNIT_ASSERT( DateSupport::isALeapYear( 2012 ) == true);
	
	//Errors
	CPPUNIT_ASSERT_THROW( DateSupport::isALeapYear( 0 ), ObjectCube::Exception );
	CPPUNIT_ASSERT_THROW( DateSupport::isALeapYear( -800 ), ObjectCube::Exception );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DateSupportTest::testLastDayOfMonth()
{
	cerr << "\nDateSupportTest::testLastDayOfMonth = ";
	
	CPPUNIT_ASSERT( DateSupport::lastDayOfMonth( 2010, 1 ) == 31 );
	CPPUNIT_ASSERT( DateSupport::lastDayOfMonth( 2010, 2 ) == 28 );
	CPPUNIT_ASSERT( DateSupport::lastDayOfMonth( 2010, 3 ) == 31 );
	CPPUNIT_ASSERT( DateSupport::lastDayOfMonth( 2010, 4 ) == 30 );
	CPPUNIT_ASSERT( DateSupport::lastDayOfMonth( 2010, 5 ) == 31 );
	CPPUNIT_ASSERT( DateSupport::lastDayOfMonth( 2010, 6 ) == 30 );
	CPPUNIT_ASSERT( DateSupport::lastDayOfMonth( 2010, 7 ) == 31 );
	CPPUNIT_ASSERT( DateSupport::lastDayOfMonth( 2010, 8 ) == 31 );
	CPPUNIT_ASSERT( DateSupport::lastDayOfMonth( 2010, 9 ) == 30 );
	CPPUNIT_ASSERT( DateSupport::lastDayOfMonth( 2010, 10 ) == 31 );
	CPPUNIT_ASSERT( DateSupport::lastDayOfMonth( 2010, 11 ) == 30 );
	CPPUNIT_ASSERT( DateSupport::lastDayOfMonth( 2010, 12 ) == 31 );
	
	//Leap year
	CPPUNIT_ASSERT( DateSupport::lastDayOfMonth( 2000, 2 ) == 29 );
	CPPUNIT_ASSERT( DateSupport::lastDayOfMonth( 2012, 2 ) == 29 );
	
	//Errors
	CPPUNIT_ASSERT_THROW( DateSupport::lastDayOfMonth( 2010, 13 ), ObjectCube::Exception );
	CPPUNIT_ASSERT_THROW( DateSupport::lastDayOfMonth( 2010, 0 ), ObjectCube::Exception );
	CPPUNIT_ASSERT_THROW( DateSupport::lastDayOfMonth( 2011, -1 ), ObjectCube::Exception );
	CPPUNIT_ASSERT_THROW( DateSupport::lastDayOfMonth( 0, 1 ), ObjectCube::Exception );
	CPPUNIT_ASSERT_THROW( DateSupport::lastDayOfMonth( -100, 1 ), ObjectCube::Exception );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DateSupportTest::testDayOfWeek()
{
	cerr << "\nDateSupportTest::testDayOfWeek = ";

	CPPUNIT_ASSERT( DateSupport::dayOfWeek( 2010, 5, 14 ) == DateSupport::FRIDAY );
	CPPUNIT_ASSERT( DateSupport::dayOfWeek( 2010, 1, 1 ) == DateSupport::FRIDAY );
	CPPUNIT_ASSERT( DateSupport::dayOfWeek( 2010, 12, 31 ) == DateSupport::FRIDAY );
	CPPUNIT_ASSERT( DateSupport::dayOfWeek( 2010, 6, 14 ) == DateSupport::MONDAY );
	CPPUNIT_ASSERT( DateSupport::dayOfWeek( 2010, 6, 13 ) == DateSupport::SUNDAY );
	CPPUNIT_ASSERT( DateSupport::dayOfWeek( 2010, 9, 7 ) == DateSupport::TUESDAY );
	CPPUNIT_ASSERT( DateSupport::dayOfWeek( 2010, 2, 24 ) == DateSupport::WEDNESDAY );
	CPPUNIT_ASSERT( DateSupport::dayOfWeek( 2010, 10, 28 ) == DateSupport::THURSDAY );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DateSupportTest::testWeekend()
{
	cerr << "\nDateSupportTest::testWeekend = ";

	CPPUNIT_ASSERT( DateSupport::weekend( 2010, 5, 14 ) == false );
	CPPUNIT_ASSERT( DateSupport::weekend( 2010, 5, 15 ) == true );
	CPPUNIT_ASSERT( DateSupport::weekend( 2010, 5, 16 ) == true );
	CPPUNIT_ASSERT( DateSupport::weekend( 2010, 5, 17 ) == false );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DateSupportTest::testWeekOfYear()
{
	cerr << "\nDateSupportTest::testWeekOfYear = ";
	
	CPPUNIT_ASSERT( DateSupport::weekOfYear( 2010, 1, 1 ) == 52 );
	CPPUNIT_ASSERT( DateSupport::weekOfYear( 2010, 1, 3 ) == 52 );
	CPPUNIT_ASSERT( DateSupport::weekOfYear( 2010, 1, 4 ) == 1 );
	CPPUNIT_ASSERT( DateSupport::weekOfYear( 2010, 1, 10 ) == 1 );
	CPPUNIT_ASSERT( DateSupport::weekOfYear( 2010, 1, 11 ) == 2 );
	CPPUNIT_ASSERT( DateSupport::weekOfYear( 2010, 1, 17 ) == 2 );
	CPPUNIT_ASSERT( DateSupport::weekOfYear( 2010, 1, 18 ) == 3 );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DateSupportTest::testDaysBetween()
{
	cerr << "\nDateSupportTest::testDaysBetween = ";
	
	CPPUNIT_ASSERT( DateSupport::daysBetween( 2010, 1, 1, 2010, 1, 1 ) == 0 );
	CPPUNIT_ASSERT( DateSupport::daysBetween( 2010, 1, 1, 2010, 1, 2 ) == 1 );
	CPPUNIT_ASSERT( DateSupport::daysBetween( 2010, 3, 31, 2010, 4, 1 ) == 1 );
	CPPUNIT_ASSERT( DateSupport::daysBetween( 2010, 2, 28, 2010, 3, 1 ) == 1 );
	CPPUNIT_ASSERT( DateSupport::daysBetween( 2010, 1, 1, 2010, 3, 1 ) == 59 );
	CPPUNIT_ASSERT( DateSupport::daysBetween(2008, 1, 1, 2008, 3, 1 ) == 60 );  //Leap year
	CPPUNIT_ASSERT( DateSupport::daysBetween(2010, 1, 1, 2010, 12, 31 ) == 364 );
	CPPUNIT_ASSERT( DateSupport::daysBetween(2008, 1, 1, 2010, 12, 31 ) == 1095 );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DateSupportTest::testQuarter()
{
	cerr << "\nDateSupportTest::testQuarter = ";

	CPPUNIT_ASSERT( DateSupport::quarter( 2010, 2, 1 ) == 1 );
	CPPUNIT_ASSERT( DateSupport::quarter( 2010, 3, 31 ) == 1 );
	CPPUNIT_ASSERT( DateSupport::quarter( 2010, 4, 1 ) == 2 );
	CPPUNIT_ASSERT( DateSupport::quarter( 2010, 6, 30 ) == 2 );
	CPPUNIT_ASSERT( DateSupport::quarter( 2010, 7, 1 ) == 3 );
	CPPUNIT_ASSERT( DateSupport::quarter( 2010, 9, 30 ) == 3 );
	CPPUNIT_ASSERT( DateSupport::quarter( 2010, 10, 1 ) == 4 );
	CPPUNIT_ASSERT( DateSupport::quarter( 2010, 12, 31 ) == 4 );
}
//____________________________________________________________________________________________________________________________________________________________________________________


