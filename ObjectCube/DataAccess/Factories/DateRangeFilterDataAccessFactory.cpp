/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/

#include "DateRangeFilterDataAccessFactory.h"

#include <sstream>

#include "../Root/DateRangeFilterDataAccess.h"
//#include "../Canned/DateRangeFilterCanned.h"
//#include "../SQLite/DateRangeFilterSQLite.h"
//#include "../MonetDB/DateRangeFilterMonetDB.h"
//#include "../Oracle/DateRangeFilterOracle.h"
#include "../PostgreSQL/DateRangeFilterPostgreSQL.h"

#include "../../LayerShared/HubCommon.h"
#include "../../LayerShared/Exception.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

DateRangeFilterDataAccess* DateRangeFilterDataAccessFactory::create()
{
	switch ( HubCommon::getDataAccessType() ) 
	{
	#ifdef OC_CANNED
		case HubCommon::CANNED :
			return new DateRangeFilterCanned();
	#endif
	#ifdef OC_SQLITE
		case HubCommon::SQLITE :
			return new DateRangeFilterSQLite();
	#endif
		
	#ifdef OC_MONETDB
		case HubCommon::MONETDB :
			return new DateRangeFilterMonetDB();
	#endif
			
	#ifdef OC_ORACLE
		case HubCommon::ORACLE :
			return new DateRangeFilterOracle();
	#endif

	#ifdef OC_POSTGRESQL
		case HubCommon::POSTGRESQL :
			return new DateRangeFilterPostgreSQL(); 
	#endif
			
		default:
			stringstream stringStream;
			stringStream << "Unknown data access type: " << HubCommon::getDataAccessType();
			throw Exception( "DateRangeFilterDataAccessFactory::create", stringStream.str() );
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________