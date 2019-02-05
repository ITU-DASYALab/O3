/*
 *  HierarchyNodeConverter.h
 *  Prada
 *
 *  Created by Grímur Tómasson on 8.2.2010.
 *  Copyright 2010 RU. All rights reserved.
 *
 */

#ifndef ObjectCube_HIERARCHYNODECONVERTER_
#define ObjectCube_HIERARCHYNODECONVERTER_

#include <vector>

#ifdef __APPLE__
#include <memory>
using std::shared_ptr;
#else
#include <tr1/memory>
using std::tr1::shared_ptr;
#endif

#include "../Hierarchy/PersistentHierarchyNode.h"

namespace ObjectCube 
{
	class HierarchyNodeDataAccess;
	
	class HierarchyNodeConverter
	{
	public:
		static shared_ptr<PersistentHierarchyNode> dataAccessToLogic( HierarchyNodeDataAccess* hierarchyNodeDA );
		static HierarchyNodeDataAccess* logicToDataAccess( const PersistentHierarchyNode* hierarchyNode );
		
		static vector<shared_ptr<HierarchyNode> > dataAccessToLogic( vector<HierarchyNodeDataAccess*> hierarchyNodesDA );
		static vector<HierarchyNodeDataAccess*> logicToDataAccess( const vector<shared_ptr<HierarchyNode> >& hierarchyNodes );
	};
}

#endif
