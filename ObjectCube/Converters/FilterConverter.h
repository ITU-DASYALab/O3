/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/


#ifndef ObjectCube_FILTER_CONVERTER_
#define ObjectCube_FILTER_CONVERTER_

#include <vector>
#include <memory>

#include "../Filters/Filter.h"

namespace ObjectCube 
{	
	class FilterDataAccess;
	
	class FilterConverter
	{
	public:
		static unique_ptr<FilterDataAccess> logicToDataAccess( const Filter* filter );
		static vector<FilterDataAccess*> logicToDataAccess( const vector<Filter*>& filters );
		
	protected:
		virtual unique_ptr<FilterDataAccess> logicToDataAccess_( const Filter* filter ) = 0;
		
	};
}

#endif