/*
 *  PersistentDimensionTest.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 20.2.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "PersistentDimensionTest.h"

#include <cppunit/extensions/HelperMacros.h>

#include "../Hierarchy/PersistentDimension.h"
#include "../Hub.h"
#include "TestIds.h"
#include "../LayerShared/HubCommon.h"
#include "../TagSet/TagSet.h"
#include "../Tag/Tag.h"
#include "../Tag/AlphanumericalTag.h"
#include "../LayerShared/Exception.h"
#include "../LayerShared/SharedDefinitions.h"
#include "../ObjectTag.h"

#include "DimensionAssertionTraits.h"
#include "HierarchyNodeAssertionTraits.h"

using namespace ObjectCube;

CPPUNIT_TEST_SUITE_REGISTRATION( PersistentDimensionTest );

//____________________________________________________________________________________________________________________________________________________________________________________


void PersistentDimensionTest::setUp()
{
	hierarchyRootName_ = "SQLite hierarchy add node test tag";
	hierarchyChildNodeName_ = "SQLite a subcategory or an entity";
	hierarchyChildChildNodeName_ = "SQLite a sub-subcategory or an entity";
}
//____________________________________________________________________________________________________________________________________________________________________________________

void PersistentDimensionTest::tearDown()
{

}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Canned tests --------------------------------------------------------------------------------------------------------------------
void PersistentDimensionTest::testAddNodeCanned()
{
	cerr << "\nPersistentDimensionTest::testAddNodeCanned = ";
	Hub::setDataAccessType( Hub::CANNED );
	
	Hub* hub = Hub::getHub();
	TagSet* tagSet = hub->getTagSet( TEST_ALPHANUMERICAL_TAG_SET_ID );
	
	CPPUNIT_ASSERT( (int)tagSet->getDimensions().size() == 2 );
	
	string dimName = "TagSet add test tag";
	AlphanumericalTag tagData( dimName );
	tagData.setId_( TEST_ALPHANUMERICAL_TAG_ID_CANNED + 1 );
	const Tag* tag = tagSet->addTag( &tagData );
	
	PersistentDimension* hierarchy = tagSet->createPersistentDimension( tag );
	
	int originalRightBorder = hierarchy->getRoot()->getRightBorder();
	
	AlphanumericalTag branchTagData( "A subcategory or an entity" );
	branchTagData.setId_( TEST_ALPHANUMERICAL_TAG_ID_CANNED + 2 );
	const Tag* branchTag = tagSet->addTag( &branchTagData );
	
	PersistentHierarchyNode* branchNode = hierarchy->addNode( hierarchy->getRoot()->getId(), branchTag );
	
	CPPUNIT_ASSERT_EQUAL( originalRightBorder + 2, hierarchy->getRoot()->getRightBorder() );
	CPPUNIT_ASSERT_EQUAL( 1, (int)hierarchy->getRoot()->getBranches().size() );

	CPPUNIT_ASSERT( branchNode->getId() != INVALID_VALUE );
	CPPUNIT_ASSERT( tagSet->getId() == branchNode->getTagSetId() );
	CPPUNIT_ASSERT( hierarchy->getId() == branchNode->getDimensionId() );
	CPPUNIT_ASSERT( branchNode->getLeftBorder() != INVALID_VALUE );
	CPPUNIT_ASSERT( branchNode->getRightBorder() != INVALID_VALUE );
	CPPUNIT_ASSERT( branchNode->getRightBorder() > branchNode->getLeftBorder() );
	CPPUNIT_ASSERT( branchNode->getTagId() != INVALID_VALUE );
	
	CPPUNIT_ASSERT( hierarchy->getRoot()->getLeftBorder() < branchNode->getRightBorder() );
	CPPUNIT_ASSERT( hierarchy->getRoot()->getRightBorder() > branchNode->getLeftBorder() );
	
	CPPUNIT_ASSERT( hierarchy->getRoot()->getName() == tag->valueAsString() );
	CPPUNIT_ASSERT( branchNode->getName() == branchTag->valueAsString() );
	
	tagSet->deleteTag( tag ); //Cleanup
	tagSet->deleteTag( branchTag ); //Cleanup
	tagSet->deleteDimension( hierarchy->getId() ); //Cleanup
}
//____________________________________________________________________________________________________________________________________________________________________________________

void PersistentDimensionTest::testRemoveBranchCanned()
{
	cerr << "\nPersistentDimensionTest::testRemoveBranchCanned = ";
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

	CPPUNIT_ASSERT_EQUAL( 1, (int)hierarchy->getRoot()->getBranches().size() );

	hierarchy->removeBranch( branchNode->getId() );  //The hierarchy is re-fetched so the data goes to crap, test using DB
	
	CPPUNIT_ASSERT_EQUAL( 1, (int)hierarchy->getRoot()->getBranches().size() ); 
	
	tagSet->deleteTag( tag ); //Cleanup
	tagSet->deleteTag( branchTag ); //Cleanup
	tagSet->deleteDimension( hierarchy->getId() ); //Cleanup
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  SQLite tests --------------------------------------------------------------------------------------------------------------------

void PersistentDimensionTest::testAddNodeSQLite()
{
	cerr << "\nPersistentDimensionTest::testAddNodeSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testAddNode_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void PersistentDimensionTest::testRemoveBranchSQLite()
{
	cerr << "\nPersistentDimensionTest::testRemoveBranchSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );

	testRemoveBranch_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void PersistentDimensionTest::testFetchDimensionSQLite()
{
	cerr << "\nPersistentDimensionTest::testFetchDimensionSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );

	testFetchDimension_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  MonetDB tests --------------------------------------------------------------------------------------------------------------------

void PersistentDimensionTest::testAddNodeMonetDB()
{
	cerr << "\nPersistentDimensionTest::testAddNodeMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );

	testAddNode_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void PersistentDimensionTest::testRemoveBranchMonetDB()
{
	cerr << "\nPersistentDimensionTest::testRemoveBranchMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );
	
	testRemoveBranch_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void PersistentDimensionTest::testFetchDimensionMonetDB()
{
	cerr << "\nPersistentDimensionTest::testFetchDimensionMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );
	
	testFetchDimension_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Oracle tests --------------------------------------------------------------------------------------------------------------------

void PersistentDimensionTest::testAddNodeOracle()
{
	cerr << "\nPersistentDimensionTest::testAddNodeOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testAddNode_();	
}
//____________________________________________________________________________________________________________________________________________________________________________________
void PersistentDimensionTest::testRemoveBranchOracle()
{
	cerr << "\nPersistentDimensionTest::testRemoveBranchOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testRemoveBranch_();	
}
//____________________________________________________________________________________________________________________________________________________________________________________
void PersistentDimensionTest::testFetchDimensionOracle()
{
	cerr << "\nPersistentDimensionTest::testFetchDimensionOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testFetchDimension_();	
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Common --------------------------------------------------------------------------------------------------------------------

void PersistentDimensionTest::testAddNode_()
{
	Hub* hub = Hub::getHub();
	TagSet* tagSet = hub->getTagSet( TEST_ALPHANUMERICAL_TAG_SET_ID );
	
	AlphanumericalTag tagData( hierarchyRootName_ );
	const Tag* tag = tagSet->addTag( &tagData );
	
	PersistentDimension* hierarchy = tagSet->createPersistentDimension( tag );
	int originalRightBorder = hierarchy->getRoot()->getRightBorder();

	PersistentHierarchyNode* root = hierarchy->getPersistentRoot();
	
	AlphanumericalTag branchTagData( hierarchyChildNodeName_ );
	const Tag* branchTag = tagSet->addTag( &branchTagData );
	
	PersistentHierarchyNode* branchNode = hierarchy->addNode( hierarchy->getRoot()->getId(), branchTag );
	
	CPPUNIT_ASSERT_EQUAL( originalRightBorder + 2, hierarchy->getRoot()->getRightBorder() );
	CPPUNIT_ASSERT_EQUAL( 1, (int)hierarchy->getRoot()->getBranches().size() );
	
	CPPUNIT_ASSERT( branchNode->getId() != INVALID_VALUE );
	CPPUNIT_ASSERT( tagSet->getId() == branchNode->getTagSetId() );
	CPPUNIT_ASSERT( hierarchy->getId() == branchNode->getDimensionId() );
	CPPUNIT_ASSERT( branchNode->getLeftBorder() != INVALID_VALUE );
	CPPUNIT_ASSERT( branchNode->getRightBorder() != INVALID_VALUE );
	CPPUNIT_ASSERT( branchNode->getRightBorder() > branchNode->getLeftBorder() );
	CPPUNIT_ASSERT( branchNode->getTagId() != INVALID_VALUE );
	
	CPPUNIT_ASSERT( hierarchy->getRoot()->getLeftBorder() < branchNode->getRightBorder() );
	CPPUNIT_ASSERT( hierarchy->getRoot()->getRightBorder() > branchNode->getLeftBorder() );
	
	CPPUNIT_ASSERT( hierarchy->getRoot()->getName() == tag->valueAsString() );
	CPPUNIT_ASSERT( branchNode->getName() == branchTag->valueAsString() );
	
	
	AlphanumericalTag branchBranchTagData( hierarchyChildChildNodeName_ );
	const Tag* branchBranchTag = tagSet->addTag( &branchBranchTagData );
	PersistentHierarchyNode* branchBranchNode = hierarchy->addNode( branchNode->getId(), branchBranchTag );	
	
	CPPUNIT_ASSERT( hierarchy->getRoot()->getBranches().size() == 1 );
	
	AlphanumericalTag branch2TagData( hierarchyChildNodeName_ + " - 2");
	const Tag* branch2Tag = tagSet->addTag( &branch2TagData );
	
	hierarchy->addNode( hierarchy->getRoot()->getId(), branch2Tag );

	CPPUNIT_ASSERT( hierarchy->getRoot()->getBranches().size() == 2 );
	
	AlphanumericalTag branch3TagData( hierarchyChildNodeName_ + " - 3");
	const Tag* branch3Tag = tagSet->addTag( &branch3TagData );
	
	hierarchy->addNode( hierarchy->getRoot()->getId(), branch3Tag );
	
	CPPUNIT_ASSERT( hierarchy->getRoot()->getBranches().size() == 3 );
	
	PersistentDimension* copyDimension = tagSet->getPersistentDimension( hierarchy->getId() );
	CPPUNIT_ASSERT( copyDimension->getRoot()->getBranches().size() == 3 );
	
	
	//This is somewhat dirty but will have to do for now
	
	Object o1 = Object::fetch( TEST_OBJECT_ID );
	ObjectTag ot1( tag );
	o1.addTag( ot1 );
	
	Object o2 = Object::fetch( TestIds::TEST_OBJECT_PREFIX + "img2.jpg" );
	ObjectTag ot2( branchBranchTag );
	o2.addTag( ot2 );
	
	Object o3 = Object::fetch( TestIds::TEST_OBJECT_PREFIX + "img3.jpg" );
	ObjectTag ot3( branch2Tag );
	o3.addTag( ot3 );
	
	Object o4 = Object::fetch( TestIds::TEST_OBJECT_PREFIX + "img4.jpg" );
	ObjectTag ot4( branch3Tag );
	o4.addTag( ot4 );
	
	Object o5 = Object::fetch( TestIds::TEST_OBJECT_PREFIX + "img5.jpg" );
	ObjectTag ot5( branchTag );
	o5.addTag( ot5 );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void PersistentDimensionTest::testRemoveBranch_()
{
	Hub* hub = Hub::getHub();
	TagSet* tagSet = hub->getTagSet( TEST_ALPHANUMERICAL_TAG_SET_ID );
	
	PersistentDimension* hierarchy = tagSet->getPersistentDimension( hierarchyRootName_ );  //Notice, this is not safe unless each tag can only be the root of a single hierarchy
	
	CPPUNIT_ASSERT_EQUAL( 3, (int)hierarchy->getRoot()->getBranches().size() );	
	
	PersistentHierarchyNode* nodeToRemove = hierarchy->getNode( hierarchyChildNodeName_ );
	hierarchy->removeBranch( nodeToRemove->getId() ); 
	
	CPPUNIT_ASSERT_EQUAL( 2, (int)hierarchy->getRoot()->getBranches().size() ); //Worthless
}
//____________________________________________________________________________________________________________________________________________________________________________________

void PersistentDimensionTest::testFetchDimension_()
{
	Hub* hub = Hub::getHub();
	TagSet* tagSet = hub->getTagSet( TEST_ALPHANUMERICAL_TAG_SET_ID );
	
	unique_ptr<PersistentDimension> dimension( PersistentDimension::fetch_( tagSet->getDimension( hierarchyRootName_ )->getId() ) );
	
	CPPUNIT_ASSERT_EQUAL( 3, (int)dimension.get()->getRoot()->getBranches().size() );

}
//____________________________________________________________________________________________________________________________________________________________________________________



