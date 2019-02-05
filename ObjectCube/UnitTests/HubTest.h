/*
 *  HubTest.h
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

#ifndef ObjectCube_HUB_TEST_
#define ObjectCube_HUB_TEST_

namespace ObjectCube
{	
	class HubTest : public TestFixture
	{
		CPPUNIT_TEST_SUITE( HubTest );
		
		//Canned
		#ifdef OC_CANNED
		CPPUNIT_TEST( testGetHubCanned );
	//	CPPUNIT_TEST( testReloadHubCanned );
		CPPUNIT_TEST( testGetUncategorizedTagCanned );
		CPPUNIT_TEST( testAddDimensionCanned );
		CPPUNIT_TEST( testAddObjectCanned );
		CPPUNIT_TEST( testGetParentDimensionsAccessTypeCanned );  //Setja inn þegar búið er að laga memory meðhöndlun
		#endif
		
		//SQLite
		#ifdef OC_SQLITE
		CPPUNIT_TEST( testGetHubSQLite );
	//	CPPUNIT_TEST( testReloadHubSQLite );
		CPPUNIT_TEST( testGetUncategorizedTagSQLite );
		CPPUNIT_TEST( testAddTagSetSQLite );
		CPPUNIT_TEST( testAddObjectSQLite );
		CPPUNIT_TEST( testGetParentDimensionsAccessTypeSQLite );		
		CPPUNIT_TEST( testGetPlugins );		
	//To time consuming with any data
	//	CPPUNIT_TEST( testProcessAllObjects );		
	//	CPPUNIT_TEST( testProcessAllObjectsCallback );		
		CPPUNIT_TEST( testLoadDimensionsSQLite );
		#endif
		
		//MonetDB
		#ifdef OC_MONETDB
		CPPUNIT_TEST( testGetHubMonetDB );
	//	CPPUNIT_TEST( testReloadHubMonetDB );
		CPPUNIT_TEST( testGetUncategorizedTagMonetDB );
		CPPUNIT_TEST( testAddTagSetMonetDB );
		CPPUNIT_TEST( testAddObjectMonetDB );
		CPPUNIT_TEST( testGetParentDimensionsAccessTypeMonetDB );
		CPPUNIT_TEST( testGetPluginsMonetDB );
		CPPUNIT_TEST( testProcessAllObjectsMonetDB );
		CPPUNIT_TEST( testProcessAllObjectsCallbackMonetDB );
		CPPUNIT_TEST( testLoadDimensionsMonetDB );
		#endif
		
		//Oracle
		#ifdef OC_ORACLE
		CPPUNIT_TEST( testGetHubOracle );
		//	CPPUNIT_TEST( testReloadHubOracle );
		CPPUNIT_TEST( testGetUncategorizedTagOracle );
		CPPUNIT_TEST( testAddTagSetOracle );
		CPPUNIT_TEST( testAddObjectOracle );
		CPPUNIT_TEST( testGetParentDimensionsAccessTypeOracle );
		CPPUNIT_TEST( testGetPluginsOracle );
		CPPUNIT_TEST( testProcessAllObjectsOracle );
		CPPUNIT_TEST( testProcessAllObjectsCallbackOracle );
		CPPUNIT_TEST( testLoadDimensionsOracle );
		#endif
		
		
		CPPUNIT_TEST_SUITE_END();
		
	public:
		//Canned
		void testGetHubCanned();
		void testReloadHubCanned();
		void testGetUncategorizedTagCanned();
		void testAddDimensionCanned();
		void testAddObjectCanned();
		void testGetParentDimensionsAccessTypeCanned();
		
		//addFilter
		//removeAllFilters
		//getObjects
		//getDimension
		
		
		//SQLite
		void testGetHubSQLite();
		void testReloadHubSQLite();
		void testGetUncategorizedTagSQLite();
		void testAddTagSetSQLite();
		void testAddObjectSQLite();
		void testGetParentDimensionsAccessTypeSQLite();
		void testGetPlugins();
		void testProcessAllObjects();
		void testProcessAllObjectsCallback();
		void testLoadDimensionsSQLite();
		
		//MonetDB
		void testGetHubMonetDB();
		void testReloadHubMonetDB();
		void testGetUncategorizedTagMonetDB();
		void testAddTagSetMonetDB();
		void testAddObjectMonetDB();
		void testGetParentDimensionsAccessTypeMonetDB();
		void testGetPluginsMonetDB();
		void testProcessAllObjectsMonetDB();
		void testProcessAllObjectsCallbackMonetDB();
		void testLoadDimensionsMonetDB();
	
		//Oracle
		void testGetHubOracle();
		void testReloadHubOracle();
		void testGetUncategorizedTagOracle();
		void testAddTagSetOracle();
		void testAddObjectOracle();
		void testGetParentDimensionsAccessTypeOracle();
		void testGetPluginsOracle();
		void testProcessAllObjectsOracle();
		void testProcessAllObjectsCallbackOracle();
		void testLoadDimensionsOracle();

		
	private:
		void testGetHub_();
		void testReloadHub_();
		void testGetUncategorizedTag_();
		void testAddTagSet_( string name );
		void testAddObject_();
		void testGetParentTagSetsAccessType_();
		void testLoadTagSets_();
		void testGetPlugins_();
		void testProcessAllObjects_();
		void testProcessAllObjectsCallback_();
		
	};
	
}

#endif