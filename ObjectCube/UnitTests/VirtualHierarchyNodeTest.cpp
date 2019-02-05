/*
 *  VirtualHierarchyNodeTest.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 5.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "VirtualHierarchyNodeTest.h"

#include <cppunit/extensions/HelperMacros.h>

#include "../Hierarchy/VirtualHierarchyNode.h"
#include "../Hub.h"
#include "TestIds.h"
#include "../LayerShared/HubCommon.h"
#include "../TagSet/TagSet.h"
#include "../LayerShared/Exception.h"
#include "../LayerShared/SharedDefinitions.h"
#include "../Hierarchy/PersistentDimension.h"

using namespace ObjectCube;

CPPUNIT_TEST_SUITE_REGISTRATION( VirtualHierarchyNodeTest );

//____________________________________________________________________________________________________________________________________________________________________________________

//  Canned tests --------------------------------------------------------------------------------------------------------------------
void VirtualHierarchyNodeTest::testGetBranchCanned()
{
	cerr << "\nVirtualHierarchyNodeTest::testGetBranchCanned = ";
	
	string outerPattern = "[0-9]{2}:";
	string innerPattern = "[0-9]{2}";
	
	VirtualHierarchyNode root( 1, "Time", TEST_TIME_TAG_SET_ID, 1, outerPattern, innerPattern, "Hours" );
	VirtualHierarchyNode branch( 2, "14", TEST_TIME_TAG_SET_ID, 1,  outerPattern, innerPattern );
	root.addBranch_( &branch );
	int borderCounter = 1;
	root.updateBorders_( borderCounter );
	
	HierarchyNode* nodeGotten = root.getBranch( 2 );
	
	CPPUNIT_ASSERT( branch.getId() == nodeGotten->getId() );
	
	//Filter support test
	//vector<int> tagIds = branch.getSubtreeTagIds();
}
//____________________________________________________________________________________________________________________________________________________________________________________

