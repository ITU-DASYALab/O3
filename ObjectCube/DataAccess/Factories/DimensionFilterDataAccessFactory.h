/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/


#ifndef ObjectCube_DIMENSION_FILTER_DATA_ACCESS_FACTORY_
#define ObjectCube_DIMENSION_FILTER_DATA_ACCESS_FACTORY_

namespace ObjectCube
{
	class DimensionFilterDataAccess;
	
	class DimensionFilterDataAccessFactory
	{
	public:
		static DimensionFilterDataAccess* create();
	};
	
}

#endif