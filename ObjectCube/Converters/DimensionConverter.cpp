/*
 *  DimensionConverter.cpp
 *  Prada
 *
 *  Created by Grímur Tómasson on 8.2.2010.
 *  Copyright 2010 RU. All rights reserved.
 *
 */

#include "DimensionConverter.h"

#include "../DataAccess/Root/DimensionDataAccess.h"
#include "../DataAccess/Factories/DimensionDataAccessFactory.h"
#include "HierarchyNodeConverter.h"
#include "../Hierarchy/HierarchyNodeFactory.h"

#include <memory>
#include <iostream>

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

PersistentDimension* DimensionConverter::dataAccessToLogic( DimensionDataAccess* dimensionHierarchyDA )
{
	PersistentDimension* hierarchy = new PersistentDimension();
	hierarchy->setId_( dimensionHierarchyDA->getId() );
	hierarchy->setTagSetId_( dimensionHierarchyDA->getTagSetId() );
	
	std::shared_ptr<PersistentHierarchyNode> rootNode( HierarchyNodeConverter::dataAccessToLogic( dimensionHierarchyDA->getRoot() ) );
	*hierarchy->root_ = *rootNode.get(); 

	return hierarchy;
}
//____________________________________________________________________________________________________________________________________________________________________________________

DimensionDataAccess* DimensionConverter::logicToDataAccess( const PersistentDimension* dimensionHierarchy )
{
	DimensionDataAccess* dimensionHierarchyDA = DimensionDataAccessFactory::create();
	dimensionHierarchyDA->setId( dimensionHierarchy->getId() );
	dimensionHierarchyDA->setTagSetId( dimensionHierarchy->getTagSetId() );
	
	dimensionHierarchyDA->setRoot( HierarchyNodeConverter::logicToDataAccess( dynamic_cast<const PersistentHierarchyNode*>( dimensionHierarchy->root_.get() )  ) );
	return dimensionHierarchyDA;
}
//____________________________________________________________________________________________________________________________________________________________________________________

vector<PersistentDimension*> DimensionConverter::dataAccessToLogic( vector<DimensionDataAccess*> dimensionHierarchiesDA )
{
	vector<PersistentDimension*> hierarchies;
	vector<DimensionDataAccess*>::iterator itr;
	for( itr = dimensionHierarchiesDA.begin(); itr != dimensionHierarchiesDA.end(); itr++ )
	{
		hierarchies.push_back( DimensionConverter::dataAccessToLogic( *itr ) );
	}
	return hierarchies;
}
//____________________________________________________________________________________________________________________________________________________________________________________

vector<DimensionDataAccess*> DimensionConverter::logicToDataAccess( const vector<PersistentDimension*>& dimensionHierarchies )
{
	vector<DimensionDataAccess*> hierarchies;
	for( vector<PersistentDimension*>::const_iterator itr = dimensionHierarchies.begin(); itr != dimensionHierarchies.end(); ++itr )
	{
		hierarchies.push_back( DimensionConverter::logicToDataAccess( *itr ) );
	}
	return hierarchies;
}
//____________________________________________________________________________________________________________________________________________________________________________________

