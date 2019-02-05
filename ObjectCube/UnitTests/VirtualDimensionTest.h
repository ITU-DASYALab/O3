/*
 *  VirtualDimensionTest.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 6.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>

using namespace CppUnit;
using namespace std;

#ifndef ObjectCube_VIRTUAL_DIMENSION_TEST_
#define ObjectCube_VIRTUAL_DIMENSION_TEST_

namespace ObjectCube
{	
	class VirtualDimensionTest : public TestFixture
	{
		CPPUNIT_TEST_SUITE( VirtualDimensionTest );

		//Canned
		#ifdef OC_CANNED
		CPPUNIT_TEST( testAddNodeCanned );
		#endif
		
		CPPUNIT_TEST_SUITE_END();
		
	public:
		//Canned
		void testAddNodeCanned();
		
	};
	
}

#endif