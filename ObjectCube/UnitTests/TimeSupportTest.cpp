/*
 *  TimeSupportTest.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 5.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "TimeSupportTest.h"

#include <cppunit/extensions/HelperMacros.h>
#include <iostream>

#include "../LayerShared/TimeSupport.h"
#include "../Hub.h"
#include "../LayerShared/Exception.h"


using namespace ObjectCube;

CPPUNIT_TEST_SUITE_REGISTRATION( TimeSupportTest );

//____________________________________________________________________________________________________________________________________________________________________________________

//  Canned tests --------------------------------------------------------------------------------------------------------------------

void TimeSupportTest::testValidTimeCanned()
{
	cerr << "\nTimeSupportTest::testValidTimeCanned = ";

	CPPUNIT_ASSERT( TimeSupport::validTime(0, 0, 0, 0) == true );
	CPPUNIT_ASSERT( TimeSupport::validTime(23, 59, 59, 999) == true );
	CPPUNIT_ASSERT( TimeSupport::validTime(14, 21, 15, 1) == true );
	
	CPPUNIT_ASSERT( TimeSupport::validTime(24, 0, 0, 0) == false );
	CPPUNIT_ASSERT( TimeSupport::validTime(-1, 0, 0, 0) == false );
	CPPUNIT_ASSERT( TimeSupport::validTime(0, 60, 0, 0) == false );
	CPPUNIT_ASSERT( TimeSupport::validTime(0, -1, 0, 0) == false );
	CPPUNIT_ASSERT( TimeSupport::validTime(0, 0, 60, 0) == false );
	CPPUNIT_ASSERT( TimeSupport::validTime(0, 0, -1, 0) == false );
	CPPUNIT_ASSERT( TimeSupport::validTime(0, 0, 0, 1000) == false );
	CPPUNIT_ASSERT( TimeSupport::validTime(0, 0, 0, -1) == false );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TimeSupportTest::testToSQLStringCanned()
{
	cerr << "\nTimeSupportTest::testToSQLStringCanned = ";
	
	CPPUNIT_ASSERT( TimeSupport::toSQLString( 0, 1, 21, 4 ) == "strftime( \"%H:%M:%f\", '00:01:21.004' )" );
	CPPUNIT_ASSERT( TimeSupport::toSQLString( 23, 45, 0, 87 ) == "strftime( \"%H:%M:%f\", '23:45:00.087' )" );
}
//____________________________________________________________________________________________________________________________________________________________________________________

