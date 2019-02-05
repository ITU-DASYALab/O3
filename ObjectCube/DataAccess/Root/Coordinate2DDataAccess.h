/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/


#ifndef ObjectCube_COORDINATE2D_DATA_ACCESS_
#define ObjectCube_COORDINATE2D_DATA_ACCESS_

namespace ObjectCube 
{
	
	class Coordinate2DDataAccess
	{
	public:
		Coordinate2DDataAccess(); 
		Coordinate2DDataAccess( double x, double y );
		
		//Get
		double getX() const { return x_; }
		double getY() const { return y_; }
		
		//Set
		void setX( double x ) { x_ = x; }
		void setY( double y ) { y_ = y; }
		
	private:
		double x_;
		double y_;
		
	};
	
}

#endif
