/*
 *  HierarchicalDimension.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 16.12.2009.
 *  Copyright 2009 Reykjavik University. All rights reserved.
 *
 */
#include "PersistentDimension.h"

#include <iostream>

#ifdef __APPLE__
#include <memory>
using std::shared_ptr;
#else
#include <tr1/memory>
using std::shared_ptr;
#endif

#include "../TagSet/TagSet.h"
#include "../Tag/Tag.h"
#include "../Tag/AlphanumericalTag.h"
//Data access
#include "../DataAccess/Root/DimensionDataAccess.h"
#include "../DataAccess/Factories/DimensionDataAccessFactory.h"
#include "../Converters/DimensionConverter.h"
#include "../Converters/HierarchyNodeConverter.h"

#include "../LayerShared/SharedDefinitions.h"
#include "../LayerShared/Exception.h"
#include "../LayerShared/MemoryManagement.h"


using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________
PersistentDimension::PersistentDimension()
: Dimension( Dimension::PERSISTENT )
{
	init_();
	root_.reset( new PersistentHierarchyNode() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

PersistentDimension::PersistentDimension( int tagSetId, const Tag* /*const*/ tag )
: Dimension( Dimension::PERSISTENT, tagSetId )
{
	init_();
	PersistentHierarchyNode root( tag, getId(), tagSetId );
	Dimension::init_( &root );
}
//____________________________________________________________________________________________________________________________________________________________________________________

PersistentDimension::PersistentDimension( int tagSetId, const Tag* /*const*/ tag, const string& childCategoryTitle )
: Dimension( Dimension::PERSISTENT, tagSetId )
{
	init_();
	PersistentHierarchyNode root( tag, getId(), tagSetId, childCategoryTitle );
	Dimension::init_( &root );
}
//____________________________________________________________________________________________________________________________________________________________________________________

PersistentDimension::~PersistentDimension()
{

}
//____________________________________________________________________________________________________________________________________________________________________________________

void PersistentDimension::init_()
{
	id_ = INVALID_VALUE;
}
//____________________________________________________________________________________________________________________________________________________________________________________

PersistentHierarchyNode* PersistentDimension::getPersistentRoot() 
{ 
	PersistentHierarchyNode* root = dynamic_cast<PersistentHierarchyNode*>( root_.get() ); 
	if( !root )
	{
		throw Exception( "PersistentDimension::getPersistentRoot", "dynamic_cast from HierarchyNode -> PersistentHierarchyNode failed!" );
	}
	return root;
}
//____________________________________________________________________________________________________________________________________________________________________________________

//Overloaded for unit testing
const PersistentHierarchyNode* PersistentDimension::getPersistentRoot() const 
{ 
	const PersistentHierarchyNode* root = dynamic_cast<const PersistentHierarchyNode*>( root_.get() ); 
	if( !root )
	{
		throw Exception( "PersistentDimension::getPersistentRoot", "dynamic_cast from HierarchyNode -> const PersistentHierarchyNode failed!" );
	}
	return root;
} 
//____________________________________________________________________________________________________________________________________________________________________________________

PersistentDimension* PersistentDimension::fetch_( int id )
{
	unique_ptr<DimensionDataAccess> dataAccess( DimensionDataAccessFactory::create() );
	vector<HierarchyNodeDataAccess*> nodesDA = dataAccess->fetch( id );
	vector<std::shared_ptr<HierarchyNode> > nodes = HierarchyNodeConverter::dataAccessToLogic( nodesDA );
	clearAndDestroy( nodesDA );
	if( !nodes.size() ) //Throw error ?
	{
		throw Exception( "PersistentDimension::fetch_", "Dimension being fetched was not retrieved", id );
	}
	unique_ptr<PersistentDimension> persistentDimension( new PersistentDimension() );
	PersistentHierarchyNode* phRoot = persistentDimension->getPersistentRoot();
	int offset = 0;
	phRoot->constructTree_( nodes, offset );
	persistentDimension->setId_( phRoot->getDimensionId() );
	persistentDimension->setTagSetId_( persistentDimension->getRoot()->getTagSetId() );
	return persistentDimension.release();
}
//____________________________________________________________________________________________________________________________________________________________________________________

int PersistentDimension::create_()
{
	//Validate whether dimension and tag exist
	unique_ptr<DimensionDataAccess> dataAccess( DimensionConverter::logicToDataAccess( this ) );
	setId_( dataAccess->nextId() );
	PersistentHierarchyNode* phRoot = getPersistentRoot();
	phRoot->setDimensionId_( getId() );
	phRoot->create_();
	updateBorders_();  //updates data storage
	return id_;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void PersistentDimension::delete_()
{
	removeBranch( getRoot()->getId() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

PersistentHierarchyNode* PersistentDimension::addNode( int parentNodeId, const Tag* /*const*/ tag )
{
	PersistentHierarchyNode child;
	getPersistentRoot()->addBranch_( parentNodeId, tag, child );
	updateBorders_();
	return dynamic_cast<PersistentHierarchyNode*>( getRoot()->getBranch( child.getId() ) );
}
//____________________________________________________________________________________________________________________________________________________________________________________

PersistentHierarchyNode* PersistentDimension::addNode( int parentNodeId, const Tag* /*const*/ tag, const string& childCategoryTitle )
{
	PersistentHierarchyNode child;
	child.setChildCategoryTitle_( childCategoryTitle );
	getPersistentRoot()->addBranch_( parentNodeId, tag, child );
	updateBorders_();
	return dynamic_cast<PersistentHierarchyNode*>( getRoot()->getBranch( child.getId() ) );
}
//____________________________________________________________________________________________________________________________________________________________________________________

PersistentHierarchyNode* PersistentDimension::getNode( const string& name )
{
	unique_ptr<AlphanumericalTag> tag( AlphanumericalTag::fetch( getTagSetId(), name ) );  //ToDo:  Fix this, very slow.
	TagBasedHierarchyNode* node = 0;
	getPersistentRoot()->getNode_( tag->getId(), &node );
	if( node == 0 )
	{
		throw Exception( "PersistentDimension::getNode(name)", "Node requested was not a member of the hierarchy" );
	}
	return dynamic_cast<PersistentHierarchyNode*>( node );
}	
//____________________________________________________________________________________________________________________________________________________________________________________

void PersistentDimension::removeBranch( int branchNodeId )
{
	getPersistentRoot()->removeBranch_( branchNodeId );
	try 
	{
		unique_ptr<PersistentDimension> persistentDimensionCopy( PersistentDimension::fetch_( id_ ) );
		*this = *persistentDimensionCopy.get();
	}
	catch( Exception& e) 
	{
		return; //The hierarchy has been totally deleted
	}
	updateBorders_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void PersistentDimension::updateBorders_()
{
	int borderCounter = 1;
	 root_->updateBorders_( borderCounter );
}
//____________________________________________________________________________________________________________________________________________________________________________________

Dimension& PersistentDimension::operator=( const Dimension& dimension )
{
	Dimension::operator=( dimension );
	return *this;
}
//____________________________________________________________________________________________________________________________________________________________________________________























