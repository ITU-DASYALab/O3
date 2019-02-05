/*
 *  HierarchyNodeDataAccessFactory.cpp
 *  Prada
 *
 *  Created by Grímur Tómasson on 8.2.2010.
 *  Copyright 2010 RU. All rights reserved.
 *
 */

#include "HierarchyNodeDataAccessFactory.h"

#include <sstream>

#include "../Root/HierarchyNodeDataAccess.h"
//#include "../Canned/HierarchyNodeCanned.h"
//#include "../SQLite/HierarchyNodeSQLite.h"
//#include "../MonetDB/HierarchyNodeMonetDB.h"
//#include "../Oracle/HierarchyNodeOracle.h"
#include "../PostgreSQL/HierarchyNodePostgreSQL.h"

#include "../../LayerShared/HubCommon.h"
#include "../../LayerShared/Exception.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

HierarchyNodeDataAccess* HierarchyNodeDataAccessFactory::create()
{
	switch ( HubCommon::getDataAccessType() ) 
	{
	#ifdef OC_CANNED
		case HubCommon::CANNED :
			return new HierarchyNodeCanned();
	#endif
			
	#ifdef OC_SQLITE
		case HubCommon::SQLITE :
			return new HierarchyNodeSQLite();
	#endif
		
	#ifdef OC_MONETDB
		case HubCommon::MONETDB :
			return new HierarchyNodeMonetDB();
	#endif
			
	#ifdef OC_ORACLE
		case HubCommon::ORACLE :
			return new HierarchyNodeOracle();
	#endif

	#ifdef OC_POSTGRESQL
		case HubCommon::POSTGRESQL :
			return new HierarchyNodePostgreSQL(); 
	#endif
			
		default:
			stringstream stringStream;
			stringStream << "Unknown data access type: " << HubCommon::getDataAccessType();
			throw Exception( "HierarchyNodeDataAccessFactory::create", stringStream.str() );
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________