/*
 *  StateDimension.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 25.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_STATE_DIMENSION_
#define ObjectCube_STATE_DIMENSION_

#include "../LayerShared/DimensionCommon.h"

#include "StateDimensionNode.h"

using namespace std;

namespace ObjectCube
{	
	class Dimension;
	
	class StateDimension : public DimensionCommon
	{
	public:
		//Constructors & destructor
		StateDimension( const Dimension* /*const*/ dimension, int filterId, map<int, map<int, vector<int> > >& filterIdNodeIdObjectIds /*const vector<StateObject>& objects*/ );
		virtual ~StateDimension() {;}
		
		int getId() const { return id_; }
		int getTypeId() const { return typeId_; }
		int getTagSetId() const { return tagSetId_; }
		int getFilterId() const { return filterId_; }
		const StateDimensionNode getRoot() const { return root_; }
		const StateDimensionNode getParentNode( int nodeId ) const;
		const StateDimensionNode getNode( int nodeId ) const;

	protected:
		void setId_( int id ) { id_ = id; }
		void setTypeId_( int typeId ) { typeId_ = typeId; }
		void setTagSetId_( int tagSetId ) { tagSetId_ = tagSetId; }
		void setFilterId_( int filterId ) { filterId_ = filterId; }
		
	private:
		int id_;
		int typeId_;
		int tagSetId_;
		int filterId_;
		StateDimensionNode root_;
		
	public:
		bool operator==( StateDimension const& x) const { return getId() == x.getId(); }
		
	};
	
}

#endif