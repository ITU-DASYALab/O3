/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/

#include "DimensionFilterDataAccessFactory.h"

#include <sstream>

#include "../Root/DimensionFilterDataAccess.h"
//#include "../Canned/DimensionFilterCanned.h"
//#include "../SQLite/DimensionFilterSQLite.h"
//#include "../MonetDB/DimensionFilterMonetDB.h"
//#include "../Oracle/DimensionFilterOracle.h"
#include "../PostgreSQL/DimensionFilterPostgreSQL.h"

#include "../../LayerShared/HubCommon.h"
#include "../../LayerShared/Exception.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

DimensionFilterDataAccess* DimensionFilterDataAccessFactory::create()
{
	switch ( HubCommon::getDataAccessType() ) 
	{
	#ifdef OC_CANNED
		case HubCommon::CANNED :
			return new DimensionFilterCanned();
	#endif
	#ifdef OC_SQLITE
		case HubCommon::SQLITE :
			return new DimensionFilterSQLite();
	#endif
				
	#ifdef OC_MONETDB
		case HubCommon::MONETDB :
			return new DimensionFilterMonetDB();
	#endif
	
	#ifdef OC_ORACLE
		case HubCommon::ORACLE :
			return new DimensionFilterOracle();
	#endif

	#ifdef OC_POSTGRESQL
		case HubCommon::POSTGRESQL :
			return new DimensionFilterPostgreSQL();
	#endif			
			
		default:
			stringstream stringStream;
			stringStream << "Unknown data access type: " << HubCommon::getDataAccessType();
			throw Exception( "DimensionFilterDataAccessFactory::create", stringStream.str() );
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________