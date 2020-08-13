/*
 *  TagTest.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 30.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "TagTest.h"

#include <cppunit/extensions/HelperMacros.h>

#include "TagAssertionTraits.h"
#include "../Hub.h"
#include "TestIds.h"
#include "../Tag/Tag.h"
#include "../Tag/AlphanumericalTag.h"
#include "../LayerShared/LanguageCommon.h"

using namespace ObjectCube;

CPPUNIT_TEST_SUITE_REGISTRATION( TagTest );

//____________________________________________________________________________________________________________________________________________________________________________________

void TagTest::setUp()
{	
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagTest::tearDown()
{
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Canned tests --------------------------------------------------------------------------------------------------------------------

void TagTest::testFetchByIdCanned()
{
	cerr << "\nTagTest::testFetchByIdCanned = ";
	HubCommon::setDataAccessType( HubCommon::CANNED );
	int id = 1;
	
	unique_ptr<Tag> tag( Tag::fetch_( 1 ) );
	AlphanumericalTag expected; //We use this since Tag is abstract
	expected.setId_( id );
	expected.setTagSetId_( 2 );	
	
	CPPUNIT_ASSERT_EQUAL( *dynamic_cast<Tag*>( &expected ), *tag.get() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  SQLite tests --------------------------------------------------------------------------------------------------------------------

void TagTest::testFetchByIdSQLite()
{
	cerr << "\nTagTest::testFetchByIdSQLite = ";
	HubCommon::setDataAccessType( HubCommon::SQLITE );
	
	testFetchById_( SQLiteTestIds::TEST_ALPHANUMERICAL_TAG_ID );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagTest::testTypeAsStringSQLite()
{
	cerr << "\nTagTest::testTypeAsStringSQLite = ";
	HubCommon::setDataAccessType( HubCommon::SQLITE );
	
	testTypeAsString_( SQLiteTestIds::TEST_ALPHANUMERICAL_TAG_ID );
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  MonetDB tests --------------------------------------------------------------------------------------------------------------------

void TagTest::testFetchByIdMonetDB()
{
	cerr << "\nTagTest::testFetchByIdMonetDB = ";
	HubCommon::setDataAccessType( HubCommon::MONETDB );

	testFetchById_( MonetDBTestIds::TEST_ALPHANUMERICAL_TAG_ID );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagTest::testTypeAsStringMonetDB()
{
	cerr << "\nTagTest::testTypeAsStringMonetDB = ";
	HubCommon::setDataAccessType( HubCommon::MONETDB );

	testTypeAsString_( MonetDBTestIds::TEST_ALPHANUMERICAL_TAG_ID );
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Oracle tests --------------------------------------------------------------------------------------------------------------------

void TagTest::testFetchByIdOracle()
{
	cerr << "\nTagTest::testFetchByIdOracle = ";
	HubCommon::setDataAccessType( HubCommon::ORACLE );
	
	testFetchById_( OracleTestIds::TEST_ALPHANUMERICAL_TAG_ID );
}
//____________________________________________________________________________________________________________________________________________________________________________________
void TagTest::testTypeAsStringOracle()
{
	cerr << "\nTagTest::testTypeAsStringOracle = ";
	HubCommon::setDataAccessType( HubCommon::ORACLE );
	
	testTypeAsString_( OracleTestIds::TEST_ALPHANUMERICAL_TAG_ID );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

//	Common --------------------------------------------------------------------------------------------------------------------

void TagTest::testFetchById_( int id )
{
	unique_ptr<Tag> tag( Tag::fetch_( id ) );
	
	unique_ptr<AlphanumericalTag> expected( AlphanumericalTag::fetch( id ) );
	CPPUNIT_ASSERT_EQUAL( *dynamic_cast<Tag*>( expected.get() ), *tag.get() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagTest::testTypeAsString_( int id )
{
	unique_ptr<Tag> tag( Tag::fetch_( id ) );
	
	Hub::setLanguageId( LanguageCommon::ENGLISH );
	CPPUNIT_ASSERT_EQUAL( tag->typeAsString() , TEST_ALPHANUMERICAL_TAG_TYPE_NAME_ENGLISH );
	
	Hub::setLanguageId( LanguageCommon::ICELANDIC );
	CPPUNIT_ASSERT_EQUAL( tag->typeAsString() , TEST_ALPHANUMERICAL_TAG_TYPE_NAME_ICELANDIC );
	
	Hub::setLanguageId( LanguageCommon::ENGLISH );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

