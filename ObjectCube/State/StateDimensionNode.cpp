/*
 *  StateDimensionNode.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 25.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "StateDimensionNode.h"

#include <sstream>
#include <set>

#include "../Hierarchy/HierarchyNode.h"
#include "../LayerShared/Parameters.h"
#include "../LayerShared/DebugInfo.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

StateDimensionNode::StateDimensionNode( const HierarchyNode* /*const*/ node, int filterId, map<int, map<int, vector<int> > >& filterIdNodeIdObjectIds /*const vector<StateObject>& objects*/ )
: node_( node )
{
	//Rekja okkur í gegnum child listann, byggja tréið
	const vector<HierarchyNode*> children = node->getBranches();
	for( vector<HierarchyNode*>::const_iterator itr = children.begin(); itr != children.end(); ++itr )
	{
		StateDimensionNode sNode( *itr, filterId, filterIdNodeIdObjectIds );
		branches_.push_back( sNode );
	}
	
	/*  Objects can be filtered in the state outside of the leafs.
	if( branches_.size() == 0 ) //Leaf
	{
		//populate object ids using the data in States object vector
	}
	 */
	
	//Hack due to lack of support in boost python for sets :(
	vector<int> tempObjectIds = objectIdsIncludedByNode_( filterId, filterIdNodeIdObjectIds);
	set<int> objectSet;
	objectSet.insert( tempObjectIds.begin(), tempObjectIds.end() );
	tempObjectIds.clear();
	tempObjectIds.insert( tempObjectIds.begin(), objectSet.begin(), objectSet.end() );
	
	setObjectIds_( tempObjectIds );
	
	if( Parameters::getParameters()->contains( "outputStateHierarchyObjects" ) )
	{
		DebugInfo::getDebugInfo()->output( "StateDimensionNode", "Node: ", getNode()->getName() );
		DebugInfo::getDebugInfo()->output( "StateDimensionNode", "StateDimensionNode", "No of objects in Node: ", getObjectIds().size() );
		stringstream ids;
		for( vector<int>::iterator itr = objectIds_.begin(); itr != objectIds_.end(); ++itr )
		{
			ids << *itr << " ";
		}
		DebugInfo::getDebugInfo()->output( "StateDimensionNode", "Object ids: ", ids.str() );
	}
}

//____________________________________________________________________________________________________________________________________________________________________________________

StateDimensionNode::StateDimensionNode( const StateDimensionNode& stateNode )
//: node_( stateNode.node_ )
{
	setBranches_( stateNode.getBranches() );
	setObjectIds_( stateNode.getObjectIds() );
	node_ = stateNode.node_;
}
//____________________________________________________________________________________________________________________________________________________________________________________

StateDimensionNode& StateDimensionNode::operator=( const StateDimensionNode& stateNode )
{
	setBranches_( stateNode.getBranches() );
	setObjectIds_( stateNode.getObjectIds() );
	node_ = stateNode.node_;
	return *this;
}
//____________________________________________________________________________________________________________________________________________________________________________________

vector<int> StateDimensionNode::objectIdsIncludedByNode_( int filterId, map<int, map<int, vector<int> > >& filterIdNodeIdObjectIds /*const vector<StateObject>& objects*/ ) const 
{
	vector<int> objectIds;
	/*
	for( vector<StateObject>::const_iterator objectItr = objects.begin(); objectItr != objects.end(); ++objectItr ) //For all objects retrieved
	{
		const vector<StateTag> tags = (*objectItr).getTags();
		for( vector<StateTag>::const_iterator tagItr = tags.begin(); tagItr != tags.end(); ++tagItr ) //For each tag of the object
		{
			map<int, int> filterAndDimensionNodeIds = (*tagItr).getFilterAndDimensionNodeIds();
			if( filterAndDimensionNodeIds.count( filterId ) == 0 )
			{
				continue;
			}
			int nodeId = filterAndDimensionNodeIds[ filterId ];
			if( nodeId == getNode()->getId() )
			{
				objectIds.push_back( (*objectItr).getId() );
			}
		}
	}
	 */
	vector<int> tempObjectIds = filterIdNodeIdObjectIds[ filterId ][ node_->getId() ];
	objectIds.insert( objectIds.end(), tempObjectIds.begin(), tempObjectIds.end() );
	
	//Add the object id's of the branches
	for( vector<StateDimensionNode>::const_iterator branchItr = branches_.begin(); branchItr != branches_.end(); ++branchItr )
	{
		const vector<int> branchObjectIds = (*branchItr).getObjectIds();
		objectIds.insert( objectIds.end(), branchObjectIds.begin(), branchObjectIds.end() );
	}
	
	return objectIds;
}
//____________________________________________________________________________________________________________________________________________________________________________________

bool StateDimensionNode::getParentNode_( int childNodeId, StateDimensionNode& parentNode ) const
{
	for( vector<StateDimensionNode>::const_iterator itr = branches_.begin(); itr != branches_.end(); ++itr )
	{
		if( (*itr).getNode()->getId() == childNodeId )
		{
			parentNode = *this;
			return true;
		}
		if( (*itr).getParentNode_( childNodeId, parentNode ) )
		{
			return true;
		}
	}
	return false;
}
//____________________________________________________________________________________________________________________________________________________________________________________

bool StateDimensionNode::getNode_( int nodeId, StateDimensionNode& node ) const
{
	if( getNode()->getId() == nodeId )
	{
		node = *this;
		return true;
	}
	
	for( vector<StateDimensionNode>::const_iterator itr = branches_.begin(); itr != branches_.end(); ++itr )
	{
		if( (*itr).getNode_( nodeId, node ) )
		{
			return true;
		}
	}
		
	return false;
}
//____________________________________________________________________________________________________________________________________________________________________________________

vector<StateDimensionNode> StateDimensionNode::getSubHierarchyLevel( int level )
{
	//DEBUG
	//return branches_;
	
    vector<StateDimensionNode> subHierarchyLevelNodes;
    
    getSubHierarchyLevel_( subHierarchyLevelNodes, level );
    
    return subHierarchyLevelNodes;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void StateDimensionNode::getSubHierarchyLevel_( vector<StateDimensionNode>& subHierarchyLevelNodes, int level ) 
{
    if( level == 0 )
    {
        subHierarchyLevelNodes.insert( subHierarchyLevelNodes.begin(), branches_.begin(), branches_.end() );
        return;
    }
    
	--level;
    for( vector<StateDimensionNode>::iterator itr = branches_.begin(); itr != branches_.end(); ++itr )
	{
        (*itr).getSubHierarchyLevel_( subHierarchyLevelNodes, level );
    }
}
//____________________________________________________________________________________________________________________________________________________________________________________
































