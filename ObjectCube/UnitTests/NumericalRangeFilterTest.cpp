/*
 *  NumericalRangeFilterTest.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 1.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "NumericalRangeFilterTest.h"

#include <cppunit/extensions/HelperMacros.h>
#include <iostream>
#include <vector>

#include "../Hub.h"
#include "../TagSet/TagSet.h"
#include "../Filters/NumericalRangeFilter.h"
#include "TestIds.h"
#include "../LayerShared/SharedDefinitions.h"
#include "../LayerShared/Exception.h"


using namespace ObjectCube;

CPPUNIT_TEST_SUITE_REGISTRATION( NumericalRangeFilterTest );

//____________________________________________________________________________________________________________________________________________________________________________________

//  Canned tests --------------------------------------------------------------------------------------------------------------------

void NumericalRangeFilterTest::testFilterCanned()
{
	cerr << "\nNumericalRangeFilterTest::testFilterCanned = ";
	
	Hub::setDataAccessType( Hub::CANNED );
	
	Hub* hub = Hub::getHub(); 
	TagSet* tagSet = hub->getTagSet( TEST_NUMERICAL_TAG_SET_ID );
	
	NumericalRangeFilter filter( 0, 20, tagSet->getId() );
 		
	hub->addFilter( &filter );
	vector<StateObject> objects = hub->getObjects();
	
	CPPUNIT_ASSERT( objects.size() );
	
	//Add a second filter to the same tag-set
	NumericalRangeFilter filter2( 20, 30, tagSet->getId() ); 
	hub->addFilter( &filter2 );
	objects = hub->getObjects();
	
	CPPUNIT_ASSERT( objects.size() ); //Should be zero but the canned implementation is limited
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  SQLite tests --------------------------------------------------------------------------------------------------------------------

void NumericalRangeFilterTest::testFilterSQLite()
{
	cerr << "\nNumericalRangeFilterTest::testFilterSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );

	testFilter_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  MonetDB tests --------------------------------------------------------------------------------------------------------------------

void NumericalRangeFilterTest::testFilterMonetDB()
{
	cerr << "\nNumericalRangeFilterTest::testFilterMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );
	
	testFilter_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Oracle tests --------------------------------------------------------------------------------------------------------------------

void NumericalRangeFilterTest::testFilterOracle()
{
	cerr << "\nNumericalRangeFilterTest::testFilterOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testFilter_();	
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Common --------------------------------------------------------------------------------------------------------------------

void NumericalRangeFilterTest::testFilter_()
{
	Hub* hub = Hub::getHub(); 
	TagSet* tagSet = hub->getTagSet( TEST_NUMERICAL_TAG_SET_ID );
	
	NumericalRangeFilter filter( 0, 20, tagSet->getId() );
	
	hub->addFilter( &filter );
	vector<StateObject> objects = hub->getObjects();
	
	CPPUNIT_ASSERT( objects.size() );
	
	//Add a second filter to the same tag-set
	NumericalRangeFilter filter2( 20, 30, tagSet->getId() ); 
	hub->addFilter( &filter2 );
	objects = hub->getObjects();
	
	CPPUNIT_ASSERT( objects.size() == 0 ); 	
}
//____________________________________________________________________________________________________________________________________________________________________________________

