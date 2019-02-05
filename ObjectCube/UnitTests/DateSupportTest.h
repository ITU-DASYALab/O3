/*
 *  DateSupportTest.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 4.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace CppUnit;

#ifndef ObjectCube_DATE_SUPPORT_TEST_
#define ObjectCube_DATE_SUPPORT_TEST_

namespace ObjectCube
{
	
	class DateSupportTest : public TestFixture
	{
		CPPUNIT_TEST_SUITE( DateSupportTest );
		
		//Canned
		#ifdef OC_CANNED
		CPPUNIT_TEST( testValidDateCanned );
		CPPUNIT_TEST( testIsALeapYear );
		CPPUNIT_TEST( testLastDayOfMonth );
		CPPUNIT_TEST( testDayOfWeek );
		CPPUNIT_TEST( testWeekend );
		CPPUNIT_TEST( testWeekOfYear );
		CPPUNIT_TEST( testDaysBetween );
		CPPUNIT_TEST( testQuarter );
		#endif
		
		CPPUNIT_TEST_SUITE_END();
		
	public:
		
		//Canned
		void testValidDateCanned();
		void testIsALeapYear();
		void testLastDayOfMonth();
		void testDayOfWeek();
		void testWeekend();
		void testWeekOfYear();
		void testDaysBetween();
		void testQuarter();
		
	};
	
}

#endif