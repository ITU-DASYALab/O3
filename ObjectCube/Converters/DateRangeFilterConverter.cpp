/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/

#include "DateRangeFilterConverter.h"

#include "../Filters/DateRangeFilter.h"
#include "../DataAccess/Root/DateRangeFilterDataAccess.h"
#include "../DataAccess/Factories/DateRangeFilterDataAccessFactory.h"
#include "../LayerShared/Exception.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

unique_ptr<FilterDataAccess> DateRangeFilterConverter::logicToDataAccess_( const Filter* filter )
{
	
	unique_ptr<DateRangeFilterDataAccess> filterDA( dynamic_cast<DateRangeFilterDataAccess*>( FilterConverter::logicToDataAccess_( filter ).release() ) );
	
	const DateRangeFilter* drFilter = dynamic_cast<const DateRangeFilter*> ( filter );
	if( !drFilter )
	{
		throw Exception( "DateRangeFilterConverter","Failure to cast Filter -> DateRangeFilter" );
	}

	filterDA->setYearFrom( drFilter->getYearFrom() );
	filterDA->setMonthFrom( drFilter->getMonthFrom() );
	filterDA->setDayOfMonthFrom( drFilter->getDayOfMonthFrom() );
	filterDA->setYearTo( drFilter->getYearTo() );
	filterDA->setMonthTo( drFilter->getMonthTo() );
	filterDA->setDayOfMonthTo( drFilter->getDayOfMonthTo() );
	
	return unique_ptr<FilterDataAccess>( filterDA.release() );
}
//____________________________________________________________________________________________________________________________________________________________________________________
