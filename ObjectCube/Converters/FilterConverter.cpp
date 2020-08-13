/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/

#include "FilterConverter.h"

#include "../DataAccess/Root/FilterDataAccess.h"
#include "../DataAccess/Factories/FilterDataAccessFactory.h"
#include "../Filters/FilterFactory.h"
#include "FilterConverterFactory.h"


using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

unique_ptr<FilterDataAccess> FilterConverter::logicToDataAccess( const Filter* filter )
{
	unique_ptr<FilterConverter> converter( FilterConverterFactory::create( filter->getTypeId()) );
	return converter->logicToDataAccess_( filter );
}
//____________________________________________________________________________________________________________________________________________________________________________________

vector<FilterDataAccess*> FilterConverter::logicToDataAccess( const vector<Filter*>& filters )
{
	vector<FilterDataAccess*> filtersDA;
	for( vector<Filter*>::const_iterator itr = filters.begin(); itr != filters.end(); ++itr )
	{
		filtersDA.push_back( FilterConverter::logicToDataAccess( (*itr) ).release() );
	}
	return filtersDA;}
//____________________________________________________________________________________________________________________________________________________________________________________

unique_ptr<FilterDataAccess> FilterConverter::logicToDataAccess_( const Filter* filter )
{
	unique_ptr<FilterDataAccess> filterDA( FilterDataAccessFactory::create( filter->getTypeId() ) );
	
	filterDA->setId( filter->getId() );
	filterDA->setTypeId( filter->getTypeId() );
	filterDA->setTagSetId( filter->getTagSetId() );
	filterDA->setNullStatus( filter->isNull() );
	
	return filterDA;
}
//____________________________________________________________________________________________________________________________________________________________________________________

