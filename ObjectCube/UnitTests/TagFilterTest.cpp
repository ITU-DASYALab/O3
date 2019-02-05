/*
 *  TagFilterTest.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 14.4.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "TagFilterTest.h"

#include <cppunit/extensions/HelperMacros.h>
#include <iostream>
#include <memory>

#include "../Hub.h"
#include "../TagSet/AlphanumericalTagSet.h"
#include "../Tag/AlphanumericalTag.h"
#include "../Filters/TagFilter.h"
#include "TestIds.h"
#include "../LayerShared/SharedDefinitions.h"
#include "../LayerShared/Exception.h"
#include "../State/StateObject.h"


using namespace ObjectCube;

CPPUNIT_TEST_SUITE_REGISTRATION( TagFilterTest );

//____________________________________________________________________________________________________________________________________________________________________________________

//  Canned tests --------------------------------------------------------------------------------------------------------------------

void TagFilterTest::testFilterCanned()
{
	cerr << "\nTagFilterTest::testFilterCanned = ";
	Hub::setDataAccessType( Hub::CANNED );
	
	Hub* hub = Hub::getHub(); 
	TagSet* tagSet = hub->getTagSet( TEST_ALPHANUMERICAL_TAG_SET_ID );
	const Tag* tag = tagSet->getTag( TEST_ALPHANUMERICAL_TAG_ID_CANNED );
	
	TagFilter filter( tag, tagSet->getId() );
	hub->addFilter( &filter );
	vector<StateObject> objects = hub->getObjects();
	
	CPPUNIT_ASSERT( objects.size() );
	
	//Add a second filter to the same tag-set
	
	const Tag* uncatTag = hub->getUncategorizedTag();
	TagFilter filter2( uncatTag, tagSet->getId() );
	hub->addFilter( &filter2 );
	objects = hub->getObjects();
	
	CPPUNIT_ASSERT( objects.size() ); //Should be zero but the canned implementation is limited
	
	//Add a filter to a different tag-set (for canned?)
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  SQLite tests --------------------------------------------------------------------------------------------------------------------

void TagFilterTest::testFilterSQLite()
{
	cerr << "\nTagFilterTest::testFilterSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testFilter_( SQLiteTestIds::TEST_ALPHANUMERICAL_TAG_ID, SQLiteTestIds::TEST_NUMERICAL_TAG_ID );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagFilterTest::testFilterTypeAsStringSQLite()
{
	cerr << "\nTagFilterTest::testFilterTypeAsStringSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testFilterTypeAsString_( SQLiteTestIds::TEST_ALPHANUMERICAL_TAG_ID );
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  MonetDB tests --------------------------------------------------------------------------------------------------------------------

void TagFilterTest::testFilterMonetDB()
{
	cerr << "\nTagFilterTest::testFilterMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );
	
	testFilter_( MonetDBTestIds::TEST_ALPHANUMERICAL_TAG_ID, MonetDBTestIds::TEST_NUMERICAL_TAG_ID );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagFilterTest::testFilterTypeAsStringMonetDB()
{
	cerr << "\nTagFilterTest::testFilterTypeAsStringMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );
	
	testFilterTypeAsString_( MonetDBTestIds::TEST_ALPHANUMERICAL_TAG_ID );
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Oracle tests --------------------------------------------------------------------------------------------------------------------

void TagFilterTest::testFilterOracle()
{
	cerr << "\nTagFilterTest::testFilterOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testFilter_( OracleTestIds::TEST_ALPHANUMERICAL_TAG_ID, OracleTestIds::TEST_NUMERICAL_TAG_ID );		
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagFilterTest::testFilterTypeAsStringOracle()
{
	cerr << "\nTagFilterTest::testFilterTypeAsStringOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testFilterTypeAsString_( OracleTestIds::TEST_ALPHANUMERICAL_TAG_ID );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Common --------------------------------------------------------------------------------------------------------------------

void TagFilterTest::testFilter_( int alphanumericalTagId, int numericalTagId )
{
	Hub* hub = Hub::getHub(); 
	AlphanumericalTagSet* tagSet = dynamic_cast<AlphanumericalTagSet*>( hub->getTagSet( TEST_ALPHANUMERICAL_TAG_SET_ID ) );
	
	const Tag* tag = tagSet->getTag( alphanumericalTagId );
	TagFilter filter( tag, tagSet->getId() );

	hub->removeAllFilters();
	hub->addFilter( &filter );
	
	vector<StateObject> objects = hub->getObjects();
	
	CPPUNIT_ASSERT( objects.size() );
	
	//Add a second filter to the same tag-set
	const Tag* tag2 = tagSet->getAlphanumericalTag( "Hierarchy root test tag" );
	TagFilter filter2( tag2, tagSet->getId() );
	hub->addFilter( &filter2 );
	
	objects = hub->getObjects();
	
	CPPUNIT_ASSERT( objects.size() == 0 );
	
	//Add a filter to a different tag-set
	TagSet* tagSet2 = hub->getTagSet( TEST_NUMERICAL_TAG_SET_ID );
	
	const Tag* tag3 = tagSet2->getTag( numericalTagId );
	TagFilter filter3( tag3, tagSet2->getId() );
	hub->addFilter( &filter3 );
	
	objects = hub->getObjects();
	
	CPPUNIT_ASSERT( objects.size() == 0 );	
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagFilterTest::testFilterTypeAsString_( int tagId )
{
	Hub* hub = Hub::getHub(); 
	AlphanumericalTagSet* tagSet = dynamic_cast<AlphanumericalTagSet*>( hub->getTagSet( TEST_ALPHANUMERICAL_TAG_SET_ID ) );
	
	const Tag* tag = tagSet->getTag( tagId );
	TagFilter filter( tag, tagSet->getId() );
	
	Hub::setLanguageId( LanguageCommon::ENGLISH );
	CPPUNIT_ASSERT_EQUAL( filter.typeAsString() , TEST_TAG_FILTER_TYPE_ENGLISH );
	
	Hub::setLanguageId( LanguageCommon::ICELANDIC );
	CPPUNIT_ASSERT_EQUAL( filter.typeAsString() , TEST_TAG_FILTER_TYPE_ICELANDIC );
	
	Hub::setLanguageId( LanguageCommon::ENGLISH );	
}
//____________________________________________________________________________________________________________________________________________________________________________________


