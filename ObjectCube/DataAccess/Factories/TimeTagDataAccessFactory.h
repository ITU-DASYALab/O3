/*
 *  TimeTagDataAccessFactory.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 10.4.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_TIME_TAG_DATA_ACCESS_FACTORY_
#define ObjectCube_TIME_TAG_DATA_ACCESS_FACTORY_

namespace ObjectCube
{
	class TimeTagDataAccess;
	
	class TimeTagDataAccessFactory
	{
	public:
		static TimeTagDataAccess* create();
	};
	
}

#endif