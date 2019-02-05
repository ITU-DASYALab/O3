/*
 *  DimensionFilterTest.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 24.4.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "DimensionFilterTest.h"

#include <cppunit/extensions/HelperMacros.h>
#include <iostream>
#include <vector>

#include "../Hub.h"
#include "../TagSet/AlphanumericalTagSet.h"
#include "../Tag/AlphanumericalTag.h"
#include "../Filters/DimensionFilter.h"
#include "../Hierarchy/PersistentDimension.h"
#include "../Hierarchy/PersistentHierarchyNode.h"
#include "TestIds.h"
#include "../LayerShared/SharedDefinitions.h"
#include "../LayerShared/Exception.h"


using namespace ObjectCube;

CPPUNIT_TEST_SUITE_REGISTRATION( DimensionFilterTest );

//____________________________________________________________________________________________________________________________________________________________________________________

//  Canned tests --------------------------------------------------------------------------------------------------------------------

void DimensionFilterTest::testFilterCanned()
{
	cerr << "\nDimensionFilterTest::testFilterCanned = ";
	
	Hub::setDataAccessType( Hub::CANNED );
	
	Hub* hub = Hub::getHub(); 
	TagSet* tagSet = hub->getTagSet( TEST_ALPHANUMERICAL_TAG_SET_ID );
	
 	PersistentDimension* dimension = tagSet->getPersistentDimension( TEST_HIERARCHY_ID );
	PersistentHierarchyNode* node = dimension->getPersistentRoot();
	DimensionFilter filter( *node, tagSet->getId() );
	
	hub->addFilter( &filter );
	vector<StateObject> objects = hub->getObjects();
	
	CPPUNIT_ASSERT( objects.size() );
	
	//Add a second filter to the same tag-set
	const vector<HierarchyNode*> children = node->getBranches();
	CPPUNIT_ASSERT( children.size() );
	PersistentHierarchyNode* subNode = dynamic_cast<PersistentHierarchyNode*>( children[0] );
	DimensionFilter filter2( *subNode, tagSet->getId() );
	hub->addFilter( &filter2 );
	objects = hub->getObjects();
	
	CPPUNIT_ASSERT( objects.size() ); //Should be zero but the canned implementation is limited
	
	//Add a filter to a different tag-set (for canned?)
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  SQLite tests --------------------------------------------------------------------------------------------------------------------

void DimensionFilterTest::testFilterSQLite()
{
	cerr << "\nDimensionFilterTest::testFilterSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testFilter_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  MonetDB tests --------------------------------------------------------------------------------------------------------------------

void DimensionFilterTest::testFilterMonetDB()
{
	cerr << "\nDimensionFilterTest::testFilterMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );

	testFilter_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Oracle tests --------------------------------------------------------------------------------------------------------------------

void DimensionFilterTest::testFilterOracle()
{
	cerr << "\nDimensionFilterTest::testFilterOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testFilter_();	
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Common --------------------------------------------------------------------------------------------------------------------

void DimensionFilterTest::testFilter_()
{
	Hub* hub = Hub::getHub(); 
	TagSet* tagSet = hub->getTagSet( TEST_ALPHANUMERICAL_TAG_SET_ID );
	
 	PersistentDimension* dimension = tagSet->getPersistentDimension( TEST_HIERARCHY_ID );
	PersistentHierarchyNode* node = dimension->getPersistentRoot();
	DimensionFilter filter( *node, tagSet->getId() );
	
	hub->addFilter( &filter );
	vector<StateObject> objects = hub->getObjects();
	
	CPPUNIT_ASSERT( objects.size() );
	
	//Time
	hub->removeAllFilters();
	
	TagSet* tTagSet = hub->getTagSet( TEST_TIME_TAG_SET_ID );
	
	const VirtualDimension* vDim = tTagSet->getVirtualDimension( "Hour" );
	const VirtualHierarchyNode* vNode = vDim->getVirtualRoot();
	DimensionFilter vFilter( *vNode, tTagSet->getId() );
	hub->addFilter( &vFilter );
	
	objects = hub->getObjects();
	CPPUNIT_ASSERT( objects.size() );
	
	//Date
	hub->removeAllFilters();
	
	TagSet* dTagSet = hub->getTagSet( TEST_DATE_TAG_SET_ID );
	
	const VirtualDimension* vdDim = dTagSet->getVirtualDimension( "Month" );
	const VirtualHierarchyNode* vdNode = vdDim->getVirtualRoot();
	DimensionFilter vdFilter( *vdNode, dTagSet->getId() );
	hub->addFilter( &vdFilter );
	
	objects = hub->getObjects();
	CPPUNIT_ASSERT( objects.size() );
	
	//Day of week (recurring)
	hub->removeAllFilters();
	
	const VirtualDimension* vdDim2 = dTagSet->getVirtualDimension( "Day of Week" );
	const VirtualHierarchyNode* vdNode2 = vdDim2->getVirtualRoot();
	DimensionFilter vdFilter2( *vdNode2, dTagSet->getId() );
	hub->addFilter( &vdFilter2 );
	
	objects = hub->getObjects();
	CPPUNIT_ASSERT( objects.size() );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

