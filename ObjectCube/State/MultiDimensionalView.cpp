/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/

#include "MultiDimensionalView.h"

#include <map>
#include <sstream>
#include <iostream>

#include "../LayerShared/SharedDefinitions.h"
#include "../LayerShared/Exception.h"
#include "StateDimension.h"
#include "StateDimensionNode.h"
#include "../TagSet/TagSet.h"
#include "../Tag/Tag.h"
#include "../Hub.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

vector<MultiDimensionalView::Axis> MultiDimensionalView::axes_(0);

//____________________________________________________________________________________________________________________________________________________________________________________

MultiDimensionalView::MultiDimensionalView( const vector<StateObject>& objects, bool withEmptySlices )
{
	setWithEmptySlices_( withEmptySlices );
	setUniqueObjectCount_( objects.size() );
	setObjectCount_( 0 );
		
	construct_( objects );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void MultiDimensionalView::construct_( const vector<StateObject>& objects )
{
	//A minimum of one dimension is set
	if( !axes_.size() )
	{
		//throw Exception( "MultiDimensionalView::construct_", "At least one dimension has to be set!");
		return;
	}
	
	//DEBUG !!!
	/*
	for( vector<StateObject>::const_iterator itr = objects.begin(); itr != objects.end(); ++itr )
	{
		cout << "Object id: " << (*itr).getId() << endl;
		const vector<StateTag> tags = (*itr).getTags();
		for( vector<StateTag>::const_iterator tagItr = tags.begin(); tagItr != tags.end(); ++tagItr )
		{
			const StateTag stateTag = (*tagItr);
			const Tag* tag = stateTag.getTag();
			if( tag == 0 )
			{
				cout << "\tNULL in tag list !!!!!!!!!!!!!!!!!!" << endl;
			}
			else 
			{
				cout << "\tTag id: " << tag->getId() << " name: " << tag->valueAsString() <<  endl;
			}
		}
	}
	 */
	
	//Create tag* lists for all axes, populate those in effect - simplifies code
	for( vector<Axis>::iterator itr = axes_.begin(); itr != axes_.end(); ++itr )
	{
		getTagsForAxis_( (*itr), objects );
	}
	addObjectsToCells_( objects );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

int MultiDimensionalView::getAxisCellCount( unsigned int axis )
{
	size_t axisST = (size_t) axis;
	if( axisST > axes_.size() )
	{
		throw Exception( "MultiDimensionalView::getAxisCellCount", "Axis has not been set!", axisST );
	}
	return getAxis_( axis ).getCellCount();
}
//____________________________________________________________________________________________________________________________________________________________________________________

MultiDimensionalView::Axis MultiDimensionalView::getAxis_( unsigned int axis )
{
	size_t axisST = (size_t) axis;

	if( axisST > axes_.size() )
	{
		throw Exception( "MultiDimensionalView::getAxis", "Axis has not been set!", axisST );
	}
	
	if( axis > axes_.size()-1 ) // Index check when fetching axis from vector.
		throw Exception( "MultiDimensionalView::getAxis", "Out of bounds!", axisST );
	
	return axes_[ axisST ];
}
//____________________________________________________________________________________________________________________________________________________________________________________

void MultiDimensionalView::setAxis( unsigned int axis, StateDimensionNode stateDimensionNode, int viewDepth )
{
	
	cout << "[!MDV]: Setting axis " << axis << endl;

	size_t axisST = (size_t) axis;
	
	if( axisST > ( axes_.size() + 1 ) ) // Jumping over one dimension, out of order
	{
		throw Exception( "MultiDimensionalView::setAxis", "The n-1 dimension has to be set before the n-th dimension!", axis );
	}
	
	Axis axisValue( stateDimensionNode, viewDepth );
	if( axisST >= axes_.size() ) //A new dimension is being added, in order
	{
		axes_.push_back( axisValue );
		return;
	}
	axes_[ axisST ] = axisValue;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void MultiDimensionalView::setAxis( unsigned int axis, TagSet* tagSet )
{
	
	cout << "[!MDV]: Setting axis " << axis << endl;

	size_t axisST = (size_t) axis;
	
	if( axisST > ( axes_.size() + 1 ) ) // Jumping over one dimension, out of order
	{
		throw Exception( "MultiDimensionalView::setAxis", "The n-1 dimension has to be set before the n-th dimension!", axis );
	}
	
	Axis axisValue( tagSet );;
	if( axisST >= axes_.size() ) //A new dimension is being added, in order
	{
		axes_.push_back( axisValue );
		return;
	}
	axes_[ axisST ] = axisValue;
}
//____________________________________________________________________________________________________________________________________________________________________________________
void MultiDimensionalView::clearAxis( unsigned int axis )
{
	
	cout << "[!MDV]: Clearing all axis " << axis << endl;

	size_t axisST = (size_t) axis;
	if( axes_.size() > 0 && axes_.size() >= axisST )
	{
		axes_.erase( axes_.begin() + axisST );
		return;
	}
	throw Exception( "MultiDimensionalView::getAxisCellCount", "Axis has not been set!", axisST );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void MultiDimensionalView::clearAxes()
{
	axes_.clear();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void MultiDimensionalView::processCell_( const vector<StateObject>& objects, Cell& cell, const string& key )
{
	for( vector<StateObject>::const_iterator itr = objects.begin(); itr != objects.end(); ++itr )
	{
		if( cell.belongs( *itr ) )
		{
			++noObjects_;
		}
	}
	dimensionalCellMap_.insert( pair<string, Cell>( key, cell) );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

bool MultiDimensionalView::generateKey_( string& key, const vector<unsigned int>& dimensionCellCounts, vector<unsigned int>& currCounts, unsigned int& currDimension )
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
		for( unsigned int resetIndex = currDimension; resetIndex < currCounts.size(); ++resetIndex )
		{
			currCounts[ resetIndex ] = 0;  
		}
		currCounts[ --currDimension ]++; //move the current dimension one up and raise it by one.
		
		return generateKey_( key, dimensionCellCounts, currCounts, currDimension );
	}
	
	//Normal processing
	currDimension = currCounts.size() - 1;
	
	stringstream keyStream;
	for( unsigned int dimIndex = 0; dimIndex < currCounts.size(); ++dimIndex )
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

void MultiDimensionalView::addObjectsToCells_( const vector<StateObject>& objects )
{	
	if( axes_.size() == 0 )
	{
		return;
	}
	
	vector<unsigned int> axisTagCounts;
	for( int axisIndex = 0; axisIndex < MultiDimensionalView::numberOfDimensions(); ++axisIndex )
	{
		axisTagCounts.push_back( axes_[ axisIndex ].tags_.size() );
	}
	
	vector<unsigned int> currAxisCounts( axisTagCounts.size(), 0 );
	unsigned int currAxis = axisTagCounts.size() - 1;
	string key;
	
	while( generateKey_( key, axisTagCounts, currAxisCounts, currAxis ) )
	{
		vector<vector<Tag*> > dimensionTags;
		vector<string> displayLabels;
		
		for( unsigned int axisNo = 0; axisNo < MultiDimensionalView::numberOfDimensions(); ++axisNo )
		{
			//The -1 is due to the counter having been raised by one compared to the key string.  Only the current axis index was raised.
			unsigned int currAxisIndex = 5000;
			axisNo == currAxis ? currAxisIndex = currAxisCounts[ axisNo ] - 1 : currAxisIndex = currAxisCounts[ axisNo ];
			
			dimensionTags.insert( dimensionTags.begin() + axisNo, axes_[ axisNo ].tags_[ currAxisIndex ] );
			displayLabels.push_back( axes_[ axisNo].displayLabels_[ currAxisIndex ] );
		}
		
		Cell currentCell( dimensionTags, displayLabels );
		processCell_( objects, currentCell, key );
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________

bool MultiDimensionalView::inUse_( int tagId, const vector<StateObject>& objects )
{
	for( vector<StateObject>::const_iterator itr = objects.begin(); itr != objects.end(); ++itr )
	{
		if( (*itr).hasTag( tagId ) )
		{
			return true;
		}
	}
	return false;
}
//____________________________________________________________________________________________________________________________________________________________________________________

bool MultiDimensionalView::inUse_( map<int, int>& tagIdNodeId, const vector<StateObject>& objects )
{
	map<int, int> replacementMap;
	bool foundTagInUse = false;
	for( map<int, int>::iterator mapItr = tagIdNodeId.begin(); mapItr != tagIdNodeId.end(); ++mapItr )
	{
		if( inUse_( mapItr->first, objects ) )
		{
			foundTagInUse = true;
			replacementMap.insert( *mapItr );
		}
	}
	tagIdNodeId = replacementMap;
	return foundTagInUse;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void MultiDimensionalView::getTagsForAxis_( Axis& axis, const vector<StateObject>& objects )
{
	if( axis.getType() == INVALID ) //Not in use, not an error
	{
		return;
	}
	
	axis.displayLabels_.clear();
	axis.tags_.clear();
	if( axis.getType() == TAG_SET )
	{
		vector<Tag*> tags = axis.getTagSet()->getTags();
		vector<vector<Tag*> > dimTags;
		for( vector<Tag*>::iterator itr = tags.begin(); itr != tags.end(); ++itr )
		{
			if( !getWithEmptySlices() && !inUse_( (*itr)->getId() , objects ) )
			{
				continue;
			}
			vector<Tag*> tempTagVector;
			tempTagVector.push_back( *itr );
			dimTags.push_back( tempTagVector );
			axis.displayLabels_.push_back( (*itr)->valueAsString() );
		}
		axis.tags_ = dimTags;
		return;
	}
	if( axis.getType() == HIERARCHY_NODE )
	{
		//Get the tags for each of the branches of the current node!!!
		//const vector<StateDimensionNode> branches = axis.node_.getBranches();
		vector<StateDimensionNode> branches = axis.node_.getSubHierarchyLevel( axis.getViewDepth() );
		for( vector<StateDimensionNode>::const_iterator itr = branches.begin(); itr != branches.end(); ++itr )
		{
			map<int, int> tagIdNodeId = (*itr).getNode()->getSubtreeTagIds();
			if( !getWithEmptySlices() && !inUse_( tagIdNodeId, objects ) )
			{
				continue;
			}
			axis.displayLabels_.push_back( (*itr).getNode()->getName() );
			TagSet* tagSet = Hub::getHub()->getTagSet( (*itr).getNode()->getTagSetId() );
			vector<Tag*> tempTagVector;
			for( map<int, int>::iterator mapItr = tagIdNodeId.begin(); mapItr != tagIdNodeId.end(); ++mapItr )
			{
				Tag* tempTag = const_cast<Tag*>( tagSet->getTag( mapItr->first ) );
				tempTagVector.push_back( tempTag );
			}
			axis.tags_.push_back( tempTagVector );
		}
		return;
	}
	throw Exception( "MultiDimensionalView::getTagsForAxis_", "Unknown axis type", axis.getType() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

const map<string, Cell> MultiDimensionalView::getCells(unsigned int maxObjects, unsigned int maxObjectsPerCell ) const
{ 
    //dimensionalCellMap_
    
    
    
    return dimensionalCellMap_; 
}
//____________________________________________________________________________________________________________________________________________________________________________________

int MultiDimensionalView::numberOfDimensions()
{
	int retVal = 0;
	for( vector<Axis>::iterator itr = axes_.begin(); itr != axes_.end(); ++itr )
	{
		if( itr->getType() != INVALID )
		{
			++retVal;
		}
	}
	
	return retVal;
}
//____________________________________________________________________________________________________________________________________________________________________________________
TagSet* getTagSet();
StateDimensionNode getNode();

MultiDimensionalView::Axis::Axis( TagSet* tagSet )
{
	tagSet_ = tagSet;
	type_ = TAG_SET;
	viewDepth_ = 0;
}
//____________________________________________________________________________________________________________________________________________________________________________________

MultiDimensionalView::Axis::Axis( StateDimensionNode node, int viewDepth )
{
	node_ = node;
	type_ = HIERARCHY_NODE;
	viewDepth_ = viewDepth;
}
//____________________________________________________________________________________________________________________________________________________________________________________

MultiDimensionalView::Axis::Axis()
{
	tagSet_ = 0;
	type_ = INVALID;
	viewDepth_ = 0;
}
//____________________________________________________________________________________________________________________________________________________________________________________

int MultiDimensionalView::Axis::getCellCount() const
{
	return tags_.size();
}
//____________________________________________________________________________________________________________________________________________________________________________________

TagSet* MultiDimensionalView::Axis::getTagSet()
{
	if( getType() != TAG_SET )
	{
		throw Exception( "MultiDimensionalView::Axis::getTagSet", "TagSet requested from an axis with no tag-set" );
	}
	return tagSet_;
}
//____________________________________________________________________________________________________________________________________________________________________________________

StateDimensionNode MultiDimensionalView::Axis::getNode()
{
	if( getType() != HIERARCHY_NODE )
	{
		throw Exception( "MultiDimensionalView::Axis::getNode", "StateDimensionNode requested from an axis with no node" );
	}

	return node_;
}
//____________________________________________________________________________________________________________________________________________________________________________________

bool MultiDimensionalView::Axis::operator==( Axis const& x ) const
{
	return	tagSet_ == x.tagSet_ && 
			node_ == x.node_ && 
			type_ == x.type_ && 
			viewDepth_ == x.viewDepth_ &&
			tags_ == x.tags_ &&
			displayLabels_ == x.displayLabels_;
}
//____________________________________________________________________________________________________________________________________________________________________________________
