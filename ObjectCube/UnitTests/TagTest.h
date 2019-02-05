/*
 *  TagTest.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 30.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace CppUnit;

#ifndef ObjectCube_TAG_TEST_
#define ObjectCube_TAG_TEST_

namespace ObjectCube
{
	
	class TagTest : public TestFixture
	{
		CPPUNIT_TEST_SUITE( TagTest );
		
		//Canned
		#ifdef OC_CANNED
		CPPUNIT_TEST( testFetchByIdCanned );
		#endif
		
		//SQLite
		#ifdef OC_SQLITE
		CPPUNIT_TEST( testFetchByIdSQLite );
		CPPUNIT_TEST( testTypeAsStringSQLite );
		#endif
		
		//MonetDB
		#ifdef OC_MONETDB
		CPPUNIT_TEST( testFetchByIdMonetDB );
		CPPUNIT_TEST( testTypeAsStringMonetDB );
		#endif
		
		//Oracle
		#ifdef OC_ORACLE
		CPPUNIT_TEST( testFetchByIdOracle );
		CPPUNIT_TEST( testTypeAsStringOracle );
		#endif
		
		CPPUNIT_TEST_SUITE_END();
		
	public:
		//Canned
		void testFetchByIdCanned();
				
		//SQLite
		void testFetchByIdSQLite();
		void testTypeAsStringSQLite();
		
		//MonetDB
		void testFetchByIdMonetDB();
		void testTypeAsStringMonetDB();
		
		//Oracle
		void testFetchByIdOracle();
		void testTypeAsStringOracle();

				
		void setUp();
		void tearDown();
		
	private:
		void testFetchById_( int id );
		void testTypeAsString_( int id );
	};
	
}

#endif