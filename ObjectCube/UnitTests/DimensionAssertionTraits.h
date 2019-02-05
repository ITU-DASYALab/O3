/*
 *  PersistentDimension.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 20.2.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

/*
 *  ObjectAssertionTraits.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 16.2.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_DIMENSION_ASSERTION_TRAITS_
#define ObjectCube_DIMENSION_ASSERTION_TRAITS_

#include "../Hierarchy/Dimension.h"
#include "HierarchyNodeAssertionTraits.h"

namespace CppUnit 
{
	
	template<>
	struct assertion_traits<ObjectCube::Dimension*>   
	{
		static bool equal( const ObjectCube::Dimension* x, const ObjectCube::Dimension* y )
		{
			return	x->getId() == y->getId() && 
			x->getTagSetId() == y->getTagSetId() && 
			*x->getRoot() == *y->getRoot();
		}
		
		static std::string toString( const ObjectCube::Dimension* x )
		{
			OStringStream ost;  //OStringStream is bugged in SDK 10.6, have to use 10.5 for this to work !!!
			ost << "id: " << x->getId() 
			<< " tagSetId: " << x->getTagSetId() 
			<< " root: { "
			<< assertion_traits<ObjectCube::HierarchyNode*>::toString( x->getRoot() )
			<< " }";
			 
			return ost.str();
		}
		
	};
}

#endif