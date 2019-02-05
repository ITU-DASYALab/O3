/*
 *  TimeSupportTest.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 5.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace CppUnit;

#ifndef ObjectCube_TIME_SUPPORT_TEST_
#define ObjectCube_TIME_SUPPORT_TEST_

namespace ObjectCube
{
	
	class TimeSupportTest : public TestFixture
	{
		CPPUNIT_TEST_SUITE( TimeSupportTest );
		
		//Canned
		#ifdef OC_CANNED
		CPPUNIT_TEST( testValidTimeCanned );
		CPPUNIT_TEST( testToSQLStringCanned );
		#endif
		
		CPPUNIT_TEST_SUITE_END();
		
	public:
		
		//Canned
		void testValidTimeCanned();
		void testToSQLStringCanned();
		
	};
	
}

#endif