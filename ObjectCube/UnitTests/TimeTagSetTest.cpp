/*
 *  TimeTagSetTest.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 12.4.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "TimeTagSetTest.h"

#include <cppunit/extensions/HelperMacros.h>

#include "../Hub.h"
#include "TestIds.h"
#include "../TagSet/TagSet.h"
#include "../TagSet/TimeTagSet.h"
#include "TagSetAssertionTraits.h"
#include "../LayerShared/HubCommon.h"
#include "../Tag/Tag.h"
#include "../Tag/TimeTag.h"
#include "../LayerShared/SharedDefinitions.h"
#include "../LayerShared/Exception.h"

using namespace ObjectCube;

CPPUNIT_TEST_SUITE_REGISTRATION( TimeTagSetTest );

//____________________________________________________________________________________________________________________________________________________________________________________

void TimeTagSetTest::setUp()
{
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TimeTagSetTest::tearDown()
{
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Canned tests --------------------------------------------------------------------------------------------------------------------

void TimeTagSetTest::testFetchCanned()
{
	cerr << "\nTimeTagSetTest::testFetchCanned = ";
	Hub::setDataAccessType( Hub::CANNED );
	/*
	Hub* hub = Hub::getHub();
	TagSet* tagSet = hub->getTagSet( TEST_TIME_TAG_SET_ID );
	
	TimeTagSet expected; // = new TimeTagSet();
	expected.setId_( TEST_TIME_TAG_SET_ID );
	expected.setName( "Canned time tag-set" );
	expected.setAccessId_( TagSet::USER );
	
	//The tag-set cleans up the memory
 	TimeTag* tag = new TimeTag( TEST_TIME_TAG_VALUE_HOURS - 4, TEST_TIME_TAG_VALUE_MINUTES, TEST_TIME_TAG_VALUE_SECONDS, TEST_TIME_TAG_VALUE_MILLISECONDS );
	tag->setTagSetId_( TEST_TIME_TAG_SET_ID );
	tag->setId_( TEST_TIME_TAG_ID_CANNED );
	vector<Tag*> tags;
	tags.push_back( tag );
	expected.setTags_( tags );
	
	CPPUNIT_ASSERT_EQUAL( *(dynamic_cast<TagSet*>( &expected ) ), *tagSet);
	 */
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TimeTagSetTest::testCreateCanned()
{
	cerr << "\nTimeTagSetTest::testCreateCanned = ";
	Hub::setDataAccessType( Hub::CANNED );
	
	TimeTagSet userDim("Yet another time user tag set");
	userDim.create();
	
	CPPUNIT_ASSERT( userDim.getId() != INVALID_VALUE );
	CPPUNIT_ASSERT_EQUAL( (int)TagSetCommon::USER, userDim.getAccessId() );
	CPPUNIT_ASSERT_EQUAL( (int)TagSetCommon::TIME, userDim.getTypeId() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  SQLite tests --------------------------------------------------------------------------------------------------------------------

void TimeTagSetTest::testFetchSQLite()
{
	cerr << "\nTimeTagSetTest::testFetchSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testFetch_( TEST_SQLITE_CLEANUP_PREFIX + " Time unit test tag-set" );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TimeTagSetTest::testCreateSQLite()
{
	cerr << "\nTimeTagSetTest::testCreateSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testCreate_( TEST_SQLITE_CLEANUP_PREFIX + " TimeTagSet creation test" );
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  MonetDB tests --------------------------------------------------------------------------------------------------------------------

void TimeTagSetTest::testFetchMonetDB()
{
	cerr << "\nTimeTagSetTest::testFetchMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );
	
	testFetch_( TEST_MONETDB_CLEANUP_PREFIX + " Time unit test tag-set" );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TimeTagSetTest::testCreateMonetDB()
{
	cerr << "\nTimeTagSetTest::testCreateMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );
	
	testCreate_( TEST_MONETDB_CLEANUP_PREFIX + " TimeTagSet creation test" );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Oracle tests --------------------------------------------------------------------------------------------------------------------

void TimeTagSetTest::testFetchOracle()
{
	cerr << "\nTimeTagSetTest::testFetchOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testFetch_( TEST_ORACLE_CLEANUP_PREFIX + " Time unit test tag-set" );		
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TimeTagSetTest::testCreateOracle()
{
	cerr << "\nTimeTagSetTest::testCreateOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testCreate_( TEST_ORACLE_CLEANUP_PREFIX + " TimeTagSet creation test" );		
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Common --------------------------------------------------------------------------------------------------------------------

void TimeTagSetTest::testFetch_( string tagSetName )
{
	Hub* hub = Hub::getHub();
	TagSet* tagSet = hub->getTagSet( TEST_TIME_TAG_SET_ID );
	
	CPPUNIT_ASSERT_EQUAL( (int)TEST_TIME_TAG_SET_ID, tagSet->getId() );
	CPPUNIT_ASSERT_EQUAL( (int)TagSet::USER, tagSet->getAccessId() );
	CPPUNIT_ASSERT_EQUAL( (int)TagSet::TIME, tagSet->getTypeId() );
	CPPUNIT_ASSERT_EQUAL( tagSetName, tagSet->getName() );
	CPPUNIT_ASSERT( tagSet->getTags().size() > 0 );
	//CPPUNIT_ASSERT( tagSet->getDimensions().size() > 0 );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TimeTagSetTest::testCreate_( string tagSetName )
{
	TimeTagSet userDim( tagSetName );
	userDim.create();
	
	CPPUNIT_ASSERT( userDim.getId() != INVALID_VALUE );
	CPPUNIT_ASSERT_EQUAL( (int)TagSetCommon::USER, userDim.getAccessId() );
	CPPUNIT_ASSERT_EQUAL( (int)TagSetCommon::TIME, userDim.getTypeId() );
	CPPUNIT_ASSERT_EQUAL( 0, (int)userDim.getTags().size() );
	CPPUNIT_ASSERT_EQUAL( 1, (int)userDim.getDimensions().size() );	
}
//____________________________________________________________________________________________________________________________________________________________________________________




