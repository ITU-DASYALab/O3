/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/

#include "FilterConverterFactory.h"

#include <sstream>

#include "../LayerShared/FilterCommon.h"
#include "FilterConverter.h"
#include "TagFilterConverter.h"
#include "DimensionFilterConverter.h"
#include "NumericalRangeFilterConverter.h"
#include "DateRangeFilterConverter.h"
#include "TimeRangeFilterConverter.h"
#include "../LayerShared/Exception.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

FilterConverter* FilterConverterFactory::create( int filterTypeId )
{
	switch ( filterTypeId  ) 
	{
		case FilterCommon::TAG_FILTER :
			return new TagFilterConverter();
		case FilterCommon::DIMENSION_FILTER :
			return new DimensionFilterConverter();
		case FilterCommon::NUMERICAL_RANGE_FILTER :
			return new NumericalRangeFilterConverter();
		case FilterCommon::DATE_RANGE_FILTER :
			return new DateRangeFilterConverter();
		case FilterCommon::TIME_RANGE_FILTER :
			return new TimeRangeFilterConverter();
		default:
			stringstream stringStream;
			stringStream << "Unknown filter type: " << filterTypeId;
			throw Exception( "FilterConverterFactory::create", stringStream.str() );
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________
