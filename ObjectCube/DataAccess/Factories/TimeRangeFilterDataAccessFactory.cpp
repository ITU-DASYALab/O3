/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/

#include "TimeRangeFilterDataAccessFactory.h"

#include <sstream>

#include "../Root/TimeRangeFilterDataAccess.h"
//#include "../Canned/TimeRangeFilterCanned.h"
//#include "../SQLite/TimeRangeFilterSQLite.h"
//#include "../MonetDB/TimeRangeFilterMonetDB.h"
//#include "../Oracle/TimeRangeFilterOracle.h"
#include "../PostgreSQL/TimeRangeFilterPostgreSQL.h"

#include "../../LayerShared/HubCommon.h"
#include "../../LayerShared/Exception.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

TimeRangeFilterDataAccess* TimeRangeFilterDataAccessFactory::create()
{
	switch ( HubCommon::getDataAccessType() ) 
	{
	#ifdef OC_CANNED
		case HubCommon::CANNED :
			return new TimeRangeFilterCanned();
	#endif
	#ifdef OC_SQLITE
		case HubCommon::SQLITE :
			return new TimeRangeFilterSQLite();
	#endif
		
	#ifdef OC_MONETDB
		case HubCommon::MONETDB :
			return new TimeRangeFilterMonetDB();
	#endif
			
	#ifdef OC_ORACLE
		case HubCommon::ORACLE :
			return new TimeRangeFilterOracle();
	#endif

	#ifdef OC_POSTGRESQL
		case HubCommon::POSTGRESQL :
			return new TimeRangeFilterPostgreSQL(); 
	#endif
			
		default:
			stringstream stringStream;
			stringStream << "Unknown data access type: " << HubCommon::getDataAccessType();
			throw Exception( "TimeRangeFilterDataAccessFactory::create", stringStream.str() );
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________