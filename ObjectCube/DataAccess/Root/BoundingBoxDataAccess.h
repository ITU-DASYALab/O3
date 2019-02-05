/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/


#ifndef ObjectCube_BOUNDINGBOX_DATA_ACCESS_
#define ObjectCube_BOUNDINGBOX_DATA_ACCESS_

#include "Coordinate2DDataAccess.h"

namespace ObjectCube 
{
	
	class BoundingBoxDataAccess
	{
	public:
		BoundingBoxDataAccess() {;}
		BoundingBoxDataAccess( Coordinate2DDataAccess upperLeftCorner, Coordinate2DDataAccess lowerRightCorner );
		
		//Get
		const Coordinate2DDataAccess& getUpperLeftCorner() const { return upperLeftCorner_; }
		const Coordinate2DDataAccess& getLowerRightCorner() const { return lowerRightCorner_; }
		
		//Set
		void setUpperLeftCorner( Coordinate2DDataAccess upperLeftCorner ) { upperLeftCorner_ = upperLeftCorner; }
		void setLowerRightCorner( Coordinate2DDataAccess lowerRightCorner ) { lowerRightCorner_ = lowerRightCorner; }
		
	protected:
		Coordinate2DDataAccess upperLeftCorner_;
		Coordinate2DDataAccess lowerRightCorner_;
		
	};
	
}

#endif
