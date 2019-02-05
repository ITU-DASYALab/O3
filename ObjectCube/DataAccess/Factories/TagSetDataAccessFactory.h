/*
 *  TagSetDataAccessFactory.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 9.2.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_TAG_SET_DATA_ACCESS_FACTORY_
#define ObjectCube_TAG_SET_DATA_ACCESS_FACTORY_

namespace ObjectCube
{
	class TagSetDataAccess;
	
	class TagSetDataAccessFactory
	{
	public:
		static TagSetDataAccess* create();
	};
	
}

#endif