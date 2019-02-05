/*
 *  FilterFactory.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 27.4.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_FILTER_FACTORY_
#define ObjectCube_FILTER_FACTORY_

namespace ObjectCube
{
	class Filter;
	
	class FilterFactory
	{
	public:
		static Filter* create( int filterType );
	};
	
}

#endif