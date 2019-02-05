/*
 *  TagFactory.cpp
 *  Prada
 *
 *  Created by Grímur Tómasson on 6.2.2010.
 *  Copyright 2010 RU. All rights reserved.
 *
 */

#include "TagDataAccessFactory.h"

#include <sstream>

#include "../Root/TagDataAccess.h"
//#include "../Canned/TagCanned.h"
//#include "../SQLite/Tag/SQLite.h"
//#include "../MonetDB/TagMonetDB.h"
//#include "../Oracle/TagOracle.h"
#include "../PostgreSQL/TagPostgreSQL.h"

#include "AlphanumericalTagDataAccessFactory.h"
#include "NumericalTagDataAccessFactory.h"
#include "TimeTagDataAccessFactory.h"
#include "DateTagDataAccessFactory.h"
#include "RGBTagDataAccessFactory.h"

#include "../../LayerShared/HubCommon.h"
#include "../../LayerShared/TagCommon.h"
#include "../../LayerShared/Exception.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

TagDataAccess* TagDataAccessFactory::create()
{
	switch ( HubCommon::getDataAccessType() ) 
	{
	#ifdef OC_CANNED
		case HubCommon::CANNED :
			return new TagCanned();
	#endif
			
	#ifdef OC_SQLITE
		case HubCommon::SQLITE :
			return new TagSQLite();
	#endif
		
	#ifdef OC_MONETDB
		case HubCommon::MONETDB :
			return new TagMonetDB();
	#endif
			
	#ifdef OC_ORACLE
		case HubCommon::ORACLE :
			return new TagOracle();
	#endif

	#ifdef OC_POSTGRESQL
		case HubCommon::POSTGRESQL :
			return new TagPostgreSQL(); 
	#endif
			
		default:
			stringstream stringStream;
			stringStream << "Unknown data access type: " << HubCommon::getDataAccessType();
			throw Exception( "TagDataAccessFactory::create", stringStream.str() );
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________

TagDataAccess* TagDataAccessFactory::create( int tagTypeId )
{
	switch ( tagTypeId ) 
	{
		case TagCommon::ALPHANUMERICAL :
			return reinterpret_cast<TagDataAccess*>( AlphanumericalTagDataAccessFactory::create() );
		case TagCommon::NUMERICAL :
			return reinterpret_cast<TagDataAccess*>( NumericalTagDataAccessFactory::create() );
		case TagCommon::TIME :
			return reinterpret_cast<TagDataAccess*>( TimeTagDataAccessFactory::create() );
		case TagCommon::DATE :
			return reinterpret_cast<TagDataAccess*>( DateTagDataAccessFactory::create() );
		case TagCommon::RGB :
			return reinterpret_cast<TagDataAccess*>( RGBTagDataAccessFactory::create() );
		default:
			ostringstream stringstream;
			stringstream << "Unknown tag type:" << tagTypeId;
			throw Exception("TagFactory::create", stringstream.str() );
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________

