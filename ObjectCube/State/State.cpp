/*
 *  PhotoSet.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 25.10.2009.
 *  Copyright 2009 Reykjavik University. All rights reserved.
 *
 */

#include "State.h"

#include <iostream>

#include "../Hub.h"
#include "../TagSet/TagSet.h"
#include "../Filters/Filter.h"
#include "../Filters/DimensionFilter.h"
#include "../LayerShared/Exception.h"
#include "../LayerShared/DebugInfo.h"


using namespace std;
using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

void State::addFilter( Filter* /*const*/ filter )
{
	Hub* hub = Hub::getHub();
	hub->addFilter( filter );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void State::removeAllFilters()
{
	Hub* hub = Hub::getHub();
	hub->removeAllFilters();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void State::removeFilter( Filter* filter )
{
	Hub::getHub()->removeFilter( filter );
}
//____________________________________________________________________________________________________________________________________________________________________________________
/*
vector<StateObject> State::getObjects()
{
	Hub* hub = Hub::getHub();
	return hub->getObjects();
}
 */
//____________________________________________________________________________________________________________________________________________________________________________________

const State State::getState() 
{

	DebugInfo::getDebugInfo()->pushTimer( "State", "getState" );

	MultiDimensionalView::clearAxes();
	
	Hub* hub = Hub::getHub();
/*
	State retState;
	retState.setObjects_( hub->getObjects() );
*/
	State retState = hub->getState();
	DebugInfo::getDebugInfo()->pushTimer( "State", "getState", "adding hierarchies" );

	//dimensions
	const vector<Filter*> dimensionFilters = hub->getFilters( Filter::DIMENSION_FILTER );
	vector<StateDimension> dimensions;
	for( vector<Filter*>::const_iterator itr = dimensionFilters.begin(); itr != dimensionFilters.end(); ++itr )
	{
		DimensionFilter* dimensionFilter = dynamic_cast<DimensionFilter*>( *itr );
		int tagSetId = dimensionFilter->getTagSetId();
		int dimensionId = dimensionFilter->getDimensionId();
		TagSet* tagSet = hub->getTagSet( tagSetId );
		Dimension* origDimension = tagSet->getDimension( dimensionId );
		
		StateDimension stateDimension( origDimension, dimensionFilter->getId(), retState.getFilterIdNodeIdObjectIds() /*retState.getObjects()*/ );
		DebugInfo::getDebugInfo()->output( "State", "getState", "No of objects in hierarchy: ", stateDimension.getRoot().getObjectIds().size() );
		
		dimensions.push_back( stateDimension );
	}
	retState.setDimensions_( dimensions );
	DebugInfo::getDebugInfo()->popTimer();
	DebugInfo::getDebugInfo()->popTimer();
	return retState;
}
//____________________________________________________________________________________________________________________________________________________________________________________

const vector<Filter*> State::getFilters()
{
	Hub* hub = Hub::getHub();
	return hub->getFilters();
}
//____________________________________________________________________________________________________________________________________________________________________________________

const vector<StateObject> State::getObjects( const vector<int>& objectIds ) const
{
	vector<StateObject> objects;
	for( vector<int>::const_iterator idItr = objectIds.begin(); idItr != objectIds.end(); ++idItr )
	{
		for( vector<StateObject>::const_iterator objectItr = objects_.begin(); objectItr != objects_.end(); ++objectItr )
		{
			if( (*idItr) == (*objectItr).getId() )
			{
				objects.push_back( *objectItr );
				continue;
			}
		}
	}
	
	return objects;
}
//____________________________________________________________________________________________________________________________________________________________________________________

const StateDimension State::getDimension( int dimensionId ) const
{
	for( vector<StateDimension>::const_iterator itr = dimensions_.begin(); itr != dimensions_.end(); ++itr )
	{
		if( (*itr).getId() == dimensionId )
		{
			return *itr;
		}
	}
	throw Exception("State::getDimension", "Dimension requested does not exist, id: ", dimensionId );
}
//____________________________________________________________________________________________________________________________________________________________________________________

const MultiDimensionalView State::getMultiDimensionalView( bool withEmptySlices ) const
{
	return MultiDimensionalView( objects_, withEmptySlices );
}
//____________________________________________________________________________________________________________________________________________________________________________________