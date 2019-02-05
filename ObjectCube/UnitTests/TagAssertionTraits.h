/*
 *  TagAssertionTraits.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 15.2.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_TAG_ASSERTION_TRAITS_
#define ObjectCube_TAG_ASSERTION_TRAITS_

#include "../Tag/Tag.h"

namespace CppUnit 
{
	
	template<>
	struct assertion_traits<ObjectCube::Tag>   
	{
		static bool equal( const ObjectCube::Tag& x, const ObjectCube::Tag& y )
		{
				return	x.getId() == y.getId() 
						&& x.getTagSetId() == y.getTagSetId() 
						&& x.getTypeId() == y.getTypeId();
		}
		
		static std::string toString( const ObjectCube::Tag& x )
		{
			OStringStream ost;  //OStringStream is bugged in SDK 10.6, have to use 10.5 for this to work !!!
			ost		<< "id: " << x.getId() 
					<< " getTagSetId: " << x.getTagSetId() 
					<< " typeId: " << x.getTypeId()
					<< " value: " << x.inUse() ;
			
			return ost.str();
		}

	};
	
}

#endif