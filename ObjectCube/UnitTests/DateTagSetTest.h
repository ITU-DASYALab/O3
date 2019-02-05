/*
 *  DateTagSetTest.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 12.4.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <string>

using namespace CppUnit;
using namespace std;

#ifndef ObjectCube_DATE_TAG_SET_TEST_
#define ObjectCube_DATE_TAG_SET_TEST_

namespace ObjectCube
{	
	class DateTagSetTest : public TestFixture
	{
		CPPUNIT_TEST_SUITE( DateTagSetTest );

		//Canned
		#ifdef OC_CANNED
		CPPUNIT_TEST( testFetchCanned );
		CPPUNIT_TEST( testCreateCanned );
		#endif
		
		//SQLite
		#ifdef OC_SQLITE
		CPPUNIT_TEST( testFetchSQLite );
		CPPUNIT_TEST( testCreateSQLite );
		#endif
		
		//MonetDB
		#ifdef OC_MONETDB
		CPPUNIT_TEST( testFetchMonetDB );
		CPPUNIT_TEST( testCreateMonetDB );
		#endif
		
		//Oracle
		#ifdef OC_ORACLE
		CPPUNIT_TEST( testFetchOracle );
		CPPUNIT_TEST( testCreateOracle );
		#endif
		
		
		CPPUNIT_TEST_SUITE_END();
	  
		
	public:
		//Canned
		void testFetchCanned();
		void testCreateCanned();
		
		//SQLite
		void testFetchSQLite();
		void testCreateSQLite();
		
		//MonetDB
		void testFetchMonetDB();
		void testCreateMonetDB();
		
		//Oracle
		void testFetchOracle();
		void testCreateOracle();		
		
		
		void setUp();
		void tearDown();
		
	private:
		void testFetch_( string tagSetName );
		void testCreate_( string tagSetName );
		
	};
	
}

#endif