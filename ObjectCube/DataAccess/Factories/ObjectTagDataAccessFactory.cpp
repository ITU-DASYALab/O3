/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2011. All rights reserved.
 **********************************************************************/

#include "ObjectTagDataAccessFactory.h"

#include <sstream>

#include "../Root/ObjectTagDataAccess.h"
//#include "../SQLite/ObjectTagSQLite.h"
//#include "../MonetDB/ObjectTagMonetDB.h"
#include "../PostgreSQL/ObjectTagPostgreSQL.h"


#include "../../LayerShared/HubCommon.h"
#include "../../LayerShared/Exception.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

ObjectTagDataAccess* ObjectTagDataAccessFactory::create()
{
	switch ( HubCommon::getDataAccessType() ) 
	{

/*
#ifdef OC_SQLITE
		case HubCommon::SQLITE :
			return new ObjectTagSQLite();
#endif
*/
			
	#ifdef OC_MONETDB
			case HubCommon::MONETDB :
				return new ObjectTagMonetDB();
	#endif

	#ifdef OC_POSTGRESQL
		case HubCommon::POSTGRESQL :
			return new ObjectTagPostgreSQL(); 
	#endif
			
		default:
			stringstream stringStream;
			stringStream << "Unknown data access type: " << HubCommon::getDataAccessType();
			throw Exception( "ObjectTagDataAccessFactory::create", stringStream.str() );
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________