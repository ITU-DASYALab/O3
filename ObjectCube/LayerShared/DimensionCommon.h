/*
 *  DimensionCommon.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 25.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_DIMENSION_COMMON_
#define ObjectCube_DIMENSION_COMMON_

namespace ObjectCube
{
	
	class DimensionCommon
	{
	public:
		DimensionCommon() {;}
		virtual ~DimensionCommon() {;}
		
		enum TYPE 
		{
			PERSISTENT = 1,
			VIRTUAL = 2,
			DEFAULT = 3
		};
				
	};
	
}

#endif
