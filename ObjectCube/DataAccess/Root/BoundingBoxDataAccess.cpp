/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/

#include "BoundingBoxDataAccess.h"


using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

BoundingBoxDataAccess::BoundingBoxDataAccess( Coordinate2DDataAccess upperLeftCorner, Coordinate2DDataAccess lowerRightCorner )
{
	upperLeftCorner_ = upperLeftCorner;
	lowerRightCorner_ = lowerRightCorner;
}
//____________________________________________________________________________________________________________________________________________________________________________________

