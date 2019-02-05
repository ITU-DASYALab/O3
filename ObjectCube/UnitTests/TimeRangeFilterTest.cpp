/*
 *  TimeRangeFilterTest.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 3.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "TimeRangeFilterTest.h"

#include <cppunit/extensions/HelperMacros.h>
#include <iostream>
#include <vector>

#include "../Hub.h"
#include "../TagSet/TagSet.h"
#include "../Filters/TimeRangeFilter.h"
#include "TestIds.h"
#include "../LayerShared/SharedDefinitions.h"
#include "../LayerShared/Exception.h"


using namespace ObjectCube;

CPPUNIT_TEST_SUITE_REGISTRATION( TimeRangeFilterTest );

//____________________________________________________________________________________________________________________________________________________________________________________

//  Canned tests --------------------------------------------------------------------------------------------------------------------

void TimeRangeFilterTest::testFilterCanned()
{
	cerr << "\nTimeRangeFilterTest::testFilterCanned = ";
	Hub::setDataAccessType( Hub::CANNED );
	
	Hub* hub = Hub::getHub(); 
	TagSet* tagSet = hub->getTagSet( TEST_TIME_TAG_SET_ID );
	
	TimeRangeFilter filter( 11, 14, tagSet->getId() );
	
	hub->addFilter( &filter );
	vector<StateObject> objects = hub->getObjects();
	
	CPPUNIT_ASSERT( objects.size() );
	
	//Add a second filter to the same tag-set
	TimeRangeFilter filter2( 15, 18, tagSet->getId() ); 
	hub->addFilter( &filter2 );
	objects = hub->getObjects();
	
	CPPUNIT_ASSERT( objects.size() ); //Should be zero but the canned implementation is limited
	
	hub->removeAllFilters();
	
	TimeRangeFilter filter3( 12, 24, tagSet->getId() ); // Illegal time
	CPPUNIT_ASSERT_THROW(  hub->addFilter( &filter3 ), ObjectCube::Exception );
	
	hub->removeAllFilters();
	
	TimeRangeFilter filter4( tagSet->getId() ); //No values
	CPPUNIT_ASSERT_THROW( hub->addFilter( &filter4 ), ObjectCube::Exception );  //Empty filter, error
}

void TimeRangeFilterTest::testFillInCanned()
{
	cerr << "\nTimeRangeFilterTest::testFilterCanned = ";
	Hub::setDataAccessType( Hub::CANNED );

	TimeRangeFilter filter( 1 );
	filter.setHoursFrom( 0 );
	filter.setMinutesFrom( 0 );
	filter.setSecondsFrom( 1 );
	filter.setMillisecondsFrom( 0 );
	filter.setHoursTo( 0 );
	filter.setMinutesTo( 0 );
	filter.setSecondsTo( 2 );
	filter.setMillisecondsTo( 0 );
	
	filter.fillInAndValidateValues();
	
	CPPUNIT_ASSERT_EQUAL( filter.getHoursFrom(), 0 );
	CPPUNIT_ASSERT_EQUAL( filter.getMinutesFrom(), 0 );
	CPPUNIT_ASSERT_EQUAL( filter.getSecondsFrom(), 1 );
	CPPUNIT_ASSERT_EQUAL( filter.getMillisecondsFrom(), 0 );
	CPPUNIT_ASSERT_EQUAL( filter.getHoursTo(), 0 );
	CPPUNIT_ASSERT_EQUAL( filter.getMinutesTo(), 0 );
	CPPUNIT_ASSERT_EQUAL( filter.getSecondsTo(), 2 );
	CPPUNIT_ASSERT_EQUAL( filter.getMillisecondsTo(), 0 );
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  SQLite tests --------------------------------------------------------------------------------------------------------------------

void TimeRangeFilterTest::testFilterSQLite()
{
	cerr << "\nTimeRangeFilterTest::testFilterSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testFilter_();	
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  MonetDB tests --------------------------------------------------------------------------------------------------------------------

void TimeRangeFilterTest::testFilterMonetDB()
{
	cerr << "\nTimeRangeFilterTest::testFilterMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );
	
	testFilter_();	
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  MonetDB tests --------------------------------------------------------------------------------------------------------------------

void TimeRangeFilterTest::testFilterOracle()
{
	cerr << "\nTimeRangeFilterTest::testFilterOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testFilter_();		
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Common --------------------------------------------------------------------------------------------------------------------

void TimeRangeFilterTest::testFilter_()
{
	Hub* hub = Hub::getHub(); 
	TagSet* tagSet = hub->getTagSet( TEST_TIME_TAG_SET_ID );
	
	TimeRangeFilter filter( 11, 14, tagSet->getId() );
	
	hub->removeAllFilters();
	hub->addFilter( &filter );
	vector<StateObject> objects = hub->getObjects();
	
	CPPUNIT_ASSERT( objects.size() );
	
	//Add a second filter to the same tag-set
	TimeRangeFilter filter2( 15, 18, tagSet->getId() ); 
	hub->addFilter( &filter2 );
	objects = hub->getObjects();
	
	CPPUNIT_ASSERT( objects.size() == 0 ); 
	
	hub->removeAllFilters();
	
	TimeRangeFilter filter3( 12, 24, tagSet->getId() ); // Illegal time
	CPPUNIT_ASSERT_THROW( hub->addFilter( &filter3 ), ObjectCube::Exception );
	
	hub->removeAllFilters();
	
	TimeRangeFilter filter4( tagSet->getId() ); //No values
	CPPUNIT_ASSERT_THROW( hub->addFilter( &filter4 ), ObjectCube::Exception );  //Empty filter, error	
}
//____________________________________________________________________________________________________________________________________________________________________________________


