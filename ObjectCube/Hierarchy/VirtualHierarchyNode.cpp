/*
 *  VirtualVirtualHierarchyNode.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 5.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "VirtualHierarchyNode.h"

#include <iostream>
#include <sstream>
#include <memory>
#include <cstdlib>

#include "../Hub.h"
#include "../TagSet/TagSet.h"
#include "../Tag/Tag.h"
#include "../LayerShared/SharedDefinitions.h"
#include "../LayerShared/Exception.h"

#include "../LayerShared/RegExSupport.h"


using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

VirtualHierarchyNode::VirtualHierarchyNode()
: HierarchyNode( HierarchyNode::VIRTUAL )
{
	init_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

VirtualHierarchyNode::~VirtualHierarchyNode()
{

}
//____________________________________________________________________________________________________________________________________________________________________________________

VirtualHierarchyNode::VirtualHierarchyNode(	int id, 
											const string& name, 
											int tagSetId,
											int dimensionId,
											const string& outerAttributePattern, 
											const string& innerAttributePattern )
: HierarchyNode( HierarchyNode::VIRTUAL )
{
	init_();
	setId_( id );  
	setName_( name );
	setTagSetId_( tagSetId );
	setDimensionId_( dimensionId );
	setOuterAttributePattern_( outerAttributePattern );
	setInnerAttributePattern_( innerAttributePattern );
}
//____________________________________________________________________________________________________________________________________________________________________________________

VirtualHierarchyNode::VirtualHierarchyNode(	int id, 
											const string& name, 
											int tagSetId,
											int dimensionId,
											const string& outerAttributePattern, 
											const string& innerAttributePattern,
											const string& childCategoryTitle )
: HierarchyNode( HierarchyNode::VIRTUAL )
{
	init_();
	setId_( id );
	setName_( name );
	setTagSetId_( tagSetId );
	setDimensionId_( dimensionId );
	setOuterAttributePattern_( outerAttributePattern );
	setInnerAttributePattern_( innerAttributePattern );
	setChildCategoryTitle_( childCategoryTitle );
}
//____________________________________________________________________________________________________________________________________________________________________________________

VirtualHierarchyNode::VirtualHierarchyNode(	int id, 
											const string& name, 
											int tagSetId, 
											int dimensionId,
											int (*extractionFunction)(int, int, int) )
: HierarchyNode( HierarchyNode::VIRTUAL )
{
	init_();
	setId_( id );
	setName_( name );
	setTagSetId_( tagSetId );
	setDimensionId_( dimensionId );
	extractionFunction_ = extractionFunction;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void VirtualHierarchyNode::init_()
{
	extractionFunction_ = 0;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void VirtualHierarchyNode::addBranch_( VirtualHierarchyNode* node )
{
	std::shared_ptr<VirtualHierarchyNode> newNode( new VirtualHierarchyNode() );
	*newNode.get() = *node;
	children_.push_back( newNode );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void VirtualHierarchyNode::addBranch_( int parentNodeId, VirtualHierarchyNode* child )
{
	if( id_ == parentNodeId )
	{
		addBranch_( child );
		return;
	}
	
	for( vector<std::shared_ptr<HierarchyNode> >::iterator itr = children_.begin(); itr != children_.end(); ++itr )
	{
		VirtualHierarchyNode* vhNode = dynamic_cast<VirtualHierarchyNode*>( (*itr).get() );
		if( vhNode->getId() == parentNodeId )
		{
			vhNode->addBranch_( child );
			return;
		}
		else 
		{
			vhNode->addBranch_( parentNodeId, child );
		}
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________

string VirtualHierarchyNode::extractByPattern_( const string& value, const string& outerPattern, const string& innerPattern ) const
{
	//Extract the outer pattern substring
	string outerMatch;
	if( !RegExSupport::patternFound( value, outerPattern, outerMatch ) )
	{
		return "";
	}
	
	//Extract the inner pattern substring
	string innerMatch;
	if( !RegExSupport::patternFound( outerMatch, innerPattern, innerMatch ) )
	{
		return "";
	}	
	return innerMatch;
}
//____________________________________________________________________________________________________________________________________________________________________________________

string VirtualHierarchyNode::extractByFunction_( const string& value ) const
{
	stringstream returnValue;
	//Date specific code, refactor !
	string year  = extractByPattern_( value, "[0-9]{4}-", "[0-9]{4}" );
	string month  = extractByPattern_( value, "-[0-9]{2}-", "[0-9]{2}" );
	string day  = extractByPattern_( value, "-[0-9]{2}$", "[0-9]{2}" );
	returnValue << extractionFunction_( atoi( year.c_str() ), atoi( month.c_str() ), atoi( day.c_str() ) );
	return returnValue.str();
}
//____________________________________________________________________________________________________________________________________________________________________________________

map<int, int> VirtualHierarchyNode::getSubtreeTagIds_() const
{
	map<int, int> tagIds;
	const vector<Tag*> tags = Hub::getHub()->getTagSet( getTagSetId() )->getTags();
	for( vector<Tag*>::const_iterator itr = tags.begin(); itr != tags.end(); ++itr )
	{
		string tagValue = (*itr)->valueAsString();
		
		string extractedValue;
		if( extractionFunction_ == 0 )
		{
			extractedValue = extractByPattern_( tagValue, outerAttributePattern_, innerAttributePattern_ );
		}
		else 
		{
			extractedValue = extractByFunction_( tagValue );
		}

		propertyInSubtree_( extractedValue, (*itr)->getId(), tagIds );
		
		/*
		int propertyCount = 0;
		if( propertyInSubtree_( extractedValue, tagIds, (*itr)->getId() ) > 0 )
		{
			//tagIds.insert( pair<int, int>( (*itr)->getId(), getId() ) );
			//cout << "VIRTUAL -> dimensionId: " << getDimensionId() <<  " tagId: " << (*itr)->getId() << " nodeId: " << getId() << endl;
		//	tagIds.push_back( (*itr)->getId() );
		}
		 */
	}
	
	return tagIds;	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void VirtualHierarchyNode::propertyInSubtree_( const string& property, int tagId, map<int, int>& tagIds ) const
{
	if( id_ == INVALID_VALUE )
	{
		return;
	}
	
//	cout << "VIRTUAL -> tag property: " << property << " tagId: " << tagId << " node name: " << name_ << endl;
	
	if( name_ == property )
	{
		tagIds.insert( pair<int, int>( tagId, getId() ) );
//		cout << "VIRTUAL -> dimensionId: " << getDimensionId() <<  " tagId: " << tagId << " nodeId: " << getId() << endl;
	}
	
	for( vector<std::shared_ptr<HierarchyNode> >::const_iterator itr = children_.begin(); itr != children_.end(); ++itr )
	{
		const VirtualHierarchyNode* vhNode = dynamic_cast<const VirtualHierarchyNode*>( (*itr).get() );
		vhNode->propertyInSubtree_( property, tagId, tagIds );
	}		
	
	return;
}
//____________________________________________________________________________________________________________________________________________________________________________________

HierarchyNode& VirtualHierarchyNode::operator=( const HierarchyNode& node )
{
	HierarchyNode::operator=( node );
	
	const VirtualHierarchyNode* vhNode = dynamic_cast<const VirtualHierarchyNode*>( &node );
	
	setOuterAttributePattern_( vhNode->getOuterAttributePattern_() );
	setInnerAttributePattern_( vhNode->getInnerAttributePattern_() );
	setExtractionFunction_( vhNode->getExtractionFunction_() );
	
	return *this;
}

//____________________________________________________________________________________________________________________________________________________________________________________











