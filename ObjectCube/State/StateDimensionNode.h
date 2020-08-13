/*
 *  StateDimensionNode.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 25.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_STATE_DIMENSION_NODE_
#define ObjectCube_STATE_DIMENSION_NODE_

#include "../LayerShared/DimensionCommon.h"

#include <vector>

#include "../LayerShared/HierarchyNodeCommon.h"
#include "StateObject.h"

using namespace std;

namespace ObjectCube
{	
	class HierarchyNode;
	
	class StateDimensionNode : public HierarchyNodeCommon
	{
	public:
		//Constructors & destructor
		StateDimensionNode( const HierarchyNode* /*const*/ node, int filterId, map<int, map<int, vector<int> > >& filterIdNodeIdObjectIds /*const vector<StateObject>& objects*/ );
		StateDimensionNode() {;}
		virtual ~StateDimensionNode() {;}
		
		StateDimensionNode( const StateDimensionNode& stateNode );  //Copy constructor
		StateDimensionNode& operator=( const StateDimensionNode& stateNode );
		
		const HierarchyNode* /*const*/ getNode() const { return node_; } //Const removed due to boost python limitation
		const vector<StateDimensionNode> getBranches() const { return branches_; }
		const vector<int> getObjectIds() const { return objectIds_; }
		vector<StateDimensionNode> getSubHierarchyLevel( int level );
		
	protected:
		void setBranches_( const vector<StateDimensionNode>& branches ) { branches_ = branches; }
		void setObjectIds_( vector<int> objectIds ) { objectIds_ = objectIds; }
		
		vector<int> objectIdsIncludedByNode_( int filterId, map<int, map<int, vector<int> > >& filterIdNodeIdObjectIds /*const vector<StateObject>& objects*/ ) const;
		bool getParentNode_( int childNodeId, StateDimensionNode& parentNode ) const;
		bool getNode_( int nodeId, StateDimensionNode& node ) const;
		
		void getSubHierarchyLevel_( vector<StateDimensionNode>& subHierarchyLevelNodes, int level );
	private:
		const HierarchyNode* /*const*/ node_; //Points to the std::shared_ptr contents in TagSet.  Do not memory manage!
		vector<StateDimensionNode> branches_;
		vector<int> objectIds_;
		
	public:
		bool operator==( StateDimensionNode const& x) const { return getNode() == x.getNode(); }

		friend class StateDimension;
	};
	
}

#endif