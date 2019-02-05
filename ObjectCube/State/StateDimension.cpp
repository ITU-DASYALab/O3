/*
 *  StateDimension.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 25.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "StateDimension.h"

#include "../Hierarchy/Dimension.h"
#include "../LayerShared/Exception.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

StateDimension::StateDimension( const Dimension* /*const*/ dimension, int filterId, map<int, map<int, vector<int> > >& filterIdNodeIdObjectIds /*const vector<StateObject>& objects*/ )
: root_( dimension->getRoot(), filterId, filterIdNodeIdObjectIds )
{
	setId_( dimension->getId() );
	setTypeId_( dimension->getTypeId() );
	setTagSetId_( dimension->getTagSetId() );
	setFilterId_( filterId );
}
//____________________________________________________________________________________________________________________________________________________________________________________

const StateDimensionNode StateDimension::getParentNode( int nodeId ) const
{
	if( nodeId == getRoot().getNode()->getId() )
	{
		throw Exception( "StateDimension::getParent", "The root of a dimension has no parent node!" );
	}
	
	StateDimensionNode parent( getRoot() ); //No empty constructor
	if( !getRoot().getParentNode_( nodeId, parent ) )
	{
		throw Exception( "StateDimension::getParent", "There was no parent found for nodeId: ", nodeId );
	}
	return parent;
}
//____________________________________________________________________________________________________________________________________________________________________________________

const StateDimensionNode StateDimension::getNode( int nodeId ) const
{
	StateDimensionNode node( getRoot() ); // No empty constructor
	if( !getRoot().getNode_( nodeId, node ) )
	{
		throw Exception( "StateDimension::getNode", "There was no node found for nodeId: ", nodeId );
	}
	return node;
}
//____________________________________________________________________________________________________________________________________________________________________________________
