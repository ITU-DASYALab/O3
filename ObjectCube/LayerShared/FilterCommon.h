/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/

#ifndef ObjectCube_FILTER_COMMON_
#define ObjectCube_FILTER_COMMON_

namespace ObjectCube
{
	
	class FilterCommon
	{
	public:
		FilterCommon() {;}
		virtual ~FilterCommon() {;}
		
		enum TYPE
		{
			NOT_SET = 0,
			TAG_FILTER = 1,
			DIMENSION_FILTER = 2,
			NUMERICAL_RANGE_FILTER = 3,
			TIME_RANGE_FILTER = 4,
			DATE_RANGE_FILTER = 5
		};
				
	};
	
}

#endif