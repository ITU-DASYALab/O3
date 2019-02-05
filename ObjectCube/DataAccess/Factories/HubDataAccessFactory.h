/*
 *  HubDataAccessFactory.h
 *  Prada
 *
 *  Created by Grímur Tómasson on 8.2.2010.
 *  Copyright 2010 RU. All rights reserved.
 *
 */

#ifndef ObjectCube_HUBDATAACCESSFACTORY_
#define ObjectCube_HUBDATAACCESSFACTORY_

namespace ObjectCube
{
	class HubDataAccess;
	
	class HubDataAccessFactory
	{
	public:
		static HubDataAccess* create();
	};
	
}

#endif