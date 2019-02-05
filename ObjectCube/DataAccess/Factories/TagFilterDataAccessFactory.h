/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/


#ifndef ObjectCube_TAG_FILTER_DATA_ACCESS_FACTORY_
#define ObjectCube_TAG_FILTER_DATA_ACCESS_FACTORY_

namespace ObjectCube
{
	class TagFilterDataAccess;
	
	class TagFilterDataAccessFactory
	{
	public:
		static TagFilterDataAccess* create();
	};
	
}

#endif