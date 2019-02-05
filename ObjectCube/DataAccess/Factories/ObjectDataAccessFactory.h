/*
 *  ObjectDataAccessFactory.h
 *  Prada
 *
 *  Created by Grímur Tómasson on 8.2.2010.
 *  Copyright 2010 RU. All rights reserved.
 *
 */

#ifndef ObjectCube_OBJECTDATAACCESSFACTORY_
#define ObjectCube_OBJECTDATAACCESSFACTORY_

namespace ObjectCube
{
	class ObjectDataAccess;
	
	class ObjectDataAccessFactory
	{
	public:
		static ObjectDataAccess* create();
	};
	
}

#endif
