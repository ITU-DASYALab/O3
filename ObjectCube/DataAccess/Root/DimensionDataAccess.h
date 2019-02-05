/*
 *  DimensionDataAccess.h
 *  Prada
 *
 *  Created by Grímur Tómasson on 8.2.2010.
 *  Copyright 2010 RU. All rights reserved.
 *
 */

#ifndef ObjectCube_DIMENSION_DATA_ACCESS_
#define ObjectCube_DIMENSION_DATA_ACCESS_

#include <vector>

#include "HierarchyNodeDataAccess.h"

using namespace std;

namespace ObjectCube
{	
	class DimensionDataAccess
	{
	public:
		DimensionDataAccess();
		virtual ~DimensionDataAccess();
		
		virtual int nextId() = 0;
		virtual vector<HierarchyNodeDataAccess*> fetch( int id ) = 0;
		
		
		void setId( int id ) { id_ = id; }
		void setTagSetId( int tagSetId ) { tagSetId_ = tagSetId; }
		void setRoot( HierarchyNodeDataAccess* node ) { root_ = node; }
		
		int getId() const { return id_; }
		int getTagSetId() const { return tagSetId_; }
		HierarchyNodeDataAccess* getRoot() {return root_; }
		
	protected: //Member variables
		int id_;
		int tagSetId_;
		HierarchyNodeDataAccess* root_;
		
	
	};
	
}

#endif