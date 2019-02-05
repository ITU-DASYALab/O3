/*
 *  TagFactory.h
 *  Prada
 *
 *  Created by Grímur Tómasson on 6.2.2010.
 *  Copyright 2010 RU. All rights reserved.
 *
 */

#ifndef ObjectCube_TAG_DATA_ACCESS_FACTORY_
#define ObjectCube_TAG_DATA_ACCESS_FACTORY_

namespace ObjectCube
{
	class TagDataAccess;

	class TagDataAccessFactory
	{
	public:
		static TagDataAccess* create();
		static TagDataAccess* create( int tagTypeId );
	};

}

#endif