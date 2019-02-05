/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/

#include "FilterDataAccessFactory.h"

#include "TagFilterDataAccessFactory.h"
#include "DimensionFilterDataAccessFactory.h"
#include "NumericalRangeFilterDataAccessFactory.h"
#include "DateRangeFilterDataAccessFactory.h"
#include "TimeRangeFilterDataAccessFactory.h"

#include <sstream>

#include "../../LayerShared/HubCommon.h"
#include "../../LayerShared/Exception.h"
#include "../../LayerShared/FilterCommon.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

FilterDataAccess* FilterDataAccessFactory::create( int filterTypeId  )
{
	switch ( filterTypeId ) 
	{
		case FilterCommon::TAG_FILTER :
			return reinterpret_cast<FilterDataAccess*>( TagFilterDataAccessFactory::create() );
		case FilterCommon::DIMENSION_FILTER :
			return reinterpret_cast<FilterDataAccess*>( DimensionFilterDataAccessFactory::create() );
		case FilterCommon::NUMERICAL_RANGE_FILTER :
			return reinterpret_cast<FilterDataAccess*>( NumericalRangeFilterDataAccessFactory::create() );
		case FilterCommon::DATE_RANGE_FILTER :
			return reinterpret_cast<FilterDataAccess*>( DateRangeFilterDataAccessFactory::create() );
		case FilterCommon::TIME_RANGE_FILTER :
			return reinterpret_cast<FilterDataAccess*>( TimeRangeFilterDataAccessFactory::create() );
		default:
			ostringstream stringstream;
			stringstream << "Unknown filter type: " << filterTypeId;
			throw Exception("FilterDataAccessFactory::create", stringstream.str() );
	}
	
}
//____________________________________________________________________________________________________________________________________________________________________________________