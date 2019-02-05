/*
 *  DefaultDimensionTest.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 5.7.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "DefaultDimensionTest.h"

#include <cppunit/extensions/HelperMacros.h>
#include <sstream>

#include "../Hierarchy/DefaultDimension.h"
#include "../Hierarchy/DefaultHierarchyNode.h"
#include "../Hub.h"
#include "TestIds.h"
#include "../LayerShared/HubCommon.h"
#include "../TagSet/TagSet.h"
#include "../Tag/Tag.h"
#include "../LayerShared/Exception.h"
#include "../LayerShared/SharedDefinitions.h"

using namespace ObjectCube;

CPPUNIT_TEST_SUITE_REGISTRATION( DefaultDimensionTest );

//____________________________________________________________________________________________________________________________________________________________________________________

//  Canned tests --------------------------------------------------------------------------------------------------------------------

void DefaultDimensionTest::testInstantiateCanned()
{
	cerr << "\nDefaultDimensionTest::testInstantiateCanned = ";

	//Basic test
	vector<Tag*> tags;
	DefaultDimension dDim( 1, tags );
	
	DefaultHierarchyNode* root = dDim.getDefaultRoot();
	
	CPPUNIT_ASSERT( root->getBranches().size() == 0 );
	CPPUNIT_ASSERT( root->getName() == DefaultDimension::getRootName() );
	CPPUNIT_ASSERT( root->getId() == INVALID_VALUE );
	
	}

//____________________________________________________________________________________________________________________________________________________________________________________

//  SQLite tests --------------------------------------------------------------------------------------------------------------------

void DefaultDimensionTest::testInstantiateSQLite()
{
	cerr << "\nDefaultDimensionTest::testInstantiateSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testInstatiate_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  MonetDB tests --------------------------------------------------------------------------------------------------------------------

void DefaultDimensionTest::testInstantiateMonetDB()
{
	cerr << "\nDefaultDimensionTest::testInstantiateMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );
	
	testInstatiate_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  MonetDB tests --------------------------------------------------------------------------------------------------------------------

void DefaultDimensionTest::testInstantiateOracle()
{
	cerr << "\nDefaultDimensionTest::testInstantiateOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testInstatiate_();	
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Common --------------------------------------------------------------------------------------------------------------------

void DefaultDimensionTest::testInstatiate_()
{	
	Hub* hub = Hub::getHub();
	TagSet* tagSet = hub->getTagSet( TEST_ALPHANUMERICAL_TAG_SET_ID );
	
	const DefaultDimension* alphaDefaultDim = tagSet->getDefaultDimension();
	const DefaultHierarchyNode* root = alphaDefaultDim->getDefaultRoot();
	
	CPPUNIT_ASSERT_EQUAL( tagSet->getTags().size(), root->getBranches().size() );
	CPPUNIT_ASSERT( root->getName() == DefaultDimension::getRootName() );
	CPPUNIT_ASSERT( root->getId() == INVALID_VALUE );
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

