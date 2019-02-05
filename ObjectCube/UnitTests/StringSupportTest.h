/*
 *  StringSupportTest.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 23.8.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */


#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace CppUnit;

#ifndef ObjectCube_STRING_SUPPORT_TEST_
#define ObjectCube_STRING_SUPPORT_TEST_

namespace ObjectCube
{
	
	class StringSupportTest : public TestFixture
	{
		CPPUNIT_TEST_SUITE( StringSupportTest );
		
		//Canned
		#ifdef OC_CANNED
		CPPUNIT_TEST( testNeutralizeControlSymbolsCanned );
		CPPUNIT_TEST( testRemoveControlSymbolNeutralizationCanned );
		CPPUNIT_TEST( testTrimCanned );
		CPPUNIT_TEST( testToSimpleAsciiCanned );
		#endif
		
		CPPUNIT_TEST_SUITE_END();
		
	public:
		
		//Canned
		void testNeutralizeControlSymbolsCanned();
		void testRemoveControlSymbolNeutralizationCanned();
		void testTrimCanned();
		void testToSimpleAsciiCanned();
		
	};
	
}

#endif