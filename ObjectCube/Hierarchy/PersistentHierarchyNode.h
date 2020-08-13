/*
 *  PersistentHierarchyNode.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 16.12.2009.
 *  Copyright 2009 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_PERSISTENT_HIERARCHY_NODE_
#define ObjectCube_PERSISTENT_HIERARCHY_NODE_

#ifdef __APPLE__
#include <memory>
using std::shared_ptr;
#else
#include <tr1/memory>
using std::shared_ptr;
#endif

#include "TagBasedHierarchyNode.h"

using namespace std;

namespace ObjectCube
{
	class Tag;
	
	class PersistentHierarchyNode : public TagBasedHierarchyNode
	{
		friend class PersistentDimension;
		friend class HierarchyNodeConverter;
		
	public: //Constructors & Destructors
		PersistentHierarchyNode();
		PersistentHierarchyNode( const Tag* /*const*/ tag );
		PersistentHierarchyNode( const Tag* /*const*/ tag, int dimensionId, int tagSetId );
		PersistentHierarchyNode( const Tag* /*const*/ tag, int dimensionId, int tagSetId, const string& childCategoryTitle );
		
		virtual ~PersistentHierarchyNode();
		
	protected: //Interface for PersistentDimension
		
		virtual void updateBorders_( int& borderCounter );
		
		PersistentHierarchyNode create_();
		void remove_();
		
		PersistentHierarchyNode* addBranch_( const Tag* /*const*/ tag ); //Direct add
		void addBranch_( int parentNodeId, const Tag* /*const*/ tag, PersistentHierarchyNode& child ); //Indirect add
		
		void removeBranch_( int id ); //Traverses the tree
		
		//void getNode_( int tagId, PersistentHierarchyNode& node );
		
		PersistentHierarchyNode* constructTree_( vector<std::shared_ptr<HierarchyNode> >& nodes, int& offset );
		
	public:
		virtual HierarchyNode& operator=( const HierarchyNode& node );
		
	};
		
}


#endif
