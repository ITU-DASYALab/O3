/*
 *  NumericalTagDataAccessFactory.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 27.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_NUMERICAL_TAG_DATA_ACCESS_FACTORY_
#define ObjectCube_NUMERICAL_TAG_DATA_ACCESS_FACTORY_

namespace ObjectCube
{
	class NumericalTagDataAccess;
	
	class NumericalTagDataAccessFactory
	{
	public:
		static NumericalTagDataAccess* create();
	};
	
}

#endif