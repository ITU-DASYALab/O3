/*
 *  StateTagDataAccess.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 18.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_STATE_TAG_DATA_ACCESS_
#define ObjectCube_STATE_TAG_DATA_ACCESS_

#include <map>

using namespace std;

namespace ObjectCube
{
	class TagDataAccess;
	class BoundingBoxDataAccess;
	
	class StateTagDataAccess
	{
	public:
		StateTagDataAccess();
		virtual ~StateTagDataAccess();
		
		const map<int, int> getFilterAndDimensionNodeIds() const { return filterAndDimensionNodeIds_; }
		int getTagId() const { return tagId_;}
		BoundingBoxDataAccess* getBoundingBox() const;
		
		void setTagId( int tagId ) { tagId_ = tagId; }
		void addFilterAndDimensionNodeId( int filterId, int dimensionNodeId ) { filterAndDimensionNodeIds_.insert( pair<int, int>( filterId, dimensionNodeId ) ); }  //Duplicates are not inserted
		void setBoundingBox( BoundingBoxDataAccess* boundingBox ) { boundingBox_ = boundingBox; }
		
		bool hasBoundingBox();
		
	private:
		map<int, int> filterAndDimensionNodeIds_; //<filterId, DimensionNodeId>
		int tagId_;
		BoundingBoxDataAccess* boundingBox_;
		
	};
	
}

#endif


