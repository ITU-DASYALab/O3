/*
 *  DimensionFilter.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 14.4.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_DIMENSION_FILTER_
#define ObjectCube_DIMENSION_FILTER_

#include "Filter.h"

#include <map>

namespace ObjectCube 
{
	class HierarchyNode;
	
	class DimensionFilter : public Filter
	{
	public:
		//Constructors
		DimensionFilter( const HierarchyNode& node, int tagSetId );
		virtual ~DimensionFilter();
		
		//Get/Set
		map<int, int> getTagAndDimensionNodeIds() const { return tagAndDimensionNodeIds_; }
		int getDimensionId() const { return dimensionId_; }
		int getLeftBorder() const { return leftBorder_; }
		int getRightBorder() const { return rightBorder_; }
		int getDimensionTypeId() const { return dimensionTypeId_; }
		
		//Operator overloading
		virtual Filter& operator=( const Filter& filter );
		
	protected:
		void getTagAndDimensionNodeIds_( const map<int, int>& tagAndDimensionNodeIds );
		void setDimensionId_( int id ) { dimensionId_ = id; }
		void setLeftBorder_( int border ) { leftBorder_ = border; }
		void setRightBorder_( int border ) { rightBorder_ = border; }
		void setDimensionTypeId_( int dimensionTypeId ) { dimensionTypeId_ = dimensionTypeId; }
		
		//Constructor for factory
		DimensionFilter();
		
	private:
		void init_();
		
	protected:
		int dimensionId_;
		int leftBorder_;
		int rightBorder_;
		int dimensionTypeId_;
		
		map<int, int> tagAndDimensionNodeIds_;
		
		friend class FilterFactory;
		friend class DimensionFilterConverter;
	};
	
}

#endif