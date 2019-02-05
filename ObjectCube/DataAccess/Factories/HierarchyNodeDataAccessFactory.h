/*
 *  HierarchyNodeDataAccessFactory.h
 *  Prada
 *
 *  Created by Grímur Tómasson on 8.2.2010.
 *  Copyright 2010 RU. All rights reserved.
 *
 */

#ifndef ObjectCube_HIERARCHYNODEDATAACCESSFACTORY_
#define ObjectCube_HIERARCHYNODEDATAACCESSFACTORY_

namespace ObjectCube
{
	class HierarchyNodeDataAccess;
	
	class HierarchyNodeDataAccessFactory
	{
	public:
		static HierarchyNodeDataAccess* create();
	};
	
}

#endif