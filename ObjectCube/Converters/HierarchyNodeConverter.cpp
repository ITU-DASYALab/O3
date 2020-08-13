/*
 *  HierarchyNodeConverter.cpp
 *  Prada
 *
 *  Created by Grímur Tómasson on 8.2.2010.
 *  Copyright 2010 RU. All rights reserved.
 *
 */

#include "HierarchyNodeConverter.h"

#include "../DataAccess/Root/HierarchyNodeDataAccess.h"
#include "../DataAccess/Factories/HierarchyNodeDataAccessFactory.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

std::shared_ptr<PersistentHierarchyNode> HierarchyNodeConverter::dataAccessToLogic( HierarchyNodeDataAccess* hierarchyNodeDA )
{
	std::shared_ptr<PersistentHierarchyNode> hierarchyNode( new PersistentHierarchyNode() );
	hierarchyNode->setId_( hierarchyNodeDA->getId() );
	hierarchyNode->setDimensionId_( hierarchyNodeDA->getDimensionId() );
	hierarchyNode->setTagSetId_( hierarchyNodeDA->getTagSetId() );
	hierarchyNode->setTagId_( hierarchyNodeDA->getTagId() );
	hierarchyNode->setLeftBorder_( hierarchyNodeDA->getLeftBorder() );
	hierarchyNode->setRightBorder_( hierarchyNodeDA->getRightBorder() );
	hierarchyNode->setChildCategoryTitle_( hierarchyNodeDA->getChildCategoryTitle() );
	
	hierarchyNode->children_ = HierarchyNodeConverter::dataAccessToLogic( hierarchyNodeDA->getBranches()  );
	return hierarchyNode;
}
//____________________________________________________________________________________________________________________________________________________________________________________

HierarchyNodeDataAccess* HierarchyNodeConverter::logicToDataAccess( const PersistentHierarchyNode* hierarchyNode )
{
	HierarchyNodeDataAccess* hierarchyNodeDA = HierarchyNodeDataAccessFactory::create();
	if( hierarchyNode == 0 )
	{
		return hierarchyNodeDA;
	}
	hierarchyNodeDA->setId( hierarchyNode->getId() );
	hierarchyNodeDA->setHierarchyId( hierarchyNode->getDimensionId() );
	hierarchyNodeDA->setTagSetId( hierarchyNode->tagSetId_ );
	hierarchyNodeDA->setTagId( hierarchyNode->getTagId() );
	hierarchyNodeDA->setLeftBorder( hierarchyNode->getLeftBorder() );
	hierarchyNodeDA->setRightBorder( hierarchyNode->getRightBorder() );
	hierarchyNodeDA->setChildCategoryTitle( hierarchyNode->getChildCategoryTitle() );
	hierarchyNodeDA->setBranches( HierarchyNodeConverter::logicToDataAccess( hierarchyNode->children_ ) );
	return hierarchyNodeDA;
}
//____________________________________________________________________________________________________________________________________________________________________________________

vector<std::shared_ptr<HierarchyNode> > HierarchyNodeConverter::dataAccessToLogic( vector<HierarchyNodeDataAccess*> hierarchyNodesDA )
{
	vector<std::shared_ptr<HierarchyNode> > nodes;
	for( vector<HierarchyNodeDataAccess*>::iterator itr = hierarchyNodesDA.begin(); itr != hierarchyNodesDA.end(); ++itr )
	{
		nodes.push_back( HierarchyNodeConverter::dataAccessToLogic( *itr ) );
	}
	return nodes;
}
//____________________________________________________________________________________________________________________________________________________________________________________

vector<HierarchyNodeDataAccess*> HierarchyNodeConverter::logicToDataAccess( const vector<std::shared_ptr<HierarchyNode> >& hierarchyNodes )
{
	vector<HierarchyNodeDataAccess*> hierarchyNodesDA;
	for( vector<std::shared_ptr<HierarchyNode> >::const_iterator itr = hierarchyNodes.begin(); itr != hierarchyNodes.end(); ++itr )
	{
		
		hierarchyNodesDA.push_back( HierarchyNodeConverter::logicToDataAccess( dynamic_cast<PersistentHierarchyNode*>( (*itr).get() ) ) );
	}
	return hierarchyNodesDA;
}
//____________________________________________________________________________________________________________________________________________________________________________________

