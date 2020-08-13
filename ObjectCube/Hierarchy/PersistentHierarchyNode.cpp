/*
 *  PersistentHierarchyNode.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 16.12.2009.
 *  Copyright 2009 Reykjavik University. All rights reserved.
 *
 */

#include "PersistentHierarchyNode.h"

#include <iostream>
#include <sstream>

#ifdef __APPLE__
#include <memory>
using std::shared_ptr;
#else
#include <tr1/memory>
using std::shared_ptr;
#endif

#include "../DataAccess/Factories/HierarchyNodeDataAccessFactory.h"
#include "../DataAccess/Root/HierarchyNodeDataAccess.h"
#include "../Converters/HierarchyNodeConverter.h"

#include "../Hub.h"
#include "../TagSet/TagSet.h"
#include "../Tag/Tag.h"
#include "../LayerShared/SharedDefinitions.h"
#include "../LayerShared/Exception.h"


using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

PersistentHierarchyNode::PersistentHierarchyNode()
: TagBasedHierarchyNode( HierarchyNode::PERSISTENT )
{

}
//____________________________________________________________________________________________________________________________________________________________________________________

PersistentHierarchyNode::PersistentHierarchyNode( const Tag* /*const*/ tag )
: TagBasedHierarchyNode( HierarchyNode::PERSISTENT, tag )
{
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

PersistentHierarchyNode::PersistentHierarchyNode( const Tag* /*const*/ tag, int dimensionId, int tagSetId )
: TagBasedHierarchyNode( HierarchyNode::PERSISTENT, tag, dimensionId, tagSetId )
{

}
//____________________________________________________________________________________________________________________________________________________________________________________

PersistentHierarchyNode::PersistentHierarchyNode( const Tag* /*const*/ tag, int dimensionId, int tagSetId, const string& childCategoryTitle )
: TagBasedHierarchyNode( HierarchyNode::PERSISTENT, tag, dimensionId, tagSetId, childCategoryTitle )
{

}
//____________________________________________________________________________________________________________________________________________________________________________________

PersistentHierarchyNode::~PersistentHierarchyNode()
{

}
//____________________________________________________________________________________________________________________________________________________________________________________

PersistentHierarchyNode* PersistentHierarchyNode::constructTree_( vector<std::shared_ptr<HierarchyNode> >& nodes, int& offset )
{
	if( offset >= nodes.size() ) 
	{
		return this;
	}
	*this = *dynamic_cast<PersistentHierarchyNode*>( nodes[ offset++ ].get() );
	name_ = Hub::getHub()->getTagSet( getTagSetId() )->getTag( getTagId() )->valueAsString();
	
	do 
	{
		if( offset >= nodes.size() ) 
		{
			return this;
		}
	
		if( dynamic_cast<PersistentHierarchyNode*>( nodes[ offset ].get() )->rightBorder_ < rightBorder_ ) //Sub branch or branches
		{
			std::shared_ptr<PersistentHierarchyNode> branch( new PersistentHierarchyNode() );
			*branch.get() = *dynamic_cast<PersistentHierarchyNode*>( nodes[ offset ].get() );
			
			branch->constructTree_( nodes, offset );
			children_.push_back( branch );
		}
		else 
		{
			return this;
		}
	}
	while( true );
}
//____________________________________________________________________________________________________________________________________________________________________________________

PersistentHierarchyNode PersistentHierarchyNode::create_()
{	
	unique_ptr<HierarchyNodeDataAccess> dataAccess( HierarchyNodeConverter::logicToDataAccess( this ) );
	std::shared_ptr<PersistentHierarchyNode> created( HierarchyNodeConverter::dataAccessToLogic( dataAccess->create() ) );
	*this = *created.get();
	
	name_ = Hub::getHub()->getTagSet( getTagSetId() )->getTag( getTagId() )->valueAsString();
	
	return *this;
}
//____________________________________________________________________________________________________________________________________________________________________________________

PersistentHierarchyNode* PersistentHierarchyNode::addBranch_( const Tag* /*const*/ tag )
{
	std::shared_ptr<PersistentHierarchyNode> child( new PersistentHierarchyNode( tag, dimensionId_, tagSetId_ ) );
	child->create_();  //Insert into db (get an id there)
	children_.push_back( child );
	return child.get();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void PersistentHierarchyNode::addBranch_( int parentNodeId, const Tag* /*const*/ tag, PersistentHierarchyNode& child )
{
	if( id_ == parentNodeId )
	{
		child = *addBranch_( tag );
		return;
	}
	
	for( vector<std::shared_ptr<HierarchyNode> >::iterator itr = children_.begin(); itr != children_.end(); ++itr )
	{
		PersistentHierarchyNode* phNode = dynamic_cast<PersistentHierarchyNode*>( (*itr).get() );
		if( phNode->getId() == parentNodeId )
		{
			child = *phNode->addBranch_( tag );
			return;
		}
		else 
		{
			phNode->addBranch_( parentNodeId, tag, child );
		}
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________

void PersistentHierarchyNode::remove_()
{
	//Remove all children and then delete self
	for( vector<std::shared_ptr<HierarchyNode> >::iterator itr = children_.begin(); itr != children_.end(); ++itr )
	{
		PersistentHierarchyNode* phNode = dynamic_cast<PersistentHierarchyNode*>( (*itr).get() );
		phNode->remove_();
	}
	
	unique_ptr<HierarchyNodeDataAccess> dataAccess( HierarchyNodeConverter::logicToDataAccess( this ) );
	dataAccess->remove();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void PersistentHierarchyNode::removeBranch_( int id )
{
	if( id_ == id ) //Top node of the branch we want to remove
	{
		remove_();
		return;
	}
	for( vector<std::shared_ptr<HierarchyNode> >::iterator itr = children_.begin(); itr != children_.end(); ++itr )
	{
		PersistentHierarchyNode* phNode = dynamic_cast<PersistentHierarchyNode*>( (*itr).get() );		
		phNode->removeBranch_( id );
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________
/*
void PersistentHierarchyNode::getNode_( int tagId, PersistentHierarchyNode& node )
{
	if( getTagId() == tagId )
	{
		node = *this;
		return;
	}
	
	for( vector<HierarchyNode*>::iterator itr = children_.begin(); itr != children_.end(); ++itr )
	{
		PersistentHierarchyNode* phNode = dynamic_cast<PersistentHierarchyNode*>( *itr );	
		phNode->getNode_( tagId, node );
	}
}
 */
//____________________________________________________________________________________________________________________________________________________________________________________

void PersistentHierarchyNode::updateBorders_( int& borderCounter )
{
	TagBasedHierarchyNode::updateBorders_( borderCounter );
	
	unique_ptr<HierarchyNodeDataAccess> dataAccess( HierarchyNodeConverter::logicToDataAccess( this ) );
	dataAccess->update();
}	
//____________________________________________________________________________________________________________________________________________________________________________________

HierarchyNode& PersistentHierarchyNode::operator=( const HierarchyNode& node )
{
	TagBasedHierarchyNode::operator=( node );	
	return *this;
}
//____________________________________________________________________________________________________________________________________________________________________________________












