/*
 *  StateTest.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 20.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "StateTest.h"

#include <cppunit/extensions/HelperMacros.h>

#include "../Hub.h"
#include "TestIds.h"
#include "../TagSet/TagSet.h"
#include "../Tag/Tag.h"
#include "../LayerShared/Exception.h"
#include "../LayerShared/SharedDefinitions.h"
#include "../Filters/DimensionFilter.h"
#include "../State/State.h"
#include "../Filters/TagFilter.h" 
#include "../Filters/NumericalRangeFilter.h"

using namespace ObjectCube;

CPPUNIT_TEST_SUITE_REGISTRATION( StateTest );

//____________________________________________________________________________________________________________________________________________________________________________________

//  Canned tests --------------------------------------------------------------------------------------------------------------------

void StateTest::testGetObjectsCanned()
{
	cerr << "\nStateTest::testGetObjectsCanned = ";
	Hub::setDataAccessType( Hub::CANNED );
	
	Hub* hub = Hub::getHub();
	TagSet* dTagSet = hub->getTagSet( TEST_DATE_TAG_SET_ID );
	
	State::removeAllFilters();
	
	const VirtualDimension* vdDim = dTagSet->getVirtualDimension( "Month" );
	const HierarchyNode* vdNode = vdDim->getVirtualRoot()->getBranch( 4 /*April*/ );
	DimensionFilter vdFilter( *vdNode, dTagSet->getId() );
	hub->addFilter( &vdFilter );
	
	vector<StateObject> stateObjects = State::getState().getObjects();
	
	CPPUNIT_ASSERT( stateObjects.size() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void StateTest::testGetDimensionsCanned()
{
	cerr << "\nStateTest::testGetDimensionsCanned = ";
	Hub::setDataAccessType( Hub::CANNED );
	
	Hub* hub = Hub::getHub();
	TagSet* dTagSet = hub->getTagSet( TEST_DATE_TAG_SET_ID );
	
	State::removeAllFilters();
	CPPUNIT_ASSERT( State::getState().getDimensions().size() == 0 );
	
	const VirtualDimension* vdDim = dTagSet->getVirtualDimension( "Month" );
	const HierarchyNode* vdNode = vdDim->getVirtualRoot()->getBranch( 4 /*April*/ );
	DimensionFilter vdFilter( *vdNode, dTagSet->getId() );
	hub->addFilter( &vdFilter );
	
	const vector<StateDimension> dimensions = State::getState().getDimensions();
	

}
//____________________________________________________________________________________________________________________________________________________________________________________

void StateTest::testGetFiltersCanned()
{
	cerr << "\nStateTest::testGetFiltersCanned = ";
	Hub::setDataAccessType( Hub::CANNED );
	
	Hub* hub = Hub::getHub();
	TagSet* anTagSet = hub->getTagSet(	TEST_ALPHANUMERICAL_TAG_SET_ID );
	
	//Empty test
	State::removeAllFilters();
	CPPUNIT_ASSERT( State::getFilters().size() == 0 );  //Empty test
	
	//Tag filter
	TagFilter tFilter( anTagSet->getTag( TEST_ALPHANUMERICAL_TAG_ID_CANNED ), anTagSet->getId() );
	State::addFilter( &tFilter );
	CPPUNIT_ASSERT( State::getFilters().size() == 1 );
	
	//Range filter
	TagSet* nTagSet = hub->getTagSet( TEST_NUMERICAL_TAG_SET_ID );
	NumericalRangeFilter nrFilter( 0, 100, nTagSet->getId() );
	State::addFilter( &nrFilter );
	CPPUNIT_ASSERT( State::getFilters().size() == 2 );
	
	//Dimension filter 
	TagSet* dTagSet = hub->getTagSet( TEST_DATE_TAG_SET_ID );
	const VirtualDimension* vdDim = dTagSet->getVirtualDimension( "Month" );
	const HierarchyNode* vdNode = vdDim->getVirtualRoot()->getBranch( 4 /*April*/ );
	DimensionFilter vdFilter( *vdNode, dTagSet->getId() );
	State::addFilter( &vdFilter );
	CPPUNIT_ASSERT( State::getFilters().size() == 3 );
	
	//Empty test
	State::removeAllFilters();
	CPPUNIT_ASSERT( State::getFilters().size() == 0 );  //Empty test	
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  SQLite tests --------------------------------------------------------------------------------------------------------------------

void StateTest::testGetObjectsSQLite()
{
	cerr << "\nStateTest::testGetObjectsSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testGetObjects_( SQLiteTestIds::TEST_ALPHANUMERICAL_TAG_ID );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void StateTest::testAddFilterSQLite()
{
	cerr << "\nStateTest::testAddFilterSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testAddFilter_( SQLiteTestIds::TEST_ALPHANUMERICAL_TAG_ID );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void StateTest::testRemoveFilterSQLite()
{
	cerr << "\nStateTest::testRemoveFilterSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );

	testRemoveFilter_( SQLiteTestIds::TEST_ALPHANUMERICAL_TAG_ID );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void StateTest::testRemoveAllFiltersSQLite()
{
	cerr << "\nStateTest::testRemoveAllFiltersSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testRemoveFilter_( SQLiteTestIds::TEST_ALPHANUMERICAL_TAG_ID );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void StateTest::testGetDimensionSQLite()
{
	cerr << "\nStateTest::testGetDimensionSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );

	testGetDimension_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void StateTest::testGetObjectIdsSQLite()
{
	cerr << "\nStateTest::testGetObjectIdsSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );

	testGetObjectIds_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void StateTest::testGetParentNodeSQLite()
{
	cerr << "\nStateTest::testGetParentNodeSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );

	testGetParentNode_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void StateTest::testGetMultiDimensionalViewSQLite()
{
	cerr << "\nStateTest::testGetMultiDimensionalViewSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testGetMultiDimensionalView_();
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  MonetDB tests --------------------------------------------------------------------------------------------------------------------

void StateTest::testGetObjectsMonetDB()
{
	cerr << "\nStateTest::testGetObjectsMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );

	testGetObjects_( MonetDBTestIds::TEST_ALPHANUMERICAL_TAG_ID );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void StateTest::testAddFilterMonetDB()
{
	cerr << "\nStateTest::testAddFilterMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );

	testAddFilter_( MonetDBTestIds::TEST_ALPHANUMERICAL_TAG_ID );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void StateTest::testRemoveFilterMonetDB()
{
	cerr << "\nStateTest::testRemoveFilterMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );
	
	testRemoveFilter_( MonetDBTestIds::TEST_ALPHANUMERICAL_TAG_ID );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void StateTest::testRemoveAllFiltersMonetDB()
{
	cerr << "\nStateTest::testRemoveAllFiltersMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );
	
	testRemoveFilter_( MonetDBTestIds::TEST_ALPHANUMERICAL_TAG_ID );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void StateTest::testGetDimensionMonetDB()
{
	cerr << "\nStateTest::testGetDimensionMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );

	testGetDimension_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void StateTest::testGetObjectIdsMonetDB()
{
	cerr << "\nStateTest::testGetObjectIdsMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );

	testGetObjectIds_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void StateTest::testGetParentNodeMonetDB()
{
	cerr << "\nStateTest::testGetParentNodeMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );

	testGetParentNode_();
}

void StateTest::testGetMultiDimensionalViewMonetDB()
{
	cerr << "\nStateTest::testGetMultiDimensionalViewMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );

	testGetMultiDimensionalView_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Oracle tests --------------------------------------------------------------------------------------------------------------------

void StateTest::testGetObjectsOracle()
{
	cerr << "\nStateTest::testGetObjectsOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testGetObjects_( OracleTestIds::TEST_ALPHANUMERICAL_TAG_ID );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void StateTest::testAddFilterOracle()
{
	cerr << "\nStateTest::testAddFilterOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testAddFilter_( OracleTestIds::TEST_ALPHANUMERICAL_TAG_ID );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void StateTest::testRemoveFilterOracle()
{
	cerr << "\nStateTest::testRemoveFilterOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testRemoveFilter_( OracleTestIds::TEST_ALPHANUMERICAL_TAG_ID );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void StateTest::testRemoveAllFiltersOracle()
{
	cerr << "\nStateTest::testRemoveAllFiltersOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testRemoveFilter_( OracleTestIds::TEST_ALPHANUMERICAL_TAG_ID );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void StateTest::testGetDimensionOracle()
{
	cerr << "\nStateTest::testGetDimensionOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testGetDimension_();	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void StateTest::testGetObjectIdsOracle()
{
	cerr << "\nStateTest::testGetObjectIdsOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testGetObjectIds_();	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void StateTest::testGetParentNodeOracle()
{
	cerr << "\nStateTest::testGetParentNodeOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testGetParentNode_();	
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Common --------------------------------------------------------------------------------------------------------------------

void StateTest::testGetObjects_( int tagId )
{
	State::removeAllFilters();
	State state = State::getState();
	vector<StateObject> objects = state.getObjects();
	CPPUNIT_ASSERT( objects.size() > 0 );
	for( vector<StateObject>::iterator itr = objects.begin(); itr != objects.end(); ++itr )
	{
		//cout << "1. id: " << (*itr).getId() << "  Name. " << (*itr).getName() << endl;
		CPPUNIT_ASSERT( (*itr).getName().length() > 0 );
	}
	
	Hub* hub = Hub::getHub();
	TagSet* anTagSet = hub->getTagSet(	TEST_ALPHANUMERICAL_TAG_SET_ID );
	
	TagFilter tagFilter( anTagSet->getTag( tagId ), anTagSet->getId() );
	State::addFilter( &tagFilter );
	
	state = State::getState();
	objects = state.getObjects();
	for( vector<StateObject>::iterator itr = objects.begin(); itr != objects.end(); ++itr )
	{
		//cout << "2. id: " << (*itr).getId() << "  Name. " << (*itr).getName() << endl;
		CPPUNIT_ASSERT( (*itr).getName().length() > 0 );
	}	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void StateTest::testAddFilter_( int tagId )
{
	Hub* hub = Hub::getHub();
	TagSet* anTagSet = hub->getTagSet(	TEST_ALPHANUMERICAL_TAG_SET_ID );
	
	State::removeAllFilters();
	CPPUNIT_ASSERT( State::getFilters().size() == 0 );  //Empty test
	
	TagFilter tFilter( anTagSet->getTag( tagId ), anTagSet->getId() );
	State::addFilter( &tFilter );
	CPPUNIT_ASSERT( State::getFilters().size() == 1 );
	
	State::removeAllFilters();
	CPPUNIT_ASSERT( State::getFilters().size() == 0 );  //Empty test	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void StateTest::testRemoveFilter_( int tagId )
{
	Hub* hub = Hub::getHub();
	TagSet* anTagSet = hub->getTagSet(	TEST_ALPHANUMERICAL_TAG_SET_ID );
	
	State::removeAllFilters();
	CPPUNIT_ASSERT( State::getFilters().size() == 0 );  //Empty test
	
	TagFilter tFilter( anTagSet->getTag( tagId ), anTagSet->getId() );
	State::addFilter( &tFilter );
	CPPUNIT_ASSERT( State::getFilters().size() == 1 );
	
	State::removeFilter( &tFilter );
	CPPUNIT_ASSERT( State::getFilters().size() == 0 );  //Empty test	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void StateTest::testRemoveAllFilters_( int tagId )
{
	Hub* hub = Hub::getHub();
	TagSet* anTagSet = hub->getTagSet(	TEST_ALPHANUMERICAL_TAG_SET_ID );
	
	//Empty test
	State::removeAllFilters();
	CPPUNIT_ASSERT( State::getFilters().size() == 0 );  //Empty test
	
	//Tag filter
	TagFilter tFilter( anTagSet->getTag( tagId ), anTagSet->getId() );
	State::addFilter( &tFilter );
	CPPUNIT_ASSERT( State::getFilters().size() == 1 );
	
	//Range filter
	TagSet* nTagSet = hub->getTagSet( TEST_NUMERICAL_TAG_SET_ID );
	NumericalRangeFilter nrFilter( 0, 100, nTagSet->getId() );
	State::addFilter( &nrFilter );
	CPPUNIT_ASSERT( State::getFilters().size() == 2 );
	
	//Dimension filter 
	TagSet* dTagSet = hub->getTagSet( TEST_DATE_TAG_SET_ID );
	const VirtualDimension* vdDim = dTagSet->getVirtualDimension( "Month" );
	const HierarchyNode* vdNode = vdDim->getVirtualRoot()->getBranch( 4 /*April*/ );
	DimensionFilter vdFilter( *vdNode, dTagSet->getId() );
	State::addFilter( &vdFilter );
	CPPUNIT_ASSERT( State::getFilters().size() == 3 );
	
	//Empty test
	State::removeAllFilters();
	CPPUNIT_ASSERT( State::getFilters().size() == 0 );  //Empty test		
}
//____________________________________________________________________________________________________________________________________________________________________________________

void StateTest::testGetDimension_()
{
	Hub* hub = Hub::getHub();

	//Empty test
	State::removeAllFilters();
	CPPUNIT_ASSERT( State::getFilters().size() == 0 );  //Empty test

	TagSet* dTagSet = hub->getTagSet( TEST_DATE_TAG_SET_ID );
	const VirtualDimension* vdDim = dTagSet->getVirtualDimension( "Month" );
	const HierarchyNode* vdNode = vdDim->getVirtualRoot()->getBranch( 4 /*April*/ );
	DimensionFilter vdFilter( *vdNode, dTagSet->getId() );
	State::addFilter( &vdFilter );
	CPPUNIT_ASSERT( State::getFilters().size() == 1 );
	
	State state = State::getState();
	const StateDimension stateDim = state.getDimension( vdDim->getId() );
	
	CPPUNIT_ASSERT_EQUAL( stateDim.getTagSetId(), dTagSet->getId() );
	CPPUNIT_ASSERT_EQUAL( stateDim.getTypeId(), vdDim->getTypeId() );
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void StateTest::testGetObjectIds_()
{
	Hub* hub = Hub::getHub();
	
	//Empty test
	State::removeAllFilters();
	CPPUNIT_ASSERT( State::getFilters().size() == 0 );  //Empty test
	
	TagSet* tagSet = hub->getTagSet( TEST_ALPHANUMERICAL_TAG_SET_ID );
	PersistentDimension* dimension = tagSet->getPersistentDimension( TEST_HIERARCHY_ID + 1 );
	HierarchyNode* root = dimension->getRoot();
	DimensionFilter dFilter( *root, tagSet->getId() );
	State::addFilter( &dFilter );
	CPPUNIT_ASSERT( State::getFilters().size() == 1 );
	
	State state = State::getState();
	const StateDimension stateDim = state.getDimension( dimension->getId() );
	
	const StateDimensionNode stateDimRoot = stateDim.getRoot();
	CPPUNIT_ASSERT_EQUAL( 3, (int) stateDimRoot.getObjectIds().size() );

}
//____________________________________________________________________________________________________________________________________________________________________________________

void StateTest::testGetParentNode_()
{
	Hub* hub = Hub::getHub();
	
	//Empty test
	State::removeAllFilters();
	CPPUNIT_ASSERT( State::getFilters().size() == 0 );  //Empty test
	
	TagSet* tagSet = hub->getTagSet( TEST_ALPHANUMERICAL_TAG_SET_ID );
	PersistentDimension* dimension = tagSet->getPersistentDimension( TEST_HIERARCHY_ID + 1 );
	HierarchyNode* root = dimension->getRoot();
	DimensionFilter dFilter( *root, tagSet->getId() );
	State::addFilter( &dFilter );
	CPPUNIT_ASSERT( State::getFilters().size() == 1 );
	
	State state = State::getState();
	const StateDimension stateDim = state.getDimension( dimension->getId() );
	
	const StateDimensionNode& stateDimRoot = stateDim.getRoot();
	CPPUNIT_ASSERT( stateDimRoot.getBranches().size() > 0 );
	
	StateDimensionNode stateDimChild = stateDimRoot.getBranches()[0];
	
	const StateDimensionNode stateDimParent = stateDim.getParentNode( stateDimChild.getNode()->getId() );
	
	CPPUNIT_ASSERT_EQUAL( stateDimRoot.getNode()->getId(), stateDimParent.getNode()->getId()  );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void StateTest::testGetMultiDimensionalView_()
{
	Hub* hub = Hub::getHub();
	
	//Empty test
	State::removeAllFilters();
	
	TagSet* tagSet = hub->getTagSet( TEST_ALPHANUMERICAL_TAG_SET_ID );
	
	State state = State::getState();
	
	//Test 1-dimensional with tag-set
	/*
	MultiDimensionalView::setAxis( MultiDimensionalView::AXIS_1, tagSet );
	const MultiDimensionalView mdv = state.getMultiDimensionalView();
	outputMultiDimensionalView_( const_cast<MultiDimensionalView*>( &mdv ) );
	*/
	//Assert 
	
	/*
	//Test 2-dimensional with tag-sets
	MultiDimensionalView::setAxis( MultiDimensionalView::AXIS_2, tagSet ); //Diagonal, same tag-set
	const MultiDimensionalView mdv2 = state.getMultiDimensionalView();
	outputMultiDimensionalView_( const_cast<MultiDimensionalView*>( &mdv2 ) );
	*/
	//Test 1-dimensional with hierarchy
	PersistentDimension* dimension = tagSet->getPersistentDimension( TEST_HIERARCHY_ID + 1 );
	HierarchyNode* root = dimension->getRoot();
	DimensionFilter dFilter( *root, tagSet->getId() );
	State::addFilter( &dFilter );
	CPPUNIT_ASSERT( State::getFilters().size() == 1 );
	
	state = State::getState();
	MultiDimensionalView::clearAxes();
	const StateDimension stateDim = state.getDimension( dimension->getId() );
	MultiDimensionalView::setAxis( MultiDimensionalView::AXIS_1, stateDim.getRoot(), 0 );
	
	const MultiDimensionalView mdv3 = state.getMultiDimensionalView( false );
	outputMultiDimensionalView_( const_cast<MultiDimensionalView*>( &mdv3 ) );
	
	/*
	PersistentDimension* dimension = tagSet->getPersistentDimension( TEST_HIERARCHY_ID + 1 );
	HierarchyNode* root = dimension->getRoot();
	DimensionFilter dFilter( *root, tagSet->getId() );
	State::addFilter( &dFilter );
	CPPUNIT_ASSERT( State::getFilters().size() == 1 );
	
	State state = State::getState();
	const StateDimension stateDim = state.getDimension( dimension->getId() );
	
	CPPUNIT_ASSERT_THROW( state.getMultiDimensionalView(), ObjectCube::Exception);
	
	MultiDimensionalView::setXAxis( &stateDim.getRoot() );
	
	const MultiDimensionalView mdv = state.getMultiDimensionalView();
	//Check contents of cells ?
	
	CPPUNIT_ASSERT_EQUAL( 3, mdv.getUniqueObjectCount() );
	CPPUNIT_ASSERT_EQUAL( 4, mdv.getObjectCount() );
	CPPUNIT_ASSERT_EQUAL( 4, mdv.getXAxisCellCount() );
	CPPUNIT_ASSERT_EQUAL( 1, mdv.getYAxisCellCount() );
	CPPUNIT_ASSERT_EQUAL( 1, mdv.getZAxisCellCount() );
	
	outputMultiDimensionalView_( &mdv );
	
	//Add Y axis, getMDV, check contents
	MultiDimensionalView::setYAxis( &stateDim.getRoot() ); //Diagonal
	const MultiDimensionalView mdv2 = state.getMultiDimensionalView();
	CPPUNIT_ASSERT_EQUAL( 3, mdv2.getUniqueObjectCount() );
	CPPUNIT_ASSERT_EQUAL( 6, mdv2.getObjectCount() );
	CPPUNIT_ASSERT_EQUAL( 4, mdv2.getXAxisCellCount() );
	CPPUNIT_ASSERT_EQUAL( 4, mdv2.getYAxisCellCount() );
	CPPUNIT_ASSERT_EQUAL( 1, mdv2.getZAxisCellCount() );
	
	
	outputMultiDimensionalView_( &mdv2 );
	//Add Z axis, getMDV, check contents
	 */
}
//____________________________________________________________________________________________________________________________________________________________________________________

bool StateTest::generateKey_( string& key, const vector<unsigned int>& dimensionCellCounts, vector<unsigned int>& currCounts, unsigned int& currDimension )
{
	//Think of this as an arbitrary number of nested loops.
	//For anything but the outer most "loop" we reset counters and recurse.
	
	// for three dimensions, and cell counts [ 3, 2, 2 ] we should get:
	//	0:0:0
	//	0:0:1
	//	0:1:0
	//	0:1:1
	//	1:0:0
	
	//When ever we raise a counter we reset all counters that come after it in the vector
	
	if( ! dimensionCellCounts.size() )
	{
		return false;
	}
	
	if( !( currCounts[ currDimension ] < dimensionCellCounts[ currDimension ] ) ) //Reset or return false
	{
		if( currDimension == 0 ) //We have processed all keys
		{
			return false;
		}
		//We have not processed all and need to raise and reset counters

		//reset the current dimension, and all after it
		for( int resetIndex = currDimension; resetIndex < currCounts.size(); ++resetIndex )
		{
			currCounts[ resetIndex ] = 0;  
		}
		currCounts[ --currDimension ]++; //move the current dimension one up and raise it by one.
				
		return generateKey_( key, dimensionCellCounts, currCounts, currDimension );
	}
	
	//Normal processing
	currDimension = currCounts.size() - 1;
	
	stringstream keyStream;
	for( int dimIndex = 0; dimIndex < currCounts.size(); ++dimIndex )
	{
		if( dimIndex > 0 )
		{
			keyStream << ":";
		}
		keyStream << currCounts[ dimIndex ];
	}
	currCounts[ currDimension ]++;
	
	key = keyStream.str();
	return true;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void StateTest::outputMultiDimensionalView_( MultiDimensionalView* mdv )
{
	map<string, Cell> cells = mdv->getCells();
	
	cout << endl << endl;
	cout << "Dimension count: " << MultiDimensionalView::numberOfDimensions() << endl << endl;
	
	vector<unsigned int> dimensionCellCounts;
	for( int cellCount = 0; cellCount < MultiDimensionalView::numberOfDimensions(); ++cellCount )
	{
		unsigned int count = mdv->getAxisCellCount( cellCount );
		cout << "Cell count for dimension: " << cellCount << " count: " << count << endl; 
		dimensionCellCounts.push_back( count );
	}
	
	vector<unsigned int> currDimensionCounts( dimensionCellCounts.size(), 0 );
	unsigned int currDimension = dimensionCellCounts.size() - 1;
	string key;
	
	while( generateKey_( key, dimensionCellCounts, currDimensionCounts, currDimension ) )
	{
		//Always the same !
		if( !cells.count( key ) )
		{
			cout << "No cell for key: " << key << " was found !!!!!" << endl << endl;
		}
		Cell tempCell = cells[ key ];
		cout << "\nkey: " << key << endl;
		cout << "Objects in cell: " << tempCell.getObjects().size() << endl;
		for( int d = 0; d < MultiDimensionalView::numberOfDimensions(); ++d )
		{
			string label = tempCell.getAxisLabel( d );
			cout << "\tAxis: " << d << " dimension tag name: " << label << endl;
		}
		const vector<StateObject> objects = tempCell.getObjects();
		for( vector<StateObject>::const_iterator oItr = objects.begin(); oItr != objects.end(); ++oItr )
		{
			cout << "\n\tObject name: " << (*oItr).getName() << endl;
			const vector<StateTag> objectTags = (*oItr).getTags();
			for( vector<StateTag>::const_iterator tItr = objectTags.begin(); tItr != objectTags.end(); ++tItr )
			{
				cout << "\t\tObject tag name: " << (*tItr).getTag()->valueAsString() << endl;
			}
		}
	}
	
	cout << endl << "Unique objects: " << mdv->getUniqueObjectCount() << endl;
	cout << "Objects total: " << mdv->getObjectCount() << endl;
}
//____________________________________________________________________________________________________________________________________________________________________________________



















