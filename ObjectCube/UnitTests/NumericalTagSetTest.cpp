/*
 *  NumericalTagSetTest.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 30.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "NumericalTagSetTest.h"

#include <cppunit/extensions/HelperMacros.h>

#include "../Hub.h"
#include "TestIds.h"
#include "../TagSet/TagSet.h"
#include "../TagSet/NumericalTagSet.h"
#include "TagSetAssertionTraits.h"
#include "../LayerShared/HubCommon.h"
#include "../Tag/Tag.h"
#include "../Tag/NumericalTag.h"
#include "../LayerShared/SharedDefinitions.h"
#include "../LayerShared/Exception.h"

using namespace ObjectCube;

CPPUNIT_TEST_SUITE_REGISTRATION( NumericalTagSetTest );

//____________________________________________________________________________________________________________________________________________________________________________________

void NumericalTagSetTest::setUp()
{
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void NumericalTagSetTest::tearDown()
{
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Canned tests --------------------------------------------------------------------------------------------------------------------

void NumericalTagSetTest::testFetchCanned()
{
	cerr << "\nNumericalTagSetTest::testFetchCanned = ";
	Hub::setDataAccessType( Hub::CANNED );
	
	Hub* hub = Hub::getHub();
	TagSet* tagSet = hub->getTagSet( TEST_NUMERICAL_TAG_SET_ID );
	/*
	NumericalTagSet expected;
	expected.setId_( TEST_NUMERICAL_TAG_SET_ID );
	expected.setName( "Canned numerical tag-set" );
	expected.setAccessId_( TagSet::USER );
	expected.setTypeId_( TagSet::NUMERICAL );
	
	//The tag-set cleans up the memory
	NumericalTag* tag = new NumericalTag( TEST_NUMERICAL_TAG_VALUE + 2 );
	tag->setTagSetId_( TEST_NUMERICAL_TAG_SET_ID );
	tag->setId_( TEST_NUMERICAL_TAG_ID_CANNED );
	vector<Tag*> tags;
	tags.push_back( tag );
	expected.setTags_( tags );
	 */
	
	//CPPUNIT_ASSERT_EQUAL( *(dynamic_cast<TagSet*>( &expected ) ), *tagSet);
}
//____________________________________________________________________________________________________________________________________________________________________________________

void NumericalTagSetTest::testCreateCanned()
{
	cerr << "\nNumericalTagSetTest::testCreateCanned = ";
	Hub::setDataAccessType( Hub::CANNED );
	
	NumericalTagSet userDim("Yet another numerical user tag set");
	userDim.create();
	
	CPPUNIT_ASSERT( userDim.getId() != INVALID_VALUE );
	CPPUNIT_ASSERT_EQUAL( (int)TagSetCommon::USER, userDim.getAccessId() );
	CPPUNIT_ASSERT_EQUAL( (int)TagSetCommon::NUMERICAL, userDim.getTypeId() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  SQLite tests --------------------------------------------------------------------------------------------------------------------

void NumericalTagSetTest::testFetchSQLite()
{
	cerr << "\nNumericalTagSetTest::testFetchSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testFetch_( TEST_SQLITE_CLEANUP_PREFIX + " Numerical unit test tag-set" );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void NumericalTagSetTest::testCreateSQLite()
{
	cerr << "\nNumericalTagSetTest::testCreateSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testCreate_( TEST_SQLITE_CLEANUP_PREFIX + " NumericalTagSet creation test" );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  MonetDB tests --------------------------------------------------------------------------------------------------------------------

void NumericalTagSetTest::testFetchMonetDB()
{
	cerr << "\nNumericalTagSetTest::testFetchMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );

	testFetch_( TEST_MONETDB_CLEANUP_PREFIX + " Numerical unit test tag-set" );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void NumericalTagSetTest::testCreateMonetDB()
{
	cerr << "\nNumericalTagSetTest::testCreateMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );
	
	testCreate_( TEST_MONETDB_CLEANUP_PREFIX + " NumericalTagSet creation test" );
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Oracle tests --------------------------------------------------------------------------------------------------------------------

void NumericalTagSetTest::testFetchOracle()
{
	cerr << "\nNumericalTagSetTest::testFetchOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testFetch_( TEST_ORACLE_CLEANUP_PREFIX + " Numerical unit test tag-set" );	
}
//____________________________________________________________________________________________________________________________________________________________________________________
void NumericalTagSetTest::testCreateOracle()
{
	cerr << "\nNumericalTagSetTest::testCreateOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testCreate_( TEST_ORACLE_CLEANUP_PREFIX + " NumericalTagSet creation test" );
}
//____________________________________________________________________________________________________________________________________________________________________________________


//  Common --------------------------------------------------------------------------------------------------------------------

void NumericalTagSetTest::testFetch_( string tagSetName )
{
	Hub* hub = Hub::getHub();
	TagSet* tagSet = hub->getTagSet( TEST_NUMERICAL_TAG_SET_ID );
	
	CPPUNIT_ASSERT_EQUAL( (int)TEST_NUMERICAL_TAG_SET_ID, tagSet->getId() );
	CPPUNIT_ASSERT_EQUAL( (int)TagSet::USER, tagSet->getAccessId() );
	CPPUNIT_ASSERT_EQUAL( (int)TagSet::NUMERICAL, tagSet->getTypeId() );
	CPPUNIT_ASSERT_EQUAL( tagSetName, tagSet->getName() );
	CPPUNIT_ASSERT( tagSet->getTags().size() > 0 );
	//CPPUNIT_ASSERT( tagSet->getDimensions().size() > 0 );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void NumericalTagSetTest::testCreate_( string tagSetName )
{
	NumericalTagSet userDim( tagSetName );
	userDim.create();
	
	CPPUNIT_ASSERT( userDim.getId() != INVALID_VALUE );
	CPPUNIT_ASSERT_EQUAL( (int)TagSetCommon::USER, userDim.getAccessId() );
	CPPUNIT_ASSERT_EQUAL( (int)TagSetCommon::NUMERICAL, userDim.getTypeId() );
	CPPUNIT_ASSERT_EQUAL( 0, (int)userDim.getTags().size() );
	CPPUNIT_ASSERT_EQUAL( 1, (int)userDim.getDimensions().size() );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

