/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/

#include "DimensionFilterConverter.h"

#include "../Filters/DimensionFilter.h"
#include "../LayerShared/Exception.h"
#include "../DataAccess/Root/DimensionFilterDataAccess.h"
#include "../DataAccess/Factories/DimensionFilterDataAccessFactory.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

unique_ptr<FilterDataAccess> DimensionFilterConverter::logicToDataAccess_( const Filter* filter )
{
	unique_ptr<DimensionFilterDataAccess> filterDA( dynamic_cast<DimensionFilterDataAccess*>( FilterConverter::logicToDataAccess_( filter ).release() ) );
		
	const DimensionFilter* dFilter = dynamic_cast<const DimensionFilter*> ( filter );
	if( !dFilter )
	{
		throw Exception( "DimensionFilterConverter","Failure to cast Filter -> DimensionFilter" );
	}
	
	filterDA->setTagAndDimensionNodeIds( dFilter->getTagAndDimensionNodeIds() );
	filterDA->setDimensionId( dFilter->getDimensionId() );
	filterDA->setLeftBorder( dFilter->getLeftBorder() );
	filterDA->setRightBorder( dFilter->getRightBorder() );
	filterDA->setDimensionTypeId( dFilter->getDimensionTypeId() );
	
	return unique_ptr<FilterDataAccess>( filterDA.release() );
}
//____________________________________________________________________________________________________________________________________________________________________________________
