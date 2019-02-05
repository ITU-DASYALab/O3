/*
 *  VirtualDimension.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 5.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "VirtualDimension.h"

#include <memory>
#include "limits.h"

#include "../LayerShared/SharedDefinitions.h"
#include "../LayerShared/Exception.h"
#include "../LayerShared/MemoryManagement.h"
#include "VirtualHierarchyNode.h"


using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

int VirtualDimension::idCounter_ = INT_MAX /*SHRT_MAX*/;

//____________________________________________________________________________________________________________________________________________________________________________________

VirtualDimension::VirtualDimension(	int tagSetId, 
									const string& outerAttributePattern, 
									const string& innerAttributePattern, 
									const string& rootValue )
: Dimension( Dimension::VIRTUAL, tagSetId )
{
	init_();
	outerAttributePattern_ = outerAttributePattern;
	innerAttributePattern_ = innerAttributePattern;
	type_ = PATTERN_MATCHING;
	VirtualHierarchyNode root( nodeIdCounter_++, rootValue, tagSetId, getId(), outerAttributePattern_, innerAttributePattern_ );
	Dimension::init_( &root );
}
//____________________________________________________________________________________________________________________________________________________________________________________

VirtualDimension::VirtualDimension( int tagSetId,
									const string& outerAttributePattern, 
									const string& innerAttributePattern, 
									const string& rootValue, 
									const string& childCategoryTitle )
: Dimension( Dimension::VIRTUAL, tagSetId )
{
	init_();
	outerAttributePattern_ = outerAttributePattern;
	innerAttributePattern_ = innerAttributePattern;
	type_ = PATTERN_MATCHING;
	VirtualHierarchyNode root( nodeIdCounter_++, rootValue, tagSetId, getId(), outerAttributePattern_, innerAttributePattern_, childCategoryTitle );
	Dimension::init_( &root );
}
//____________________________________________________________________________________________________________________________________________________________________________________

VirtualDimension::VirtualDimension(	int tagSetId, 
									extractionFunction function,
									const string& rootValue )
: Dimension( Dimension::VIRTUAL, tagSetId )
{
	init_();
	type_ = EXTRACTION_FUNCTION;
	extractionFunction_ = function;
	VirtualHierarchyNode root( nodeIdCounter_++, rootValue, tagSetId, getId(), extractionFunction_ );
	Dimension::init_( &root );
}
//____________________________________________________________________________________________________________________________________________________________________________________

VirtualDimension::VirtualDimension()
: Dimension( Dimension::VIRTUAL )
{
	init_();
	type_ = PATTERN_MATCHING;
	VirtualHierarchyNode root;
	Dimension::init_( &root );
}
//____________________________________________________________________________________________________________________________________________________________________________________

VirtualDimension::~VirtualDimension()
{

}
//____________________________________________________________________________________________________________________________________________________________________________________

void VirtualDimension::init_()
{
	nodeIdCounter_ = 1;
	type_ = -1;
	setId_( idCounter_-- );
}
//____________________________________________________________________________________________________________________________________________________________________________________

VirtualHierarchyNode* VirtualDimension::addNode( int parentNodeId, const string& nodeValue )
{
	if( getType() == PATTERN_MATCHING )
	{
		VirtualHierarchyNode node( nodeIdCounter_++, nodeValue, getTagSetId(), getId(), outerAttributePattern_, innerAttributePattern_ );
		return addNode_( parentNodeId, &node);
	}
	// extraction function
	VirtualHierarchyNode node( nodeIdCounter_++, nodeValue, getTagSetId(), getId(), extractionFunction_ );
	return addNode_( parentNodeId, &node);
}
//____________________________________________________________________________________________________________________________________________________________________________________

VirtualHierarchyNode* VirtualDimension::addNode( int parentNodeId, const string& nodeValue, const string& childCategoryTitle )
{
	VirtualHierarchyNode node( nodeIdCounter_++, nodeValue, getTagSetId(), getId(), outerAttributePattern_, innerAttributePattern_, childCategoryTitle );
	return addNode_( parentNodeId, &node );
}
//____________________________________________________________________________________________________________________________________________________________________________________

VirtualHierarchyNode* VirtualDimension::addNode_( int parentNodeId, VirtualHierarchyNode* node )
{
	dynamic_cast<VirtualHierarchyNode*>( root_.get() )->addBranch_( parentNodeId, node );
	updateBorders_();
	return dynamic_cast<VirtualHierarchyNode*>( root_->getBranch( node->getId() ) );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

Dimension& VirtualDimension::operator=( const Dimension& dimension )
{
	Dimension::operator=( dimension );
	
	const VirtualDimension* vDimension = dynamic_cast<const VirtualDimension*>( &dimension );
	setNodeIdCounter_( vDimension->getNodeIdCounter_() );
	setOuterAttributePattern_( vDimension->getOuterAttributePattern() );
	setInnerAttributePattern_( vDimension->getInnerAttributePattern() );
	setType_( vDimension->getType() );
	setExtractionFunction( vDimension->getExtractionFunction_() );
	
	return *this;
}
//____________________________________________________________________________________________________________________________________________________________________________________
















