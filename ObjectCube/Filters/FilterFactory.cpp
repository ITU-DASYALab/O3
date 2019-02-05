/*
 *  FilterFactory.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 27.4.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "FilterFactory.h"

#include <sstream>

#include "Filter.h"

#include "TagFilter.h"
#include "DimensionFilter.h"
#include "NumericalRangeFilter.h"
#include "DateRangeFilter.h"
#include "TimeRangeFilter.h"

#include "../LayerShared/Exception.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

Filter* FilterFactory::create( int filterType)
{
	switch ( filterType ) 
	{
		case Filter::TAG_FILTER :
			return new TagFilter();
		case Filter::DIMENSION_FILTER :
			return new DimensionFilter();
		case Filter::NUMERICAL_RANGE_FILTER :
			return new NumericalRangeFilter();
		case Filter::DATE_RANGE_FILTER :
			return new DateRangeFilter();
		case Filter::TIME_RANGE_FILTER :
			return new TimeRangeFilter();
		default:
			
			ostringstream stringstream;
			stringstream << "Unknown filter type: " << filterType;
			throw Exception("FilterFactory::create", stringstream.str() );
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________