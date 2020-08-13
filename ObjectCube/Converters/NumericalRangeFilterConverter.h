/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/


#ifndef ObjectCube_NUMERICAL_RANGE_FILTER_CONVERTER_
#define ObjectCube_NUMERICAL_RANGE_FILTER_CONVERTER_

#include <memory>

#include "FilterConverter.h"

namespace ObjectCube 
{	
	class FilterDataAccess;
	
	class NumericalRangeFilterConverter : public FilterConverter
	{
	protected:
		virtual unique_ptr<FilterDataAccess> logicToDataAccess_( const Filter* filter );
		
	};
}

#endif