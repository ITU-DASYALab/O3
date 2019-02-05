/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/


#ifndef ObjectCube_BOUNDINGBOX_
#define ObjectCube_BOUNDINGBOX_

#include "Coordinate2D.h"

namespace ObjectCube 
{
	
	class BoundingBox
	{
	public:
		BoundingBox();
		BoundingBox( Coordinate2D upperLeftCorner, Coordinate2D lowerRightCorner );
		
		//Get
		const Coordinate2D getUpperLeftCorner() const { return upperLeftCorner_; }
		const Coordinate2D getLowerRightCorner() const { return lowerRightCorner_; }
		
		//Set
		void setUpperLeftCorner( Coordinate2D upperLeftCorner ) { upperLeftCorner_ = upperLeftCorner; }
		void setLowerRightCorner( Coordinate2D lowerRightCorner ) { lowerRightCorner_ = lowerRightCorner; }
		
		bool operator==( const BoundingBox& x ) const;
		
	protected:
		Coordinate2D upperLeftCorner_;
		Coordinate2D lowerRightCorner_;
		
	};
	
}

#endif
