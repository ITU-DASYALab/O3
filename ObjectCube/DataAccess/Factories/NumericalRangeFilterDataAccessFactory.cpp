/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/

#include "NumericalRangeFilterDataAccessFactory.h"

#include <sstream>

#include "../Root/NumericalRangeFilterDataAccess.h"
//#include "../Canned/NumericalRangeFilterCanned.h"
//#include "../SQLite/NumericalRangeFilterSQLite.h"
//#include "../MonetDB/NumericalRangeFilterMonetDB.h"
//#include "../Oracle/NumericalRangeFilterOracle.h"
#include "../PostgreSQL/NumericalRangeFilterPostgreSQL.h"

#include "../../LayerShared/HubCommon.h"
#include "../../LayerShared/Exception.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

NumericalRangeFilterDataAccess* NumericalRangeFilterDataAccessFactory::create()
{
	switch ( HubCommon::getDataAccessType() ) 
	{
	#ifdef OC_CANNED
		case HubCommon::CANNED :
			return new NumericalRangeFilterCanned();
	#endif
			
	#ifdef OC_SQLITE
		case HubCommon::SQLITE :
			return new NumericalRangeFilterSQLite();
	#endif
			
	#ifdef OC_MONETDB
		case HubCommon::MONETDB :
			return new NumericalRangeFilterMonetDB();
	#endif

	#ifdef OC_ORACLE
		case HubCommon::ORACLE :
			return new NumericalRangeFilterOracle();
	#endif

	#ifdef OC_POSTGRESQL
		case HubCommon::POSTGRESQL :
			return new NumericalRangeFilterPostgreSQL(); 
	#endif
			
		default:
			stringstream stringStream;
			stringStream << "Unknown data access type: " << HubCommon::getDataAccessType();
			throw Exception( "NumericalRangeFilterDataAccessFactory::create", stringStream.str() );
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________