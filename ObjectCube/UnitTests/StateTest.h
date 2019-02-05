/*
 *  StateTest.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 20.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */
#ifndef ObjectCube_STATE_TEST_
#define ObjectCube_STATE_TEST_

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

#include <vector>
#include <string>

using namespace CppUnit;
using namespace std;

namespace ObjectCube
{	
	class MultiDimensionalView;
	
	class StateTest : public TestFixture
	{
		CPPUNIT_TEST_SUITE( StateTest );
		
		//Canned
		#ifdef OC_CANNED
		CPPUNIT_TEST( testGetObjectsCanned );
		CPPUNIT_TEST( testGetFiltersCanned );
		CPPUNIT_TEST( testGetDimensionsCanned );
		#endif
		
		//SQLite
		#ifdef OC_SQLITE
		CPPUNIT_TEST( testGetObjectsSQLite );
		CPPUNIT_TEST( testAddFilterSQLite );
		CPPUNIT_TEST( testRemoveFilterSQLite );
		CPPUNIT_TEST( testRemoveAllFiltersSQLite );
		CPPUNIT_TEST( testGetDimensionSQLite );
		CPPUNIT_TEST( testGetObjectIdsSQLite );
		CPPUNIT_TEST( testGetParentNodeSQLite );
		CPPUNIT_TEST( testGetMultiDimensionalViewSQLite );
		#endif
		
		//MonetDB
		#ifdef OC_MONETDB
		CPPUNIT_TEST( testGetObjectsMonetDB );
		CPPUNIT_TEST( testAddFilterMonetDB );
		CPPUNIT_TEST( testRemoveFilterMonetDB );
		CPPUNIT_TEST( testRemoveAllFiltersMonetDB );
		CPPUNIT_TEST( testGetDimensionMonetDB );
		CPPUNIT_TEST( testGetObjectIdsMonetDB );
		CPPUNIT_TEST( testGetParentNodeMonetDB );
		CPPUNIT_TEST( testGetMultiDimensionalViewMonetDB );
		#endif
	
		//Oracle
		#ifdef OC_ORACLE
		CPPUNIT_TEST( testGetObjectsOracle );
		CPPUNIT_TEST( testAddFilterOracle );
		CPPUNIT_TEST( testRemoveFilterOracle );
		CPPUNIT_TEST( testRemoveAllFiltersOracle );
		CPPUNIT_TEST( testGetDimensionOracle );
		CPPUNIT_TEST( testGetObjectIdsOracle );
		CPPUNIT_TEST( testGetParentNodeOracle );
		#endif
		
		
		CPPUNIT_TEST_SUITE_END();
		
	public:
		//Canned
		void testGetObjectsCanned();
		void testGetFiltersCanned();
		void testGetDimensionsCanned();
		
		//SQLite
		void testGetObjectsSQLite();
		void testAddFilterSQLite();
		void testRemoveFilterSQLite();
		void testRemoveAllFiltersSQLite();
		void testGetDimensionSQLite();
		void testGetObjectIdsSQLite();
		void testGetParentNodeSQLite();
		void testGetMultiDimensionalViewSQLite();
		
		//MonetDB
		void testGetObjectsMonetDB();
		void testAddFilterMonetDB();
		void testRemoveFilterMonetDB();
		void testRemoveAllFiltersMonetDB();
		void testGetDimensionMonetDB();
		void testGetObjectIdsMonetDB();
		void testGetParentNodeMonetDB();
		void testGetMultiDimensionalViewMonetDB();
		
		//Oracle
		void testGetObjectsOracle();
		void testAddFilterOracle();
		void testRemoveFilterOracle();
		void testRemoveAllFiltersOracle();
		void testGetDimensionOracle();
		void testGetObjectIdsOracle();
		void testGetParentNodeOracle();
		
		
	private:
		void testGetObjects_( int tagId );
		void testAddFilter_( int tagId );
		void testRemoveFilter_( int tagId );
		void testRemoveAllFilters_( int tagId );
		void testGetDimension_();
		void testGetObjectIds_();
		void testGetParentNode_();
		void testGetMultiDimensionalView_();
		
		//Helpers
		void outputMultiDimensionalView_( MultiDimensionalView* mdv );
		bool generateKey_( string& key, const vector<unsigned int>& dimensionCellCounts, vector<unsigned int>& currCounts, unsigned int& currDimension );
		
	};
	
}

#endif