/*
 *  DimensionDataAccessFactory.h
 *  Prada
 *
 *  Created by Grímur Tómasson on 8.2.2010.
 *  Copyright 2010 RU. All rights reserved.
 *
 */

#ifndef ObjectCube_DIMENSION_DATA_ACCESS_FACTORY_
#define ObjectCube_DIMENSION_DATA_ACCESS_FACTORY_

namespace ObjectCube
{
	class DimensionDataAccess;
	
	class DimensionDataAccessFactory
	{
	public:
		static DimensionDataAccess* create();
	};
	
}

#endif