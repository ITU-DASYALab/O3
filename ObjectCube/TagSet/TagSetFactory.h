/*
 *  TagSetFactory.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 9.11.2009.
 *  Copyright 2009 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_TAG_SET_FACTORY_
#define ObjectCube_TAG_SET_FACTORY_

namespace ObjectCube
{
	class TagSet;
	
	class TagSetFactory
	{
	public:
		static TagSet* create( int tagSetType );
	};
	
}

#endif