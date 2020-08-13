/*
 *  HierarchyNode.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 6.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "HierarchyNode.h"

#include <iostream>
#include <sstream>
#include <memory>

#include "../LayerShared/SharedDefinitions.h"
#include "../LayerShared/Exception.h"
#include "../LayerShared/MemoryManagement.h"
#include "HierarchyNodeFactory.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

HierarchyNode::HierarchyNode( int typeId )
{
	init_();
	typeId_ = typeId;
}
//____________________________________________________________________________________________________________________________________________________________________________________

HierarchyNode::~HierarchyNode()
{
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void HierarchyNode::init_()
{
	id_ = INVALID_VALUE;
	typeId_ = INVALID_VALUE;
	tagSetId_ = INVALID_VALUE;
	leftBorder_ = INVALID_VALUE;
	rightBorder_ = INVALID_VALUE;	
	name_ = "Not Initialized!";
}
//____________________________________________________________________________________________________________________________________________________________________________________

HierarchyNode::HierarchyNode( const HierarchyNode& node )
{
	copyValues_( node );
}
//____________________________________________________________________________________________________________________________________________________________________________________

HierarchyNode& HierarchyNode::operator=( const HierarchyNode& node )
{
	children_.clear();
	copyValues_( node );
	
	return *this;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void HierarchyNode::copyValues_( const HierarchyNode& node )
{	
	setId_( node.getId() );
	typeId_ = node.getTypeId();
	setTagSetId_( node.getTagSetId() );
	setDimensionId_( node.getDimensionId() );
	setLeftBorder_( node.getLeftBorder() );
	setRightBorder_( node.getRightBorder() );
	setName_( node.getName() );
	setChildCategoryTitle_( node.getChildCategoryTitle() );
	
	//Children
	/*
	const vector<HierarchyNode*> children = node.getBranches();
	for( vector<HierarchyNode*>::const_iterator itr = children.begin(); itr != children.end(); ++itr )
	{
		std::shared_ptr<HierarchyNode> nNode( HierarchyNodeFactory::create( node.getTypeId() ) );  //All the nodes of a dimension must be of the same type
		*nNode.get() = *(*itr);
		children_.push_back( nNode );
	}
	 */
	children_ = node.children_;
}
//____________________________________________________________________________________________________________________________________________________________________________________

map<int, int> HierarchyNode::getSubtreeTagIds() const
{
	return getSubtreeTagIds_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

const vector<HierarchyNode*> HierarchyNode::getBranches() const
{
	vector<HierarchyNode*> nodes;
	for( vector< std::shared_ptr<HierarchyNode> >::const_iterator itr = children_.begin(); itr != children_.end(); ++itr )
	{
		nodes.push_back( (*itr).get() );
	}
	return nodes;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void HierarchyNode::setBranches_( const vector<HierarchyNode*>& branches )
{
	for( vector<HierarchyNode*>::const_iterator itr = branches.begin(); itr != branches.end(); ++itr )
	{
		std::shared_ptr<HierarchyNode> nNode( HierarchyNodeFactory::create( (*itr)->getTypeId() ) );  //All the nodes of a dimension must be of the same type
		*nNode.get() = *(*itr);
		children_.push_back( nNode );	
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________

HierarchyNode* HierarchyNode::getBranch( int id )
{
	if( getId() == id )
	{
		throw Exception( "HierarchyNode::getBranch","A node in a hierarchy is not a branch of it self.", id );
	}
	
	HierarchyNode* node = 0;
	for( vector< std::shared_ptr<HierarchyNode> >::iterator itr = children_.begin(); itr != children_.end(); ++itr )
	{
		if( (*itr)->getBranch_( id, node ) )
		{
			break;
		}
	}
	
	if( node == 0 )
	{
		throw Exception("HierarchyNode::getBranch", "Hierarchy did not contain requested branch.", id );	
	}
	
	return node;
}
//____________________________________________________________________________________________________________________________________________________________________________________

const HierarchyNode* HierarchyNode::getBranch( int id ) const 
{
	HierarchyNode* thisNotConst = const_cast<HierarchyNode*>( this );
	return thisNotConst->getBranch( id );
}
//____________________________________________________________________________________________________________________________________________________________________________________

bool HierarchyNode::getBranch_( int id, HierarchyNode*& node )
{
	if( getId() == id )
	{
		node = this;
		return true;
	}
	for( vector<std::shared_ptr<HierarchyNode> >::iterator itr = children_.begin(); itr != children_.end(); ++itr )
	{
		if( (*itr)->getBranch_( id, node ) )
		{
			return true;
		}
	}
	return false;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void HierarchyNode::updateBorders_( int& borderCounter )
{
	if( id_ == HierarchyNode::INVALID )
	{
		return;
	}
	
	leftBorder_ = borderCounter++;
	
	for( vector<std::shared_ptr<HierarchyNode> >::iterator itr = children_.begin(); itr != children_.end(); ++itr )
	{
		(*itr)->updateBorders_( borderCounter );
	}		
	rightBorder_ = borderCounter++;
}	
//____________________________________________________________________________________________________________________________________________________________________________________

string HierarchyNode::traverse( int indent ) const
{
	if( id_ == INVALID_VALUE ) 
	{
		return "";
	}
	
	string prefix;
	for( int i = 0; i < indent; i++) 
	{
		prefix += " ";
	}
	
	stringstream stringStream;
	stringStream << prefix << "name: " << name_ << "\n";
	stringStream << prefix << "  left: " << leftBorder_ << "\n";
	
	indent += 4;
	for( vector<std::shared_ptr<HierarchyNode> >::const_iterator itr = children_.begin(); itr != children_.end(); ++itr )
	{
		stringStream << (*itr)->traverse( indent );
	}		
	
	stringStream << prefix << "  right: " << rightBorder_ << "\n";
	stringStream << prefix << "name: " << name_ << "\n\n";
	
	return stringStream.str();
}
//____________________________________________________________________________________________________________________________________________________________________________________

bool HierarchyNode::operator==( HierarchyNode const& x) const 
{ 
	return this->getId() == x.getId(); 
}
//____________________________________________________________________________________________________________________________________________________________________________________

bool HierarchyNode::operator!=( HierarchyNode const& x) const 
{ 
	return this->getId() != x.getId(); 
}
//____________________________________________________________________________________________________________________________________________________________________________________

bool HierarchyNode::operator < ( const HierarchyNode& x ) const
{
	return getId() < x.getId();
}
//____________________________________________________________________________________________________________________________________________________________________________________















