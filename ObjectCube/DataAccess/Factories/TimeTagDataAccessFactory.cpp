/*
 *  TimeTagDataAccessFactory.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 10.4.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "TimeTagDataAccessFactory.h"

#include <sstream>

#include "../Root/TimeTagDataAccess.h"
//#include "../Canned/TimeTagCanned.h"
//#include "../SQLite/TimeTagSQLite.h"
//#include "../MonetDB/TimeTagMonetDB.h"
//#include "../Oracle/TimeTagOracle.h"
#include "../PostgreSQL/TimeTagPostgreSQL.h"

#include "../../LayerShared/HubCommon.h"
#include "../../LayerShared/Exception.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

TimeTagDataAccess* TimeTagDataAccessFactory::create()
{
	switch ( HubCommon::getDataAccessType() ) 
	{
	#ifdef OC_CANNED
		case HubCommon::CANNED :
			return new TimeTagCanned();
	#endif
			
	#ifdef OC_SQLITE
		case HubCommon::SQLITE :
			return new TimeTagSQLite();
	#endif
		
	#ifdef OC_MONETDB
		case HubCommon::MONETDB :
			return new TimeTagMonetDB();
	#endif
	
	#ifdef OC_ORACLE
		case HubCommon::ORACLE :
			return new TimeTagOracle();
	#endif

	#ifdef OC_POSTGRESQL
		case HubCommon::POSTGRESQL :
			return new TimeTagPostgreSQL(); 
	#endif			
			
		default:
			stringstream stringStream;
			stringStream << "Unknown data access type: " << HubCommon::getDataAccessType();
			throw Exception( "TimeTagDataAccessFactory::create", stringStream.str() );
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________