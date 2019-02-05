/*
 *  DefaultDimension.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 2.7.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_DEFAULT_DIMENSION_
#define ObjectCube_DEFAULT_DIMENSION_

#include <string>

using namespace std;

#include "Dimension.h"
#include "DefaultHierarchyNode.h"

namespace ObjectCube
{	
	class Tag;

	/*
	 This class is a specialized form of a virtual dimension, those two classes should share an ancestor
	 */
	
	class DefaultDimension : public Dimension
	{
		friend class TagSet;

	public:
		DefaultDimension();
		DefaultDimension( int tagSetId, const vector<Tag*>& tags );
		
		virtual ~DefaultDimension();
		
		DefaultHierarchyNode* getNode( const string& name );
		
		DefaultHierarchyNode* getDefaultRoot() { return dynamic_cast<DefaultHierarchyNode*>( root_.get() ); }
		const DefaultHierarchyNode* getDefaultRoot() const { return dynamic_cast<const DefaultHierarchyNode*>( root_.get() ); } //Overloaded for testing

		virtual Dimension& operator=( const Dimension& dimension );
		
		static string getRootName() { return rootName_;}
		
	protected:
		//Get
		int getNodeIdCounter_() const { return nodeIdCounter_; }

		//Set
		void setNodeIdCounter_( int counter ) { nodeIdCounter_ = counter; }
		
		virtual void delete_() {;}
		
	private:
		void init_();
		void init_( const vector<Tag*>& tags );
		
		static int idCounter_;
		static string rootName_;
		int nodeIdCounter_;
		
	};
	
}

#endif
