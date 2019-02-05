/*
 *  ObjectTest.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 16.2.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */


#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace CppUnit;

#ifndef ObjectCube_OBJECT_TEST_
#define ObjectCube_OBJECT_TEST_

namespace ObjectCube
{
	
	class ObjectTest : public TestFixture
	{
		CPPUNIT_TEST_SUITE( ObjectTest );
		
		//Canned
		#ifdef OC_CANNED
		CPPUNIT_TEST( testFetchCanned );
		CPPUNIT_TEST( testFetchNameCanned );	
		CPPUNIT_TEST( testCreateCanned );
		CPPUNIT_TEST( testAddTagCanned );
		CPPUNIT_TEST( testRemoveTagCanned );
		CPPUNIT_TEST( testHasUserTagsCanned );
		#endif
		
		//SQLite
		#ifdef OC_SQLITE
		CPPUNIT_TEST( testFetchSQLite );
		CPPUNIT_TEST( testFetchNameSQLite );
		CPPUNIT_TEST( testCreateSQLite );
		CPPUNIT_TEST( testAddTagSQLite );
		CPPUNIT_TEST( testRemoveTagSQLite );
		CPPUNIT_TEST( testHasUserTagsSQLite );
		CPPUNIT_TEST( testEraseSQLite );
		#endif
		
		//MonetDB
		#ifdef OC_MONETDB
		CPPUNIT_TEST( testFetchMonetDB );
		CPPUNIT_TEST( testFetchNameMonetDB );
		CPPUNIT_TEST( testCreateMonetDB );
		CPPUNIT_TEST( testAddTagMonetDB );
		CPPUNIT_TEST( testRemoveTagMonetDB );
		CPPUNIT_TEST( testHasUserTagsMonetDB );
		CPPUNIT_TEST( testEraseMonetDB );
		#endif
		
		//Oracle
		#ifdef OC_ORACLE
		CPPUNIT_TEST( testFetchOracle );
		CPPUNIT_TEST( testFetchNameOracle );
		CPPUNIT_TEST( testCreateOracle );
		CPPUNIT_TEST( testAddTagOracle );
		CPPUNIT_TEST( testRemoveTagOracle );
		CPPUNIT_TEST( testHasUserTagsOracle );
		CPPUNIT_TEST( testEraseOracle );
		#endif
		
		
		CPPUNIT_TEST_SUITE_END();
		
	public:
		//Canned
		void testFetchCanned();
		void testFetchNameCanned();
		void testCreateCanned();
		void testAddTagCanned();
		void testRemoveTagCanned();
		void testHasUserTagsCanned();
		
		//SQLite
		void testFetchSQLite();
		void testFetchNameSQLite();
		void testCreateSQLite();
		void testAddTagSQLite();
		void testRemoveTagSQLite();
		void testHasUserTagsSQLite();		
		void testEraseSQLite();
		
		//MonetDB
		void testFetchMonetDB();
		void testFetchNameMonetDB();
		void testCreateMonetDB();
		void testAddTagMonetDB();
		void testRemoveTagMonetDB();
		void testHasUserTagsMonetDB();		
		void testEraseMonetDB();		
		
		//Oracle
		void testFetchOracle();
		void testFetchNameOracle();
		void testCreateOracle();
		void testAddTagOracle();
		void testRemoveTagOracle();
		void testHasUserTagsOracle();		
		void testEraseOracle();		
		
				
		void setUp();
		void tearDown();

	private:
		void testFetch_();
		void testFetchName_();
		void testCreate_();
		void testAddTag_( int upperLeftX = 0, int upperLeftY = 100, int lowerRightX = 100, int lowerRightY = 0 );
		void testRemoveTag_();
		void testHasUserTags_( int id );
		void testErase_( int alphanumericalId, int numericalId );
		
	};
	
}

#endif