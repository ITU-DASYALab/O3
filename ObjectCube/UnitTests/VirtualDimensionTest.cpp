/*
 *  VirtualDimensionTest.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 6.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "VirtualDimensionTest.h"

#include <cppunit/extensions/HelperMacros.h>
#include <sstream>

#include "../Hierarchy/VirtualDimension.h"
#include "../Hierarchy/VirtualHierarchyNode.h"
#include "../Hub.h"
#include "TestIds.h"
#include "../LayerShared/HubCommon.h"
#include "../TagSet/TagSet.h"
#include "../LayerShared/Exception.h"
#include "../LayerShared/SharedDefinitions.h"

using namespace ObjectCube;

CPPUNIT_TEST_SUITE_REGISTRATION( VirtualDimensionTest );

//____________________________________________________________________________________________________________________________________________________________________________________

//  Canned tests --------------------------------------------------------------------------------------------------------------------
void VirtualDimensionTest::testAddNodeCanned()
{
	cerr << "\nVirtualDimensionTest::testAddNodeCanned = ";
	
	string dimensionName = "Hours";
	VirtualDimension dimension( TEST_TIME_TAG_SET_ID, "[0-9]{2}:", "[0-9]{2}", dimensionName );
	
	for( int i = 0; i < 24; i++ )
	{
		stringstream stringStream;
		stringStream << i;
		dimension.addNode( dimension.getRoot()->getId(), stringStream.str() );
	}
	
	CPPUNIT_ASSERT( dimension.getTagSetId() == TEST_TIME_TAG_SET_ID );
	string deb = dimension.getRoot()->getName();
	CPPUNIT_ASSERT( dimension.getRoot()->getName() == dimensionName );
	
	const vector<HierarchyNode*> nodes = dimension.getRoot()->getBranches();
	for( vector<HierarchyNode*>::const_iterator itr = nodes.begin(); itr != nodes.end(); ++itr )
	{
		const VirtualHierarchyNode* node = dynamic_cast<VirtualHierarchyNode*>( *itr );
		CPPUNIT_ASSERT( node->getId() != INVALID_VALUE );
		CPPUNIT_ASSERT( node->getName() != "Not Initialized!" );
		CPPUNIT_ASSERT( node->getTagSetId() == TEST_TIME_TAG_SET_ID );
		CPPUNIT_ASSERT( node->getLeftBorder() != INVALID_VALUE );
		CPPUNIT_ASSERT( node->getRightBorder() != INVALID_VALUE );
		CPPUNIT_ASSERT( node->getChildCategoryTitle() == "" );
	}
	
}
//____________________________________________________________________________________________________________________________________________________________________________________
