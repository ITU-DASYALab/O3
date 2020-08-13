/*
 *  TagSetTest.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 17.2.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "TagSetTest.h"

#include <cppunit/extensions/HelperMacros.h>

#include "../Hub.h"
#include "TestIds.h"
#include "../TagSet/TagSet.h"
#include "../TagSet/AlphanumericalTagSet.h"
#include "TagSetAssertionTraits.h"
#include "TagAssertionTraits.h"
#include "../Tag/AlphanumericalTag.h"
#include "../LayerShared/HubCommon.h"
#include "../LayerShared/Exception.h"
#include "../LayerShared/SharedDefinitions.h"

using namespace ObjectCube;

CPPUNIT_TEST_SUITE_REGISTRATION( TagSetTest );

//____________________________________________________________________________________________________________________________________________________________________________________

void TagSetTest::setUp()
{

}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSetTest::tearDown()
{
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Canned tests --------------------------------------------------------------------------------------------------------------------

void TagSetTest::testFetchCanned()
{
	cerr << "\nTagSetTest::testFetchCanned = ";
	Hub::setDataAccessType( Hub::CANNED );
	
	Hub* hub = Hub::getHub();
	TagSet* tagSet = hub->getTagSet( TEST_ALPHANUMERICAL_TAG_SET_ID );
	
	/*
	expected_->setId_( TEST_ALPHANUMERICAL_TAG_SET_ID );
	expected_->setName( HubCommon::getUncategorizedDimensionName() );
	expected_->setAccessId_( TagSet::SYSTEM );
	expected_->setTypeId_( TagSet::ALPHANUMERICAL );
	
	AlphanumericalTag* tag = new AlphanumericalTag( HubCommon::getUncategorizedTagName() );
	tag->tagSetId_ = TEST_ALPHANUMERICAL_TAG_SET_ID;
	tag->id_ = TEST_ALPHANUMERICAL_TAG_ID_CANNED;
	vector<Tag*> tags;
	tags.push_back( tag );
	expected_->setTags_( tags );
	*/
	int id = TEST_ALPHANUMERICAL_TAG_SET_ID; //Test
	int accessId = TagSet::SYSTEM;
	int typeId = TagSet::ALPHANUMERICAL;
	string name = Hub::getUncategorizedDimensionName();
	
	CPPUNIT_ASSERT_EQUAL( id, tagSet->getId() );
	CPPUNIT_ASSERT_EQUAL( accessId, tagSet->getAccessId() );
	CPPUNIT_ASSERT_EQUAL( typeId, tagSet->getTypeId() );
	CPPUNIT_ASSERT_EQUAL( name, tagSet->getName() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSetTest::testFetchNameCanned()
{
	cerr << "\nTagSetTest::testFetchNameCanned = ";
	
	Hub::setDataAccessType( Hub::CANNED );
	
	Hub* hub = Hub::getHub();
	TagSet* tagSetById = hub->getTagSet( TEST_ALPHANUMERICAL_TAG_SET_ID );
	TagSet* tagSetByName = hub->getTagSet( tagSetById->getName() );
	CPPUNIT_ASSERT_EQUAL( tagSetById, tagSetByName );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSetTest::testAddTagCanned()
{
	cerr << "\nTagSetTest::testAddTagCanned = ";
	Hub::setDataAccessType( Hub::CANNED );

	Hub* hub = Hub::getHub();
	TagSet* tagSet = hub->getTagSet( TEST_ALPHANUMERICAL_TAG_SET_ID );
	
	AlphanumericalTag tagData( "TagSet add test tag" );
	tagData.id_ = TEST_ALPHANUMERICAL_TAG_ID_CANNED + 1;
	const Tag* tag = tagSet->addTag( &tagData );
	
	const Tag* tagExpected = tagSet->getTag( tag->getId() );  //Testing getTag(id)
	
	CPPUNIT_ASSERT_EQUAL( const_cast<Tag*>( tagExpected ), const_cast<Tag*>( tag ) );
	
	if( tagSet->getTypeId() == TagSetCommon::ALPHANUMERICAL )
	{
		const Tag* tagExpected2 = dynamic_cast<AlphanumericalTagSet*>( tagSet )->getAlphanumericalTag( dynamic_cast<const AlphanumericalTag*>( tag )->getName() ); //Testing getTag(name)
		
		CPPUNIT_ASSERT_EQUAL( const_cast<Tag*>( tagExpected2 ), const_cast<Tag*>( tag ) ); 
	}
	tagSet->deleteTag( tag ); //Resetting
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSetTest::testDeleteTagCanned()
{
	cerr << "\nTagSetTest::testDeleteTagCanned = ";
	Hub::setDataAccessType( Hub::CANNED );
	
	Hub* hub = Hub::getHub();
	TagSet* tagSet = hub->getTagSet( TEST_ALPHANUMERICAL_TAG_SET_ID );
	
	AlphanumericalTag tagData( "TagSet add test tag" );
	tagData.id_ = TEST_ALPHANUMERICAL_TAG_ID_CANNED + 1;
	const Tag* tag = tagSet->addTag( &tagData );
		
	const Tag* tagExpected = tagSet->getTag( tag->getId() );  
	
	CPPUNIT_ASSERT_EQUAL( const_cast<Tag*>( tagExpected ), const_cast<Tag*>( tag ) ); 
	
	CPPUNIT_ASSERT( tagSet->getTags().size() == 3 );
	
	const AlphanumericalTag tagCopy = *dynamic_cast<const AlphanumericalTag*>( tag );
	tagSet->deleteTag( tag );  //All tag pointers from this tag-set may now be invalid!
	CPPUNIT_ASSERT( tagSet->getTags().size() == 2 );

	CPPUNIT_ASSERT_THROW( tagSet->deleteTag( &tagCopy ), ObjectCube::Exception); 
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSetTest::testGetTagIdCanned()
{
	cerr << "\nTagSetTest::testGetTagIdCanned = ";
	Hub::setDataAccessType( Hub::CANNED );
	
	Hub* hub = Hub::getHub();
	TagSet* tagSet = hub->getTagSet( TEST_ALPHANUMERICAL_TAG_SET_ID );
	
	AlphanumericalTag tagData( "TagSet add test tag" );
	tagData.id_ = TEST_ALPHANUMERICAL_TAG_ID_CANNED + 1;
	const Tag* tag = tagSet->addTag( &tagData );
	
	const Tag* tagExpected = tagSet->getTag( tag->getId() );  
	
	CPPUNIT_ASSERT_EQUAL( const_cast<Tag*>( tagExpected ), const_cast<Tag*>( tag ) );
	CPPUNIT_ASSERT_THROW( tagSet->getTag( TEST_ALPHANUMERICAL_TAG_ID_CANNED + 500), ObjectCube::Exception ); //Does not exist
	
	tagSet->deleteTag( tag );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSetTest::testGetTagNameCanned()
{
	cerr << "\nTagSetTest::testGetTagNameCanned = ";
	Hub::setDataAccessType( Hub::CANNED );
	
	Hub* hub = Hub::getHub();
	TagSet* tagSet = hub->getTagSet( TEST_ALPHANUMERICAL_TAG_SET_ID );
	
	string dimName = "TagSet add test tag";
	AlphanumericalTag tagData( dimName );
	tagData.id_ = TEST_ALPHANUMERICAL_TAG_ID_CANNED + 1;
	const Tag* tag = tagSet->addTag( &tagData );
	
	if( tagSet->getTypeId() == TagSetCommon::ALPHANUMERICAL )
	{
		const Tag* tagExpected = dynamic_cast<AlphanumericalTagSet*>( tagSet )->getAlphanumericalTag( dimName );  
	
		CPPUNIT_ASSERT_EQUAL( const_cast<Tag*>( tagExpected ), const_cast<Tag*>( tag ) );
		CPPUNIT_ASSERT_THROW( dynamic_cast<AlphanumericalTagSet*>( tagSet )->getAlphanumericalTag( "Tag that does not exist" ), ObjectCube::Exception ); //Does not exist
	}
	tagSet->deleteTag( tag ); //cleanup
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSetTest::testCreateHierarchyCanned()
{
	cerr << "\nTagSetTest::testCreateHierarchyCanned = ";
	Hub::setDataAccessType( Hub::CANNED );
	
	Hub* hub = Hub::getHub();
	TagSet* tagSet = hub->getTagSet( TEST_ALPHANUMERICAL_TAG_SET_ID );

	CPPUNIT_ASSERT( tagSet->getDimensions().size() == 2 );
	
	string dimName = "TagSet add test tag";
	AlphanumericalTag tagData( dimName );
	tagData.id_ = TEST_ALPHANUMERICAL_TAG_ID_CANNED + 1;
	const Tag* tag = tagSet->addTag( &tagData );
	
	PersistentDimension* hierarchy = tagSet->createPersistentDimension( tag );
	
	CPPUNIT_ASSERT( hierarchy->getId() != INVALID_VALUE );
	CPPUNIT_ASSERT( hierarchy->getTagSetId() != INVALID_VALUE );
	CPPUNIT_ASSERT( hierarchy->getPersistentRoot()->getId() != INVALID_VALUE );
	CPPUNIT_ASSERT( hierarchy->getPersistentRoot()->getTagSetId() == hierarchy->getTagSetId() );
	CPPUNIT_ASSERT( hierarchy->getPersistentRoot()->getDimensionId() == hierarchy->getId() );
	CPPUNIT_ASSERT( hierarchy->getPersistentRoot()->getLeftBorder() != INVALID_VALUE );
	CPPUNIT_ASSERT( hierarchy->getPersistentRoot()->getRightBorder() != INVALID_VALUE );
	CPPUNIT_ASSERT( hierarchy->getPersistentRoot()->getRightBorder() > hierarchy->getPersistentRoot()->getLeftBorder() );
	CPPUNIT_ASSERT( hierarchy->getPersistentRoot()->getTagId() != INVALID_VALUE );
	
	PersistentDimension* expected = tagSet->getPersistentDimension( hierarchy->getId() );
	
	CPPUNIT_ASSERT_EQUAL( expected, hierarchy );
	
	tagSet->deleteTag( tag ); //Cleanup
	tagSet->deleteDimension( hierarchy->getId() ); //Cleanup
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSetTest::testDeleteHierarchyCanned()
{
	cerr << "\nTagSetTest::testDeleteHierarchyCanned = ";
	Hub::setDataAccessType( Hub::CANNED );
	
	Hub* hub = Hub::getHub();
	TagSet* tagSet = hub->getTagSet( TEST_ALPHANUMERICAL_TAG_SET_ID );

	CPPUNIT_ASSERT( tagSet->getDimensions().size() == 2 );
	
	string dimName = "TagSet add test tag";
	AlphanumericalTag tagData( dimName );
	tagData.id_ = TEST_ALPHANUMERICAL_TAG_ID_CANNED + 1;
	const Tag* tag = tagSet->addTag( &tagData );
	
	PersistentDimension* hierarchy = tagSet->createPersistentDimension( tag );
	CPPUNIT_ASSERT_EQUAL( 3, (int)tagSet->getDimensions().size() );
	
	tagSet->deleteDimension( hierarchy->getId() );

	CPPUNIT_ASSERT_EQUAL( 2, (int)tagSet->getDimensions().size() ); // Has been deleted
	
	tagSet->deleteTag( tag ); //Cleanup
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSetTest::testGetHierarchyCanned()
{
	cerr << "\nTagSetTest::testGetHierarchyCanned = ";
	Hub::setDataAccessType( Hub::CANNED );
	
	Hub* hub = Hub::getHub();
	TagSet* tagSet = hub->getTagSet( TEST_ALPHANUMERICAL_TAG_SET_ID );
	
	CPPUNIT_ASSERT( tagSet->getDimensions().size() == 2 );
	
	string dimName = "TagSet add test tag";
	AlphanumericalTag tagData( dimName );
	tagData.id_ = TEST_ALPHANUMERICAL_TAG_ID_CANNED + 1;
	const Tag* tag = tagSet->addTag( &tagData );
	
	PersistentDimension* hierarchy = tagSet->createPersistentDimension( tag );

	PersistentDimension* expected = tagSet->getPersistentDimension( hierarchy->getId() );
	
	CPPUNIT_ASSERT_EQUAL( expected, hierarchy );
	
	tagSet->deleteDimension( hierarchy->getId() ); //Cleanup
	tagSet->deleteTag( tag ); //Cleanup
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  SQLite tests --------------------------------------------------------------------------------------------------------------------

void TagSetTest::testFetchSQLite()
{
	cerr << "\nTagSetTest::testFetchSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testFetch_( TEST_SQLITE_CLEANUP_PREFIX + " Alphanumerical unit test tag-set" );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSetTest::testFetchNameSQLite()
{
	cerr << "\nTagSetTest::testFetchNameSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );

	testFetchName_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSetTest::testAddTagSQLite()
{
	cerr << "\nTagSetTest::testAddTagSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testAddTag_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSetTest::testDeleteTagSQLite()
{
	cerr << "\nTagSetTest::testDeleteTagSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testDeleteTag_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSetTest::testGetTagIdSQLite()
{
	cerr << "\nTagSetTest::testGetTagIdSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testGetTagId_( SQLiteTestIds::TEST_ALPHANUMERICAL_TAG_ID );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSetTest::testGetTagNameSQLite()
{
	cerr << "\nTagSetTest::testGetTagNameSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testGetTagName_( SQLiteTestIds::TEST_ALPHANUMERICAL_TAG_ID, TEST_SQLITE_CLEANUP_PREFIX + TEST_ALPHANUMERICAL_TAG_NAME );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSetTest::testCreateHierarchySQLite()
{
	cerr << "\nTagSetTest::testCreateHierarchySQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );

	testCreateHierarchy_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSetTest::testDeleteHierarchySQLite()
{
	cerr << "\nTagSetTest::testDeleteHierarchySQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );

	testDeleteHierarchy_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSetTest::testGetHierarchySQLite()
{
	cerr << "\nTagSetTest::testGetHierarchySQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );

	testGetHierarchy_( SQLiteTestIds::TEST_ALPHANUMERICAL_TAG_ID );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSetTest::testEraseSQLite()
{
	cerr << "\nTagSetTest::testEraseSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testErase_( TEST_SQLITE_CLEANUP_PREFIX + " erase tag-set test" );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSetTest::testTypeAsStringSQLite()
{
	cerr << "\nTagSetTest::testTypeAsStringSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );

	testTypeAsString_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSetTest::testAccessTypeAsStringSQLite()
{
	cerr << "\nTagSetTest::testAccessTypeAsStringSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testAccessTypeAsString_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  MonetDB tests --------------------------------------------------------------------------------------------------------------------

void TagSetTest::testFetchMonetDB()
{
	cerr << "\nTagSetTest::testFetchMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );

	testFetch_( string( TEST_MONETDB_CLEANUP_PREFIX + " Alphanumerical unit test tag-set" ) );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSetTest::testFetchNameMonetDB()
{
	cerr << "\nTagSetTest::testFetchNameMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );
	
	testFetchName_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSetTest::testAddTagMonetDB()
{
	cerr << "\nTagSetTest::testAddTagMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );
	
	testAddTag_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSetTest::testDeleteTagMonetDB()
{
	cerr << "\nTagSetTest::testDeleteTagMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );
	
	testDeleteTag_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSetTest::testGetTagIdMonetDB()
{
	cerr << "\nTagSetTest::testGetTagIdMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );
	
	testGetTagId_( MonetDBTestIds::TEST_ALPHANUMERICAL_TAG_ID );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSetTest::testGetTagNameMonetDB()
{
	cerr << "\nTagSetTest::testGetTagNameMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );
	
	testGetTagName_( MonetDBTestIds::TEST_ALPHANUMERICAL_TAG_ID, TEST_MONETDB_CLEANUP_PREFIX + TEST_ALPHANUMERICAL_TAG_NAME );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSetTest::testCreateHierarchyMonetDB()
{
	cerr << "\nTagSetTest::testCreateHierarchyMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );

	testCreateHierarchy_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSetTest::testDeleteHierarchyMonetDB()
{
	cerr << "\nTagSetTest::testDeleteHierarchyMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );
	
	testDeleteHierarchy_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSetTest::testGetHierarchyMonetDB()
{
	cerr << "\nTagSetTest::testGetHierarchyMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );

	testGetHierarchy_( MonetDBTestIds::TEST_ALPHANUMERICAL_TAG_ID );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSetTest::testEraseMonetDB()
{
	cerr << "\nTagSetTest::testEraseMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );
	
	testErase_( TEST_MONETDB_CLEANUP_PREFIX + " erase tag-set test" );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSetTest::testTypeAsStringMonetDB()
{
	cerr << "\nTagSetTest::testTypeAsStringMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );

	testTypeAsString_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSetTest::testAccessTypeAsStringMonetDB()
{
	cerr << "\nTagSetTest::testAccessTypeAsStringMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );
	
	testAccessTypeAsString_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Oracle tests --------------------------------------------------------------------------------------------------------------------

void TagSetTest::testFetchOracle()
{
	cerr << "\nTagSetTest::testFetchOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testFetch_( string( TEST_ORACLE_CLEANUP_PREFIX + " Alphanumerical unit test tag-set" ) );
}
//____________________________________________________________________________________________________________________________________________________________________________________
void TagSetTest::testFetchNameOracle()
{
	cerr << "\nTagSetTest::testFetchNameOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testFetchName_();	
}
//____________________________________________________________________________________________________________________________________________________________________________________
void TagSetTest::testAddTagOracle()
{
	cerr << "\nTagSetTest::testAddTagOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testAddTag_();	
}
//____________________________________________________________________________________________________________________________________________________________________________________
void TagSetTest::testDeleteTagOracle()
{
	cerr << "\nTagSetTest::testDeleteTagOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testDeleteTag_();	
}
//____________________________________________________________________________________________________________________________________________________________________________________
void TagSetTest::testGetTagIdOracle()
{
	cerr << "\nTagSetTest::testGetTagIdOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testGetTagId_( OracleTestIds::TEST_ALPHANUMERICAL_TAG_ID );	
}
//____________________________________________________________________________________________________________________________________________________________________________________
void TagSetTest::testGetTagNameOracle()
{
	cerr << "\nTagSetTest::testGetTagNameOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testGetTagName_( OracleTestIds::TEST_ALPHANUMERICAL_TAG_ID, TEST_ORACLE_CLEANUP_PREFIX + TEST_ALPHANUMERICAL_TAG_NAME );	
}
//____________________________________________________________________________________________________________________________________________________________________________________
void TagSetTest::testCreateHierarchyOracle()
{
	cerr << "\nTagSetTest::testCreateHierarchyOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testCreateHierarchy_();	
}
//____________________________________________________________________________________________________________________________________________________________________________________
void TagSetTest::testDeleteHierarchyOracle()
{
	cerr << "\nTagSetTest::testDeleteHierarchyOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testDeleteHierarchy_();	
}
//____________________________________________________________________________________________________________________________________________________________________________________
void TagSetTest::testGetHierarchyOracle()
{
	cerr << "\nTagSetTest::testGetHierarchyOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testGetHierarchy_( OracleTestIds::TEST_ALPHANUMERICAL_TAG_ID );	
}
//____________________________________________________________________________________________________________________________________________________________________________________
void TagSetTest::testEraseOracle()
{
	cerr << "\nTagSetTest::testEraseOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testErase_( TEST_ORACLE_CLEANUP_PREFIX + " erase tag-set test" );	
}
//____________________________________________________________________________________________________________________________________________________________________________________
void TagSetTest::testTypeAsStringOracle()
{
	cerr << "\nTagSetTest::testTypeAsStringOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testTypeAsString_();	
}
//____________________________________________________________________________________________________________________________________________________________________________________
void TagSetTest::testAccessTypeAsStringOracle()
{
	cerr << "\nTagSetTest::testAccessTypeAsStringOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testAccessTypeAsString_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Common --------------------------------------------------------------------------------------------------------------------

void TagSetTest::testFetch_( string name )
{
	Hub* hub = Hub::getHub();
	TagSet* tagSet = hub->getTagSet( TEST_ALPHANUMERICAL_TAG_SET_ID );
	
	CPPUNIT_ASSERT_EQUAL( (int)TEST_ALPHANUMERICAL_TAG_SET_ID, tagSet->getId() );
	CPPUNIT_ASSERT_EQUAL( (int)TagSet::USER, tagSet->getAccessId() );
	CPPUNIT_ASSERT_EQUAL( (int)TagSet::ALPHANUMERICAL, tagSet->getTypeId() );
	CPPUNIT_ASSERT_EQUAL( name, tagSet->getName() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSetTest::testFetchName_()
{
	Hub* hub = Hub::getHub();
	TagSet* tagSetById = hub->getTagSet( TEST_ALPHANUMERICAL_TAG_SET_ID );
	TagSet* tagSetByName = hub->getTagSet( tagSetById->getName() );
	CPPUNIT_ASSERT_EQUAL( tagSetById, tagSetByName );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSetTest::testAddTag_()
{
	Hub* hub = Hub::getHub();
	TagSet* tagSet = hub->getTagSet( TEST_ALPHANUMERICAL_TAG_SET_ID );
	
	AlphanumericalTag tagData( "TagSet add test tag" );
	const Tag* tag = tagSet->addTag( &tagData );
	
	const Tag* tagExpected = tagSet->getTag( tag->getId() );  //Testing getTag(id)
	CPPUNIT_ASSERT_EQUAL( *const_cast<Tag*>( tagExpected ), *const_cast<Tag*>( tag ) );
	
	if( tagSet->getTypeId() == TagSetCommon::ALPHANUMERICAL )
	{
		const AlphanumericalTag* tagExpected = dynamic_cast<AlphanumericalTagSet*>( tagSet)->getAlphanumericalTag( dynamic_cast<const AlphanumericalTag*>( tag )->getName() ); //Testing getTag(name)
		CPPUNIT_ASSERT_EQUAL( *dynamic_cast<Tag*>( const_cast<AlphanumericalTag*>( tagExpected ) ), *const_cast<Tag*>( tag ) ); 
	}
	unique_ptr<Tag> persistentTag( Tag::fetch_( tag->getId() ) ); //Persistence testing
	CPPUNIT_ASSERT_EQUAL( *persistentTag.get(), *tag );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSetTest::testDeleteTag_()
{
	Hub* hub = Hub::getHub();
	TagSet* tagSet = hub->getTagSet( TEST_ALPHANUMERICAL_TAG_SET_ID );
	
	AlphanumericalTag tagData( "TagSet delete test tag" );
	const Tag* tag = tagSet->addTag( &tagData );
	
	const Tag* tagExpected = tagSet->getTag( tag->getId() );  
	CPPUNIT_ASSERT_EQUAL( const_cast<Tag*>( tagExpected ), const_cast<Tag*>( tag ) ); 
	
	const AlphanumericalTag tagCopy = *dynamic_cast<const AlphanumericalTag*>( tag );  //To use after deletion of tag
	tagSet->deleteTag( tag ); //The tag pointer gets deleted, no usage after deletion !!!
	
	CPPUNIT_ASSERT_THROW( Tag::fetch_( tagCopy.getId() ), ObjectCube::Exception );  //Should not exist
	CPPUNIT_ASSERT_THROW( tagSet->deleteTag( &tagCopy ), ObjectCube::Exception ); //Should not exists	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSetTest::testGetTagId_( int tagId )
{
	Hub* hub = Hub::getHub();
	TagSet* tagSet = hub->getTagSet( TEST_ALPHANUMERICAL_TAG_SET_ID );
	
	const Tag* tag = tagSet->getTag( tagId );
	unique_ptr<Tag> expected( Tag::fetch_( tagId ) );
	
	CPPUNIT_ASSERT_EQUAL( *expected, *const_cast<Tag*>( tag ) );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSetTest::testGetTagName_( int tagId, string name )
{
	Hub* hub = Hub::getHub();
	TagSet* tagSet = hub->getTagSet( TEST_ALPHANUMERICAL_TAG_SET_ID );
	
	const AlphanumericalTag* tag = dynamic_cast<AlphanumericalTagSet*>( tagSet )->getAlphanumericalTag( name );
	unique_ptr<Tag> expected( Tag::fetch_( tagId ) );
	
	CPPUNIT_ASSERT_EQUAL( *expected, *dynamic_cast<Tag*>( const_cast<AlphanumericalTag*>( tag ) ) );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSetTest::testCreateHierarchy_()
{
	Hub* hub = Hub::getHub();
	TagSet* tagSet = hub->getTagSet( TEST_ALPHANUMERICAL_TAG_SET_ID );
	
	string tagName = "Hierarchy root test tag";
	AlphanumericalTag tagData( tagName );
	const Tag* tag = tagSet->addTag( &tagData );
	
	PersistentDimension* hierarchy = tagSet->createPersistentDimension( tag );
	
	CPPUNIT_ASSERT( hierarchy->getId() != INVALID_VALUE );
	CPPUNIT_ASSERT( hierarchy->getTagSetId() != INVALID_VALUE );
	CPPUNIT_ASSERT( hierarchy->getRoot()->getId() != INVALID_VALUE );
	CPPUNIT_ASSERT( hierarchy->getRoot()->getTagSetId() == hierarchy->getTagSetId() );
	CPPUNIT_ASSERT( hierarchy->getPersistentRoot()->getDimensionId() == hierarchy->getId() );
	CPPUNIT_ASSERT_EQUAL( 1, hierarchy->getRoot()->getLeftBorder() );
	CPPUNIT_ASSERT_EQUAL( 2, hierarchy->getRoot()->getRightBorder() );
	CPPUNIT_ASSERT( hierarchy->getPersistentRoot()->getTagId() != INVALID_VALUE );
	
	PersistentDimension* expected = tagSet->getPersistentDimension( hierarchy->getId() );
	
	CPPUNIT_ASSERT_EQUAL( expected , hierarchy );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSetTest::testDeleteHierarchy_()
{
	Hub* hub = Hub::getHub();
	TagSet* tagSet = hub->getTagSet( TEST_ALPHANUMERICAL_TAG_SET_ID );
	
	PersistentDimension* hierarchy =  tagSet->getPersistentDimension("Hierarchy root test tag");
	int hierarchyId = hierarchy->getId();
	tagSet->deleteDimension( hierarchy->getId() );
	
	CPPUNIT_ASSERT_THROW( tagSet->getDimension( hierarchyId ), ObjectCube::Exception ); //Should not exist
	CPPUNIT_ASSERT_THROW( tagSet->deleteDimension( hierarchyId ), ObjectCube::Exception ); //Should not exist	
	 
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSetTest::testGetHierarchy_( int tagId )
{
	Hub* hub = Hub::getHub();
	TagSet* tagSet = hub->getTagSet( TEST_ALPHANUMERICAL_TAG_SET_ID );
	
	PersistentDimension* hierarchy = tagSet->getPersistentDimension( TEST_HIERARCHY_ID );
	
	CPPUNIT_ASSERT_EQUAL( (int)TEST_HIERARCHY_ID, hierarchy->getId() );
	CPPUNIT_ASSERT_EQUAL( (int)TEST_ALPHANUMERICAL_TAG_SET_ID, hierarchy->getTagSetId() );
	CPPUNIT_ASSERT_EQUAL( (int)TEST_HIERARCHY_NODE_ID, hierarchy->getRoot()->getId() );
	CPPUNIT_ASSERT_EQUAL( (int)TEST_HIERARCHY_ID, hierarchy->getPersistentRoot()->getDimensionId() );
	CPPUNIT_ASSERT_EQUAL( (int)TEST_ALPHANUMERICAL_TAG_SET_ID, hierarchy->getRoot()->getTagSetId() );
	CPPUNIT_ASSERT_EQUAL( 1, hierarchy->getRoot()->getLeftBorder() );
	CPPUNIT_ASSERT_EQUAL( 2, hierarchy->getRoot()->getRightBorder() );
	CPPUNIT_ASSERT_EQUAL( tagId, hierarchy->getPersistentRoot()->getTagId() );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSetTest::testErase_( string tagSetName )
{
	Hub* hub = Hub::getHub();
	
	AlphanumericalTagSet tagSetToCreate( tagSetName );
	TagSet* tagSet = tagSetToCreate.create();
	
	//Add tags
	AlphanumericalTag tagToCreate( "Tag to erase" );
	const Tag* tag = tagSet->addTag( &tagToCreate );
	
	//Add dimensions
	PersistentDimension* hierarchy = tagSet->createPersistentDimension( tag );
	
	//Add tags to objects
	Object object = Object::fetch( TEST_OBJECT_ID );
	ObjectTag objectTag( tag );
	object.addTag( objectTag );
	
	//Erase all of the above
	int tagSetId = tagSet->getId();
	tagSet->erase();
	
	
	//Try to fetch from Hub
	CPPUNIT_ASSERT_THROW( hub->getTagSet( tagSetId ), ObjectCube::Exception );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSetTest::testTypeAsString_()
{
	TagSet* tagSet = Hub::getHub()->getTagSet( TEST_ALPHANUMERICAL_TAG_SET_ID );
	
	Hub::setLanguageId( LanguageCommon::ENGLISH );
	CPPUNIT_ASSERT_EQUAL( tagSet->typeAsString() , TEST_ALPHANUMERICAL_TAG_SET_TYPE_NAME_ENGLISH );
	
	Hub::setLanguageId( LanguageCommon::ICELANDIC );
	CPPUNIT_ASSERT_EQUAL( tagSet->typeAsString() , TEST_ALPHANUMERICAL_TAG_SET_TYPE_NAME_ICELANDIC );
	
	Hub::setLanguageId( LanguageCommon::ENGLISH );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSetTest::testAccessTypeAsString_()
{
	TagSet* tagSet = Hub::getHub()->getTagSet( TEST_ALPHANUMERICAL_TAG_SET_ID );
	
	Hub::setLanguageId( LanguageCommon::ENGLISH );
	CPPUNIT_ASSERT_EQUAL( tagSet->accessTypeAsString() , TEST_ACCESS_USER_ENGLISH );
	
	Hub::setLanguageId( LanguageCommon::ICELANDIC );
	CPPUNIT_ASSERT_EQUAL( tagSet->accessTypeAsString() , TEST_ACCESS_USER_ICELANDIC );
	
	Hub::setLanguageId( LanguageCommon::ENGLISH );	
}
//____________________________________________________________________________________________________________________________________________________________________________________


