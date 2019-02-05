/*
 *  StateObjectTest.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 26.8.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "StateObjectTest.h"

#include <cppunit/extensions/HelperMacros.h>

#include "../Hub.h"
#include "TestIds.h"
#include "../TagSet/TagSet.h"
#include "../LayerShared/Exception.h"
#include "../LayerShared/SharedDefinitions.h"
#include "../Filters/DimensionFilter.h"
#include "../State/State.h"
#include "../Filters/TagFilter.h" 
#include "../Filters/NumericalRangeFilter.h"

using namespace ObjectCube;

CPPUNIT_TEST_SUITE_REGISTRATION( StateObjectTest );

//____________________________________________________________________________________________________________________________________________________________________________________

//  Canned tests --------------------------------------------------------------------------------------------------------------------

void StateObjectTest::testGetTagsByTagSetIdCanned()
{
	cerr << "\nStateObjectTest::testGetTagsByTagSetIdCanned = ";
	Hub::setDataAccessType( Hub::CANNED );
	
	State::removeAllFilters();
	Hub* hub = Hub::getHub();
	TagSet* anTagSet = hub->getTagSet(	TEST_ALPHANUMERICAL_TAG_SET_ID );
	TagFilter tFilter( anTagSet->getTag( TEST_ALPHANUMERICAL_TAG_ID_CANNED ), anTagSet->getId() );
	State::addFilter( &tFilter );
	
	State state = State::getState();
	vector<StateObject> objects = state.getObjects();
	for( vector<StateObject>::iterator itr = objects.begin(); itr != objects.end(); ++itr )
	{
		CPPUNIT_ASSERT( (*itr).getTags( TEST_ALPHANUMERICAL_TAG_SET_ID ).size() > 0 ); //We filtered by a tag from this tag-set, all objects in the results should have it		
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  SQLite tests --------------------------------------------------------------------------------------------------------------------

void StateObjectTest::testGetTagsByTagSetIdSQLite()
{
	cerr << "\nStateObjectTest::testGetTagsByTagSetIdSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testGetTagsByTagSetId_( SQLiteTestIds::TEST_ALPHANUMERICAL_TAG_ID );
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  MonetDB tests --------------------------------------------------------------------------------------------------------------------

void StateObjectTest::testGetTagsByTagSetIdMonetDB()
{
	cerr << "\nStateObjectTest::testGetTagsByTagSetIdMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );
	
	testGetTagsByTagSetId_( MonetDBTestIds::TEST_ALPHANUMERICAL_TAG_ID );
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Oracle tests --------------------------------------------------------------------------------------------------------------------

void StateObjectTest::testGetTagsByTagSetIdOracle()
{
	cerr << "\nStateObjectTest::testGetTagsByTagSetIdOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testGetTagsByTagSetId_( OracleTestIds::TEST_ALPHANUMERICAL_TAG_ID );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Common --------------------------------------------------------------------------------------------------------------------

void StateObjectTest::testGetTagsByTagSetId_( int tagId )
{
	State::removeAllFilters();
	Hub* hub = Hub::getHub();
	TagSet* anTagSet = hub->getTagSet(	TEST_ALPHANUMERICAL_TAG_SET_ID );
	TagFilter tFilter( anTagSet->getTag( tagId ), anTagSet->getId() );
	State::addFilter( &tFilter );
	
	State state = State::getState();
	vector<StateObject> objects = state.getObjects();
	for( vector<StateObject>::iterator itr = objects.begin(); itr != objects.end(); ++itr )
	{
		CPPUNIT_ASSERT( (*itr).getTags( TEST_ALPHANUMERICAL_TAG_SET_ID ).size() > 0 ); //We filtered by a tag from this tag-set, all objects in the results should have it		
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________


