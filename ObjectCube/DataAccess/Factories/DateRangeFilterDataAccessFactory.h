/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/


#ifndef ObjectCube_DATE_RANGE_FILTER_DATA_ACCESS_FACTORY_
#define ObjectCube_DATE_RANGE_FILTER_DATA_ACCESS_FACTORY_

namespace ObjectCube
{
	class DateRangeFilterDataAccess;
	
	class DateRangeFilterDataAccessFactory
	{
	public:
		static DateRangeFilterDataAccess* create();
	};
	
}

#endif