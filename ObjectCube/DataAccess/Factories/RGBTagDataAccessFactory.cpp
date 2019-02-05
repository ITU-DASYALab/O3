/*
 *  RGBTagDataAccessFactory.cpp
 *  ObjectCube
 *
 */

#include "RGBTagDataAccessFactory.h"

#include <sstream>

#include "../Root/RGBTagDataAccess.h"
#include "../PostgreSQL/RGBTagPostgreSQL.h"


#include "../../LayerShared/HubCommon.h"
#include "../../LayerShared/Exception.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

RGBTagDataAccess* RGBTagDataAccessFactory::create()
{
	switch ( HubCommon::getDataAccessType() ) 
	{
	#ifdef OC_CANNED
		case HubCommon::CANNED :
			return new RGBTagCanned();
	#endif
	#ifdef OC_SQLITE
		case HubCommon::SQLITE :
			return new RGBTagSQLite();
	#endif
		
	#ifdef OC_MONETDB
		case HubCommon::MONETDB :
			return new RGBTagMonetDB();
	#endif
		
	#ifdef OC_ORACLE
		case HubCommon::ORACLE :
			return new RGBTagOracle();
	#endif

	#ifdef OC_POSTGRESQL
		case HubCommon::POSTGRESQL :
			return new RGBTagPostgreSQL(); 
	#endif		
			
		default:
			stringstream stringStream;
			stringStream << "Unknown data access type: " << HubCommon::getDataAccessType();
			throw Exception( "RGBTagDataAccessFactory::create", stringStream.str() );
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________