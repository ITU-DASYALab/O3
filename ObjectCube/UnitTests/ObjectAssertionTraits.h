/*
 *  ObjectAssertionTraits.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 16.2.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_OBJECT_ASSERTION_TRAITS_
#define ObjectCube_OBJECT_ASSERTION_TRAITS_

#include <vector>
#include "../Object.h"
#include "../ObjectTag.h"
#include "../Tag/Tag.h"
#include "ObjectTagAssertionTraits.h"
#include "AssertionTraitsCommon.h"


namespace CppUnit 
{	
	template<>
	struct assertion_traits<ObjectCube::Object>   
	{
		
		static bool equal( const ObjectCube::Object& x, const ObjectCube::Object& y )
		{
			return	x.getId() == y.getId() && 
					x.getName() == y.getName() && 
					AssertionTraitsCommon::equalLists( x.getTags(), y.getTags() );
		}
		
		static std::string toString( const ObjectCube::Object& x )
		{
			OStringStream ost;  //OStringStream is bugged in SDK 10.6, have to use 10.5 for this to work !!!
			ost << "id: " << x.getId() 
				<< " name: " << x.getName() 
				<< " objectTags: \n{\n";
			vector<ObjectCube::ObjectTag> objectTags = x.getTags();
			sort( objectTags.begin(), objectTags.end() );
	
			bool first = true; // To fix the hanging pipe in the tag list
			for( vector<ObjectCube::ObjectTag>::iterator itr = objectTags.begin(); itr != objectTags.end(); ++itr )
			{
				if( first )
				{
					first = false;
				}
				else 
				{
					ost << "\n";
				}

				ost << assertion_traits<ObjectCube::ObjectTag>::toString( (*itr) );
			}
			
			ost << "\n}";
			return ost.str();
		}
		
	};
}

#endif