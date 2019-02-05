/*
 *  StateObjectTest.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 26.8.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_STATE_OBJECT_TEST_
#define ObjectCube_STATE_OBJECT_TEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace CppUnit;

namespace ObjectCube
{	
	class StateObjectTest : public TestFixture
	{
		CPPUNIT_TEST_SUITE( StateObjectTest );
		
		//Canned
	//	CPPUNIT_TEST( testGetTagsByTagSetIdCanned ); The implementation for canned state is lacking
		//SQLite
		#ifdef OC_SQLITE
		CPPUNIT_TEST( testGetTagsByTagSetIdSQLite );
		#endif
		
		//MonetDB
		#ifdef OC_MONETDB
		CPPUNIT_TEST( testGetTagsByTagSetIdMonetDB );
		#endif
		
		//Oracle
		#ifdef OC_ORACLE
		CPPUNIT_TEST( testGetTagsByTagSetIdOracle );
		#endif
		
		
		CPPUNIT_TEST_SUITE_END();
		
	public:
		//Canned
		void testGetTagsByTagSetIdCanned();
			
		//SQLite
		void testGetTagsByTagSetIdSQLite();
		
		//MonetDB
		void testGetTagsByTagSetIdMonetDB();
		
		//Oracle
		void testGetTagsByTagSetIdOracle();

		
	private:
		void testGetTagsByTagSetId_( int tagId );
	};
	
}

#endif