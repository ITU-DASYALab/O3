/*
 *  DateTagDataAccessFactory.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 10.4.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "DateTagDataAccessFactory.h"

#include <sstream>

#include "../Root/DateTagDataAccess.h"
//#include "../Canned/DateTagCanned.h"
//#include "../SQLite/DateTagSQLite.h"
//#include "../MonetDB/DateTagMonetDB.h"
//#include "../Oracle/DateTagOracle.h"
#include "../PostgreSQL/DateTagPostgreSQL.h"

#include "../../LayerShared/HubCommon.h"
#include "../../LayerShared/Exception.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

DateTagDataAccess* DateTagDataAccessFactory::create()
{
	switch ( HubCommon::getDataAccessType() ) 
	{
	#ifdef OC_CANNED
		case HubCommon::CANNED :
			return new DateTagCanned();
	#endif
			
	#ifdef OC_SQLITE
		case HubCommon::SQLITE :
			return new DateTagSQLite();
	#endif
			
	#ifdef OC_MONETDB
		case HubCommon::MONETDB :
			return new DateTagMonetDB();
	#endif
			
	#ifdef OC_ORACLE
		case HubCommon::ORACLE :
			return new DateTagOracle();
	#endif

	#ifdef OC_POSTGRESQL
		case HubCommon::POSTGRESQL :
			return new DateTagPostgreSQL(); 
	#endif			
			
		default:
			stringstream stringStream;
			stringStream << "Unknown data access type: " << HubCommon::getDataAccessType();
			throw Exception( "DateTagDataAccessFactory::create", stringStream.str() );
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________