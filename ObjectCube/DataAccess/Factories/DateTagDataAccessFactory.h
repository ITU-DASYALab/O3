/*
 *  DateTagDataAccessFactory.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 10.4.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_DATE_TAG_DATA_ACCESS_FACTORY_
#define ObjectCube_DATE_TAG_DATA_ACCESS_FACTORY_

namespace ObjectCube
{
	class DateTagDataAccess;
	
	class DateTagDataAccessFactory
	{
	public:
		static DateTagDataAccess* create();
	};
	
}

#endif