/*
 *  TestHierarchyNode.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 20.2.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "PersistentHierarchyNodeTest.h"

#include <cppunit/extensions/HelperMacros.h>

#include "../Hierarchy/PersistentHierarchyNode.h"
#include "../Hub.h"
#include "TestIds.h"
#include "../LayerShared/HubCommon.h"
#include "../TagSet/TagSet.h"
#include "../Tag/Tag.h"
#include "../Tag/AlphanumericalTag.h"
#include "../LayerShared/Exception.h"
#include "../LayerShared/SharedDefinitions.h"
#include "../Hierarchy/PersistentDimension.h"

#include "HierarchyNodeAssertionTraits.h"

using namespace ObjectCube;

CPPUNIT_TEST_SUITE_REGISTRATION( PersistentHierarchyNodeTest );

//____________________________________________________________________________________________________________________________________________________________________________________

void PersistentHierarchyNodeTest::setUp()
{
	hierarchyRootName_ = "SQLite hierarchy add node test tag";
	hierarchyChildNodeName_ = "SQLite a subcategory or an entity";
}
//____________________________________________________________________________________________________________________________________________________________________________________

void PersistentHierarchyNodeTest::tearDown()
{
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Canned tests --------------------------------------------------------------------------------------------------------------------

void PersistentHierarchyNodeTest::testGetBranchCanned()
{
	cerr << "\nPersistentHierarchyNodeTest::testGetBranchCanned = ";
	Hub::setDataAccessType( Hub::CANNED );
	
	Hub* hub = Hub::getHub();
	TagSet* tagSet = hub->getTagSet( TEST_ALPHANUMERICAL_TAG_SET_ID );
	
	CPPUNIT_ASSERT( tagSet->getDimensions().size() == 2 );
	
	string dimName = "TagSet add test tag";
	AlphanumericalTag tagData( dimName );
	tagData.setId_( TEST_ALPHANUMERICAL_TAG_ID_CANNED + 1 );
	const Tag* tag = tagSet->addTag( &tagData );
	
	PersistentDimension* hierarchy = tagSet->createPersistentDimension( tag );
	
	AlphanumericalTag branchTagData( "A subcategory or an entity" );
	branchTagData.setId_( TEST_ALPHANUMERICAL_TAG_ID_CANNED + 2 );
	const Tag* branchTag = tagSet->addTag( &branchTagData );
	
	PersistentHierarchyNode* branchNode = hierarchy->addNode( hierarchy->getRoot()->getId(), branchTag );
	
	PersistentHierarchyNode* nodeGotten = dynamic_cast<PersistentHierarchyNode*>( hierarchy->getRoot()->getBranch( branchNode->getId() ) );
	
	CPPUNIT_ASSERT_EQUAL( branchNode, nodeGotten );
	
	CPPUNIT_ASSERT_THROW( hierarchy->getRoot()->getBranch( hierarchy->getRoot()->getId() ), ObjectCube::Exception ); //Asking for itself, a branch that does not exist
		
	tagSet->deleteTag( tag ); //Cleanup
	tagSet->deleteTag( branchTag ); //Cleanup
	tagSet->deleteDimension( hierarchy->getId() ); //Cleanup
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  SQLite tests --------------------------------------------------------------------------------------------------------------------

void PersistentHierarchyNodeTest::testGetBranchSQLite()
{
	cerr << "\nPersistentHierarchyNodeTest::testGetBranchSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );

	testGetBranch_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  MonetDB tests --------------------------------------------------------------------------------------------------------------------

void PersistentHierarchyNodeTest::testGetBranchMonetDB()
{
	cerr << "\nPersistentHierarchyNodeTest::testGetBranchMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );

	testGetBranch_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Oracle tests --------------------------------------------------------------------------------------------------------------------

void PersistentHierarchyNodeTest::testGetBranchOracle()
{
	cerr << "\nPersistentHierarchyNodeTest::testGetBranchOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testGetBranch_();	
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Common --------------------------------------------------------------------------------------------------------------------

void PersistentHierarchyNodeTest::testGetBranch_()
{
	Hub* hub = Hub::getHub();
	TagSet* tagSet = hub->getTagSet( TEST_ALPHANUMERICAL_TAG_SET_ID );
	
	PersistentDimension* hierarchy = tagSet->getPersistentDimension( hierarchyRootName_ );
	
	unique_ptr<AlphanumericalTag> branchTag( AlphanumericalTag::fetch( tagSet->getId(), hierarchyChildNodeName_ ) ); 	
	PersistentHierarchyNode* branchNode = hierarchy->addNode( hierarchy->getRoot()->getId(), branchTag.get() );
	
	PersistentHierarchyNode* nodeReturned = dynamic_cast<PersistentHierarchyNode*>( hierarchy->getRoot()->getBranch( branchNode->getId() ) );
	
	CPPUNIT_ASSERT_EQUAL( branchNode, nodeReturned );
	
	CPPUNIT_ASSERT_THROW( hierarchy->getRoot()->getBranch( hierarchy->getRoot()->getId() ), ObjectCube::Exception ); //Asking for itself, a branch that does not exist	
}
//____________________________________________________________________________________________________________________________________________________________________________________



