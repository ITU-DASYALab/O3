/*
 *  NumericalTagTest.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 30.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "NumericalTagTest.h"

#include <cppunit/extensions/HelperMacros.h>

#include "TagAssertionTraits.h"
#include "../Hub.h"
#include "TestIds.h"
#include "../TagSet/TagSet.h"
#include "../Tag/NumericalTag.h"

using namespace ObjectCube;

CPPUNIT_TEST_SUITE_REGISTRATION( NumericalTagTest );

//____________________________________________________________________________________________________________________________________________________________________________________

void NumericalTagTest::setUp()
{	
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void NumericalTagTest::tearDown()
{
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Canned tests --------------------------------------------------------------------------------------------------------------------

void NumericalTagTest::testCreateCanned()
{
	cerr << "\nNumericalTagTest::testCreateCanned = ";
	Hub::setDataAccessType( Hub::CANNED );
	
	NumericalTag tag( TEST_NUMERICAL_TAG_VALUE + 1 );
	tag.setTagSetId_( 1 ); //Should only be created through a dimension.
	tag.create_();
	
	CPPUNIT_ASSERT( tag.getId() > 0 ); //The only thing that changes
}
//____________________________________________________________________________________________________________________________________________________________________________________

void NumericalTagTest::testFetchByIdCanned()
{
	cerr << "\nNumericalTagTest::testFetchByIdCanned = ";
	Hub::setDataAccessType( Hub::CANNED );

	int id = 1;
	unique_ptr<Tag> tag( Tag::fetch_( id ) );
	NumericalTag expected( TEST_NUMERICAL_TAG_VALUE );
	expected.setId_( id );
	expected.setTagSetId_( 2 );	
	expected.setTypeId_( 1 );
	
	CPPUNIT_ASSERT_EQUAL( *dynamic_cast<Tag*>( &expected ), *tag.get() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void NumericalTagTest::testFetchByDimensionIdAndNumberCanned()
{
	cerr << "\nNumericalTagTest::testFetchByDimensionIdAndNumberCanned = ";
	Hub::setDataAccessType( Hub::CANNED );
	
	unique_ptr<NumericalTag> tag( NumericalTag::fetch( TEST_NUMERICAL_TAG_SET_ID, TEST_NUMERICAL_TAG_VALUE ) );
	
	NumericalTag expected( TEST_NUMERICAL_TAG_VALUE );
	expected.setId_( TEST_NUMERICAL_TAG_ID_CANNED );
	expected.setTagSetId_( TEST_NUMERICAL_TAG_SET_ID );
	
	CPPUNIT_ASSERT_EQUAL( *dynamic_cast<Tag*>( &expected ), *dynamic_cast<Tag*>( tag.get() ) );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void NumericalTagTest::testInUseCanned()
{
	cerr << "\nNumericalTagTest::testInUseCanned = ";
	Hub::setDataAccessType( Hub::CANNED );
	
	Hub* hub = Hub::getHub(); 
	const Tag* tag = hub->getUncategorizedTag();
	
	CPPUNIT_ASSERT( tag->inUse() == false ); //No persistent storage
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  SQLite tests --------------------------------------------------------------------------------------------------------------------

void NumericalTagTest::testFetchByIdSQLite()
{
	cerr << "\nNumericalTagTest::testFetchByIdSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testFetchById_( SQLiteTestIds::TEST_NUMERICAL_TAG_ID );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void NumericalTagTest::testFetchByDimensionIdAndNumberSQLite()
{
	cerr << "\nNumericalTagTest::testFetchByDimensionIdAndNumberSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testFetchByTagSetIdAndNumber_( SQLiteTestIds::TEST_NUMERICAL_TAG_ID );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void NumericalTagTest::testInUseSQLite()
{
	cerr << "\nNumericalTagTest::testInUseSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testInUse_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  MonetDB tests --------------------------------------------------------------------------------------------------------------------

void NumericalTagTest::testFetchByIdMonetDB()
{
	cerr << "\nNumericalTagTest::testFetchByIdMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );

	testFetchById_( MonetDBTestIds::TEST_NUMERICAL_TAG_ID );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void NumericalTagTest::testFetchByDimensionIdAndNumberMonetDB()
{
	cerr << "\nNumericalTagTest::testFetchByDimensionIdAndNumberMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );

	testFetchByTagSetIdAndNumber_( MonetDBTestIds::TEST_NUMERICAL_TAG_ID );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void NumericalTagTest::testInUseMonetDB()
{
	cerr << "\nNumericalTagTest::testInUseMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );

	testInUse_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Oracle tests --------------------------------------------------------------------------------------------------------------------

void NumericalTagTest::testFetchByIdOracle()
{
	cerr << "\nNumericalTagTest::testFetchByIdOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testFetchById_( OracleTestIds::TEST_NUMERICAL_TAG_ID );
}
//____________________________________________________________________________________________________________________________________________________________________________________
void NumericalTagTest::testFetchByDimensionIdAndNumberOracle()
{
	cerr << "\nNumericalTagTest::testFetchByDimensionIdAndNumberOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testFetchByTagSetIdAndNumber_( OracleTestIds::TEST_NUMERICAL_TAG_ID );
}
//____________________________________________________________________________________________________________________________________________________________________________________
void NumericalTagTest::testInUseOracle()
{
	cerr << "\nNumericalTagTest::testInUseOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testInUse_();	
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Common --------------------------------------------------------------------------------------------------------------------

void NumericalTagTest::testFetchById_( int id )
{
	unique_ptr<Tag> tag( Tag::fetch_( id ) );
	
	NumericalTag expected( TEST_NUMERICAL_TAG_VALUE );
	expected.setId_( id );
	expected.setTagSetId_( TEST_NUMERICAL_TAG_SET_ID );
	
	CPPUNIT_ASSERT_EQUAL( *dynamic_cast<Tag*>( &expected ), *tag.get() );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void NumericalTagTest::testFetchByTagSetIdAndNumber_( int tagId )
{
	unique_ptr<NumericalTag> tag( NumericalTag::fetch( TEST_NUMERICAL_TAG_SET_ID, TEST_NUMERICAL_TAG_VALUE ) );
	
	NumericalTag expected( TEST_NUMERICAL_TAG_VALUE );
	expected.setId_( tagId );
	expected.setTagSetId_( TEST_NUMERICAL_TAG_SET_ID );
	
	CPPUNIT_ASSERT_EQUAL( *dynamic_cast<Tag*>( &expected ), *dynamic_cast<Tag*>( tag.get() ) );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void NumericalTagTest::testInUse_()
{
	Hub* hub = Hub::getHub();
	NumericalTag tagData( TEST_NUMERICAL_TAG_VALUE + 1 );
	TagSet* testDim = hub->getTagSet( TEST_NUMERICAL_TAG_SET_ID );
	const Tag* tag = testDim->addTag( &tagData );
	
	CPPUNIT_ASSERT( tag->inUse() == false ); //Not in use yet
	
	Object object( TestIds::TEST_OBJECT_PREFIX + "img6.jpg" );
	object.create();
	ObjectTag objectTag( tag );
	object.addTag( objectTag );
	
	CPPUNIT_ASSERT( tag->inUse() == true ); 	
}
//____________________________________________________________________________________________________________________________________________________________________________________


