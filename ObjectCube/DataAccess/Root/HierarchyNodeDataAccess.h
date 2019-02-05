/*
 *  HierarchyNodeDataAccess.h
 *  Prada
 *
 *  Created by Grímur Tómasson on 8.2.2010.
 *  Copyright 2010 RU. All rights reserved.
 *
 */

#ifndef ObjectCube_HIERARCHY_NODE_DATA_ACCESS_
#define ObjectCube_HIERARCHY_NODE_DATA_ACCESS_

#include <string>
#include <vector>

#include "../../LayerShared/HierarchyNodeCommon.h"

using namespace std;

namespace ObjectCube
{
	
	class HierarchyNodeDataAccess : public HierarchyNodeCommon
	{
	public:
		HierarchyNodeDataAccess();
		virtual ~HierarchyNodeDataAccess();
		
		virtual HierarchyNodeDataAccess* create() = 0;
		virtual void update() = 0;
		virtual void remove() = 0;		
		
		//Set
		void setId( int id ) { id_ = id; }
		void setHierarchyId( int id ) { hierarchyId_ = id; }
		void setTagSetId( int id ) { tagSetId_ = id; }
		void setTagId( int tagId ) { tagId_ = tagId; }
		void setChildCategoryTitle( const string& childCategoryTitle ) { childCategoryTitle_ = childCategoryTitle; }
		void setLeftBorder( int left ) { leftBorder_ = left; }
		void setRightBorder( int right ) { rightBorder_ = right; }
		void setBranches( vector<HierarchyNodeDataAccess*> branches ) { children_ = branches; }
	
		//Get
		int getId() const { return id_; }
		int getDimensionId() const { return hierarchyId_; }
		int getTagSetId() const { return tagSetId_; }
		int getTagId() const { return tagId_; }
		string getChildCategoryTitle() const { return childCategoryTitle_; }
		int getLeftBorder() const { return leftBorder_; }
		int getRightBorder() const { return rightBorder_; }
		const vector<HierarchyNodeDataAccess*> getBranches() const { return children_; }
		
	protected: //Member variables
		int id_;
		int hierarchyId_; //Leave out of interface
		int tagSetId_; //Leave out of interface
		int tagId_;
		string childCategoryTitle_;
		int leftBorder_;
		int rightBorder_;
		
		vector<HierarchyNodeDataAccess*> children_;
		
	
	};
	
}

#endif