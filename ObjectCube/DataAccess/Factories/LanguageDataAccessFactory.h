/*
 *  LanguageDataAccessFactory.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 8.7.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_LANGUAGE_DATA_ACCESS_FACTORY_
#define ObjectCube_LANGUAGE_DATA_ACCESS_FACTORY_

namespace ObjectCube
{
	class LanguageDataAccess;
	
	class LanguageDataAccessFactory
	{
	public:
		static LanguageDataAccess* create();
		
	};
	
}

#endif