/*
 *  DimensionDataAccessFactory.cpp
 *  Prada
 *
 *  Created by Grímur Tómasson on 8.2.2010.
 *  Copyright 2010 RU. All rights reserved.
 *
 */

#include "DimensionDataAccessFactory.h"

#include <sstream>

#include "../Root/DimensionDataAccess.h" 
//#include "../Canned/DimensionCanned.h" 
//#include "../SQLite/DimensionSQLite.h" 
//#include "../MonetDB/DimensionMonetDB.h"
//#include "../Oracle/DimensionOracle.h"
#include "../PostgreSQL/DimensionPostgreSQL.h"

#include "../../LayerShared/HubCommon.h" 
#include "../../LayerShared/Exception.h" 

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

DimensionDataAccess* DimensionDataAccessFactory::create()
{
	switch ( HubCommon::getDataAccessType() ) 
	{
	#ifdef OC_CANNED
		case HubCommon::CANNED :
			return new DimensionCanned();
	#endif
			
	#ifdef OC_SQLITE
		case HubCommon::SQLITE :
			return new DimensionSQLite();
	#endif

	#ifdef OC_MONETDB
		case HubCommon::MONETDB :
			return new DimensionMonetDB();
	#endif
			
	#ifdef OC_ORACLE
		case HubCommon::ORACLE :
			return new DimensionOracle();
	#endif

	#ifdef OC_POSTGRESQL
		case HubCommon::POSTGRESQL :
			return new DimensionPostgreSQL();
	#endif
			
		default:
			stringstream stringStream;
			stringStream << "Unknown data access type: " << HubCommon::getDataAccessType();
			throw Exception( "DimensionDataAccessFactory::create", stringStream.str() );
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________