/*
 *  HierarchyNodeCommon.h
 *  Prada
 *
 *  Created by Grímur Tómasson on 8.2.2010.
 *  Copyright 2010 RU. All rights reserved.
 *
 */

#ifndef ObjectCube_HIERARCHYNODE_COMMON_
#define ObjectCube_HIERARCHYNODE_COMMON_

namespace ObjectCube
{
	
	class HierarchyNodeCommon
	{
	public:
		HierarchyNodeCommon() {;}
		virtual ~HierarchyNodeCommon() {;}
		
		enum STATUS 
		{
			INVALID = -1
		};
		
		enum TYPE 
		{
			PERSISTENT = 1,
			VIRTUAL = 2,
			DEFAULT = 3
		};
		
	};
	
}

#endif
