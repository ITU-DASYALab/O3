/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/


#ifndef ObjectCube_OBJECT_TAG_ASSERTION_TRAITS_
#define ObjectCube_OBJECT_TAG_ASSERTION_TRAITS_

#include "../ObjectTag.h"
#include "../Boundaries/BoundingBox.h"
#include "../Tag/Tag.h"

#include "TagAssertionTraits.h"
#include "BoundingBoxAssertionTraits.h"

namespace CppUnit 
{
	
	template<>
	struct assertion_traits<ObjectCube::ObjectTag>   
	{
		static bool equal( const ObjectCube::ObjectTag& x, const ObjectCube::ObjectTag& y )
		{
			bool tagsAreEqual = assertion_traits<ObjectCube::Tag>::equal( *x.getTag(), *y.getTag() );
			bool boundingBoxesAreEqual = false;
			bool xHasBoundingBox = false;
			bool yHasBoundingBox = false;
			
			try {
				x.getBoundingBox();
				xHasBoundingBox = true;
			} catch (...) {}
			
			try {
				y.getBoundingBox();
				yHasBoundingBox = true;
			} catch (...) {}
			
			if( xHasBoundingBox && yHasBoundingBox )
			{
				boundingBoxesAreEqual = assertion_traits<ObjectCube::BoundingBox>::equal( x.getBoundingBox(), y.getBoundingBox() );
			}
			else if( !xHasBoundingBox && !yHasBoundingBox )
			{
				boundingBoxesAreEqual = true;
			}
			
			return tagsAreEqual && boundingBoxesAreEqual;
		}
		
		static std::string toString( const ObjectCube::ObjectTag& x )
		{
			OStringStream ost;  //OStringStream is bugged in SDK 10.6, have to use 10.5 for this to work !!!
			
			ost	<< "Tag: \n{\n\t" 
			<< assertion_traits<ObjectCube::Tag>::toString( *x.getTag() )
			<< "\n}\n"
			<< "BoundingBox: \n{\n\t";
			try 
			{
				ost << assertion_traits<ObjectCube::BoundingBox>::toString( x.getBoundingBox() );
			}
			catch(...) 
			{
				ost << "No bounding box";
			}
			
			ost	<< "\n}";
			 
			return ost.str();
		}
		
	};
	
}

#endif