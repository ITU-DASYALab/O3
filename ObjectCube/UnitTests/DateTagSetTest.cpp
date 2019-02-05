/*
 *  DateTagSetTest.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 12.4.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "DateTagSetTest.h"

#include <cppunit/extensions/HelperMacros.h>

#include "../Hub.h"
#include "TestIds.h"
#include "../TagSet/TagSet.h"
#include "../TagSet/DateTagSet.h"
#include "TagSetAssertionTraits.h"
#include "../LayerShared/HubCommon.h"
#include "../Tag/Tag.h"
#include "../Tag/DateTag.h"
#include "../LayerShared/SharedDefinitions.h"
#include "../LayerShared/Exception.h"

using namespace ObjectCube;

CPPUNIT_TEST_SUITE_REGISTRATION( DateTagSetTest );

//____________________________________________________________________________________________________________________________________________________________________________________

void DateTagSetTest::setUp()
{
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DateTagSetTest::tearDown()
{
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Canned tests --------------------------------------------------------------------------------------------------------------------

void DateTagSetTest::testFetchCanned()
{
	cerr << "\nDateTagSetTest::testFetchCanned = ";
	Hub::setDataAccessType( Hub::CANNED );
	
	
	Hub* hub = Hub::getHub();
	TagSet* tagSet = hub->getTagSet( TEST_DATE_TAG_SET_ID );
	/*
	DateTagSet expected; // = new DateTagSet();
	expected.setId_( TEST_DATE_TAG_SET_ID );
	expected.setName( "Canned date tag-set" );
	expected.setAccessId_( TagSet::USER );
	expected.setTypeId_( TagSet::DATE );
	
	//The tag-set cleans up the memory
	DateTag* tag = new DateTag( TEST_DATE_TAG_VALUE_YEAR + 2, TEST_DATE_TAG_VALUE_MONTH, TEST_DATE_TAG_VALUE_DAY );
	tag->setTagSetId_( TEST_DATE_TAG_SET_ID );
	tag->setId_( TEST_DATE_TAG_ID_CANNED );
	vector<Tag*> tags;
	tags.push_back( tag );
	expected.setTags_( tags );
	
	CPPUNIT_ASSERT_EQUAL( *(dynamic_cast<TagSet*>( &expected ) ), *tagSet);
	 */
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DateTagSetTest::testCreateCanned()
{
	cerr << "\nDateTagSetTest::testCreateCanned = ";
	Hub::setDataAccessType( Hub::CANNED );
	
	DateTagSet userDim("Yet another date user tag set");
	userDim.create();
	
	CPPUNIT_ASSERT( userDim.getId() != INVALID_VALUE );
	CPPUNIT_ASSERT_EQUAL( (int)TagSetCommon::USER, userDim.getAccessId() );
	CPPUNIT_ASSERT_EQUAL( (int)TagSetCommon::DATE, userDim.getTypeId() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  SQLite tests --------------------------------------------------------------------------------------------------------------------

void DateTagSetTest::testFetchSQLite()
{
	cerr << "\nDateTagSetTest::testFetchSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testFetch_( TEST_SQLITE_CLEANUP_PREFIX + " Date unit test tag-set" );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DateTagSetTest::testCreateSQLite()
{
	cerr << "\nDateTagSetTest::testCreateSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testCreate_( TEST_SQLITE_CLEANUP_PREFIX + " DateTagSet creation test" );
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  MonetDB tests --------------------------------------------------------------------------------------------------------------------

void DateTagSetTest::testFetchMonetDB()
{
	cerr << "\nDateTagSetTest::testFetchMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );
	
	testFetch_( TEST_MONETDB_CLEANUP_PREFIX + " Date unit test tag-set" );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DateTagSetTest::testCreateMonetDB()
{
	cerr << "\nDateTagSetTest::testCreateMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );
	
	testCreate_( TEST_MONETDB_CLEANUP_PREFIX + " DateTagSet creation test" );
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Oracle tests --------------------------------------------------------------------------------------------------------------------

void DateTagSetTest::testFetchOracle()
{
	cerr << "\nDateTagSetTest::testFetchOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testFetch_( TEST_ORACLE_CLEANUP_PREFIX + " Date unit test tag-set" );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DateTagSetTest::testCreateOracle()
{
	cerr << "\nDateTagSetTest::testCreateOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testCreate_( TEST_ORACLE_CLEANUP_PREFIX + " DateTagSet creation test" );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Common --------------------------------------------------------------------------------------------------------------------

void DateTagSetTest::testFetch_( string tagSetName )
{
	Hub* hub = Hub::getHub();
	TagSet* tagSet = hub->getTagSet( TEST_DATE_TAG_SET_ID );
	
	CPPUNIT_ASSERT_EQUAL( (int)TEST_DATE_TAG_SET_ID, tagSet->getId() );
	CPPUNIT_ASSERT_EQUAL( (int)TagSet::USER, tagSet->getAccessId() );
	CPPUNIT_ASSERT_EQUAL( (int)TagSet::DATE, tagSet->getTypeId() );
	CPPUNIT_ASSERT_EQUAL( tagSetName, tagSet->getName() );
	CPPUNIT_ASSERT( tagSet->getTags().size() > 0 );
	//CPPUNIT_ASSERT( tagSet->getDimensions().size() > 0 );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DateTagSetTest::testCreate_( string tagSetName )
{
	DateTagSet userDim( tagSetName );
	userDim.create();
	
	CPPUNIT_ASSERT( userDim.getId() != INVALID_VALUE );
	CPPUNIT_ASSERT_EQUAL( (int)TagSetCommon::USER, userDim.getAccessId() );
	CPPUNIT_ASSERT_EQUAL( (int)TagSetCommon::DATE, userDim.getTypeId() );
	CPPUNIT_ASSERT_EQUAL( 0, (int)userDim.getTags().size() );
	CPPUNIT_ASSERT_EQUAL( 1, (int)userDim.getDimensions().size() );
}
//____________________________________________________________________________________________________________________________________________________________________________________


