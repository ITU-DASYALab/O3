/*
 *  TagBasedHierarchyNode.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 2.7.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "TagBasedHierarchyNode.h"

#include "../Hub.h"
#include "../TagSet/TagSet.h"
#include "../Tag/Tag.h"
#include "../LayerShared/SharedDefinitions.h"
#include "../LayerShared/Exception.h"


using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

TagBasedHierarchyNode::TagBasedHierarchyNode( int typeId )
: HierarchyNode( typeId )
{
	init_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

TagBasedHierarchyNode::TagBasedHierarchyNode( int typeId, const Tag* /*const*/ tag )
: HierarchyNode( typeId )
{
	init_();
	tagId_ = tag->getId();
	name_ = tag->valueAsString();
}
//____________________________________________________________________________________________________________________________________________________________________________________

TagBasedHierarchyNode::TagBasedHierarchyNode( int typeId, const Tag* /*const*/ tag, int dimensionId, int tagSetId )
: HierarchyNode( typeId )
{
	init_();
	tagId_ = tag->getId();
	dimensionId_ = dimensionId;
	tagSetId_ = tagSetId;
	name_ = tag->valueAsString();
}
//____________________________________________________________________________________________________________________________________________________________________________________

TagBasedHierarchyNode::TagBasedHierarchyNode( int typeId, const Tag* /*const*/ tag, int dimensionId, int tagSetId, const string& childCategoryTitle )
: HierarchyNode( typeId )
{
	init_();
	tagId_ = tag->getId();
	dimensionId_ = dimensionId;
	tagSetId_ = tagSetId;
	name_ = tag->valueAsString();
	childCategoryTitle_ = childCategoryTitle;
}
//____________________________________________________________________________________________________________________________________________________________________________________

TagBasedHierarchyNode::~TagBasedHierarchyNode()
{

}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagBasedHierarchyNode::init_()
{
	tagId_ = INVALID_VALUE;
	dimensionId_ = INVALID_VALUE;
}
//____________________________________________________________________________________________________________________________________________________________________________________

HierarchyNode& TagBasedHierarchyNode::operator=( const HierarchyNode& node )
{
	HierarchyNode::operator=( node );
	
	const TagBasedHierarchyNode* tbNode = dynamic_cast<const TagBasedHierarchyNode*>( &node );
	setTagId_( tbNode->getTagId() );
	
	return *this;
}

//____________________________________________________________________________________________________________________________________________________________________________________

map<int, int> TagBasedHierarchyNode::getSubtreeTagIds_() const
{
	map<int, int> tagIds;
	tagIds.insert( pair<int, int>( getTagId(), getId() ) );  //The root of the subtree
	//	cout << "PERSISTENT -> tagId: " << getTagId() << " nodeId: " << getId() << endl;
	for( vector<std::shared_ptr<HierarchyNode> >::const_iterator itr = children_.begin(); itr != children_.end(); ++itr )
	{	
		map<int, int> tempIds = (*itr)->getSubtreeTagIds();
		tagIds.insert( tempIds.begin(), tempIds.end() );
		//vector<int> tempIds = (*itr)->getSubtreeTagIds();
		//tagIds.insert( tagIds.end(), tempIds.begin(), tempIds.end() );
	}	
	return tagIds;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagBasedHierarchyNode::updateBorders_( int& borderCounter )
{
	if( id_ == HierarchyNodeCommon::INVALID )
	{
		return;
	}
	
	leftBorder_ = borderCounter++;
	
	//DEBUG
	//	Tag tag = Tag::fetch( tagId_ );
	//	cout << "name: " << tag.name() << endl;
	//	cout << "left: " << leftBorder_ << endl;
	
	for( vector<std::shared_ptr<HierarchyNode> >::iterator itr = children_.begin(); itr != children_.end(); ++itr )
	{
		TagBasedHierarchyNode* tbNode = dynamic_cast<TagBasedHierarchyNode*>( (*itr).get() );
		tbNode->updateBorders_( borderCounter );
	//	PersistentHierarchyNode* phNode = dynamic_cast<PersistentHierarchyNode*>( *itr );	
	//	phNode->updateBorders_( borderCounter );
	//	(*itr)->updateBorders_( borderCounter );
	}		
	rightBorder_ = borderCounter++;
	
	//DEBUG
	//	cout << "right: " << rightBorder_ << endl;
	//	cout << "name: " << tag.name() << endl;
}	
//____________________________________________________________________________________________________________________________________________________________________________________

void TagBasedHierarchyNode::getNode_( int tagId, TagBasedHierarchyNode** node )
{
	if( getTagId() == tagId )
	{
		*node = this;
		return;
	}
	
	for( vector<std::shared_ptr<HierarchyNode> >::iterator itr = children_.begin(); itr != children_.end(); ++itr )
	{
		TagBasedHierarchyNode* phNode = dynamic_cast<TagBasedHierarchyNode*>( (*itr).get() );	
		phNode->getNode_( tagId, node );
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________