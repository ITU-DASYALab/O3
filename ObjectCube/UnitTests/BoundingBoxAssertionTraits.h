/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/


#ifndef ObjectCube_BOUNDINGBOX_ASSERTION_TRAITS_
#define ObjectCube_BOUNDINGBOX_ASSERTION_TRAITS_

#include "../Boundaries/BoundingBox.h"

namespace CppUnit 
{
	
	template<>
	struct assertion_traits<ObjectCube::BoundingBox>   
	{
		static bool equal( ObjectCube::BoundingBox x, ObjectCube::BoundingBox y )
		{
			return x.getUpperLeftCorner().getX() == y.getUpperLeftCorner().getX()
			&& x.getUpperLeftCorner().getY() == y.getUpperLeftCorner().getY()
			&& x.getLowerRightCorner().getX() == y.getLowerRightCorner().getX()
			&& x.getLowerRightCorner().getY() == y.getLowerRightCorner().getY();
		}
		
		static std::string toString( const ObjectCube::BoundingBox& x )
		{
			
			OStringStream ost;  //OStringStream is bugged in SDK 10.6, have to use 10.5 for this to work !!!

			ost	<<	"Upper left X: " << x.getUpperLeftCorner().getX()
				<<	". Upper left Y: " << x.getUpperLeftCorner().getY()
				<<	". Lower right X: " << x.getLowerRightCorner().getX()
			<<	". Lower right Y: " << x.getLowerRightCorner().getY();

			return ost.str();
		}
		
	};
	
}

#endif