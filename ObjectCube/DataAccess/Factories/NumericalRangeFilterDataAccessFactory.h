/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/


#ifndef ObjectCube_NUMERICAL_RANGE_FILTER_DATA_ACCESS_FACTORY_
#define ObjectCube_NUMERICAL_RANGE_FILTER_DATA_ACCESS_FACTORY_

namespace ObjectCube
{
	class NumericalRangeFilterDataAccess;
	
	class NumericalRangeFilterDataAccessFactory
	{
	public:
		static NumericalRangeFilterDataAccess* create();
	};
	
}

#endif