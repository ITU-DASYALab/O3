/*
 *  DateRangeFilterTest.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 3.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "DateRangeFilterTest.h"

#include <cppunit/extensions/HelperMacros.h>
#include <iostream>
#include <vector>

#include "../Hub.h"
#include "../TagSet/TagSet.h"
#include "../Filters/DateRangeFilter.h"
#include "TestIds.h"
#include "../LayerShared/SharedDefinitions.h"
#include "../LayerShared/Exception.h"


using namespace ObjectCube;

CPPUNIT_TEST_SUITE_REGISTRATION( DateRangeFilterTest );

//____________________________________________________________________________________________________________________________________________________________________________________

//  Canned tests --------------------------------------------------------------------------------------------------------------------

void DateRangeFilterTest::testFilterCanned()
{
	cerr << "\nDateRangeFilterTest::testFilterCanned = ";
	
	Hub::setDataAccessType( Hub::CANNED );
	
	Hub* hub = Hub::getHub(); 
	TagSet* tagSet = hub->getTagSet( TEST_DATE_TAG_SET_ID );
	
	DateRangeFilter filter( 2010, tagSet->getId() );
	
	hub->addFilter( &filter );
	vector<StateObject> objects = hub->getObjects();
	
	CPPUNIT_ASSERT( objects.size() );
	
	//Add a second filter to the same tag-set
	DateRangeFilter filter2( 2050, tagSet->getId() ); 
	hub->addFilter( &filter2 );
	objects = hub->getObjects();
	
	CPPUNIT_ASSERT( objects.size() ); //Should be zero but the canned implementation is limited
	
	hub->removeAllFilters();
	
	DateRangeFilter filter3( 2010, 3, 25, 2010, 2, 30, tagSet->getId() ); // Illegal date
	CPPUNIT_ASSERT_THROW( hub->addFilter( &filter3 ), ObjectCube::Exception );
	
	hub->removeAllFilters();
	
	DateRangeFilter filter4( tagSet->getId() ); //No values
	CPPUNIT_ASSERT_THROW( hub->addFilter( &filter4 ), ObjectCube::Exception );  //Empty filter, error
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  SQLite tests --------------------------------------------------------------------------------------------------------------------

void DateRangeFilterTest::testFilterSQLite()
{
	cerr << "\nDateRangeFilterTest::testFilterSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testFilter_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  MonetDB tests --------------------------------------------------------------------------------------------------------------------

void DateRangeFilterTest::testFilterMonetDB()
{
	cerr << "\nDateRangeFilterTest::testFilterMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );
	
	testFilter_();	
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Oracle tests --------------------------------------------------------------------------------------------------------------------

void DateRangeFilterTest::testFilterOracle()
{
	cerr << "\nDateRangeFilterTest::testFilterOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testFilter_();		
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Common --------------------------------------------------------------------------------------------------------------------

void DateRangeFilterTest::testFilter_()
{
	Hub* hub = Hub::getHub(); 
	TagSet* tagSet = hub->getTagSet( TEST_DATE_TAG_SET_ID );
	
	DateRangeFilter filter( 2009, tagSet->getId() );
	
	hub->addFilter( &filter );
	vector<StateObject> objects = hub->getObjects();
	
	CPPUNIT_ASSERT( objects.size() );
	
	//Add a second filter to the same tag-set
	DateRangeFilter filter2( 2050, tagSet->getId() ); 
	hub->addFilter( &filter2 );
	objects = hub->getObjects();
	
	CPPUNIT_ASSERT( objects.size() == 0 );
	
	hub->removeAllFilters();
	
	DateRangeFilter filter3( 2010, 3, 25, 2010, 2, 30, tagSet->getId() ); // Illegal date
	CPPUNIT_ASSERT_THROW( hub->addFilter( &filter3 ), ObjectCube::Exception );
	
	hub->removeAllFilters();
	
	DateRangeFilter filter4( tagSet->getId() ); //No values
	CPPUNIT_ASSERT_THROW( hub->addFilter( &filter4 ), ObjectCube::Exception );  //Empty filter, error	
}
//____________________________________________________________________________________________________________________________________________________________________________________

