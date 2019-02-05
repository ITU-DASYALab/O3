/*
 *  HubTest.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 17.2.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "HubTest.h"

#include <cppunit/extensions/HelperMacros.h>

#include "../Hub.h"
#include "TestIds.h"
#include "../TagSet/TagSet.h"
#include "TagSetAssertionTraits.h"
#include "ObjectAssertionTraits.h"
#include "../LayerShared/HubCommon.h"
#include "../TagSet/AlphanumericalTagSet.h"
#include "../Tag/AlphanumericalTag.h"
#include "../LayerShared/SharedDefinitions.h"
#include "../Plugin/PluginCommon.h"

using namespace ObjectCube;

CPPUNIT_TEST_SUITE_REGISTRATION( HubTest );

//____________________________________________________________________________________________________________________________________________________________________________________

//  Canned tests --------------------------------------------------------------------------------------------------------------------

void HubTest::testGetHubCanned()
{
	cerr << "\nHubTest::testGetHubCanned = ";
	Hub::setDataAccessType( Hub::CANNED );
	
	Hub* hub = Hub::getHub();
	
	CPPUNIT_ASSERT( hub->getTagSets().size() > 0 );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void HubTest::testReloadHubCanned()
{
	cerr << "\nHubTest::testReloadHubCanned = ";
	Hub::setDataAccessType( Hub::CANNED );
	
	Hub::getHub()->instance_.reset( new Hub() );
	Hub::getHub()->init_();
	
	Hub* hub = Hub::getHub();  //This is a memory corruption/leakage test, there are no assertions
}
//____________________________________________________________________________________________________________________________________________________________________________________

void HubTest::testGetUncategorizedTagCanned()
{
	cerr << "\nHubTest::testGetUncategorizedTagCanned = ";
	Hub::setDataAccessType( Hub::CANNED );
	Hub* hub = Hub::getHub();
	
	const Tag* uncatTag = hub->getUncategorizedTag();
	
	AlphanumericalTag expected( HubCommon::getUncategorizedTagName() );
	expected.setId_( TEST_ALPHANUMERICAL_TAG_ID_CANNED );
	expected.setTagSetId_( TEST_ALPHANUMERICAL_TAG_SET_ID );
	
	CPPUNIT_ASSERT_EQUAL( *dynamic_cast<Tag*>( &expected ), *uncatTag );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void HubTest::testAddDimensionCanned()
{
	cerr << "\nHubTest::testAddDimensionCanned = ";
	Hub::setDataAccessType( Hub::CANNED );
	
	Hub* hub = Hub::getHub();
	AlphanumericalTagSet userDim("Yet another user dimension");
	TagSet* tagSet = hub->addTagSet( &userDim );
	
	CPPUNIT_ASSERT( tagSet->getId() != INVALID_VALUE );
	CPPUNIT_ASSERT_EQUAL( (int)TagSetCommon::USER, tagSet->getAccessId() );
	CPPUNIT_ASSERT_EQUAL( (int)TagSetCommon::ALPHANUMERICAL, tagSet->getTypeId() );
	
	TagSet* expected = hub->getTagSet( tagSet->getId() );
	CPPUNIT_ASSERT_EQUAL( *expected, *tagSet );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void HubTest::testAddObjectCanned()
{
	cerr << "\nHubTest::testAddObjectCanned = ";
	Hub::setDataAccessType( Hub::CANNED );
	
	Object created( "/Canned/UnitTest/img3.jpg" );
	Hub* hub = Hub::getHub();
	hub->addObject( created );
	
	CPPUNIT_ASSERT( created.getId() >= TEST_OBJECT_ID );
	/* Virkar í DB
	Object expected = Object::fetch( created.getId() );
	CPPUNIT_ASSERT_EQUAL( expected, created );
	 */
}
//____________________________________________________________________________________________________________________________________________________________________________________

void HubTest::testGetParentDimensionsAccessTypeCanned()
{
	cerr << "\nHubTest::testGetParentDimensionsAccessTypeCanned = ";
	Hub::setDataAccessType( Hub::CANNED );
	
	Hub* hub = Hub::getHub();
	const Tag* uncat = hub->getUncategorizedTag();
	
	int accessType = hub->getParentTagSetsAccessType( uncat );
	CPPUNIT_ASSERT_EQUAL( (int)TagSetCommon::SYSTEM, accessType );
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  SQLite tests --------------------------------------------------------------------------------------------------------------------

void HubTest::testGetHubSQLite()
{
	cerr << "\nHubTest::testGetHubSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testGetHub_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void HubTest::testReloadHubSQLite()
{
	cerr << "\nHubTest::testReloadHubSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );

	testReloadHub_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void HubTest::testGetUncategorizedTagSQLite()
{
	cerr << "\nHubTest::testGetUncategorizedTagSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testGetUncategorizedTag_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void HubTest::testAddTagSetSQLite()
{
	cerr << "\nHubTest::testAddTagSetSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testAddTagSet_( TEST_SQLITE_CLEANUP_PREFIX + " - yet another user dimension" );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void HubTest::testAddObjectSQLite()
{
	cerr << "\nHubTest::testAddObjectSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );

	testAddObject_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void HubTest::testGetParentDimensionsAccessTypeSQLite()
{
	cerr << "\nHubTest::testGetParentDimensionsAccessTypeSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testGetParentTagSetsAccessType_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void HubTest::testLoadDimensionsSQLite()
{
	cerr << "\nHubTest::testLoadDimensionsSQLite = ";
	//Forcing reload
	Hub* hub = Hub::getHub();
	hub->destroy();
	hub = Hub::getHub();
	
	testLoadTagSets_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void HubTest::testGetPlugins()
{
	cerr << "\nHubTest::testGetPlugins = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testGetPlugins_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void HubTest::testProcessAllObjects()
{
	cerr << "\nHubTest::testProcessAllObjects = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testProcessAllObjects_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void callbackFunction( int count )
{
	cerr << "\nFinished processing: " << count;
}

void HubTest::testProcessAllObjectsCallback()
{
	cerr << "\nHubTest::testProcessAllObjectsCallback  = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testProcessAllObjectsCallback_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  MonetDB tests --------------------------------------------------------------------------------------------------------------------

void HubTest::testGetHubMonetDB()
{
	cerr << "\nHubTest::testGetHubMonetDB  = ";
	Hub::setDataAccessType( Hub::MONETDB );
	
	testGetHub_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void HubTest::testReloadHubMonetDB()
{
	cerr << "\nHubTest::testReloadHubMonetDB  = ";
	Hub::setDataAccessType( Hub::MONETDB );

	testReloadHub_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void HubTest::testGetUncategorizedTagMonetDB()
{
	cerr << "\nHubTest::testGetUncategorizedTagMonetDB  = ";
	Hub::setDataAccessType( Hub::MONETDB );
	
	testGetUncategorizedTag_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void HubTest::testAddTagSetMonetDB()
{
	cerr << "\nHubTest::testAddTagSetMonetDB  = ";
	Hub::setDataAccessType( Hub::MONETDB );

	testAddTagSet_( TEST_MONETDB_CLEANUP_PREFIX + " - yet another user dimension" );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void HubTest::testAddObjectMonetDB()
{
	cerr << "\nHubTest::testAddObjectMonetDB  = ";
	Hub::setDataAccessType( Hub::MONETDB );

	testAddObject_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void HubTest::testGetParentDimensionsAccessTypeMonetDB()
{
	cerr << "\nHubTest::testGetParentDimensionsAccessTypeMonetDB  = ";
	Hub::setDataAccessType( Hub::MONETDB );
	
	testGetParentTagSetsAccessType_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void HubTest::testGetPluginsMonetDB()
{
	cerr << "\nHubTest::testGetPluginsMonetDB  = ";
	Hub::setDataAccessType( Hub::MONETDB );
	
	testGetPlugins_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void HubTest::testProcessAllObjectsMonetDB()
{
	cerr << "\nHubTest::testProcessAllObjectsMonetDB  = ";
	Hub::setDataAccessType( Hub::MONETDB );
	
	testProcessAllObjects_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void HubTest::testProcessAllObjectsCallbackMonetDB()
{
	cerr << "\nHubTest::testProcessAllObjectsCallbackMonetDB  = ";
	Hub::setDataAccessType( Hub::MONETDB );
	
	testProcessAllObjectsCallback_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void HubTest::testLoadDimensionsMonetDB()
{
	cerr << "\nHubTest::testLoadDimensionsMonetDB  = ";
	//Hub::setDataAccessType( Hub::CANNED );
	Hub* hub = Hub::getHub();
	hub->destroy();
	hub = Hub::getHub();
	
	testLoadTagSets_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Oracle tests --------------------------------------------------------------------------------------------------------------------

void HubTest::testGetHubOracle()
{
	cerr << "\nHubTest::testGetHubOracle  = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testGetHub_();	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void HubTest::testReloadHubOracle()
{
	cerr << "\nHubTest::testReloadHubOracle  = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testReloadHub_();	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void HubTest::testGetUncategorizedTagOracle()
{
	cerr << "\nHubTest::testGetUncategorizedTagOracle  = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testGetUncategorizedTag_();	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void HubTest::testAddTagSetOracle()
{
	cerr << "\nHubTest::testAddTagSetOracle  = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testAddTagSet_( TEST_ORACLE_CLEANUP_PREFIX + " - yet another user dimension" );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void HubTest::testAddObjectOracle()
{
	cerr << "\nHubTest::testAddObjectOracle  = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testAddObject_();	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void HubTest::testGetParentDimensionsAccessTypeOracle()
{
	cerr << "\nHubTest::testGetParentDimensionsAccessTypeOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testGetParentTagSetsAccessType_();	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void HubTest::testGetPluginsOracle()
{
	cerr << "\nHubTest::testGetPluginsOracle  = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testGetPlugins_();	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void HubTest::testProcessAllObjectsOracle()
{
	cerr << "\nHubTest::testProcessAllObjectsOracle  = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testProcessAllObjects_();	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void HubTest::testProcessAllObjectsCallbackOracle()
{
	cerr << "\nHubTest::testProcessAllObjectsCallbackOracle  = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testProcessAllObjectsCallback_();	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void HubTest::testLoadDimensionsOracle()
{
	cerr << "\nHubTest::testLoadDimensionsOracle  = ";
	//Hub::setDataAccessType( Hub::CANNED );
	Hub* hub = Hub::getHub();
	hub->destroy();
	hub = Hub::getHub();
	
	testLoadTagSets_();	
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Common --------------------------------------------------------------------------------------------------------------------

void HubTest::testGetHub_()
{
	Hub* hub = Hub::getHub();
	CPPUNIT_ASSERT( hub->getTagSets().size() > 0 );		
}
//____________________________________________________________________________________________________________________________________________________________________________________

void HubTest::testGetUncategorizedTag_()
{
	Hub* hub = Hub::getHub();
	const Tag* uncatTag = hub->getUncategorizedTag();
	
	CPPUNIT_ASSERT_EQUAL( uncatTag->valueAsString(), HubCommon::getUncategorizedTagName() );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void HubTest::testAddTagSet_( string name )
{
	Hub* hub = Hub::getHub();
	AlphanumericalTagSet userDim( name );
	TagSet* tagSet = hub->addTagSet( &userDim );
	
	CPPUNIT_ASSERT( tagSet->getId() != INVALID_VALUE );
	CPPUNIT_ASSERT_EQUAL( (int)TagSetCommon::USER, tagSet->getAccessId() );
	CPPUNIT_ASSERT_EQUAL( (int)TagSetCommon::ALPHANUMERICAL, tagSet->getTypeId() );
	
	TagSet* expected = hub->getTagSet( tagSet->getId() );
	CPPUNIT_ASSERT_EQUAL( *expected, *(dynamic_cast<TagSet*>( tagSet ) ) );
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void HubTest::testAddObject_()
{
	Object created( TestIds::TEST_OBJECT_PREFIX + "img5.jpg" );
	Hub* hub = Hub::getHub();
	hub->addObject( created );
	
	CPPUNIT_ASSERT( created.getId() > 0 );
	Object expected = Object::fetch( created.getId() );
	CPPUNIT_ASSERT_EQUAL( expected, created );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void HubTest::testReloadHub_()
{
	Hub::getHub()->instance_.reset( new Hub() );
	Hub::getHub()->init_();
	Hub* hub = Hub::getHub(); 
}
//____________________________________________________________________________________________________________________________________________________________________________________

void HubTest::testGetParentTagSetsAccessType_()
{
	Hub* hub = Hub::getHub();
	const Tag* uncat = hub->getUncategorizedTag();
	
	int accessType = hub->getParentTagSetsAccessType( uncat );
	CPPUNIT_ASSERT_EQUAL( (int)TagSetCommon::SYSTEM, accessType );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void HubTest::testLoadTagSets_()
{
	Hub* hub = Hub::getHub();
	vector<TagSet*> dimensions = hub->getTagSets();
	CPPUNIT_ASSERT( dimensions.size() > 0 );
	
	for( vector<TagSet*>::iterator itr = dimensions.begin(); itr != dimensions.end(); ++itr )
	{
		CPPUNIT_ASSERT( (*itr)->getId() != INVALID_VALUE );
	}	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void HubTest::testGetPlugins_()
{
	Hub* hub = Hub::getHub();
	vector<PluginCommon*> plugins = hub->getProcessObjectPlugins();
	
	CPPUNIT_ASSERT( plugins.size() > 0 );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void HubTest::testProcessAllObjects_()
{
	Hub* hub = Hub::getHub();
	
	vector<PluginCommon*> plugins = hub->getProcessObjectPlugins();
	CPPUNIT_ASSERT( plugins.size() > 0 );
	PluginCommon* plugin = plugins[0];
	
	int count = hub->processAllObjects( plugin->getId() );
	CPPUNIT_ASSERT( count > 0 );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void HubTest::testProcessAllObjectsCallback_()
{
	Hub* hub = Hub::getHub();
	
	vector<PluginCommon*> plugins = hub->getProcessObjectPlugins();
	CPPUNIT_ASSERT( plugins.size() > 0 );
	PluginCommon* plugin = plugins[0];
	
	int count = hub->processAllObjects( plugin->getId(), 2, callbackFunction );
	CPPUNIT_ASSERT( count > 0 );		
}
//____________________________________________________________________________________________________________________________________________________________________________________



