/*
 *  HierarchyNodeAssertionTraits.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 20.2.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_HIERARCHY_NODE_ASSERTION_TRAITS_
#define ObjectCube_HIERARCHY_NODE_ASSERTION_TRAITS_

#include <vector>
#include "../Hierarchy/HierarchyNode.h"
#include "AssertionTraitsCommon.h"

namespace CppUnit 
{
	
	template<>
	struct assertion_traits<ObjectCube::HierarchyNode*>   
	{
		static bool equal( const ObjectCube::HierarchyNode* x, const ObjectCube::HierarchyNode* y )
		{
			return	x->getId() == y->getId() && 
			x->getDimensionId() == y->getDimensionId() &&
			x->getTagSetId() == y->getTagSetId() &&
//			x->getTagId() == y.getTagId() &&
			x->getLeftBorder() == y->getLeftBorder() &&
			x->getRightBorder() == y->getRightBorder() &&
			AssertionTraitsCommon::equalLists( x->getBranches(), y->getBranches() );
		}
		
		static std::string toString( const ObjectCube::HierarchyNode* x )
		{
			OStringStream ost;  //OStringStream is bugged in SDK 10.6, have to use 10.5 for this to work !!!
		
			ost << "id: " << x->getId() 
				<< " hierarchyId: " << x->getDimensionId()
				<< " tagSetId: " << x->getTagSetId() 
//				<< " tagId: " << x.getTagId()
				<< " leftBorder: " << x->getLeftBorder()
				<< " rightBorder: " << x->getRightBorder()
				<< " children: { ";
		
			vector<ObjectCube::HierarchyNode*> children = x->getBranches();
			vector<ObjectCube::HierarchyNode*>::iterator itr = children.begin();
			bool first = true;
			for( ; itr != children.end(); itr++ )
			{	
				if( first )
				{
					first = false;
				}
				else 
				{
					ost << " | ";
				}
				
				ost << assertion_traits<ObjectCube::HierarchyNode*>::toString( (*itr) );
			}
			ost << " }";
			
			return ost.str();
		}
		
	};
}

#endif