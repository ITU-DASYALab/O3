/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/

#include "Coordinate2DConverter.h"



using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

Coordinate2D Coordinate2DConverter::dataAccessToLogic( Coordinate2DDataAccess coordinateDA )
{
	return Coordinate2D( coordinateDA.getX(), coordinateDA.getY() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

Coordinate2DDataAccess Coordinate2DConverter::logicToDataAccess( Coordinate2D coordinate )
{
	return Coordinate2DDataAccess( coordinate.getX(), coordinate.getY() );
}
//____________________________________________________________________________________________________________________________________________________________________________________
/*
vector<Coordinate2D> Coordinate2DConverter::dataAccessToLogic( vector<Coordinate2DDataAccess*> coordinatesDA )
{
	vector<Coordinate2D> coordinates;
	for( vector<Coordinate2DDataAccess*>::iterator itr = coordinatesDA.begin(); itr != coordinatesDA.end(); ++itr )
	{
		coordinates.push_back( Coordinate2DConverter::dataAccessToLogic( *itr ) );
	}
	return coordinates;
}
//____________________________________________________________________________________________________________________________________________________________________________________

vector<Coordinate2DDataAccess*> Coordinate2DConverter::logicToDataAccess( const vector<Coordinate2D>& coordinates )
{
	vector<Coordinate2DDataAccess*> coordinatesDA;
	for( vector<Coordinate2D>::const_iterator itr = coordinates.begin(); itr != coordinates.end(); ++itr )
	{
		coordinatesDA.push_back( Coordinate2DConverter::logicToDataAccess( &(*itr) ) );
	}
	return coordinatesDA;	
}
//____________________________________________________________________________________________________________________________________________________________________________________
*/