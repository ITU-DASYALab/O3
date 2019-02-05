/*
 *  TestHierarchyNode.h
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

#ifndef ObjectCube_HIERARCHY_NODE_TEST_
#define ObjectCube_HIERARCHY_NODE_TEST_

namespace ObjectCube
{	
	class PersistentHierarchyNodeTest : public TestFixture
	{
		CPPUNIT_TEST_SUITE( PersistentHierarchyNodeTest );

		//Canned
		#ifdef OC_CANNED
		CPPUNIT_TEST( testGetBranchCanned );
		#endif
		
		//SQLite
		#ifdef OC_SQLITE
		CPPUNIT_TEST( testGetBranchSQLite );
		#endif
		
		//MonetDB
		#ifdef OC_MONETDB
		CPPUNIT_TEST( testGetBranchMonetDB );
		#endif
		
		//Oracle
		#ifdef OC_ORACLE
		CPPUNIT_TEST( testGetBranchOracle );
		#endif
		
		
		CPPUNIT_TEST_SUITE_END();
		
		
	public:
		//Canned
		void testGetBranchCanned();
		
		//SQLite
		void testGetBranchSQLite();
		
		//MonetDB
		void testGetBranchMonetDB();
		
		//Oracle
		void testGetBranchOracle();
		
		
		void setUp();
		void tearDown();
	
	protected:
		string hierarchyRootName_;
		string hierarchyChildNodeName_;
		
	private:
		void testGetBranch_();
		
	};
	
}

#endif
