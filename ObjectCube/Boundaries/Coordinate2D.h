/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/


#ifndef ObjectCube_COORDINATE2D_
#define ObjectCube_COORDINATE2D_

namespace ObjectCube 
{
	
	class Coordinate2D
	{
	public:
		Coordinate2D();
		Coordinate2D( double x, double y );
		
		//Get
		double getX() const { return x_; }
		double getY() const { return y_; }
		
		//Set
		void setX( double x ) { x_ = x; }
		void setY( double y ) { y_ = y; }
		
		bool operator==( const Coordinate2D& x ) const;
		
	private:
		double x_;
		double y_;
		
	};

}

#endif
