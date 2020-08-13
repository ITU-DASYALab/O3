/*
 *  TimeTagTest.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 12.4.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "TimeTagTest.h"

#include <cppunit/extensions/HelperMacros.h>

#include "TagAssertionTraits.h"
#include "../Hub.h"
#include "TestIds.h"
#include "../TagSet/TagSet.h"
#include "../Tag/TimeTag.h"

using namespace ObjectCube;

CPPUNIT_TEST_SUITE_REGISTRATION( TimeTagTest );

//____________________________________________________________________________________________________________________________________________________________________________________

void TimeTagTest::setUp()
{	

}
//____________________________________________________________________________________________________________________________________________________________________________________

void TimeTagTest::tearDown()
{
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Canned tests --------------------------------------------------------------------------------------------------------------------

void TimeTagTest::testFetchByIdCanned()
{
	cerr << "\nTimeTagTest::testFetchByIdCanned = ";
	Hub::setDataAccessType( Hub::CANNED );

	int id = 1;
	unique_ptr<Tag> tag( Tag::fetch_( id ) );
	TimeTag expected( TEST_TIME_TAG_VALUE_HOURS, TEST_TIME_TAG_VALUE_MINUTES, TEST_TIME_TAG_VALUE_SECONDS, TEST_TIME_TAG_VALUE_MILLISECONDS );
	expected.setId_( id );
	expected.setTagSetId_( 2 );	
	expected.setTypeId_( 1 );
	
	CPPUNIT_ASSERT_EQUAL( *dynamic_cast<Tag*>( &expected ), *tag );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TimeTagTest::testFetchByDimensionIdAndNumberCanned()
{
	cerr << "\nTimeTagTest::testFetchByDimensionIdAndNumberCanned = ";
	Hub::setDataAccessType( Hub::CANNED );
	
	unique_ptr<TimeTag> tag( TimeTag::fetch( TEST_TIME_TAG_SET_ID, TEST_TIME_TAG_VALUE_HOURS, TEST_TIME_TAG_VALUE_MINUTES, TEST_TIME_TAG_VALUE_SECONDS, TEST_TIME_TAG_VALUE_MILLISECONDS ) );
	
	TimeTag expected( TEST_TIME_TAG_VALUE_HOURS, TEST_TIME_TAG_VALUE_MINUTES, TEST_TIME_TAG_VALUE_SECONDS, TEST_TIME_TAG_VALUE_MILLISECONDS );
	expected.setId_( TEST_TIME_TAG_ID_CANNED );
	expected.setTagSetId_( TEST_TIME_TAG_SET_ID );
	
	CPPUNIT_ASSERT_EQUAL( *dynamic_cast<Tag*>( &expected ), *dynamic_cast<Tag*>( tag.get() ) );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TimeTagTest::testInUseCanned()
{
	cerr << "\nTimeTagTest::testInUseCanned = ";
	Hub::setDataAccessType( Hub::CANNED );
	
	Hub* hub = Hub::getHub(); 
	const Tag* tag = hub->getUncategorizedTag();
	
	CPPUNIT_ASSERT( tag->inUse() == false ); //No persistent storage
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  SQLite tests --------------------------------------------------------------------------------------------------------------------

void TimeTagTest::testFetchByIdSQLite()
{
	cerr << "\nTimeTagTest::testFetchByIdSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testFetchById_( SQLiteTestIds::TEST_TIME_TAG_ID );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TimeTagTest::testFetchByDimensionIdAndNumberSQLite()
{
	cerr << "\nTimeTagTest::testFetchByDimensionIdAndNumberSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testFetchByTagSetIdAndTime_( SQLiteTestIds::TEST_TIME_TAG_ID );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TimeTagTest::testInUseSQLite()
{
	cerr << "\nTimeTagTest::testInUseSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testInUse_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  MonetDB tests --------------------------------------------------------------------------------------------------------------------

void TimeTagTest::testFetchByIdMonetDB()
{
	cerr << "\nTimeTagTest::testFetchByIdMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );

	testFetchById_( MonetDBTestIds::TEST_TIME_TAG_ID );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TimeTagTest::testFetchByDimensionIdAndNumberMonetDB()
{
	cerr << "\nTimeTagTest::testFetchByDimensionIdAndNumberMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );

	testFetchByTagSetIdAndTime_( MonetDBTestIds::TEST_TIME_TAG_ID );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TimeTagTest::testInUseMonetDB()
{
	cerr << "\nTimeTagTest::testInUseMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );
	
	testInUse_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Oracle tests --------------------------------------------------------------------------------------------------------------------

void TimeTagTest::testFetchByIdOracle()
{
	cerr << "\nTimeTagTest::testFetchByIdOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testFetchById_( OracleTestIds::TEST_TIME_TAG_ID );
}
//____________________________________________________________________________________________________________________________________________________________________________________
void TimeTagTest::testFetchByDimensionIdAndNumberOracle()
{
	cerr << "\nTimeTagTest::testFetchByDimensionIdAndNumberOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testFetchByTagSetIdAndTime_( OracleTestIds::TEST_TIME_TAG_ID );
}
//____________________________________________________________________________________________________________________________________________________________________________________
void TimeTagTest::testInUseOracle()
{
	cerr << "\nTimeTagTest::testInUseOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testInUse_();	
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Common --------------------------------------------------------------------------------------------------------------------

void TimeTagTest::testFetchById_( int id )
{
	unique_ptr<Tag> tag( Tag::fetch_( id ) );
	
	TimeTag expected( TEST_TIME_TAG_VALUE_HOURS, TEST_TIME_TAG_VALUE_MINUTES, TEST_TIME_TAG_VALUE_SECONDS, TEST_TIME_TAG_VALUE_MILLISECONDS );
	expected.setId_( id );
	expected.setTagSetId_( TEST_TIME_TAG_SET_ID );
	
	CPPUNIT_ASSERT_EQUAL( *dynamic_cast<Tag*>( &expected ), *tag );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TimeTagTest::testFetchByTagSetIdAndTime_( int id )
{
	unique_ptr<TimeTag> tag( TimeTag::fetch( TEST_TIME_TAG_SET_ID, TEST_TIME_TAG_VALUE_HOURS, TEST_TIME_TAG_VALUE_MINUTES, TEST_TIME_TAG_VALUE_SECONDS, TEST_TIME_TAG_VALUE_MILLISECONDS ) );
	
	TimeTag expected( TEST_TIME_TAG_VALUE_HOURS, TEST_TIME_TAG_VALUE_MINUTES, TEST_TIME_TAG_VALUE_SECONDS, TEST_TIME_TAG_VALUE_MILLISECONDS );
	expected.setId_( id );
	expected.setTagSetId_( TEST_TIME_TAG_SET_ID );
	
	CPPUNIT_ASSERT_EQUAL( *dynamic_cast<Tag*>( &expected ), *dynamic_cast<Tag*>( tag.get() ) );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TimeTagTest::testInUse_()
{
	Hub* hub = Hub::getHub();
	TimeTag timeTag( TEST_TIME_TAG_VALUE_HOURS + 1, TEST_TIME_TAG_VALUE_MINUTES, TEST_TIME_TAG_VALUE_SECONDS, TEST_TIME_TAG_VALUE_MILLISECONDS );
	TagSet* testDim = hub->getTagSet( TEST_TIME_TAG_SET_ID );
	const Tag* tag = testDim->addTag( &timeTag );
	
	CPPUNIT_ASSERT( tag->inUse() == false ); //Not in use yet
	
	Object object( TestIds::TEST_OBJECT_PREFIX + "img7.jpg" );
	object.create();
	ObjectTag objectTag( tag );
	object.addTag( objectTag );
	
	CPPUNIT_ASSERT( tag->inUse() == true ); 	
}
//____________________________________________________________________________________________________________________________________________________________________________________



