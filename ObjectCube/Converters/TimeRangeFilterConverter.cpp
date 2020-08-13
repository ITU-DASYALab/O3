/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/

#include "TimeRangeFilterConverter.h"

#include "../Filters/TimeRangeFilter.h"
#include "../DataAccess/Root/TimeRangeFilterDataAccess.h"
#include "../DataAccess/Factories/TimeRangeFilterDataAccessFactory.h"
#include "../LayerShared/Exception.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

unique_ptr<FilterDataAccess> TimeRangeFilterConverter::logicToDataAccess_( const Filter* filter )
{
	
	unique_ptr<TimeRangeFilterDataAccess> filterDA( dynamic_cast<TimeRangeFilterDataAccess*>( FilterConverter::logicToDataAccess_( filter ).release() ) );
	
	
	const TimeRangeFilter* trFilter = dynamic_cast<const TimeRangeFilter*> ( filter );
	if( !trFilter )
	{
		throw Exception( "TimeRangeFilterConverter","Failure to cast Filter -> TimeRangeFilter" );
	}

	filterDA->setHoursFrom( trFilter->getHoursFrom() );
	filterDA->setMinutesFrom( trFilter->getMinutesFrom() );
	filterDA->setSecondsFrom( trFilter->getSecondsFrom() );
	filterDA->setMillisecondsFrom( trFilter->getMillisecondsFrom() );
		
	filterDA->setHoursTo( trFilter->getHoursTo() );
	filterDA->setMinutesTo( trFilter->getMinutesTo() );
	filterDA->setSecondsTo( trFilter->getSecondsTo() );
	filterDA->setMillisecondsTo( trFilter->getMillisecondsTo() );
	
	return unique_ptr<FilterDataAccess>( filterDA.release() );
}
//____________________________________________________________________________________________________________________________________________________________________________________
