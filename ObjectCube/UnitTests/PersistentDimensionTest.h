/*
 *  PersistentDimensionTest.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 20.2.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>

using namespace CppUnit;
using namespace std;

#ifndef ObjectCube_DIMENSION_HIERARCHY_TEST_
#define ObjectCube_DIMENSION_HIERARCHY_TEST_

namespace ObjectCube
{	
	class PersistentDimensionTest : public TestFixture
	{
		CPPUNIT_TEST_SUITE( PersistentDimensionTest );

		//Canned
		#ifdef OC_CANNED
		CPPUNIT_TEST( testAddNodeCanned );
		CPPUNIT_TEST( testRemoveBranchCanned );
		#endif
		
		//SQLite
		#ifdef OC_SQLITE
		CPPUNIT_TEST( testAddNodeSQLite );
		CPPUNIT_TEST( testFetchDimensionSQLite );
		CPPUNIT_TEST( testRemoveBranchSQLite );
		#endif
		
		//MonetDB
		#ifdef OC_MONETDB
		CPPUNIT_TEST( testAddNodeMonetDB );
		CPPUNIT_TEST( testFetchDimensionMonetDB );
		CPPUNIT_TEST( testRemoveBranchMonetDB );
		#endif
		
		//Oracle
		#ifdef OC_ORACLE
		CPPUNIT_TEST( testAddNodeOracle );
		CPPUNIT_TEST( testFetchDimensionOracle );
		CPPUNIT_TEST( testRemoveBranchOracle );
		#endif
		
		
		CPPUNIT_TEST_SUITE_END();
		 
		
	public:
		//Canned
		void testAddNodeCanned();
		void testRemoveBranchCanned();
		
		//SQLite
		void testAddNodeSQLite();
		void testRemoveBranchSQLite();
		void testFetchDimensionSQLite();
		
		//MonetDB
		void testAddNodeMonetDB();
		void testRemoveBranchMonetDB();
		void testFetchDimensionMonetDB();
		
		//Oracle
		void testAddNodeOracle();
		void testRemoveBranchOracle();
		void testFetchDimensionOracle();
		
		
		void setUp();
		void tearDown();
		
	protected:
		string hierarchyRootName_;
		string hierarchyChildNodeName_;
		string hierarchyChildChildNodeName_;
		
	private:
		void testAddNode_();
		void testRemoveBranch_();
		void testFetchDimension_();
		
	};
	
}

#endif
