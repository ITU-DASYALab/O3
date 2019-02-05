/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/


#ifndef ObjectCube_TIME_RANGE_FILTER_DATA_ACCESS_FACTORY_
#define ObjectCube_TIME_RANGE_FILTER_DATA_ACCESS_FACTORY_

namespace ObjectCube
{
	class TimeRangeFilterDataAccess;
	
	class TimeRangeFilterDataAccessFactory
	{
	public:
		static TimeRangeFilterDataAccess* create();
	};
	
}

#endif