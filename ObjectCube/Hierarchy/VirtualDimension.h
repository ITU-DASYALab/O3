/*
 *  VirtualDimension.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 5.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_VIRTUAL_DIMENSION_
#define ObjectCube_VIRTUAL_DIMENSION_

#include <string>

#include "Dimension.h"
#include "VirtualHierarchyNode.h"

using namespace std;

namespace ObjectCube
{	
	class VirtualHierarchyNode;
	
	class VirtualDimension : public Dimension
	{
		friend class TagSet;
		typedef int (*extractionFunction)(int, int, int);
		
	public: //Constructors & Destructors
		VirtualDimension(	int tagSetId, 
							const string& outerAttributePattern, 
							const string& innerAttributePattern, 
							const string& rootValue );
		
		VirtualDimension(	int tagSetId, 
							const string& outerAttributePattern, 
							const string& innerAttributePattern, 
							const string& rootValue, 
							const string& childCategoryTitle );
		
		VirtualDimension(	int tagSetId, 
							extractionFunction function,
							const string& rootValue );
		
		VirtualDimension(); //For factory use
		
		
		
		
		virtual ~VirtualDimension();
		
		VirtualHierarchyNode* addNode( int parentNodeId, const string& nodeValue );
		VirtualHierarchyNode* addNode( int parentNodeId, const string& nodeValue, const string& childCategoryTitle );
		
		//Get/Set
		string getOuterAttributePattern() const { return outerAttributePattern_; }
		string getInnerAttributePattern() const { return innerAttributePattern_; }
		int getType() const { return type_; }
		
		VirtualHierarchyNode* getVirtualRoot() { return dynamic_cast<VirtualHierarchyNode*>( root_.get() ); }
		const VirtualHierarchyNode* getVirtualRoot() const { return dynamic_cast<const VirtualHierarchyNode*>( root_.get() ); } //Overloaded for testing
		
	protected:
		//Get
		int getNodeIdCounter_() const { return nodeIdCounter_; }
		extractionFunction getExtractionFunction_() const { return extractionFunction_; }
		//Set
		void setNodeIdCounter_( int counter ) { nodeIdCounter_ = counter; }
		void setOuterAttributePattern_( const string& pattern ) { outerAttributePattern_ = pattern; }
		void setInnerAttributePattern_( const string& pattern ) { innerAttributePattern_ = pattern; }
		void setType_( int type ) { type_ = type; }
		void setExtractionFunction( extractionFunction function ) { extractionFunction_ = function; }
	
		virtual void delete_() {;}
		
	protected: //Member variables
		int nodeIdCounter_;
		//int depthOfHierarchy (add this)
		//int noOfVertices (add this)
		string outerAttributePattern_;
		string innerAttributePattern_;
		int type_;
		extractionFunction extractionFunction_;
		
	private:
		void init_();
		VirtualHierarchyNode* addNode_( int parentNodeId, VirtualHierarchyNode* node );
		static int idCounter_;
		
	public:
		virtual Dimension& operator=( const Dimension& dimension );
		
		enum TYPE
		{
			PATTERN_MATCHING = 1,
			EXTRACTION_FUNCTION = 2
		};

	};
	
}

#endif
