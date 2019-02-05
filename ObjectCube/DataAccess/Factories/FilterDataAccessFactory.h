/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/


#ifndef ObjectCube_FILTER_DATA_ACCESS_FACTORY_
#define ObjectCube_FILTER_DATA_ACCESS_FACTORY_

namespace ObjectCube
{
	class FilterDataAccess;
	
	class FilterDataAccessFactory
	{
	public:
		static FilterDataAccess* create( int filterTypeId );
	};
	
}

#endif