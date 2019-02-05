/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/

#include "BoundingBox.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

BoundingBox::BoundingBox()
{
	upperLeftCorner_.setX( 0.0 );
	upperLeftCorner_.setY( 100.0 );
	lowerRightCorner_.setX( 100.0 );
	lowerRightCorner_.setY( 0.0 );
}
//____________________________________________________________________________________________________________________________________________________________________________________
BoundingBox::BoundingBox( Coordinate2D upperLeftCorner, Coordinate2D lowerRightCorner )
{
	upperLeftCorner_ = upperLeftCorner;
	lowerRightCorner_ = lowerRightCorner;
}
//____________________________________________________________________________________________________________________________________________________________________________________

bool BoundingBox::operator==( const BoundingBox& x ) const
{
	return upperLeftCorner_ == x.getUpperLeftCorner() && lowerRightCorner_ == x.getLowerRightCorner();
}
//____________________________________________________________________________________________________________________________________________________________________________________