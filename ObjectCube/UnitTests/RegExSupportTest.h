/*
 *  RegExSupportTest.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 6.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace CppUnit;

#ifndef ObjectCube_REGEX_SUPPORT_TEST_
#define ObjectCube_REGEX_SUPPORT_TEST_

namespace ObjectCube
{
	
	class RegExSupportTest : public TestFixture
	{
		CPPUNIT_TEST_SUITE( RegExSupportTest );
		
		//Canned
		#ifdef OC_CANNED
		CPPUNIT_TEST( testPatternFoundCanned );
		#endif
		
		CPPUNIT_TEST_SUITE_END();
		
	public:
		
		//Canned
		void testPatternFoundCanned();
		
	};
	
}

#endif