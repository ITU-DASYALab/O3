/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/

#include "TagFilterDataAccessFactory.h"

#include <sstream>

#include "../Root/TagFilterDataAccess.h"
//#include "../Canned/TagFilterCanned.h"
//#include "../SQLite/TagFilterSQLite.h"
//#include "../MonetDB/TagFilterMonetDB.h"
//#include "../Oracle/TagFilterOracle.h"
#include "../PostgreSQL/TagFilterPostgreSQL.h"

#include "../../LayerShared/HubCommon.h"
#include "../../LayerShared/Exception.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

TagFilterDataAccess* TagFilterDataAccessFactory::create()
{
	switch ( HubCommon::getDataAccessType() ) 
	{
	#ifdef OC_CANNED
		case HubCommon::CANNED :
			return new TagFilterCanned();
	#endif
	
	#ifdef OC_SQLITE
		case HubCommon::SQLITE :
			return new TagFilterSQLite();
	#endif
			
	#ifdef OC_MONETDB
		case HubCommon::MONETDB :
			return new TagFilterMonetDB();
	#endif			
		
	#ifdef OC_ORACLE
		case HubCommon::ORACLE :
			return new TagFilterOracle();
	#endif

	#ifdef OC_POSTGRESQL
		case HubCommon::POSTGRESQL :
			return new TagFilterPostgreSQL(); 
	#endif
			
		default:
			stringstream stringStream;
			stringStream << "Unknown data access type: " << HubCommon::getDataAccessType();
			throw Exception( "TagFilterDataAccessFactory::create", stringStream.str() );
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________