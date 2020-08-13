/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/

#include "NumericalRangeFilterConverter.h"

#include "../Filters/NumericalRangeFilter.h"
#include "../DataAccess/Root/NumericalRangeFilterDataAccess.h"
#include "../DataAccess/Factories/NumericalRangeFilterDataAccessFactory.h"
#include "../LayerShared/Exception.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

unique_ptr<FilterDataAccess> NumericalRangeFilterConverter::logicToDataAccess_( const Filter* filter )
{
	
	unique_ptr<NumericalRangeFilterDataAccess> filterDA( dynamic_cast<NumericalRangeFilterDataAccess*>( FilterConverter::logicToDataAccess_( filter ).release() ) );
	
	const NumericalRangeFilter* nrFilter = dynamic_cast<const NumericalRangeFilter*> ( filter );
	if( !nrFilter )
	{
		throw Exception( "NumericalRangeFilterConverter","Failure to cast Filter -> NumericalRangeFilter" );
	}
	
	filterDA->numberFrom_ = nrFilter->getNumberFrom();
	filterDA->numberTo_ = nrFilter->getNumberTo();
	filterDA->numberFromIsNull_ = nrFilter->numberFromIsNull_;
	filterDA->numberToIsNull_ = nrFilter->numberToIsNull_;
	
	return unique_ptr<FilterDataAccess>( filterDA.release() );
}
//____________________________________________________________________________________________________________________________________________________________________________________
