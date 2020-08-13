/*
 *  StateTag.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 17.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_STATE_TAG_
#define ObjectCube_STATE_TAG_

#include <string>
#include <map>

#ifdef __APPLE__
#include <memory>
using std::shared_ptr;
#else
#include <tr1/memory>
using std::shared_ptr;
#endif

#include "../Boundaries/BoundingBox.h"

using namespace std;

namespace ObjectCube
{	
	class Tag;
	
	class StateTag
	{
		friend class Hub;
	public:
		//Constructors & destructor
		StateTag( Tag* tag );
		StateTag( const map<int, int>& filterAndDimensionNodeIds );
		StateTag( const StateTag& stateTag ); //Copy constructor
		~StateTag();
		
		//Get/Set
		bool ledToInclusion() const { return filterAndDimensionNodeIds_.size() > 0 ? true : false; }
		map<int, int> getFilterAndDimensionNodeIds() const { return filterAndDimensionNodeIds_; }
		const Tag* getTag() const { return tag_;}
		const BoundingBox getBoundingBox() const;
		
		bool hasBoundingBox() const { return boundingBox_.get() == 0 ? false : true; }
		
	protected:
		void setTag_( Tag* tag ) { tag_ = tag; }
		void setBoundingBox_( BoundingBox* boundingBox ) { *boundingBox_ = *boundingBox; }
		void addFilterAndDimensionNodeId_( int filterId, int dimensionNodeId ) { filterAndDimensionNodeIds_.insert( pair<int, int>( filterId, dimensionNodeId ) ); }  //Duplicates are not inserted
		
	private:
		//Each dimension node can only appear once for each filter.
		map<int, int> filterAndDimensionNodeIds_; //<filterId, DimensionNodeId>
		Tag* tag_;
		std::shared_ptr<BoundingBox> boundingBox_;
		
		void cleanup_();

	public:
		bool operator==( StateTag const& x) const { return getTag() == x.getTag(); }
		StateTag& operator=( const StateTag& stateTag );

		friend class StateTagConverter;
	};
	
}

#endif
