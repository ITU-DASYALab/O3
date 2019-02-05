/*
 *  VirtualHierarchyNodeTest.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 5.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <string>

using namespace CppUnit;
using namespace std;

#ifndef ObjectCube_VIRTUAL_HIERARCHY_NODE_TEST_
#define ObjectCube_VIRTUAL_HIERARCHY_NODE_TEST_

namespace ObjectCube
{	
	class VirtualHierarchyNodeTest : public TestFixture
	{
		CPPUNIT_TEST_SUITE( VirtualHierarchyNodeTest );

		//Canned
		#ifdef OC_CANNED
		CPPUNIT_TEST( testGetBranchCanned );
		#endif
		
		CPPUNIT_TEST_SUITE_END();
		
	public:
		//Canned
		void testGetBranchCanned();
		
	};
	
}

#endif