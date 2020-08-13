/*
 *  Dimension.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 7.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_DIMENSION_
#define ObjectCube_DIMENSION_

#ifdef __APPLE__
#include <memory>
using std::shared_ptr;
#else
#include <tr1/memory>
using std::shared_ptr;
#endif

#include "../LayerShared/DimensionCommon.h"
#include "HierarchyNode.h"

using namespace std;

namespace ObjectCube
{
	class TagSet;
	class Tag;
	
	class Dimension : public DimensionCommon
	{
		
	public: //Constructors & Destructors
		Dimension( int typeId );
		Dimension( int typeId, int tagSetId );
		
		virtual ~Dimension();
		
		//For memory management
		Dimension( const Dimension& dimension );  //Copy constructor
		virtual Dimension& operator=( const Dimension& dimension ) = 0;
		
		//Get/Set
		int getId() const { return id_; }
		int getTypeId() const { return typeId_; }
		int getTagSetId() const { return tagSetId_; }
		HierarchyNode* getRoot();
		const HierarchyNode* /*const*/ getRoot() const; //Overloaded for testing
		
	protected:
		void setId_( int id ) { id_ = id; }
		void setTypeId_( int typeId ) { typeId_ = typeId; }
		void setTagSetId_( int tagSetId ) { tagSetId_ = tagSetId; }
		
		void init_( const HierarchyNode* /*const*/ node );
		virtual void updateBorders_();
		virtual void delete_() = 0;

		//Memory management 
		void copyValues_( const Dimension& dimension );
		
	protected: //Member variables
		int id_;
		int typeId_;
		int tagSetId_;
		std::shared_ptr<HierarchyNode> root_;
		
		//int depthOfHierarchy (add this)
		//int noOfVertices (add this)
		
	public:
		
		virtual bool operator==( Dimension const& x) const;
		virtual bool operator!=( Dimension const& x) const;
		virtual bool operator < ( const Dimension& x ) const;
		
		friend class TagSet;
		
	};
	
}

#endif


