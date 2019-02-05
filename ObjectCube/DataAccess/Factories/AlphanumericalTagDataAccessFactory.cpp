/*
 *  AlphanumericalTagDataAccessFactory.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 22.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "AlphanumericalTagDataAccessFactory.h"

#include <sstream>

#include "../Root/AlphanumericalTagDataAccess.h"
//#include "../Canned/AlphanumericalTagCanned.h"
//#include "../SQLite/AlphanumericalTagSQLite.h"
//#include "../MonetDB/AlphanumericalTagMonetDB.h"
//#include "../Oracle/AlphanumericalTagOracle.h"
#include "../PostgreSQL/AlphanumericalTagPostgreSQL.h"


#include "../../LayerShared/HubCommon.h"
#include "../../LayerShared/Exception.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

AlphanumericalTagDataAccess* AlphanumericalTagDataAccessFactory::create()
{
	switch ( HubCommon::getDataAccessType() ) 
	{
	#ifdef OC_CANNED
		case HubCommon::CANNED :
			return new AlphanumericalTagCanned();
	#endif
	#ifdef OC_SQLITE
		case HubCommon::SQLITE :
			return new AlphanumericalTagSQLite();
	#endif
		
	#ifdef OC_MONETDB
		case HubCommon::MONETDB :
			return new AlphanumericalTagMonetDB();
	#endif
		
	#ifdef OC_ORACLE
		case HubCommon::ORACLE :
			return new AlphanumericalTagOracle();
	#endif

	#ifdef OC_POSTGRESQL
		case HubCommon::POSTGRESQL :
			return new AlphanumericalTagPostgreSQL(); 
	#endif		
			
		default:
			stringstream stringStream;
			stringStream << "Unknown data access type: " << HubCommon::getDataAccessType();
			throw Exception( "AlphanumericalTagDataAccessFactory::create", stringStream.str() );
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________