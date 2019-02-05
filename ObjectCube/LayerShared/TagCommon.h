/*
 *  TagCommon.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 20.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_TAG__COMMON_
#define ObjectCube_TAG__COMMON_

namespace ObjectCube
{
	
	class TagCommon
	{
	public:
		TagCommon() {;}
		virtual ~TagCommon() {;}
		
		enum TYPE
		{
			UNKNOWN = 0,
			ALPHANUMERICAL = 1,
			NUMERICAL = 2,
			DATE = 3,
			TIME = 4,
			RGB = 5
		};	
				
	};
	
}

#endif
