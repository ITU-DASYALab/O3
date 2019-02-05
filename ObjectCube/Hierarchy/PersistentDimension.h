/*
 *  HierarchicalDimension.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 16.12.2009.
 *  Copyright 2009 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_PERSISTENT_DIMENSION_
#define ObjectCube_PERSISTENT_DIMENSION_

#include "Dimension.h"
#include "PersistentHierarchyNode.h"

using namespace std;

namespace ObjectCube
{
	class TagSet;
	class Tag;
	
	class PersistentDimension : public Dimension 
	{
		friend class DimensionConverter;
		friend class TagSet;
		friend class PersistentDimensionTest;
		
	public: //Constructors & Destructors
		PersistentDimension();
		PersistentDimension( int tagSetId, const Tag* /*const*/ tag );
		PersistentDimension( int tagSetId, const Tag* /*const*/ tag, const string& childCategoryTitle );
		
		virtual ~PersistentDimension();
		
		//Interface
		PersistentHierarchyNode* addNode( int parentNodeId, const Tag* /*const*/ tag );
		PersistentHierarchyNode* addNode( int parentNodeId, const Tag* /*const*/ tag, const string& childCategoryTitle );
		void removeBranch( int branchNodeId );
		PersistentHierarchyNode* getNode( const string& name );
		
		PersistentHierarchyNode* getPersistentRoot(); 
		const PersistentHierarchyNode* getPersistentRoot() const; 
				
	protected:
		static PersistentDimension* fetch_( int id );  
		int create_();
		virtual void delete_(); 
		virtual void updateBorders_();
		
	private:
		void init_();
		
	public:
		virtual Dimension& operator=( const Dimension& dimension );
		
	};
	
}

#endif

