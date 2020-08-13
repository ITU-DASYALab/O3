/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/


#ifndef ObjectCube_DIMENSION_FILTER_CONVERTER_
#define ObjectCube_DIMENSION_FILTER_CONVERTER_

#include <memory>

#include "FilterConverter.h"

namespace ObjectCube 
{	
	class FilterDataAccess;
	
	class DimensionFilterConverter : public FilterConverter
	{
	protected:
		virtual unique_ptr<FilterDataAccess> logicToDataAccess_( const Filter* filter );
		
	};
}

#endif