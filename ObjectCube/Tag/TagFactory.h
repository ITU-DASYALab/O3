/*
 *  TagFactory.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 20.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_TAG_FACTORY_
#define ObjectCube_TAG_FACTORY_

namespace ObjectCube
{
	class Tag;
	
	class TagFactory
	{
	public:
		static Tag* create( int tagType );
	};
	
}

#endif