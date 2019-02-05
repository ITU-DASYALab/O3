/*
 *  ObjectTest.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 16.2.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "ObjectTest.h"

#include <cppunit/extensions/HelperMacros.h>

#include "ObjectAssertionTraits.h"
#include "../Hub.h"
#include "TestIds.h"
#include "../TagSet/AlphanumericalTagSet.h"
#include "../Tag/AlphanumericalTag.h"
#include "../ObjectTag.h"
#include "../LayerShared/SharedDefinitions.h"
#include "../LayerShared/Exception.h"
#include "../Boundaries/BoundingBox.h"

using namespace ObjectCube;

CPPUNIT_TEST_SUITE_REGISTRATION( ObjectTest );

//____________________________________________________________________________________________________________________________________________________________________________________

void ObjectTest::setUp()
{

}
//____________________________________________________________________________________________________________________________________________________________________________________

void ObjectTest::tearDown()
{

}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Canned tests --------------------------------------------------------------------------------------------------------------------

void ObjectTest::testFetchCanned()
{
	cerr << "\nObjectTest::testFetchCanned = ";
	Hub::setDataAccessType( Hub::CANNED );
	
	Object expected( TEST_OBJECT_NAME );
	expected.id_ = TEST_OBJECT_ID;
	
	Object object = Object::fetch( TEST_OBJECT_ID );
	
	CPPUNIT_ASSERT_EQUAL( expected, object );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void ObjectTest::testFetchNameCanned()
{
	cerr << "\nObjectTest::testCreateCanned = ";
	Hub::setDataAccessType( Hub::CANNED );
	
	Object expected( TEST_OBJECT_NAME );
	expected.id_ = TEST_OBJECT_ID;
	
	Object object = Object::fetch( TEST_OBJECT_NAME );
	
	CPPUNIT_ASSERT_EQUAL( expected, object );
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void ObjectTest::testCreateCanned()
{
	cerr << "\nObjectTest::testCreateCanned = ";
	Hub::setDataAccessType( Hub::CANNED );
	
	string name = "/Canned/UnitTest/img2.jpg";
	Object created( name );
	
	created.create();
	
	Object expected( name );
	expected.setId_( created.getId() ); //We are interested in seeing whether the rest matches
	
	Hub* hub = Hub::getHub();
	expected.tags_.push_back( const_cast<Tag*>( hub->getUncategorizedTag() ) );
	
	CPPUNIT_ASSERT( created.getId() > 0 );
	CPPUNIT_ASSERT_EQUAL( expected, created );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void ObjectTest::testAddTagCanned()
{
	cerr << "\nObjectTest::testAddTagCanned = ";
	Hub::setDataAccessType( Hub::CANNED );
	
	Object object = Object::fetch( TEST_OBJECT_ID );
	
	CPPUNIT_ASSERT( object.getTags().size() == 0 ); 
	
	Hub* hub = Hub::getHub(); 
	ObjectTag objectTag( hub->getUncategorizedTag() );
	object.addTag( objectTag );

	CPPUNIT_ASSERT( object.getTags().size() == 1 ); 
	CPPUNIT_ASSERT_EQUAL( *objectTag.getTag(), *object.getTags()[0].getTag() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void ObjectTest::testRemoveTagCanned()
{
	cerr << "\nObjectTest::testRemoveTagCanned = ";
	Hub::setDataAccessType( Hub::CANNED );
	
	Object object = Object::fetch( TEST_OBJECT_ID );
	Hub* hub = Hub::getHub(); 
	ObjectTag objectTag( hub->getUncategorizedTag() );
	object.addTag( objectTag );

	CPPUNIT_ASSERT( object.getTags().size() == 1 ); 
	
	object.removeTag( objectTag );
	
	CPPUNIT_ASSERT( object.getTags().size() == 0 ); 
}
//____________________________________________________________________________________________________________________________________________________________________________________

void ObjectTest::testHasUserTagsCanned()
{
	cerr << "\nObjectTest::testHasUserTagsCanned = ";
	Hub::setDataAccessType( Hub::CANNED );
	
	Object object = Object::fetch( TEST_OBJECT_ID );

	CPPUNIT_ASSERT( object.getTags().size() == 0 ); 
	CPPUNIT_ASSERT( object.hasUserTags() == false ); //No tags
	
	Hub* hub = Hub::getHub(); 
	ObjectTag objectTag( hub->getUncategorizedTag() ); //Not a user tag
	object.addTag( objectTag );

	CPPUNIT_ASSERT( object.hasUserTags() == false ); 
	
	AlphanumericalTag userTag( "Yet another user tag" );
	//userTag.setId_(TEST_TAG_ID + 1);
	AlphanumericalTagSet userDimension("A user dimension");
	userDimension.create();
	ObjectTag objectTag2( userDimension.addTag( &userTag ) );
	
	object.addTag( objectTag2 );
	
	CPPUNIT_ASSERT( object.hasUserTags() == true ); 
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  SQLite tests --------------------------------------------------------------------------------------------------------------------

void ObjectTest::testFetchSQLite()
{
	cerr << "\nObjectTest::testFetchSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testFetch_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void ObjectTest::testFetchNameSQLite()
{
	cerr << "\nObjectTest::testFetchSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testFetchName_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void ObjectTest::testCreateSQLite()
{
	cerr << "\nObjectTest::testCreateSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );

	testCreate_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void ObjectTest::testAddTagSQLite()
{
	cerr << "\nObjectTest::testAddTagSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );

	testAddTag_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void ObjectTest::testRemoveTagSQLite()
{
	cerr << "\nObjectTest::testRemoveTagSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testRemoveTag_();	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void ObjectTest::testHasUserTagsSQLite()
{
	cerr << "\nObjectTest::testHasUserTagsSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testHasUserTags_( SQLiteTestIds::TEST_ALPHANUMERICAL_TAG_ID );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void ObjectTest::testEraseSQLite()
{
	cerr << "\nObjectTest::testEraseSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testErase_( SQLiteTestIds::TEST_ALPHANUMERICAL_TAG_ID, SQLiteTestIds::TEST_NUMERICAL_TAG_ID );
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  MonetDB tests --------------------------------------------------------------------------------------------------------------------

void ObjectTest::testFetchMonetDB()
{
	cerr << "\nObjectTest::testFetchMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );

	testFetch_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void ObjectTest::testFetchNameMonetDB()
{
	cerr << "\nObjectTest::testFetchNameMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );
	
	testFetchName_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void ObjectTest::testCreateMonetDB()
{
	cerr << "\nObjectTest::testCreateMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );
	
	testCreate_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void ObjectTest::testAddTagMonetDB()
{
	cerr << "\nObjectTest::testAddTagMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );
	
	testAddTag_( 20, 85, 64, 12);
}
//____________________________________________________________________________________________________________________________________________________________________________________

void ObjectTest::testRemoveTagMonetDB()
{
	cerr << "\nObjectTest::testRemoveTagMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );
	
	testRemoveTag_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void ObjectTest::testHasUserTagsMonetDB()
{
	cerr << "\nObjectTest::testHasUserTagsMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );

	testHasUserTags_( MonetDBTestIds::TEST_ALPHANUMERICAL_TAG_ID );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void ObjectTest::testEraseMonetDB()
{
	cerr << "\nObjectTest::testEraseMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );
	
	testErase_( MonetDBTestIds::TEST_ALPHANUMERICAL_TAG_ID, MonetDBTestIds::TEST_NUMERICAL_TAG_ID );
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Oracle tests --------------------------------------------------------------------------------------------------------------------

void ObjectTest::testFetchOracle()
{
	cerr << "\nObjectTest::testFetchOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testFetch_();	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void ObjectTest::testFetchNameOracle()
{
	cerr << "\nObjectTest::testFetchNameOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testFetchName_();	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void ObjectTest::testCreateOracle()
{
	cerr << "\nObjectTest::testCreateOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testCreate_();	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void ObjectTest::testAddTagOracle()
{
	cerr << "\nObjectTest::testAddTagOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testAddTag_();	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void ObjectTest::testRemoveTagOracle()
{
	cerr << "\nObjectTest::testRemoveTagOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testRemoveTag_();	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void ObjectTest::testHasUserTagsOracle()
{
	cerr << "\nObjectTest::testHasUserTagsOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testHasUserTags_( OracleTestIds::TEST_ALPHANUMERICAL_TAG_ID );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void ObjectTest::testEraseOracle()
{
	cerr << "\nObjectTest::testEraseOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testErase_( OracleTestIds::TEST_ALPHANUMERICAL_TAG_ID, OracleTestIds::TEST_NUMERICAL_TAG_ID );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Common --------------------------------------------------------------------------------------------------------------------

void ObjectTest::testFetch_()
{
	Object object = Object::fetch( TEST_OBJECT_ID );
	
	CPPUNIT_ASSERT_EQUAL( (int)TEST_OBJECT_ID, object.getId() );
	CPPUNIT_ASSERT_EQUAL( TestIds::TEST_OBJECT_PREFIX + TEST_OBJECT_NAME, object.getName() );	
}

//____________________________________________________________________________________________________________________________________________________________________________________

void ObjectTest::testFetchName_()
{
	string qualifiedName = TestIds::TEST_OBJECT_PREFIX + TEST_OBJECT_NAME;
	Object object = Object::fetch( qualifiedName );
	
	CPPUNIT_ASSERT_EQUAL( (int)TEST_OBJECT_ID, object.getId() );
	CPPUNIT_ASSERT_EQUAL( qualifiedName, object.getName() );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void ObjectTest::testCreate_()
{
	string name = TestIds::TEST_OBJECT_PREFIX + "img1.jpg";
	Object created( name );
	
	created.create();
	
	Object expected = Object::fetch( created.getId() );
	
	CPPUNIT_ASSERT( created.getId() != (int)INVALID_VALUE );
	CPPUNIT_ASSERT_EQUAL( expected, created );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void ObjectTest::testAddTag_( int upperLeftX, int upperLeftY, int lowerRightX, int lowerRightY )
{
	Hub* hub = Hub::getHub();
	Object object = Object::fetch( TEST_OBJECT_ID );	
	
	TagSet* tagSet = hub->getTagSet( TEST_ALPHANUMERICAL_TAG_SET_ID );
	AlphanumericalTag tag( "Add tag to object unit test" );
	BoundingBox bBox( Coordinate2D( upperLeftX, upperLeftY), Coordinate2D( lowerRightX, lowerRightY ) );
	ObjectTag objectTag( tagSet->addTag( &tag ), bBox );
	
	object.addTag( objectTag );
	
	const ObjectTag objectTagExpected = object.getTag( objectTag.getTag()->getId() );
	
	CPPUNIT_ASSERT_EQUAL( *objectTagExpected.getTag(), *objectTag.getTag() );
	
	//Test persistent storage
	Object expected = Object::fetch( object.getId() );
	CPPUNIT_ASSERT_EQUAL( expected, object );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void ObjectTest::testRemoveTag_()
{
	Hub* hub = Hub::getHub();
	Object object = Object::fetch( TEST_OBJECT_ID );	
	TagSet* tagSet = hub->getTagSet( TEST_ALPHANUMERICAL_TAG_SET_ID );
	
	AlphanumericalTag tagData( "Add & remove tag for unit test" );
	
	ObjectTag objectTag( tagSet->addTag( &tagData ) );
	object.addTag( objectTag );
	
	//const Tag* tagExpected = object.getTag( tag->getId() );  //Throws an exception if it is not found
	
	object.removeTag( objectTag );
	
	CPPUNIT_ASSERT_THROW( object.getTag( objectTag.getTag()->getId() ), ObjectCube::Exception);
	
	//Test persistent storage
	Object expected = Object::fetch( object.getId() );
	CPPUNIT_ASSERT_EQUAL( expected, object );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void ObjectTest::testHasUserTags_( int id )
{
	Hub* hub = Hub::getHub();
	
	string name = TestIds::TEST_OBJECT_PREFIX + "img3.jpg";
	Object object( name );
	
	object.create();
	
	CPPUNIT_ASSERT_EQUAL( false, object.hasUserTags() );
	
	TagSet* tagSet = hub->getTagSet( TEST_ALPHANUMERICAL_TAG_SET_ID );
	ObjectTag objectTag( tagSet->getTag( id ) );
	object.addTag( objectTag );
	
	CPPUNIT_ASSERT_EQUAL( true, object.hasUserTags() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void ObjectTest::testErase_( int alphanumericalId, int numericalId )
{
	Object toErase( TestIds::TEST_OBJECT_PREFIX + "img9.jpg" );
	toErase.create();
	int objectId = toErase.getId();
	
	Hub* hub = Hub::getHub();
	TagSet* aTagSet = hub->getTagSet( TEST_ALPHANUMERICAL_TAG_SET_ID );
	TagSet* nTagSet = hub->getTagSet( TEST_NUMERICAL_TAG_SET_ID );
	
	const Tag* aTag = aTagSet->getTag( alphanumericalId );
	const Tag* nTag = nTagSet->getTag( numericalId );
	
	ObjectTag objectTagA( aTag );
	ObjectTag objectTagN( nTag );
	
	toErase.addTag( objectTagA );
	toErase.addTag( objectTagN );
	
	toErase.erase();
	
	CPPUNIT_ASSERT_THROW( Object::fetch( objectId ), ObjectCube::Exception );	
}
//____________________________________________________________________________________________________________________________________________________________________________________























