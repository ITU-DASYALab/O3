/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/


#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace CppUnit;

#ifndef ObjectCube_COMMONSQLITE_TEST_
#define ObjectCube_COMMONSQLITE_TEST_

namespace ObjectCube
{
	
	class CommonSQLiteTest : public TestFixture
	{
		CPPUNIT_TEST_SUITE( CommonSQLiteTest );
		
		//Canned
	#ifdef OC_SQLITE
		CPPUNIT_TEST( testToSQLStringCanned );
	#endif
		
		CPPUNIT_TEST_SUITE_END();
		
	public:
		
		//Canned
		void testToSQLStringCanned();
		
	};
	
}

#endif