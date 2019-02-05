/*
 *  AlphanumericalTagTest.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 12.2.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */


#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <string>

using namespace CppUnit;
using namespace std;

#ifndef ObjectCube_ALPHANUMERICAL_TAG_TEST_
#define ObjectCube_ALPHANUMERICAL_TAG_TEST_

namespace ObjectCube
{
	
	class AlphanumericalTagTest : public TestFixture
	{
		CPPUNIT_TEST_SUITE( AlphanumericalTagTest );
		//Canned
		#ifdef OC_CANNED
		CPPUNIT_TEST( testFetchByIdCanned );
		CPPUNIT_TEST( testFetchByDimensionIdAndNameCanned );
		CPPUNIT_TEST( testCreateCanned );
		CPPUNIT_TEST( testInUseCanned );
		#endif
		
		//SQLite
		#ifdef OC_SQLITE
		CPPUNIT_TEST( testFetchByIdSQLite );
		CPPUNIT_TEST( testFetchByDimensionIdAndNameSQLite );
		CPPUNIT_TEST( testInUseSQLite );
		CPPUNIT_TEST( testControlCharactersHandlingSQLite );
		#endif
		
		//MonetDB
		#ifdef OC_MONETDB
		CPPUNIT_TEST( testFetchByIdMonetDB );
		CPPUNIT_TEST( testFetchByDimensionIdAndNameMonetDB );
		CPPUNIT_TEST( testInUseMonetDB );
		CPPUNIT_TEST( testControlCharactersHandlingMonetDB );
		CPPUNIT_TEST( testIcelandicCharactersMonetDB );
		#endif
		
		//Oracle
		#ifdef OC_ORACLE
		CPPUNIT_TEST( testFetchByIdOracle );
		CPPUNIT_TEST( testFetchByDimensionIdAndNameOracle );
		CPPUNIT_TEST( testInUseOracle );
		CPPUNIT_TEST( testControlCharactersHandlingOracle );
		#endif
		
		CPPUNIT_TEST_SUITE_END();
		
	public:
		//Canned
		void testFetchByIdCanned();
		void testFetchByDimensionIdAndNameCanned();
		void testCreateCanned();  //Should only be done through a dimension, remove
		void testInUseCanned();
				
		//SQLite
		void testFetchByIdSQLite();
		void testFetchByDimensionIdAndNameSQLite();
		void testInUseSQLite();
		void testControlCharactersHandlingSQLite();
		
		//MonetDB
		void testFetchByIdMonetDB();
		void testFetchByDimensionIdAndNameMonetDB();
		void testInUseMonetDB();
		void testControlCharactersHandlingMonetDB();
		void testIcelandicCharactersMonetDB();
		
		//Oracle
		void testFetchByIdOracle();
		void testFetchByDimensionIdAndNameOracle();
		void testInUseOracle();
		void testControlCharactersHandlingOracle();
		
		
		void setUp();
		void tearDown();
		
	private:
		void testFetchById_( int id, const string& tagName );
		void testFetchByDimensionIdAndName_( int id, const string& tagName );
		void testInUse_( const string& tagName );
		void testControlCharactersHandling_( const string& tagNamePrefix );
	};
	
}

#endif