/*
 *  NumericalTagTest.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 30.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace CppUnit;

#ifndef ObjectCube_NUMERICAL_TAG_TEST_
#define ObjectCube_NUMERICAL_TAG_TEST_

namespace ObjectCube
{
	
	class NumericalTagTest : public TestFixture
	{
		CPPUNIT_TEST_SUITE( NumericalTagTest );

		//Canned
		#ifdef OC_CANNED
		CPPUNIT_TEST( testFetchByIdCanned );
		CPPUNIT_TEST( testFetchByDimensionIdAndNumberCanned );
		CPPUNIT_TEST( testCreateCanned );
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
		void testCreateCanned();  //Should only be done through a dimension, remove
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
		void testFetchByTagSetIdAndNumber_( int tagId );
		void testInUse_();
		
		
	};
	
}

#endif