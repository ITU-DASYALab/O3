/*
 *  DefaultHierarchyNode.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 2.7.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_DEFAULT_HIERARCHY_NODE_
#define ObjectCube_DEFAULT_HIERARCHY_NODE_

#include "TagBasedHierarchyNode.h"

using namespace std;

namespace ObjectCube
{	
	class DefaultHierarchyNode : public TagBasedHierarchyNode 
	{
		friend class DefaultDimension;
		friend class DefaultHierarchyNodeTest;
		
	public: //Constructors & Destructors
		DefaultHierarchyNode();
		DefaultHierarchyNode( const Tag* /*const*/ tag );
		DefaultHierarchyNode( const Tag* /*const*/ tag, int dimensionId, int tagSetId );
		DefaultHierarchyNode( const Tag* /*const*/ tag, int dimensionId, int tagSetId, const string& childCategoryTitle );
		
		virtual ~DefaultHierarchyNode();
		
	protected: //Interface for PersistentDimension
		void addBranch_( DefaultHierarchyNode* node ); //Direct add
		
	public:
		virtual HierarchyNode& operator=( const HierarchyNode& node );
	};
	
}

#endif
