/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2011. All rights reserved.
 **********************************************************************/

#ifndef ObjectCube_OBJECT_TAG_DATA_ACCESS_FACTORY_
#define ObjectCube_OBJECT_TAG_DATA_ACCESS_FACTORY_

namespace ObjectCube
{
	class ObjectTagDataAccess;
	
	class ObjectTagDataAccessFactory
	{
	public:
		static ObjectTagDataAccess* create();
	};
	
}

#endif
