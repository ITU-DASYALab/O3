/*
 *  AlphanumericalTagSetTest.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 18.2.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "AlphanumericalTagSetTest.h"

#include <cppunit/extensions/HelperMacros.h>

#include "../Hub.h"
#include "TestIds.h"
#include "../TagSet/TagSet.h"
#include "../TagSet/AlphanumericalTagSet.h"
#include "TagSetAssertionTraits.h"
#include "../LayerShared/HubCommon.h"
#include "../Tag/Tag.h"
#include "../Tag/AlphanumericalTag.h"
#include "../LayerShared/SharedDefinitions.h"
#include "../LayerShared/Exception.h"

using namespace ObjectCube;

CPPUNIT_TEST_SUITE_REGISTRATION( AlphanumericalTagSetTest );

//____________________________________________________________________________________________________________________________________________________________________________________

void AlphanumericalTagSetTest::setUp()
{
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void AlphanumericalTagSetTest::tearDown()
{
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Canned tests --------------------------------------------------------------------------------------------------------------------

void AlphanumericalTagSetTest::testFetchCanned()
{
	cerr << "\nAlphanumericalTagSetTest::testFetchCanned = ";
	Hub::setDataAccessType( Hub::CANNED );

	Hub* hub = Hub::getHub();
	TagSet* tagSet = hub->getTagSet( TEST_ALPHANUMERICAL_TAG_SET_ID );
	
	AlphanumericalTagSet expected; // = new AlphanumericalTagSet();
	expected.setId_( TEST_ALPHANUMERICAL_TAG_SET_ID );
	expected.setName( HubCommon::getUncategorizedDimensionName() );
	expected.setAccessId_( TagSet::SYSTEM );
	expected.setTypeId_( TagSet::ALPHANUMERICAL );
	
	//The tag-set cleans up the memory
	tr1::std::shared_ptr<AlphanumericalTag> tag( new AlphanumericalTag( HubCommon::getUncategorizedTagName() ) );
	tag->setTagSetId_( TEST_ALPHANUMERICAL_TAG_SET_ID );
	tag->setId_( TEST_ALPHANUMERICAL_TAG_ID_CANNED );
	vector<tr1::std::shared_ptr<Tag> > tags;
	tags.push_back( tag );
	
	tr1::std::shared_ptr<AlphanumericalTag> tag2( new AlphanumericalTag( "Another silly test tag" ) );
	tag2->setTagSetId_( TEST_ALPHANUMERICAL_TAG_SET_ID );
	tag2->setId_( SQLiteTestIds::TEST_ALPHANUMERICAL_TAG_ID  );
	tags.push_back( tag2 );
	
	expected.setTags_( tags );
	//This is complicated and not a central part of this test
	expected.dimensions_ = dynamic_cast<AlphanumericalTagSet*>( tagSet )->dimensions_;
	
	CPPUNIT_ASSERT_EQUAL( *(dynamic_cast<TagSet*>( &expected ) ), *tagSet);	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void AlphanumericalTagSetTest::testCreateCanned()
{
	cerr << "\nAlphanumericalTagSetTest::testCreateCanned = ";
	Hub::setDataAccessType( Hub::CANNED );
	
	AlphanumericalTagSet userDim("Yet another user tag-set");
	userDim.create();
	
	CPPUNIT_ASSERT( userDim.getId() != INVALID_VALUE );
	CPPUNIT_ASSERT_EQUAL( (int)TagSetCommon::USER, userDim.getAccessId() );
	CPPUNIT_ASSERT_EQUAL( (int)TagSetCommon::ALPHANUMERICAL, userDim.getTypeId() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  SQLite tests --------------------------------------------------------------------------------------------------------------------

void AlphanumericalTagSetTest::testFetchSQLite()
{
	cerr << "\nAlphanumericalTagSetTest::testFetchSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testFetch_( TEST_SQLITE_CLEANUP_PREFIX + " Alphanumerical unit test tag-set" );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void AlphanumericalTagSetTest::testCreateSQLite()
{
	cerr << "\nAlphanumericalTagSetTest::testCreateSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );

	testCreate_( TEST_SQLITE_CLEANUP_PREFIX + " AlphanumericalTagSet creation test" );
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  MonetDB --------------------------------------------------------------------------------------------------------------------

void AlphanumericalTagSetTest::testFetchMonetDB()
{
	cerr << "\nAlphanumericalTagSetTest::testFetchMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );

	testFetch_( TEST_MONETDB_CLEANUP_PREFIX + " Alphanumerical unit test tag-set" );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void AlphanumericalTagSetTest::testCreateMonetDB()
{
	cerr << "\nAlphanumericalTagSetTest::testCreateMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );

	testCreate_( TEST_MONETDB_CLEANUP_PREFIX + " AlphanumericalTagSet creation test" );
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Oracle --------------------------------------------------------------------------------------------------------------------

void AlphanumericalTagSetTest::testFetchOracle()
{
	cerr << "\nAlphanumericalTagSetTest::testFetchOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testFetch_( TEST_ORACLE_CLEANUP_PREFIX + " Alphanumerical unit test tag-set" );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void AlphanumericalTagSetTest::testCreateOracle()
{
	cerr << "\nAlphanumericalTagSetTest::testCreateOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testCreate_( TEST_ORACLE_CLEANUP_PREFIX + " AlphanumericalTagSet creation test" );
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Common --------------------------------------------------------------------------------------------------------------------

void AlphanumericalTagSetTest::testFetch_( string tagSetName )
{
	Hub* hub = Hub::getHub();
	TagSet* tagSet = hub->getTagSet( TEST_ALPHANUMERICAL_TAG_SET_ID );
	
	CPPUNIT_ASSERT_EQUAL( (int)TEST_ALPHANUMERICAL_TAG_SET_ID, tagSet->getId() );
	CPPUNIT_ASSERT_EQUAL( (int)TagSet::USER, tagSet->getAccessId() );
	CPPUNIT_ASSERT_EQUAL( (int)TagSet::ALPHANUMERICAL, tagSet->getTypeId() );
	CPPUNIT_ASSERT_EQUAL( tagSetName, tagSet->getName() );
	CPPUNIT_ASSERT( tagSet->getTags().size() > 0 );
	CPPUNIT_ASSERT( tagSet->getDimensions().size() > 0 );
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void AlphanumericalTagSetTest::testCreate_( string tagSetName )
{
	AlphanumericalTagSet userDim( tagSetName );
	userDim.create();
	
	//const Tag* tag = userDim.fetchOrAddTag( "Nonsense test tag (fetchOrAddTag)" );
	
	CPPUNIT_ASSERT( userDim.getId() != INVALID_VALUE );
	CPPUNIT_ASSERT_EQUAL( (int)TagSetCommon::USER, userDim.getAccessId() );
	CPPUNIT_ASSERT_EQUAL( (int)TagSetCommon::ALPHANUMERICAL, userDim.getTypeId() );
	CPPUNIT_ASSERT_EQUAL( 0, (int)userDim.getTags().size() );
	CPPUNIT_ASSERT_EQUAL( 1, (int)userDim.getDimensions().size() );	
	
	/*
	AlphanumericalTagSet desc( "Description" );
	Hub* hub = Hub::getHub();
	TagSet* descriptionTS = hub->addTagSet( desc );
	*/
}
//____________________________________________________________________________________________________________________________________________________________________________________





