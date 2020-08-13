/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/

#include "TagFilterConverter.h"

#include "../Filters/TagFilter.h"
#include "../DataAccess/Root/TagFilterDataAccess.h"
#include "../DataAccess/Factories/TagFilterDataAccessFactory.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

unique_ptr<FilterDataAccess> TagFilterConverter::logicToDataAccess_( const Filter* filter )
{
	unique_ptr<TagFilterDataAccess> filterDA( dynamic_cast<TagFilterDataAccess*>( FilterConverter::logicToDataAccess_( filter ).release() ) );
	filterDA->setTagId( dynamic_cast<const TagFilter*>( filter )->getTagId() );
	
	return unique_ptr<FilterDataAccess>( filterDA.release() );
}
//____________________________________________________________________________________________________________________________________________________________________________________
