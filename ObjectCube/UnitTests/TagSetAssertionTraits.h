/*
 *  DimensionAssertionTraits.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 17.2.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_TAG_SET_ASSERTION_TRAITS_
#define ObjectCube_TAG_SET_ASSERTION_TRAITS_

#include "../TagSet/TagSet.h"
#include "TagAssertionTraits.h"
#include "DimensionAssertionTraits.h"
#include "AssertionTraitsCommon.h"

namespace CppUnit 
{
	
	template<>
	struct assertion_traits<ObjectCube::TagSet>   
	{
		static bool equal( const ObjectCube::TagSet& x, const ObjectCube::TagSet& y )
		{
			return	x.getId() == y.getId() && 
					x.getName() == y.getName() && 
					x.getDescription() == y.getDescription() && 
					x.getTypeId() == y.getTypeId() && 
					x.getAccessId() == y.getAccessId() &&
					AssertionTraitsCommon::equalLists( x.getTags(), y.getTags() ) && 
					AssertionTraitsCommon::equalLists( x.getDimensions(), y.getDimensions() );
		}
		
		static std::string toString( const ObjectCube::TagSet& x )
		{
			OStringStream ost;  //OStringStream is bugged in SDK 10.6, have to use 10.5 for this to work !!!
			ost << "id: " << x.getId() 
				<< " name: " << x.getName() 
				<< " description: " << x.getDescription() 
				<< " typeId: " << x.getTypeId() 
				<< " accessId: " << x.getAccessId() 
				<< " tags: { ";
			
			const vector<ObjectCube::Tag*> tags = x.getTags();
			vector<ObjectCube::Tag*>::const_iterator itr = tags.begin();
			bool first = true;
			for( ; itr != tags.end(); itr++ )
			{
				if( first )
				{
					first = false;
				}
				else 
				{
					ost << " | ";
				}

				ost << assertion_traits<ObjectCube::Tag>::toString( *(*itr) );
			}
			
			ost << " } hierarchies: { ";
			const vector<ObjectCube::Dimension*> hierarchies = x.getDimensions();
			vector<ObjectCube::Dimension*>::const_iterator hierItr = hierarchies.begin();
			first = true;
			for( ; hierItr != hierarchies.end(); hierItr++ )
			{
				if( first )
				{
					first = false;
				}
				else 
				{
					ost << " | ";
				}
				
				ost << 	assertion_traits<ObjectCube::Dimension*>::toString( *hierItr );
			}
			
			ost << " }";
			
			return ost.str();
		}
		
	};
}

#endif