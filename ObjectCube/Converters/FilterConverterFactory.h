/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/


#ifndef ObjectCube_FILTER_CONVERTER_FACTORY_
#define ObjectCube_FILTER_CONVERTER_FACTORY_


namespace ObjectCube
{
	class FilterConverter;
	
	class FilterConverterFactory
	{
	public:
		static FilterConverter* create( int filterTypeId );
	};
	
}
#endif