/*
 *  TagBasedHierarchyNode.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 2.7.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_TAG_BASED_HIERARCHY_NODE_
#define ObjectCube_TAG_BASED_HIERARCHY_NODE_

#include "HierarchyNode.h"

#include <string>

using namespace std;

namespace ObjectCube
{
	class Tag;
	
	class TagBasedHierarchyNode : public HierarchyNode
	{
	public: //Constructors & Destructors
		TagBasedHierarchyNode( int typeId );
		TagBasedHierarchyNode( int typeId, const Tag* /*const*/ tag );
		TagBasedHierarchyNode( int typeId, const Tag* /*const*/ tag, int dimensionId, int tagSetId );
		TagBasedHierarchyNode( int typeId, const Tag* /*const*/ tag, int dimensionId, int tagSetId, const string& childCategoryTitle );
		
		virtual ~TagBasedHierarchyNode();
		
	protected: //Interface for Dimension implementations
		virtual map<int, int> getSubtreeTagIds_() const;
		virtual void updateBorders_( int& borderCounter );
		void getNode_( int tagId, TagBasedHierarchyNode** node );
		
	protected: //Set
		void setTagId_( int tagId ) { tagId_ = tagId; }
		
	public: //Get
		int getTagId() const { return tagId_; }
		
	protected: //Member variables
		int tagId_;
		
	private:
		void init_();
		
	public:
		virtual HierarchyNode& operator=( const HierarchyNode& node ) = 0;

	};
}

#endif
