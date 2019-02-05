/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/


#ifndef ObjectCube_DIMENSION_FACTORY_
#define ObjectCube_DIMENSION_FACTORY_

namespace ObjectCube
{
	class Dimension;
	
	class DimensionFactory
	{
	public:
		static Dimension* create( int typeId );
	};
	
}

#endif