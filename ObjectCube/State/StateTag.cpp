/*
 *  StateTag.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 17.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "StateTag.h"
#include "../LayerShared/Exception.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

StateTag::StateTag( Tag* tag )
:	tag_( 0 )
{
	setTag_( tag );
}
//____________________________________________________________________________________________________________________________________________________________________________________

StateTag::StateTag( const map<int, int>& filterAndDimensionNodeIds )
:	tag_( 0 )
{
	filterAndDimensionNodeIds_ = filterAndDimensionNodeIds;
}
//____________________________________________________________________________________________________________________________________________________________________________________

StateTag::~StateTag()
{
	cleanup_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

StateTag::StateTag( const StateTag& stateTag )
:	tag_( 0 )
{
	filterAndDimensionNodeIds_ = stateTag.getFilterAndDimensionNodeIds();
	tag_ = stateTag.tag_;
	if( stateTag.hasBoundingBox() )
	{
		boundingBox_.reset( new BoundingBox() );
		*boundingBox_.get() = *stateTag.boundingBox_;
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________

const BoundingBox StateTag::getBoundingBox() const
{
	if( boundingBox_ == 0 )
	{
		throw Exception( "StateTag::getBoundingBox", "No bounding box set!");
	}
	return *boundingBox_.get();
}
//____________________________________________________________________________________________________________________________________________________________________________________

StateTag& StateTag::operator=( const StateTag& stateTag )
{
	cleanup_();
	
	tag_ = stateTag.tag_;
	filterAndDimensionNodeIds_ = stateTag.getFilterAndDimensionNodeIds();
	if( stateTag.boundingBox_ != 0 )
	{
		boundingBox_.reset( new BoundingBox() );
		*boundingBox_.get() = *stateTag.boundingBox_;
	}
	return *this;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void StateTag::cleanup_()
{

}
//____________________________________________________________________________________________________________________________________________________________________________________

