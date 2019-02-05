/*
 *  AlphanumericalTagDataAccessFactory.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 22.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_ALPHANUMERICAL_TAG_DATA_ACCESS_FACTORY_
#define ObjectCube_ALPHANUMERICAL_TAG_DATA_ACCESS_FACTORY_

namespace ObjectCube
{
	class AlphanumericalTagDataAccess;
	
	class AlphanumericalTagDataAccessFactory
	{
	public:
		static AlphanumericalTagDataAccess* create();
	};
	
}

#endif