/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/


#ifndef ObjectCube_COORDINATE2D_CONVERTER_
#define ObjectCube_COORDINATE2D_CONVERTER_

#include <vector>
#include "../Boundaries/Coordinate2D.h"
#include "../DataAccess/Root/Coordinate2DDataAccess.h"

//#include "../DataAccess/Root/Coordinate2DDataAccess.h"

namespace ObjectCube 
{
	class Coordinate2DDataAccess;
	
	class Coordinate2DConverter
	{
	public:
		static Coordinate2D dataAccessToLogic( Coordinate2DDataAccess coordinateDA );
		static Coordinate2DDataAccess logicToDataAccess( Coordinate2D coordinate );
		
//		static vector<Coordinate2D> dataAccessToLogic( vector<Coordinate2DDataAccess*> coordinatesDA );
//		static vector<Coordinate2DDataAccess*> logicToDataAccess( const vector<Coordinate2D>& coordinates );
		
	};
	
}

#endif