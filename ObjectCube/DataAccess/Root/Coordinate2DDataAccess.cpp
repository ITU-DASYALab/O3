/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/

#include "Coordinate2DDataAccess.h"
#include "../../LayerShared/SharedDefinitions.h"


using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

Coordinate2DDataAccess::Coordinate2DDataAccess()
:	x_( INVALID_VALUE ),
	y_( INVALID_VALUE )
{

}

Coordinate2DDataAccess::Coordinate2DDataAccess( double x, double y )
:	x_( INVALID_VALUE ),
	y_( INVALID_VALUE )
{
	x_ = x;
	y_ = y;
}
//____________________________________________________________________________________________________________________________________________________________________________________

