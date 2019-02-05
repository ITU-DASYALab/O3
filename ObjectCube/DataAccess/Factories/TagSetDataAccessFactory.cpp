/*
 *  TagSetDataAccessFactory.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 9.2.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "TagSetDataAccessFactory.h"

#include <sstream>

#include "../Root/TagSetDataAccess.h"
//#include "../Canned/TagSetCanned.h"
//#include "../SQLite/TagSetSQLite.h"
//#include "../MonetDB/TagSetMonetDB.h"
//#include "../Oracle/TagSetOracle.h"
#include "../PostgreSQL/TagSetPostgreSQL.h"

#include "../../LayerShared/HubCommon.h"
#include "../../LayerShared/Exception.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

TagSetDataAccess* TagSetDataAccessFactory::create()
{
	switch ( HubCommon::getDataAccessType() ) 
	{
	#ifdef OC_CANNED
		case HubCommon::CANNED :
			return new TagSetCanned();
	#endif
			
	#ifdef OC_SQLITE
		case HubCommon::SQLITE :
			return new TagSetSQLite();
	#endif
		
	#ifdef OC_MONETDB
		case HubCommon::MONETDB :
			return new TagSetMonetDB();
	#endif
			
	#ifdef OC_ORACLE
		case HubCommon::ORACLE :
			return new TagSetOracle();
	#endif

	#ifdef OC_POSTGRESQL
		case HubCommon::POSTGRESQL :
			return new TagSetPostgreSQL();  
	#endif
			
		default:
			stringstream stringStream;
			stringStream << "Unknown data access type: " << HubCommon::getDataAccessType();
			throw Exception( "TagSetDataAccessFactory::create", stringStream.str() );	
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________