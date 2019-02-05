/*
 *  HierarchyNodeDataAccess.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 16.2.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */


#include "HierarchyNodeDataAccess.h"
#include "../../LayerShared/SharedDefinitions.h"
#include "../../LayerShared/MemoryManagement.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

HierarchyNodeDataAccess::HierarchyNodeDataAccess()
{
	id_ = INVALID_VALUE;
	hierarchyId_ = INVALID_VALUE; 
	tagSetId_ = INVALID_VALUE; 
	tagId_ = INVALID_VALUE;
	leftBorder_ = INVALID_VALUE;
	rightBorder_ = INVALID_VALUE;
}
//____________________________________________________________________________________________________________________________________________________________________________________

HierarchyNodeDataAccess::~HierarchyNodeDataAccess()
{
	clearAndDestroy( children_ );
}
//____________________________________________________________________________________________________________________________________________________________________________________

