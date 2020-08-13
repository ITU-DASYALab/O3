/*
 *  DefaultDimension.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 2.7.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "DefaultDimension.h"

#include <memory>
#include "limits.h"

#include "../TagSet/TagSet.h"
#include "../Tag/Tag.h"
#include "../Tag/AlphanumericalTag.h"

#include "../LayerShared/SharedDefinitions.h"
#include "../LayerShared/Exception.h"
#include "../LayerShared/MemoryManagement.h"


using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

int DefaultDimension::idCounter_ = INT_MAX /*SHRT_MAX*/ / 2;
string DefaultDimension::rootName_ = "Default dimension";

//____________________________________________________________________________________________________________________________________________________________________________________

DefaultDimension::DefaultDimension()
: Dimension( Dimension::DEFAULT )
{
	init_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

DefaultDimension::DefaultDimension( int tagSetId, const vector<Tag*>& tags )
: Dimension( Dimension::DEFAULT, tagSetId )
{
	init_( tags );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DefaultDimension::init_()
{
	setNodeIdCounter_( 1 );
	setId_( idCounter_-- );
	
	DefaultHierarchyNode root;
	root.setTagId_( INVALID_VALUE );
	root.setTagSetId_( getTagSetId() );
	root.setDimensionId_( getId() );
	root.setName_( DefaultDimension::getRootName() );
	
	Dimension::init_( &root );  	
}
//____________________________________________________________________________________________________________________________________________________________________________________
void DefaultDimension::init_( const vector<Tag*>& tags )
{
	init_();
	
	for( vector<Tag*>::const_iterator itr = tags.begin(); itr != tags.end(); ++itr )
	{
		DefaultHierarchyNode node( *itr, getId(), getTagSetId() );
		getDefaultRoot()->addBranch_( &node );
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________

DefaultDimension::~DefaultDimension()
{

}
//____________________________________________________________________________________________________________________________________________________________________________________

DefaultHierarchyNode* DefaultDimension::getNode( const string& name )
{
	unique_ptr<AlphanumericalTag> tag( AlphanumericalTag::fetch( getTagSetId(), name ) ); ///VERY SLOW, ToDo:  FIX
	TagBasedHierarchyNode* node = 0;
	dynamic_cast<DefaultHierarchyNode*>( getRoot() )->getNode_( tag->getId(), &node );
	if( node == 0 )
	{
		throw Exception( "DefaultDimension::getNode(name)", "Node requested was not a member of the hierarchy" );
	}
	return dynamic_cast<DefaultHierarchyNode*>( node );
}	
//____________________________________________________________________________________________________________________________________________________________________________________

Dimension& DefaultDimension::operator=( const Dimension& dimension )
{
	//copyValues_( dimension ); //Copy base class values
	Dimension::operator=( dimension );
	
	const DefaultDimension* dDimension = dynamic_cast<const DefaultDimension*>( &dimension );
	setNodeIdCounter_( dDimension->getNodeIdCounter_() );
	
	return *this;
}
//____________________________________________________________________________________________________________________________________________________________________________________

