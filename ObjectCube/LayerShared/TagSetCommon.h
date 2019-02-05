/*
 *  DimensionCommon.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 17.2.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_TAG_SET_COMMON_
#define ObjectCube_TAG_SET_COMMON_

namespace ObjectCube
{
	
	class TagSetCommon
	{
	public:
		TagSetCommon() {;}
		virtual ~TagSetCommon() {;}
		
		
		enum TYPE
		{
			TYPE_UNKOWN = 0,
			ALPHANUMERICAL = 1,
			NUMERICAL = 2,
			DATE = 3,
			TIME = 4,
			RGB = 5
		};
		
		enum ACCESS_TYPE
		{
			ACCESS_TYPE_UNKNOWN = 0,
			SYSTEM = 1,
			USER = 2
		};
		
	};
	
}

#endif
