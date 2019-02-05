/*
 *  VirtualHierarchyNode.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 5.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_VIRTUAL_HIERARCHY_NODE_
#define ObjectCube_VIRTUAL_HIERARCHY_NODE_

#include "HierarchyNode.h"

using namespace std;

namespace ObjectCube
{	
	class VirtualHierarchyNode : public HierarchyNode 
	{
		friend class VirtualDimension;
		friend class VirtualHierarchyNodeTest;
		
		typedef int (*extractionFunction)(int, int, int);
	public: //Constructors & Destructors
		VirtualHierarchyNode();
		virtual ~VirtualHierarchyNode();
		
		VirtualHierarchyNode(	int id, 
								const string& name, 
								int tagSetId, 
								int dimensionId,
								const string& outerAttributePattern, 
								const string& innerAttributePattern );
		
		VirtualHierarchyNode(	int id, 
								const string& name, 
								int tagSetId, 
								int dimensionId,
								const string& outerAttributePattern, 
								const string& innerAttributePattern, 
								const string& childCategoryTitle );
		
		VirtualHierarchyNode(	int id, 
								const string& name, 
								int tagSetId, 
								int dimensionId,
								int (*extractionFunction)(int, int, int) );
		
	public: 
		virtual HierarchyNode& operator=( const HierarchyNode& node );
		
	protected: 
		virtual map<int, int> getSubtreeTagIds_() const;
		void addBranch_( VirtualHierarchyNode* node ); //Direct add
		void addBranch_( int parentNodeId, VirtualHierarchyNode* child ); //Indirect add
		
	protected: 
		//Get
		string getOuterAttributePattern_() const { return outerAttributePattern_; }
		string getInnerAttributePattern_() const { return innerAttributePattern_; }
		extractionFunction getExtractionFunction_() const { return extractionFunction_; }
		
		//Set
		void setOuterAttributePattern_( const string& pattern ) { outerAttributePattern_ = pattern; }
		void setInnerAttributePattern_( const string& pattern ) { innerAttributePattern_ = pattern; }
		void setExtractionFunction_( extractionFunction function ) { extractionFunction_ = function; }
		
	protected: //Member variables
		string outerAttributePattern_;
		string innerAttributePattern_;
		extractionFunction extractionFunction_;
		
	private:
		void init_();
		void propertyInSubtree_( const string& property, int tagId, map<int, int>& tagIds ) const;
		string extractByPattern_( const string& value, const string& outerPattern, const string& innerPattern ) const;
		string extractByFunction_( const string& value ) const;  
				
	};
	
}

#endif
