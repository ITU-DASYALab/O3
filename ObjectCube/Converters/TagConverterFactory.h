/*
 *  TagConverterFactory.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 29.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_TAG_CONVERTER_FACTORY_
#define ObjectCube_TAG_CONVERTER_FACTORY_


#include "TagConverter.h"

namespace ObjectCube
{
	class TagConverter;
	
	class TagConverterFactory
	{
	public:
		static TagConverter* create( int tagTypeId );
	};
	
}
#endif