/*
 *  TagSetTest.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 17.2.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */


#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <string>

using namespace CppUnit;
using namespace std;

#ifndef ObjectCube_TAG_SET_TEST_
#define ObjectCube_TAG_SET_TEST_

namespace ObjectCube
{
	class TagSet;
	
	class TagSetTest : public TestFixture
	{
		CPPUNIT_TEST_SUITE( TagSetTest );

		//Canned
		#ifdef OC_CANNED
		CPPUNIT_TEST( testFetchCanned );
		CPPUNIT_TEST( testFetchNameCanned );
		CPPUNIT_TEST( testAddTagCanned );
		CPPUNIT_TEST( testDeleteTagCanned );
		CPPUNIT_TEST( testGetTagIdCanned );
		CPPUNIT_TEST( testGetTagNameCanned );
		CPPUNIT_TEST( testCreateHierarchyCanned );
		CPPUNIT_TEST( testDeleteHierarchyCanned );
		CPPUNIT_TEST( testGetHierarchyCanned );
		#endif
		
		//SQLite
		#ifdef OC_SQLITE
		CPPUNIT_TEST( testFetchSQLite );
		CPPUNIT_TEST( testFetchNameSQLite );
		CPPUNIT_TEST( testAddTagSQLite );
		CPPUNIT_TEST( testDeleteTagSQLite );
		CPPUNIT_TEST( testGetTagIdSQLite );
		CPPUNIT_TEST( testGetTagNameSQLite );
		CPPUNIT_TEST( testCreateHierarchySQLite );
		CPPUNIT_TEST( testDeleteHierarchySQLite );
		CPPUNIT_TEST( testGetHierarchySQLite );
		CPPUNIT_TEST( testEraseSQLite );
		CPPUNIT_TEST( testTypeAsStringSQLite );
		CPPUNIT_TEST( testAccessTypeAsStringSQLite );
		#endif
		
		//MonetDB
		#ifdef OC_MONETDB
		CPPUNIT_TEST( testFetchMonetDB );
		CPPUNIT_TEST( testFetchNameMonetDB );
		CPPUNIT_TEST( testAddTagMonetDB );
		CPPUNIT_TEST( testDeleteTagMonetDB );
		CPPUNIT_TEST( testGetTagIdMonetDB );
		CPPUNIT_TEST( testGetTagNameMonetDB );
		CPPUNIT_TEST( testCreateHierarchyMonetDB );
		CPPUNIT_TEST( testDeleteHierarchyMonetDB );
		CPPUNIT_TEST( testGetHierarchyMonetDB );
		CPPUNIT_TEST( testEraseMonetDB );
		CPPUNIT_TEST( testTypeAsStringMonetDB );
		CPPUNIT_TEST( testAccessTypeAsStringMonetDB );
		#endif
		
		//Oracle
	#ifdef OC_ORACLE
		CPPUNIT_TEST( testFetchOracle );
		CPPUNIT_TEST( testFetchNameOracle );
		CPPUNIT_TEST( testAddTagOracle );
		CPPUNIT_TEST( testDeleteTagOracle );
		CPPUNIT_TEST( testGetTagIdOracle );
		CPPUNIT_TEST( testGetTagNameOracle );
		CPPUNIT_TEST( testCreateHierarchyOracle );
		CPPUNIT_TEST( testDeleteHierarchyOracle );
		CPPUNIT_TEST( testGetHierarchyOracle );
		CPPUNIT_TEST( testEraseOracle );
		CPPUNIT_TEST( testTypeAsStringOracle );
		CPPUNIT_TEST( testAccessTypeAsStringOracle );
	#endif
		
		
		CPPUNIT_TEST_SUITE_END();
		
	public:
		//Canned
		void testFetchCanned();
		void testFetchNameCanned();
		void testAddTagCanned();
		void testDeleteTagCanned();
		void testGetTagIdCanned();
		void testGetTagNameCanned();
		void testCreateHierarchyCanned();
		void testDeleteHierarchyCanned();
		void testGetHierarchyCanned();
				
		//SQLite
		void testFetchSQLite();
		void testFetchNameSQLite();
		void testAddTagSQLite();
		void testDeleteTagSQLite();
		void testGetTagIdSQLite();
		void testGetTagNameSQLite();
		void testCreateHierarchySQLite();
		void testDeleteHierarchySQLite();
		void testGetHierarchySQLite();
		void testEraseSQLite();
		void testTypeAsStringSQLite();
		void testAccessTypeAsStringSQLite();

		//MonetDB
		void testFetchMonetDB();
		void testFetchNameMonetDB();
		void testAddTagMonetDB();
		void testDeleteTagMonetDB();
		void testGetTagIdMonetDB();
		void testGetTagNameMonetDB();
		void testCreateHierarchyMonetDB();
		void testDeleteHierarchyMonetDB();
		void testGetHierarchyMonetDB();
		void testEraseMonetDB();
		void testTypeAsStringMonetDB();
		void testAccessTypeAsStringMonetDB();
		
		//Oracle
		void testFetchOracle();
		void testFetchNameOracle();
		void testAddTagOracle();
		void testDeleteTagOracle();
		void testGetTagIdOracle();
		void testGetTagNameOracle();
		void testCreateHierarchyOracle();
		void testDeleteHierarchyOracle();
		void testGetHierarchyOracle();
		void testEraseOracle();
		void testTypeAsStringOracle();
		void testAccessTypeAsStringOracle();
				
				
		void setUp();
		void tearDown();

	private:
		void testFetch_( string name );
		void testFetchName_();
		void testAddTag_();
		void testDeleteTag_();
		void testGetTagId_( int tagId );
		void testGetTagName_( int tagId, string name );
		void testCreateHierarchy_();
		void testDeleteHierarchy_();
		void testGetHierarchy_( int tagId );
		void testErase_( string tagSetName );
		void testTypeAsString_();
		void testAccessTypeAsString_();
		
	};
	
}

#endif