/*
 *  Dimension.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 7.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "Dimension.h"

#include <memory>
#include <iostream>

#include "../LayerShared/SharedDefinitions.h"
#include "../LayerShared/Exception.h"
#include "../LayerShared/MemoryManagement.h"
#include "HierarchyNodeFactory.h"


using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

Dimension::Dimension( int typeId, int tagSetId )
{
	setTypeId_( typeId );
	setTagSetId_( tagSetId );
}
//____________________________________________________________________________________________________________________________________________________________________________________

Dimension::Dimension( int typeId )
{
	setTypeId_( typeId );
}
//____________________________________________________________________________________________________________________________________________________________________________________

Dimension::~Dimension()
{
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

Dimension::Dimension( const Dimension& dimension )
{
	copyValues_( dimension );
}
//____________________________________________________________________________________________________________________________________________________________________________________

Dimension& Dimension::operator=( const Dimension& dimension )
{	
	copyValues_( dimension );
	return *this;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void Dimension::copyValues_( const Dimension& dimension )
{	
	setId_( dimension.getId() );
	setTypeId_( dimension.getTypeId() );
	setTagSetId_( dimension.getTagSetId() );
	
	if( dimension.root_ != 0 )
	{
		root_.reset( HierarchyNodeFactory::create( dimension.getRoot()->getTypeId() ) );
		*root_.get() = *dimension.getRoot();
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________

void Dimension::init_( const HierarchyNode* /*const*/ node )
{
	/*
	HierarchyNode* hNode = HierarchyNodeFactory::create( node->getTypeId() );
	*hNode = *node;
	root_ = hNode;
	 */
	root_.reset( HierarchyNodeFactory::create( node->getTypeId() ) );
	*root_.get() = *node;
	
	updateBorders_();  
}
//____________________________________________________________________________________________________________________________________________________________________________________

HierarchyNode* Dimension::getRoot()
{
	if( root_ == 0 )
	{
		throw Exception( "Dimension::getRoot", "The root of this dimension has not been initialized!" );
	}
	return root_.get();
}
//____________________________________________________________________________________________________________________________________________________________________________________

const HierarchyNode* /*const*/ Dimension::getRoot() const
{
	if( root_ == 0 )
	{
		throw Exception( "Dimension::getRoot const", "The root of this dimension has not been initialized!" );
	}
	return root_.get();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void Dimension::updateBorders_()
{
	int borderCounter = 1;
	root_->updateBorders_( borderCounter );
}
//____________________________________________________________________________________________________________________________________________________________________________________

bool Dimension::operator==( Dimension const& x) const 
{ 
	return getTagSetId() == x.getTagSetId() && getRoot()->getName() == x.getRoot()->getName(); 
}
//____________________________________________________________________________________________________________________________________________________________________________________

bool Dimension::operator!=( Dimension const& x) const 
{ 
	return !(getTagSetId() == x.getTagSetId() && getRoot()->getName() == x.getRoot()->getName() ); 
}
//____________________________________________________________________________________________________________________________________________________________________________________

bool Dimension::operator < ( const Dimension& x ) const
{
	return getTagSetId() < x.getTagSetId();
}
//____________________________________________________________________________________________________________________________________________________________________________________
























