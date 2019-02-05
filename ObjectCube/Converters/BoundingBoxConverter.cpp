/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/

#include "BoundingBoxConverter.h"

#include "Coordinate2DConverter.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

BoundingBox BoundingBoxConverter::dataAccessToLogic( BoundingBoxDataAccess boundingBoxDA )
{
	return BoundingBox( 
					   Coordinate2DConverter::dataAccessToLogic( boundingBoxDA.getUpperLeftCorner() ),
					   Coordinate2DConverter::dataAccessToLogic( boundingBoxDA.getLowerRightCorner() ) 
					   );
}
//____________________________________________________________________________________________________________________________________________________________________________________

BoundingBoxDataAccess BoundingBoxConverter::logicToDataAccess( BoundingBox boundingBox )
{
	
	return BoundingBoxDataAccess(
									 Coordinate2DConverter::logicToDataAccess( boundingBox.getUpperLeftCorner() ),
									 Coordinate2DConverter::logicToDataAccess( boundingBox.getLowerRightCorner() ) 
									 );
}
//____________________________________________________________________________________________________________________________________________________________________________________

