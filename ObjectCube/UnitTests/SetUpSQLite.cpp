/*
 *  SetupSQLite.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 16.2.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifdef OC_SQLITE

#include "SetUpSQLite.h"
#include <sstream>
#include <iostream> 
#include "../DataAccess/SQLite/CommonSQLite.h"
#include "TestIds.h"
#include "../Tag/Tag.h"
#include "../LayerShared/DebugInfo.h"

using namespace ObjectCube;
using namespace std;

/*
 
-- delete from dimension where name = 'SQLite unit test dimension';
-- insert into dimension (name, description, type_id, access_id) values( 'SQLite unit test dimension','Throw away',1,2);
 
-- delete from object_tag where tag_id = (select id from tag where dimension_id in( select id from dimension where name = 'SQLite unit test dimension'));
-- delete from object where qualified_name like '/SQLite%';
-- delete from tag where name like 'SQLite%';
 
-- insert into object values( (select ifnull(max(id),0)+1 from object), '/SQLite/UnitTest/1.obj');
-- insert into tag values((select ifnull(max(id),1)+1 from tag), 1, 'SQLite unit test tag');
 
 */

//____________________________________________________________________________________________________________________________________________________________________________________

SetupSQLite::SetupSQLite()
{
	TestIds::updateObjectPrefix();
}

void SetupSQLite::setup()
{
	try
	{
		DebugInfo::getDebugInfo()->output( "SetupSQLite", "setup", "Starting SQLite setup" );
		insertAlphanumericalTestTagSets_();
		insertNumericalTestTagSets_();
		insertTimeTestTagSets_();
		insertDateTestTagSets_();

		insertTestObjects_();
		
		insertTestTagsAlphanumerical_();
		insertTestTagObjects_( TEST_OBJECT_ID, SQLiteTestIds::TEST_ALPHANUMERICAL_TAG_ID );
		insertTestTagsNumerical_();
		insertTestTagObjects_( TEST_OBJECT_ID, SQLiteTestIds::TEST_NUMERICAL_TAG_ID );
		insertTestTagsTime_();
		insertTestTagObjects_( TEST_OBJECT_ID, SQLiteTestIds::TEST_TIME_TAG_ID );
		insertTestTagsDate_();
		insertTestTagObjects_( TEST_OBJECT_ID, SQLiteTestIds::TEST_DATE_TAG_ID );
		

		insertTestDimensions_();
	}
	catch(...)
	{
		cerr << "Error in SQLite setup" << endl;
		throw;
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupSQLite::cleanup()
{
	try 
	{
		DebugInfo::getDebugInfo()->output( "SetupSQLite", "cleanup", "Starting SQLite cleanup" );
		deleteTestObjectTags_();
		deleteTestObjects_();
		
		deleteAlphanumericalTags_();
		deleteNumericalTags_();
		deleteDateTags_();
		deleteTimeTags_();
		deleteTestTags_();
		
		deleteTestDimensions_();
		deleteTestTagSets_();
	}
	catch(...)
	{
		cerr << "Error in SQLite cleanup" << endl;
		throw;
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Delete ---------------------------------------------------------------------------------------------------
void SetupSQLite::deleteTestObjectTags_()
{
	ostringstream sstream;
	sstream << "delete from object_tag where object_id in (select id from main.object where qualified_name like '" 
	<< TestIds::TEST_OBJECT_PREFIX << "%' or qualified_name like '" << TestIds::TEST_OBJECT_PREFIX_DEFAULT << "%')";
	CommonSQLite db;
	char** result = db.getTable( sstream.str() );
	db.getTableCleanup( result );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupSQLite::deleteAlphanumericalTags_()
{
	ostringstream sstream;
	sstream << "delete from alphanumerical_tag where tag_set_id in( select id from tag_set where name like '" << TEST_SQLITE_CLEANUP_PREFIX << "%')";
	CommonSQLite db;
	char** result = db.getTable( sstream.str() );
	db.getTableCleanup( result );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupSQLite::deleteNumericalTags_()
{
	ostringstream sstream;
	sstream << "delete from numerical_tag where tag_set_id in( select id from tag_set where name like '" << TEST_SQLITE_CLEANUP_PREFIX << "%')";
	CommonSQLite db;
	char** result = db.getTable( sstream.str() );
	db.getTableCleanup( result );			
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupSQLite::deleteDateTags_()
{
	ostringstream sstream;
	sstream << "delete from date_tag where tag_set_id in( select id from tag_set where name like '" << TEST_SQLITE_CLEANUP_PREFIX << "%')";
	CommonSQLite db;
	char** result = db.getTable( sstream.str() );
	db.getTableCleanup( result );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupSQLite::deleteTimeTags_()
{
	ostringstream sstream;
	sstream << "delete from time_tag where tag_set_id in( select id from tag_set where name like '" << TEST_SQLITE_CLEANUP_PREFIX << "%')";
	CommonSQLite db;
	char** result = db.getTable( sstream.str() );
	db.getTableCleanup( result );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupSQLite::deleteTestTags_()
{
	ostringstream sstream;
	sstream << "delete from tag where tag_set_id in( select id from tag_set where name like '" << TEST_SQLITE_CLEANUP_PREFIX << "%')";
	CommonSQLite db;
	char** result = db.getTable( sstream.str() );
	db.getTableCleanup( result );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupSQLite::deleteTestObjects_()
{
	ostringstream sstream;
	sstream << "delete from object where qualified_name like '" << TestIds::TEST_OBJECT_PREFIX << "%' or qualified_name like '" << TestIds::TEST_OBJECT_PREFIX_DEFAULT << "%'";
	CommonSQLite db;
	char** result = db.getTable( sstream.str() );
	db.getTableCleanup( result );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupSQLite::deleteTestDimensions_()
{
	ostringstream sstream;
	sstream << "delete from dimension where tag_set_id in (select id from tag_set where name like '" << TEST_SQLITE_CLEANUP_PREFIX << "%')";
	CommonSQLite db;
	char** result = db.getTable( sstream.str() );
	db.getTableCleanup( result );	
}
//____________________________________________________________________________________________________________________________________________________________________________________
void SetupSQLite::deleteTestTagSets_()
{
	ostringstream sstream;
	sstream << "delete from tag_set where name like '" << TEST_SQLITE_CLEANUP_PREFIX << "%'";
	CommonSQLite db;
	char** result = db.getTable( sstream.str() );
	db.getTableCleanup( result );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Insert ---------------------------------------------------------------------------------------------------
void SetupSQLite::insertAlphanumericalTestTagSets_()
{
	ostringstream stringStream;
	stringStream << "insert into tag_set (id, name, description, type_id, access_id) values(" << TEST_ALPHANUMERICAL_TAG_SET_ID << ", '" << TEST_SQLITE_CLEANUP_PREFIX << " Alphanumerical unit test tag-set','Throw away',1,2)";
	string sql = stringStream.str();
	CommonSQLite db;
	char** result = db.getTable( sql );
	db.getTableCleanup( result );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupSQLite::insertNumericalTestTagSets_()
{
	ostringstream stringStream;
	stringStream << "insert into tag_set (id, name, description, type_id, access_id) values(" << TEST_NUMERICAL_TAG_SET_ID << ", '" << TEST_SQLITE_CLEANUP_PREFIX << " Numerical unit test tag-set','Throw away',2,2)";
	string sql = stringStream.str();
	CommonSQLite db;
	char** result = db.getTable( sql );
	db.getTableCleanup( result );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupSQLite::insertTimeTestTagSets_()
{
	ostringstream stringStream;
	stringStream << "insert into tag_set (id, name, description, type_id, access_id) values(" << TEST_TIME_TAG_SET_ID << ", '" << TEST_SQLITE_CLEANUP_PREFIX << " Time unit test tag-set','Throw away',4,2)";
	string sql = stringStream.str();
	CommonSQLite db;
	char** result = db.getTable( sql );
	db.getTableCleanup( result );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupSQLite::insertDateTestTagSets_()
{
	ostringstream stringStream;
	stringStream << "insert into tag_set (id, name, description, type_id, access_id) values(" << TEST_DATE_TAG_SET_ID << ", '" << TEST_SQLITE_CLEANUP_PREFIX << " Date unit test tag-set','Throw away',3,2)";
	string sql = stringStream.str();
	CommonSQLite db;
	char** result = db.getTable( sql );
	db.getTableCleanup( result );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

int SetupSQLite::insertTestTag_( int tagSetId, int typeId, CommonSQLite& db )
{
	ostringstream stringStream;	
	stringStream << "insert into tag (tag_set_id, type_id) values(" << tagSetId << "," << typeId << ")";
	string sql = stringStream.str();
	char** result = db.getTable( sql );
	db.getTableCleanup( result );
	
	return db.getCurrentSequence( "tag" );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupSQLite::insertTestTagsAlphanumerical_()
{
	CommonSQLite db;
	SQLiteTestIds::TEST_ALPHANUMERICAL_TAG_ID = insertTestTag_( TEST_ALPHANUMERICAL_TAG_SET_ID, Tag::ALPHANUMERICAL, db );
	
	ostringstream stringStream;	
	stringStream << "insert into alphanumerical_tag values(" << SQLiteTestIds::TEST_ALPHANUMERICAL_TAG_ID << "," << "'" << TEST_SQLITE_CLEANUP_PREFIX << TEST_ALPHANUMERICAL_TAG_NAME << "'" << "," << TEST_ALPHANUMERICAL_TAG_SET_ID << ")";
	string sql = stringStream.str();
	
	char** result = db.getTable( sql );
	db.getTableCleanup( result );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupSQLite::insertTestTagsNumerical_()
{
	CommonSQLite db;
	SQLiteTestIds::TEST_NUMERICAL_TAG_ID = insertTestTag_( TEST_NUMERICAL_TAG_SET_ID, Tag::NUMERICAL, db );
	
	ostringstream stringStream;	
	stringStream << "insert into numerical_tag values(" << SQLiteTestIds::TEST_NUMERICAL_TAG_ID << "," << TEST_NUMERICAL_TAG_VALUE << "," << TEST_NUMERICAL_TAG_SET_ID << ")";
	string sql = stringStream.str();
	
	char** result = db.getTable( sql );
	db.getTableCleanup( result );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupSQLite::insertTestTagsTime_()
{
	CommonSQLite db;
	SQLiteTestIds::TEST_TIME_TAG_ID = insertTestTag_( TEST_TIME_TAG_SET_ID, Tag::TIME, db );
	
	ostringstream stringStream;	
	stringStream << "insert into time_tag values(" << SQLiteTestIds::TEST_TIME_TAG_ID << "," 
	<< "strftime( \"%H:%M:%f\", '" << TEST_TIME_TAG_VALUE_HOURS << ":" << TEST_TIME_TAG_VALUE_MINUTES << ":" << TEST_TIME_TAG_VALUE_SECONDS << "." << TEST_TIME_TAG_VALUE_MILLISECONDS << "')," 
	<< TEST_TIME_TAG_SET_ID << ")";
	
	string sql = stringStream.str();
	
	char** result = db.getTable( sql );
	db.getTableCleanup( result );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupSQLite::insertTestTagsDate_()
{
	CommonSQLite db;
	SQLiteTestIds::TEST_DATE_TAG_ID = insertTestTag_( TEST_DATE_TAG_SET_ID, Tag::DATE, db );
	
	ostringstream stringStream;	
	stringStream << "insert into date_tag values(" << SQLiteTestIds::TEST_DATE_TAG_ID << "," 
	<<  "strftime( \"%Y-%m-%d\", '" << TEST_DATE_TAG_VALUE_YEAR << "-0" << TEST_DATE_TAG_VALUE_MONTH << "-" << TEST_DATE_TAG_VALUE_DAY << "')," 
	<< TEST_DATE_TAG_SET_ID << ")";
	
	string sql = stringStream.str();
	
	char** result = db.getTable( sql );
	db.getTableCleanup( result );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupSQLite::insertTestObjects_()
{
	ostringstream stringStream;	
	stringStream << "insert into object values(" << TEST_OBJECT_ID << ", '" << TestIds::TEST_OBJECT_PREFIX + TEST_OBJECT_NAME << "')";
	string sql = stringStream.str();
	CommonSQLite db;
	char** result = db.getTable( sql );
	db.getTableCleanup( result );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupSQLite::insertTestTagObjects_( int objectId, int tagId )
{
	ostringstream stringStream;	
	stringStream << "insert into object_tag( object_id, tag_id) values(" << objectId << ", " << tagId << ")";
	string sql = stringStream.str();
	CommonSQLite db;
	char** result = db.getTable( sql );
	db.getTableCleanup( result );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupSQLite::insertTestDimensions_()
{
	ostringstream stringStream;	
	stringStream << "insert into dimension values("	<< TEST_HIERARCHY_ID << ", " 
													<< TEST_HIERARCHY_NODE_ID << ", " 
													<< TEST_ALPHANUMERICAL_TAG_SET_ID << ", " 
													<< SQLiteTestIds::TEST_ALPHANUMERICAL_TAG_ID << ", "
													<< "'Test child category name'" << ", "
													<< 1 << ", " << 2 << " )";
	string sql = stringStream.str();
	CommonSQLite db;
	char** result = db.getTable( sql );
	db.getTableCleanup( result );	
	
}
//____________________________________________________________________________________________________________________________________________________________________________________


#endif