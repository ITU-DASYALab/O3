/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/


#ifndef ObjectCube_TAG_FILTER_CONVERTER_
#define ObjectCube_TAG_FILTER_CONVERTER_

#include <memory>

#include "FilterConverter.h"

namespace ObjectCube 
{	
	class FilterDataAccess;
	
	class TagFilterConverter : public FilterConverter
	{
	protected:
		virtual unique_ptr<FilterDataAccess> logicToDataAccess_( const Filter* filter );
		
	};
}

#endif