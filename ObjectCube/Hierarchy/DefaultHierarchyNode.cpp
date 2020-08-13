/*
 *  DefaultHierarchyNode.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 2.7.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "DefaultHierarchyNode.h"

#include "../Hub.h"
#include "../TagSet/TagSet.h"
#include "../Tag/Tag.h"
#include "../LayerShared/SharedDefinitions.h"
#include "../LayerShared/Exception.h"


using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

DefaultHierarchyNode::DefaultHierarchyNode()
: TagBasedHierarchyNode( HierarchyNode::DEFAULT )
{
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

DefaultHierarchyNode::DefaultHierarchyNode( const Tag* /*const*/ tag )
: TagBasedHierarchyNode( HierarchyNode::DEFAULT, tag )
{
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

DefaultHierarchyNode::DefaultHierarchyNode( const Tag* /*const*/ tag, int dimensionId, int tagSetId )
: TagBasedHierarchyNode( HierarchyNode::DEFAULT, tag, dimensionId, tagSetId )
{
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

DefaultHierarchyNode::DefaultHierarchyNode( const Tag* /*const*/ tag, int dimensionId, int tagSetId, const string& childCategoryTitle )
: TagBasedHierarchyNode( HierarchyNode::DEFAULT, tag, dimensionId, tagSetId, childCategoryTitle )
{
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

DefaultHierarchyNode::~DefaultHierarchyNode()
{
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

HierarchyNode& DefaultHierarchyNode::operator=( const HierarchyNode& node )
{
	TagBasedHierarchyNode::operator=( node );

	return *this;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DefaultHierarchyNode::addBranch_( DefaultHierarchyNode* node )
{
	std::shared_ptr<DefaultHierarchyNode> pNode( new DefaultHierarchyNode() );
	*pNode.get() = *node;
	children_.push_back( pNode );
}
//____________________________________________________________________________________________________________________________________________________________________________________

