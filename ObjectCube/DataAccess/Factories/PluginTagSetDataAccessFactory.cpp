/*
 *  PluginTagSetDataAccessFactory.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 26.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "PluginTagSetDataAccessFactory.h"

#include <sstream>

#include "../Root/PluginTagSetDataAccess.h"
//#include "../Canned/PluginTagSetCanned.h"
//#include "../SQLite/PluginTagSetSQLite.h"
//#include "../MonetDB/PluginTagSetMonetDB.h"
//#include "../Oracle/PluginTagSetOracle.h"
#include "../PostgreSQL/PluginTagSetPostgreSQL.h"

#include "../../LayerShared/HubCommon.h"
#include "../../LayerShared/Exception.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

PluginTagSetDataAccess* PluginTagSetDataAccessFactory::create()
{
	switch ( HubCommon::getDataAccessType() ) 
	{
	#ifdef OC_CANNED
		case HubCommon::CANNED :
			return new PluginTagSetCanned();
	#endif
			
	#ifdef OC_SQLITE
		case HubCommon::SQLITE :
			return new PluginTagSetSQLite();
	#endif
		
	#ifdef OC_MONETDB
		case HubCommon::MONETDB :
			return new PluginTagSetMonetDB();
	#endif
			
	#ifdef OC_ORACLE
		case HubCommon::ORACLE :
			return new PluginTagSetOracle();
	#endif

	#ifdef OC_POSTGRESQL
		case HubCommon::POSTGRESQL :
			return new PluginTagSetPostgreSQL(); 
	#endif

		default:
			stringstream stringStream;
			stringStream << "Unknown data access type: " << HubCommon::getDataAccessType();
			throw Exception( "PluginTagSetDataAccessFactory::create", stringStream.str() );
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________

