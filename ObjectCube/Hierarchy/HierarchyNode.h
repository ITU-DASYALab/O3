/*
 *  HierarchyNode.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 6.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_HIERARCHY_NODE_
#define ObjectCube_HIERARCHY_NODE_

#include <string>
#include <vector>
#include <map>

#ifdef __APPLE__
#include <memory>
using std::shared_ptr;
#else
#include <tr1/memory>
using std::shared_ptr;
#endif

#include "../LayerShared/HierarchyNodeCommon.h"

using namespace std;

namespace ObjectCube
{
	
	class HierarchyNode : public HierarchyNodeCommon
	{
		friend class Dimension;
		friend class PersistentDimension;
		friend class VirtualDimension;
		
	public: //Constructors & Destructors
		HierarchyNode( int typeId );
		virtual ~HierarchyNode();
		
		//For memory management
		HierarchyNode( const HierarchyNode& node );  //Copy constructor
		virtual HierarchyNode& operator=( const HierarchyNode& node ) = 0;
		
	public: 
		map<int, int> getSubtreeTagIds() const;
		string traverse( int indent ) const; //For debugging
		HierarchyNode* getBranch( int id );
		const HierarchyNode* getBranch( int id ) const;
		
	protected: 
		virtual map<int, int> getSubtreeTagIds_() const = 0;
		virtual void updateBorders_( int& borderCounter );
		bool getBranch_( int id, HierarchyNode*& node );
		void setBranches_( const vector<HierarchyNode*>& branches );
		
		//Memory management and = support
		void copyValues_( const HierarchyNode& node );
		
		//Set
		void setId_( int id ) { id_ = id; }
		void setTagSetId_( int tagSetId ) { tagSetId_ = tagSetId; }
		void setDimensionId_( int dimensionId ) { dimensionId_ = dimensionId; }
		void setLeftBorder_( int left ) { leftBorder_ = left; }
		void setRightBorder_( int right ) { rightBorder_ = right; }
		void setName_( const string& name ) { name_ = name; }
		void setChildCategoryTitle_( const string& title ) { childCategoryTitle_ = title; }
		
	public: //Get
	
		//Get
		int getId() const { return id_; }
		int getTagSetId() const { return tagSetId_; }
		int getDimensionId() const { return dimensionId_; }
		int getLeftBorder() const { return leftBorder_; }
		int getRightBorder() const { return rightBorder_; }
		string getName() const { return name_; }
		string getChildCategoryTitle() const { return childCategoryTitle_; }
		int getTypeId() const { return typeId_; }

		const vector<HierarchyNode*> getBranches() const;
		
	protected: //Member variables
		int id_;
		int typeId_;
		int tagSetId_;
		int dimensionId_;
		int leftBorder_;
		int rightBorder_;
		string name_;
		string childCategoryTitle_;
		
		vector<std::shared_ptr<HierarchyNode> > children_;
		
	private:
		void init_();
		
	public:
		virtual bool operator==( HierarchyNode const& x) const;
		virtual bool operator!=( HierarchyNode const& x) const;
		virtual bool operator < ( const HierarchyNode& x ) const;
		
	};
	
}

#endif


