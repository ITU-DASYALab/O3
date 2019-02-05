/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/


#ifndef ObjectCube_DIMENSION_FILTER_DATA_ACCESS_
#define ObjectCube_DIMENSION_FILTER_DATA_ACCESS_

#include "FilterDataAccess.h"

#include <map>

namespace ObjectCube 
{
	
	class DimensionFilterDataAccess : public FilterDataAccess
	{
	public:
		//Constructors
		DimensionFilterDataAccess();
		virtual ~DimensionFilterDataAccess();
		
		//Get/Set
		map<int, int> getTagAndDimensionNodeIds() const { return tagAndDimensionNodeIds_; }
		int getDimensionId() const { return dimensionId_; }
		int getLeftBorder() const { return leftBorder_; }
		int getRightBorder() const { return rightBorder_; }
		int getDimensionTypeId() const { return dimensionTypeId_; }
		
		void setTagAndDimensionNodeIds( const map<int, int>& tagAndDimensionNodeIds );
		void setDimensionId( int id ) { dimensionId_ = id; }
		void setLeftBorder( int border ) { leftBorder_ = border; }
		void setRightBorder( int border )  { rightBorder_ = border; }
		void setDimensionTypeId( int dimensionTypeId ) { dimensionTypeId_ = dimensionTypeId; }
		
	protected:
		virtual string getSelectionPredicate_();
		virtual string getFiltrationPredicate_();
			
	protected:
		int dimensionId_;
		int leftBorder_;
		int rightBorder_;
		int dimensionTypeId_;
		
		map<int, int> tagAndDimensionNodeIds_;
	};
	
}

#endif