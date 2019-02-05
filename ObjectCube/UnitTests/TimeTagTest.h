/*
 *  TimeTagTest.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 12.4.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace CppUnit;

#ifndef ObjectCube_TIME_TAG_TEST_
#define ObjectCube_TIME_TAG_TEST_

namespace ObjectCube
{
	
	class TimeTagTest : public TestFixture
	{
		CPPUNIT_TEST_SUITE( TimeTagTest );

		//Canned
		#ifdef OC_CANNED
		CPPUNIT_TEST( testFetchByIdCanned );
		CPPUNIT_TEST( testFetchByDimensionIdAndNumberCanned );
		CPPUNIT_TEST( testInUseCanned );
		#endif	
		
		//SQLite
		#ifdef OC_SQLITE
		CPPUNIT_TEST( testFetchByIdSQLite );
		CPPUNIT_TEST( testFetchByDimensionIdAndNumberSQLite );
		CPPUNIT_TEST( testInUseSQLite );
		#endif
		
		//MonetDB
		#ifdef OC_MONETDB
		CPPUNIT_TEST( testFetchByIdMonetDB );
		CPPUNIT_TEST( testFetchByDimensionIdAndNumberMonetDB );
		CPPUNIT_TEST( testInUseMonetDB );
		#endif
		
		//Oracle
		#ifdef OC_ORACLE
		CPPUNIT_TEST( testFetchByIdOracle );
		CPPUNIT_TEST( testFetchByDimensionIdAndNumberOracle );
		CPPUNIT_TEST( testInUseOracle );
		#endif
		
		CPPUNIT_TEST_SUITE_END();
		
	public:
		//Canned
		void testFetchByIdCanned();
		void testFetchByDimensionIdAndNumberCanned();
		void testInUseCanned();
		
		//SQLite
		void testFetchByIdSQLite();
		void testFetchByDimensionIdAndNumberSQLite();
		void testInUseSQLite();
		
		//MonetDB
		void testFetchByIdMonetDB();
		void testFetchByDimensionIdAndNumberMonetDB();
		void testInUseMonetDB();
		
		//Oracle
		void testFetchByIdOracle();
		void testFetchByDimensionIdAndNumberOracle();
		void testInUseOracle();
		
		void setUp();
		void tearDown();
		
	private:
		void testFetchById_( int id );
		void testFetchByTagSetIdAndTime_( int id );
		void testInUse_();
	};
	
}

#endif