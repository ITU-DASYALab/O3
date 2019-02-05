/*
 *  SearchDataAccessFactory.cpp
 *
 */

#include "SearchDataAccessFactory.h"

#include <sstream>

#include "../Root/SearchDataAccess.h"
#include "../PostgreSQL/SearchPostgreSQL.h"

#include "../../LayerShared/HubCommon.h"
#include "../../LayerShared/Exception.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

SearchDataAccess* SearchDataAccessFactory::create()
{
	switch ( HubCommon::getDataAccessType() ) 
	{
	#ifdef OC_POSTGRESQL
		case HubCommon::POSTGRESQL :
			return new SearchPostgreSQL(); 
	#endif
			
		default:
			stringstream stringStream;
			stringStream << "Unknown data access type: " << HubCommon::getDataAccessType();
			throw Exception( "SearchDataAccessFactory::create", stringStream.str() );
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________