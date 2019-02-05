/*
 *  HierarchyNodeFactory.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 7.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_HIERARCHY_NODE_FACTORY_
#define ObjectCube_HIERARCHY_NODE_FACTORY_

namespace ObjectCube
{
	class HierarchyNode;
	
	class HierarchyNodeFactory
	{
	public:
		static HierarchyNode* create( int typeId );
	};
	
}

#endif