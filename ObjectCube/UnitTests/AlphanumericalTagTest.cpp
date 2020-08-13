/*
 *  AlphanumericalTagTest.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 12.2.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "AlphanumericalTagTest.h"

#include <cppunit/extensions/HelperMacros.h>

#include "TagAssertionTraits.h"
#include "../Hub.h"
#include "TestIds.h"
#include "../TagSet/TagSet.h"
#include "../Tag/AlphanumericalTag.h"

using namespace ObjectCube;

CPPUNIT_TEST_SUITE_REGISTRATION( AlphanumericalTagTest );

//____________________________________________________________________________________________________________________________________________________________________________________

void AlphanumericalTagTest::setUp()
{	
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void AlphanumericalTagTest::tearDown()
{

}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Canned tests --------------------------------------------------------------------------------------------------------------------
void AlphanumericalTagTest::testCreateCanned()
{
	cerr << "\nAlphanumericalTagTest::testCreateCanned = ";
	Hub::setDataAccessType( Hub::CANNED );
	
	AlphanumericalTag tag("Canned creation test tag");
	tag.setTagSetId_( 1 ); //Should only be created through a dimension.
	tag.create_();
	
	CPPUNIT_ASSERT( tag.getId() > 0 ); //The only thing that changes
}
//____________________________________________________________________________________________________________________________________________________________________________________

void AlphanumericalTagTest::testFetchByIdCanned()
{
	cerr << "\nAlphanumericalTagTest::testFetchByIdCanned = ";
	Hub::setDataAccessType( Hub::CANNED );

	int id = 1;
	unique_ptr<Tag> tag( Tag::fetch_( id ) );
	AlphanumericalTag expected("Canned tag");
	expected.setId_( id );
	expected.setTagSetId_( 2 );	
	
	CPPUNIT_ASSERT_EQUAL( *dynamic_cast<Tag*>( &expected ), *tag.get() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void AlphanumericalTagTest::testFetchByDimensionIdAndNameCanned()
{
	cerr << "\nAlphanumericalTagTest::testFetchByDimensionIdAndNameCanned = ";
	Hub::setDataAccessType( Hub::CANNED );
	
	unique_ptr<AlphanumericalTag> tag( AlphanumericalTag::fetch( TEST_ALPHANUMERICAL_TAG_SET_ID, HubCommon::getUncategorizedDimensionName() ) );
	
	AlphanumericalTag expected( HubCommon::getUncategorizedDimensionName() );
	expected.setId_( TEST_ALPHANUMERICAL_TAG_ID_CANNED );
	expected.setTagSetId_( TEST_ALPHANUMERICAL_TAG_SET_ID );
	
	CPPUNIT_ASSERT_EQUAL( *dynamic_cast<Tag*>( &expected ), *dynamic_cast<Tag*>( tag.get() ) );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void AlphanumericalTagTest::testInUseCanned()
{
	cerr << "\nAlphanumericalTagTest::testInUseCanned = ";
	Hub::setDataAccessType( Hub::CANNED );
	
	Hub* hub = Hub::getHub(); 
	const Tag* tag = hub->getUncategorizedTag();

	CPPUNIT_ASSERT( tag->inUse() == false ); //No persistent storage
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  SQLite tests --------------------------------------------------------------------------------------------------------------------
void AlphanumericalTagTest::testFetchByIdSQLite()
{
	cerr << "\nAlphanumericalTagTest::testFetchByIdSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testFetchById_( SQLiteTestIds::TEST_ALPHANUMERICAL_TAG_ID, TEST_SQLITE_CLEANUP_PREFIX + TEST_ALPHANUMERICAL_TAG_NAME );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void AlphanumericalTagTest::testFetchByDimensionIdAndNameSQLite()
{
	cerr << "\nAlphanumericalTagTest::testFetchByDimensionIdAndNameSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testFetchByDimensionIdAndName_( SQLiteTestIds::TEST_ALPHANUMERICAL_TAG_ID, TEST_SQLITE_CLEANUP_PREFIX + TEST_ALPHANUMERICAL_TAG_NAME );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void AlphanumericalTagTest::testInUseSQLite()
{
	cerr << "\nAlphanumericalTagTest::testInUseSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testInUse_( TEST_SQLITE_CLEANUP_PREFIX + " - inUse test tag" );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void AlphanumericalTagTest::testControlCharactersHandlingSQLite()
{
	cerr << "\nAlphanumericalTagTest::testControlCharactersHandlingSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testControlCharactersHandling_( TEST_SQLITE_CLEANUP_PREFIX );
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  MonetDB tests --------------------------------------------------------------------------------------------------------------------

void AlphanumericalTagTest::testFetchByIdMonetDB()
{
	cerr << "\nAlphanumericalTagTest::testFetchByIdMonetDB = ";
	HubCommon::setDataAccessType( HubCommon::MONETDB );

	testFetchById_( MonetDBTestIds::TEST_ALPHANUMERICAL_TAG_ID, TEST_MONETDB_CLEANUP_PREFIX + TEST_ALPHANUMERICAL_TAG_NAME );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void AlphanumericalTagTest::testFetchByDimensionIdAndNameMonetDB()
{
	cerr << "\nAlphanumericalTagTest::testFetchByDimensionIdAndNameMonetDB = ";
	HubCommon::setDataAccessType( HubCommon::MONETDB );
	
	testFetchByDimensionIdAndName_( MonetDBTestIds::TEST_ALPHANUMERICAL_TAG_ID, TEST_MONETDB_CLEANUP_PREFIX + TEST_ALPHANUMERICAL_TAG_NAME );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void AlphanumericalTagTest::testInUseMonetDB()
{
	cerr << "\nAlphanumericalTagTest::testInUseMonetDB = ";
	HubCommon::setDataAccessType( HubCommon::MONETDB );
	
	testInUse_( TEST_MONETDB_CLEANUP_PREFIX + " - inUse test tag" );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void AlphanumericalTagTest::testControlCharactersHandlingMonetDB()
{
	cerr << "\nAlphanumericalTagTest::testControlCharactersHandlingMonetDB = ";
	HubCommon::setDataAccessType( HubCommon::MONETDB );

	testControlCharactersHandling_( TEST_MONETDB_CLEANUP_PREFIX );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void AlphanumericalTagTest::testIcelandicCharactersMonetDB()
{
	cerr << "\nAlphanumericalTagTest::testIcelandicCharactersMonetDB = ";
	HubCommon::setDataAccessType( HubCommon::MONETDB );

	Hub* hub = Hub::getHub();
	TagSet* testTagSet = hub->getTagSet( TEST_ALPHANUMERICAL_TAG_SET_ID );
	
	string tagName = TEST_MONETDB_CLEANUP_PREFIX  + " - áÁíÍóÓæÆöÖþÞðÐýÝúÚéÉ";
	AlphanumericalTag tag( tagName );
	
	const Tag* tagCreated = testTagSet->addTag( &tag );
	
	const Tag* tagReturned = testTagSet->getTag( tagCreated->getId() );
	CPPUNIT_ASSERT_EQUAL( *tagCreated, *tagReturned );
	
	unique_ptr<AlphanumericalTag> tagFetched( AlphanumericalTag::fetch( testTagSet->getId(), tagName ) );
	
	CPPUNIT_ASSERT_EQUAL( *tagCreated, *dynamic_cast<Tag*>( tagFetched.get() ) );
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Oracle tests --------------------------------------------------------------------------------------------------------------------

void AlphanumericalTagTest::testFetchByIdOracle()
{
	cerr << "\nAlphanumericalTagTest::testFetchByIdOracle = ";
	HubCommon::setDataAccessType( HubCommon::ORACLE );
	
	testFetchById_( OracleTestIds::TEST_ALPHANUMERICAL_TAG_ID, TEST_ORACLE_CLEANUP_PREFIX + TEST_ALPHANUMERICAL_TAG_NAME );
}
//____________________________________________________________________________________________________________________________________________________________________________________
void AlphanumericalTagTest::testFetchByDimensionIdAndNameOracle()
{
	cerr << "\nAlphanumericalTagTest::testFetchByDimensionIdAndNameOracle = ";
	HubCommon::setDataAccessType( HubCommon::ORACLE );
	
	testFetchByDimensionIdAndName_( OracleTestIds::TEST_ALPHANUMERICAL_TAG_ID, TEST_ORACLE_CLEANUP_PREFIX + TEST_ALPHANUMERICAL_TAG_NAME );	
}
//____________________________________________________________________________________________________________________________________________________________________________________
void AlphanumericalTagTest::testInUseOracle()
{
	cerr << "\nAlphanumericalTagTest::testInUseOracle = ";
	HubCommon::setDataAccessType( HubCommon::ORACLE );
	
	testInUse_( TEST_ORACLE_CLEANUP_PREFIX + " - inUse test tag" );	
}
//____________________________________________________________________________________________________________________________________________________________________________________
void AlphanumericalTagTest::testControlCharactersHandlingOracle()
{
	cerr << "\nAlphanumericalTagTest::testControlCharactersHandlingOracle = ";
	HubCommon::setDataAccessType( HubCommon::ORACLE );
	
	testControlCharactersHandling_( TEST_ORACLE_CLEANUP_PREFIX );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Common --------------------------------------------------------------------------------------------------------------------

void AlphanumericalTagTest::testFetchById_( int id, const string& tagName )
{
	unique_ptr<Tag> tag( Tag::fetch_( id ) );
	
	AlphanumericalTag expected( tagName );
	expected.setId_( id );
	expected.setTagSetId_( TEST_ALPHANUMERICAL_TAG_SET_ID );
	
	CPPUNIT_ASSERT_EQUAL( *dynamic_cast<Tag*>( &expected ), *tag.get() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void AlphanumericalTagTest::testFetchByDimensionIdAndName_( int id, const string& tagName )
{
	unique_ptr<AlphanumericalTag> tag( AlphanumericalTag::fetch( TEST_ALPHANUMERICAL_TAG_SET_ID, tagName ) );
	
	AlphanumericalTag expected( tagName );
	expected.setId_( id );
	expected.setTagSetId_( TEST_ALPHANUMERICAL_TAG_SET_ID );
	
	CPPUNIT_ASSERT_EQUAL( *dynamic_cast<Tag*>( &expected ), *dynamic_cast<Tag*>( tag.get() ) );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void AlphanumericalTagTest::testInUse_( const string& tagName )
{
	Hub* hub = Hub::getHub();
	AlphanumericalTag tag( tagName );
	TagSet* testDim = hub->getTagSet( TEST_ALPHANUMERICAL_TAG_SET_ID );
	const Tag* addedTag = testDim->addTag( &tag );
	
	CPPUNIT_ASSERT( addedTag->inUse() == false ); //Not in use yet
	
	string name = TestIds::TEST_OBJECT_PREFIX + "img2.jpg";
	Object object( name );
	object.create();
	ObjectTag objectTag( addedTag );
	object.addTag( objectTag );
	
	CPPUNIT_ASSERT( objectTag.getTag()->inUse() == true ); 
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void AlphanumericalTagTest::testControlCharactersHandling_( const string& tagNamePrefix )
{
	Hub* hub = Hub::getHub();
	
	TagSet* testTagSet = hub->getTagSet( TEST_ALPHANUMERICAL_TAG_SET_ID );
	
	string tagName = tagNamePrefix  + " - Po's";
	AlphanumericalTag tag( tagName );
	
	const Tag* tagCreated = testTagSet->addTag( &tag );
	
	const Tag* tagReturned = testTagSet->getTag( tagCreated->getId() );
	CPPUNIT_ASSERT_EQUAL( *tagCreated, *tagReturned );
	
	unique_ptr<AlphanumericalTag> tagFetched( AlphanumericalTag::fetch( testTagSet->getId(), tagName ) );

	CPPUNIT_ASSERT_EQUAL( *tagCreated, *dynamic_cast<Tag*>( tagFetched.get() ) );
}
//____________________________________________________________________________________________________________________________________________________________________________________




