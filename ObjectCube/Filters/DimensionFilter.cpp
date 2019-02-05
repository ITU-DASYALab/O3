/*
 *  DimensionFilter.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 14.4.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "DimensionFilter.h"

#include <sstream>

#include "../Hierarchy/PersistentHierarchyNode.h"
#include "../LayerShared/SharedDefinitions.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

DimensionFilter::DimensionFilter()
{
	init_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

DimensionFilter::DimensionFilter( const HierarchyNode& node, int tagSetId )
: Filter( tagSetId )
{
	init_();
	setDimensionId_( node.getDimensionId() );
	setLeftBorder_( node.getLeftBorder() );
	setRightBorder_( node.getRightBorder() );
	setDimensionTypeId_( node.getTypeId() ); //Nodes are of the same type as the dimensions
	getTagAndDimensionNodeIds_( node.getSubtreeTagIds() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

DimensionFilter::~DimensionFilter()
{

}
//____________________________________________________________________________________________________________________________________________________________________________________

void DimensionFilter::init_()
{
	setTypeId_( Filter::DIMENSION_FILTER );
	setDimensionId_( INVALID_VALUE );
	setDimensionTypeId_( INVALID_VALUE );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DimensionFilter::getTagAndDimensionNodeIds_( const map<int, int>& tagAndDimensionNodeIds ) 
{ 
	tagAndDimensionNodeIds_ = tagAndDimensionNodeIds; 
	setNullStatus_( false );
}
//____________________________________________________________________________________________________________________________________________________________________________________

Filter& DimensionFilter::operator=( const Filter& filter )
{
	assignValues_( filter );
	const DimensionFilter* dFilter = dynamic_cast<const DimensionFilter*>( &filter );
	getTagAndDimensionNodeIds_( dFilter->getTagAndDimensionNodeIds() );
	setDimensionId_( dFilter->getDimensionId() );
	setLeftBorder_( dFilter->getLeftBorder() );
	setRightBorder_( dFilter->getRightBorder() );
	setDimensionTypeId_( dFilter->getDimensionTypeId() );
	return *this;
}
//____________________________________________________________________________________________________________________________________________________________________________________


