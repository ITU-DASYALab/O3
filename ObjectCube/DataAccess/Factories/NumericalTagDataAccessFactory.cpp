/*
 *  NumericalTagDataAccessFactory.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 27.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "NumericalTagDataAccessFactory.h"

#include <sstream>

#include "../Root/NumericalTagDataAccess.h"
//#include "../Canned/NumericalTagCanned.h"
//#include "../SQLite/NumericalTagSQLite.h"
//#include "../MonetDB/NumericalTagMonetDB.h"
//#include "../Oracle/NumericalTagOracle.h"
#include "../PostgreSQL/NumericalTagPostgreSQL.h"

#include "../../LayerShared/HubCommon.h"
#include "../../LayerShared/Exception.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

NumericalTagDataAccess* NumericalTagDataAccessFactory::create()
{
	switch ( HubCommon::getDataAccessType() ) 
	{
	#ifdef OC_CANNED
		case HubCommon::CANNED :
			return new NumericalTagCanned();
	#endif
			
	#ifdef OC_SQLITE
		case HubCommon::SQLITE :
			return new NumericalTagSQLite();
	#endif
	
	#ifdef OC_MONETDB
		case HubCommon::MONETDB :
			return new NumericalTagMonetDB();
	#endif
			
	#ifdef OC_ORACLE
		case HubCommon::ORACLE :
			return new NumericalTagOracle();
	#endif		

	#ifdef OC_POSTGRESQL
		case HubCommon::POSTGRESQL :
			return new NumericalTagPostgreSQL(); 
	#endif	
			
		default:
			stringstream stringStream;
			stringStream << "Unknown data access type: " << HubCommon::getDataAccessType();
			throw Exception( "NumericalTagDataAccessFactory::create", stringStream.str() );
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________