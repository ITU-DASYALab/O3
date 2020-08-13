/*
 *  DateTagTest.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 12.4.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "DateTagTest.h"

#include <cppunit/extensions/HelperMacros.h>

#include "TagAssertionTraits.h"
#include "../Hub.h"
#include "TestIds.h"
#include "../TagSet/TagSet.h"
#include "../Tag/DateTag.h"

using namespace ObjectCube;

CPPUNIT_TEST_SUITE_REGISTRATION( DateTagTest );

//____________________________________________________________________________________________________________________________________________________________________________________

void DateTagTest::setUp()
{	

}
//____________________________________________________________________________________________________________________________________________________________________________________

void DateTagTest::tearDown()
{
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Canned tests --------------------------------------------------------------------------------------------------------------------

void DateTagTest::testFetchByIdCanned()
{
	cerr << "\nDateTagTest::testFetchByIdCanned = ";
	Hub::setDataAccessType( Hub::CANNED );

	int id = 1;
	unique_ptr<Tag> tag( Tag::fetch_( id ) );
	DateTag expected( TEST_DATE_TAG_VALUE_YEAR, TEST_DATE_TAG_VALUE_MONTH, TEST_DATE_TAG_VALUE_DAY );
	expected.setId_( id );
	expected.setTagSetId_( 2 );	
	expected.setTypeId_( 1 );
	
	CPPUNIT_ASSERT_EQUAL( *dynamic_cast<Tag*>( &expected ), *tag.get() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DateTagTest::testFetchByDimensionIdAndNumberCanned()
{
	cerr << "\nDateTagTest::testFetchByDimensionIdAndNumberCanned = ";
	Hub::setDataAccessType( Hub::CANNED );
	
	unique_ptr<DateTag> tag( DateTag::fetch( TEST_DATE_TAG_SET_ID, TEST_DATE_TAG_VALUE_YEAR, TEST_DATE_TAG_VALUE_MONTH, TEST_DATE_TAG_VALUE_DAY ) );
	
	DateTag expected( TEST_DATE_TAG_VALUE_YEAR, TEST_DATE_TAG_VALUE_MONTH, TEST_DATE_TAG_VALUE_DAY );
	expected.setId_( TEST_DATE_TAG_ID_CANNED );
	expected.setTagSetId_( TEST_DATE_TAG_SET_ID );
	
	CPPUNIT_ASSERT_EQUAL( *dynamic_cast<Tag*>( &expected ), *dynamic_cast<Tag*>( tag.get() ) );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DateTagTest::testInUseCanned()
{
	cerr << "\nDateTagTest::testInUseCanned = ";
	Hub::setDataAccessType( Hub::CANNED );
	
	Hub* hub = Hub::getHub(); 
	const Tag* tag = hub->getUncategorizedTag();
	
	CPPUNIT_ASSERT( tag->inUse() == false ); //No persistent storage
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  SQLite tests --------------------------------------------------------------------------------------------------------------------
void DateTagTest::testFetchByIdSQLite()
{
	cerr << "\nDateTagTest::testFetchByIdSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testFetchById_( SQLiteTestIds::TEST_DATE_TAG_ID );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DateTagTest::testFetchByDimensionIdAndNumberSQLite()
{
	cerr << "\nDateTagTest::testFetchByDimensionIdAndNumberSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testFetchByTagSetIdAndDate_( SQLiteTestIds::TEST_DATE_TAG_ID );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DateTagTest::testInUseSQLite()
{
	cerr << "\nDateTagTest::testInUseSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testInUse_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  MonetDB tests --------------------------------------------------------------------------------------------------------------------

void DateTagTest::testFetchByIdMonetDB()
{
	cerr << "\nDateTagTest::testFetchByIdMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );

	testFetchById_( MonetDBTestIds::TEST_DATE_TAG_ID );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DateTagTest::testFetchByDimensionIdAndNumberMonetDB()
{
	cerr << "\nDateTagTest::testFetchByDimensionIdAndNumberMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );

	testFetchByTagSetIdAndDate_( MonetDBTestIds::TEST_DATE_TAG_ID );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DateTagTest::testInUseMonetDB()
{
	cerr << "\nDateTagTest::testInUseMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );

	testInUse_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Oracle tests --------------------------------------------------------------------------------------------------------------------

void DateTagTest::testFetchByIdOracle()
{
	cerr << "\nDateTagTest::testFetchByIdOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testFetchById_( OracleTestIds::TEST_DATE_TAG_ID );
}
//____________________________________________________________________________________________________________________________________________________________________________________
void DateTagTest::testFetchByDimensionIdAndNumberOracle()
{
	cerr << "\nDateTagTest::testFetchByDimensionIdAndNumberOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testFetchByTagSetIdAndDate_( OracleTestIds::TEST_DATE_TAG_ID );
}
//____________________________________________________________________________________________________________________________________________________________________________________
void DateTagTest::testInUseOracle()
{
	cerr << "\nDateTagTest::testInUseOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testInUse_();	
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Common --------------------------------------------------------------------------------------------------------------------

void DateTagTest::testFetchById_( int id )
{
	unique_ptr<Tag> tag( Tag::fetch_( id ) );
	
	DateTag expected( TEST_DATE_TAG_VALUE_YEAR, TEST_DATE_TAG_VALUE_MONTH, TEST_DATE_TAG_VALUE_DAY );
	expected.setId_( id );
	expected.setTagSetId_( TEST_DATE_TAG_SET_ID );
	
	CPPUNIT_ASSERT_EQUAL( *dynamic_cast<Tag*>( &expected ), *tag.get() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DateTagTest::testFetchByTagSetIdAndDate_( int id )
{
	unique_ptr<DateTag> tag( DateTag::fetch( TEST_DATE_TAG_SET_ID, TEST_DATE_TAG_VALUE_YEAR, TEST_DATE_TAG_VALUE_MONTH, TEST_DATE_TAG_VALUE_DAY ) );
	
	DateTag expected( TEST_DATE_TAG_VALUE_YEAR, TEST_DATE_TAG_VALUE_MONTH, TEST_DATE_TAG_VALUE_DAY );
	expected.setId_( id );
	expected.setTagSetId_( TEST_DATE_TAG_SET_ID );
	
	CPPUNIT_ASSERT_EQUAL( *dynamic_cast<Tag*>( &expected ), *dynamic_cast<Tag*>( tag.get() ) );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DateTagTest::testInUse_()
{
	Hub* hub = Hub::getHub();
	DateTag dateTag( TEST_DATE_TAG_VALUE_YEAR + 1, TEST_DATE_TAG_VALUE_MONTH, TEST_DATE_TAG_VALUE_DAY );
	TagSet* testDim = hub->getTagSet( TEST_DATE_TAG_SET_ID );
	const Tag* tag = testDim->addTag( &dateTag );
	
	CPPUNIT_ASSERT( tag->inUse() == false ); //Not in use yet
	
	Object object( TestIds::TEST_OBJECT_PREFIX + "img8.jpg" );
	object.create();
	ObjectTag objectTag( tag );
	object.addTag( objectTag );
	
	CPPUNIT_ASSERT( tag->inUse() == true ); 	
}
//____________________________________________________________________________________________________________________________________________________________________________________



