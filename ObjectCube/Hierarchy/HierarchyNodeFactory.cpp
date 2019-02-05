/*
 *  HierarchyNodeFactory.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 7.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "HierarchyNodeFactory.h"

#include <sstream>

#include "HierarchyNode.h"

#include "PersistentHierarchyNode.h"
#include "VirtualHierarchyNode.h"
#include "DefaultHierarchyNode.h"

#include "../LayerShared/Exception.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

HierarchyNode* HierarchyNodeFactory::create( int typeId )
{
	switch ( typeId ) 
	{
		case HierarchyNode::PERSISTENT :
			return new PersistentHierarchyNode();
		case HierarchyNode::VIRTUAL :
			return new VirtualHierarchyNode();
		case HierarchyNode::DEFAULT :
			return new DefaultHierarchyNode();
		default:
			
			ostringstream stringstream;
			stringstream << "Unknown hierarchy node type: " << typeId;
			throw Exception("HierarchyNodeFactory::create", stringstream.str() );
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________