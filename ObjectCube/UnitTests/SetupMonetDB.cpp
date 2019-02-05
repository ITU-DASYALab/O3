/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/

#ifdef OC_MONETDB

#include "SetupMonetDB.h"

#include <sstream>
#include <iostream> 
#include "../DataAccess/MonetDB/CommonMonetDB.h"
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

SetupMonetDB::SetupMonetDB()
{
	TestIds::updateObjectPrefix();
}

void SetupMonetDB::setup()
{
	try
	{
		DebugInfo::getDebugInfo()->output( "SetupMonetDB", "setup", "Starting MonetDB setup" );
		insertAlphanumericalTestTagSets_();
		insertNumericalTestTagSets_();
		insertTimeTestTagSets_();
		insertDateTestTagSets_();
		
		insertTestObjects_();
		
		insertTestTagsAlphanumerical_();
		insertTestTagObjects_( TEST_OBJECT_ID, MonetDBTestIds::TEST_ALPHANUMERICAL_TAG_ID );
		insertTestTagsNumerical_();
		insertTestTagObjects_( TEST_OBJECT_ID, MonetDBTestIds::TEST_NUMERICAL_TAG_ID );
		insertTestTagsTime_();
		insertTestTagObjects_( TEST_OBJECT_ID, MonetDBTestIds::TEST_TIME_TAG_ID );
		insertTestTagsDate_();
		insertTestTagObjects_( TEST_OBJECT_ID, MonetDBTestIds::TEST_DATE_TAG_ID );

		insertTestDimensions_();
		
		refreshMaterializedViews_();
	}
	catch(...)
	{
		cerr << "Error in MonetDB setup" << endl;
		throw;
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupMonetDB::cleanup()
{
	try 
	{
		DebugInfo::getDebugInfo()->output( "SetupMonetDB", "cleanup", "Starting MonetDB cleanup" );
		deleteTestObjectTags_();
		deleteTestObjects_();
		
		deleteTestDimensions_();
		
		deleteAlphanumericalTags_();
		deleteNumericalTags_();
		deleteDateTags_();
		deleteTimeTags_();
		deleteTestTags_();
	
		deleteTestTagSets_();
	}
	catch(...)
	{
		cerr << "Error in MonetDB cleanup" << endl;
		throw;
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Delete ---------------------------------------------------------------------------------------------------
void SetupMonetDB::deleteTestObjectTags_()
{
	ostringstream sstream;
	sstream << "delete from object_tag where object_id in (select id from object where qualified_name like '" 
	<< TestIds::TEST_OBJECT_PREFIX << "%' or qualified_name like '" << TestIds::TEST_OBJECT_PREFIX_DEFAULT << "%')";
	CommonMonetDB db;
	db.executeSQLNoResults( sstream.str() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupMonetDB::deleteAlphanumericalTags_()
{
	ostringstream sstream;
	sstream << "delete from alphanumerical_tag where tag_set_id in( select id from tag_set where name like '" << TEST_MONETDB_CLEANUP_PREFIX << "%')";
	CommonMonetDB db;
	db.executeSQLNoResults( sstream.str() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupMonetDB::deleteNumericalTags_()
{
	ostringstream sstream;
	sstream << "delete from numerical_tag where tag_set_id in( select id from tag_set where name like '" << TEST_MONETDB_CLEANUP_PREFIX << "%')";
	CommonMonetDB db;
	db.executeSQLNoResults( sstream.str() );}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupMonetDB::deleteDateTags_()
{
	ostringstream sstream;
	sstream << "delete from date_tag where tag_set_id in( select id from tag_set where name like '" << TEST_MONETDB_CLEANUP_PREFIX << "%')";
	CommonMonetDB db;
	db.executeSQLNoResults( sstream.str() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupMonetDB::deleteTimeTags_()
{
	ostringstream sstream;
	sstream << "delete from time_tag where tag_set_id in( select id from tag_set where name like '" << TEST_MONETDB_CLEANUP_PREFIX << "%')";
	CommonMonetDB db;
	db.executeSQLNoResults( sstream.str() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupMonetDB::deleteTestTags_()
{
	ostringstream sstream;
	sstream << "delete from tag where tag_set_id in( select id from tag_set where name like '" << TEST_MONETDB_CLEANUP_PREFIX << "%')";
	CommonMonetDB db;
	db.executeSQLNoResults( sstream.str() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupMonetDB::deleteTestObjects_()
{
	ostringstream sstream;
	sstream << "delete from object where qualified_name like '" << TestIds::TEST_OBJECT_PREFIX << "%' or qualified_name like '" << TestIds::TEST_OBJECT_PREFIX_DEFAULT << "%'";
	CommonMonetDB db;
	db.executeSQLNoResults( sstream.str() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupMonetDB::deleteTestDimensions_()
{
	ostringstream sstream;
	sstream << "delete from dimension where tag_set_id in (select id from tag_set where name like '" << TEST_MONETDB_CLEANUP_PREFIX << "%')";
	CommonMonetDB db;
	db.executeSQLNoResults( sstream.str() );
}
//____________________________________________________________________________________________________________________________________________________________________________________
void SetupMonetDB::deleteTestTagSets_()
{
	ostringstream sstream;
	sstream << "delete from tag_set where name like '" << TEST_MONETDB_CLEANUP_PREFIX << "%'";
	CommonMonetDB db;
	db.executeSQLNoResults( sstream.str() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Insert ---------------------------------------------------------------------------------------------------
void SetupMonetDB::insertAlphanumericalTestTagSets_()
{
	ostringstream stringStream;
	stringStream << "insert into tag_set (id, name, description, type_id, access_id) values(" << TEST_ALPHANUMERICAL_TAG_SET_ID << ", '" << TEST_MONETDB_CLEANUP_PREFIX << " Alphanumerical unit test tag-set','Throw away',1,2)";
	string sql = stringStream.str();
	CommonMonetDB db;
	db.executeSQLNoResults( sql );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupMonetDB::insertNumericalTestTagSets_()
{
	ostringstream stringStream;
	stringStream << "insert into tag_set (id, name, description, type_id, access_id) values(" << TEST_NUMERICAL_TAG_SET_ID << ", '" << TEST_MONETDB_CLEANUP_PREFIX << " Numerical unit test tag-set','Throw away',2,2)";
	string sql = stringStream.str();
	CommonMonetDB db;
	db.executeSQLNoResults( sql );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupMonetDB::insertTimeTestTagSets_()
{
	ostringstream stringStream;
	stringStream << "insert into tag_set (id, name, description, type_id, access_id) values(" << TEST_TIME_TAG_SET_ID << ", '" << TEST_MONETDB_CLEANUP_PREFIX << " Time unit test tag-set','Throw away',4,2)";
	string sql = stringStream.str();
	CommonMonetDB db;
	db.executeSQLNoResults( sql );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupMonetDB::insertDateTestTagSets_()
{
	ostringstream stringStream;
	stringStream << "insert into tag_set (id, name, description, type_id, access_id) values(" << TEST_DATE_TAG_SET_ID << ", '" << TEST_MONETDB_CLEANUP_PREFIX << " Date unit test tag-set','Throw away',3,2)";
	string sql = stringStream.str();
	CommonMonetDB db;
	db.executeSQLNoResults( sql );
}
//____________________________________________________________________________________________________________________________________________________________________________________

int SetupMonetDB::insertTestTag_( int tagSetId, int typeId )
{
	ostringstream stringStream;	
	stringStream << "insert into tag (tag_set_id, type_id) values(" << tagSetId << "," << typeId << ")";
	string sql = stringStream.str();
	CommonMonetDB db;
	MapiHdl hdl = db.executeSQL( sql );
	int id = db.getLastAutoincrementedInsertId( hdl );
	db.cleanup( hdl );
	return id;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupMonetDB::insertTestTagsAlphanumerical_()
{
	CommonMonetDB db;
	MonetDBTestIds::TEST_ALPHANUMERICAL_TAG_ID = insertTestTag_( TEST_ALPHANUMERICAL_TAG_SET_ID, Tag::ALPHANUMERICAL );
	
	ostringstream stringStream;	
	stringStream << "insert into alphanumerical_tag values(" << MonetDBTestIds::TEST_ALPHANUMERICAL_TAG_ID << "," << "'" << TEST_MONETDB_CLEANUP_PREFIX << TEST_ALPHANUMERICAL_TAG_NAME << "'" << "," << TEST_ALPHANUMERICAL_TAG_SET_ID << ")";
	string sql = stringStream.str();
	
	db.executeSQLNoResults( sql );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupMonetDB::insertTestTagsNumerical_()
{
	CommonMonetDB db;
	MonetDBTestIds::TEST_NUMERICAL_TAG_ID = insertTestTag_( TEST_NUMERICAL_TAG_SET_ID, Tag::NUMERICAL );
	
	ostringstream stringStream;	
	stringStream << "insert into numerical_tag values(" << MonetDBTestIds::TEST_NUMERICAL_TAG_ID << "," << TEST_NUMERICAL_TAG_VALUE << "," << TEST_NUMERICAL_TAG_SET_ID << ")";
	string sql = stringStream.str();
	
	db.executeSQLNoResults( sql );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupMonetDB::insertTestTagsTime_()
{
	CommonMonetDB db;
	MonetDBTestIds::TEST_TIME_TAG_ID = insertTestTag_( TEST_TIME_TAG_SET_ID, Tag::TIME );
	
	ostringstream stringStream;	
	stringStream << "insert into time_tag values(" << MonetDBTestIds::TEST_TIME_TAG_ID << "," 
	<< "'" << TEST_TIME_TAG_VALUE_HOURS << ":" << TEST_TIME_TAG_VALUE_MINUTES << ":" << TEST_TIME_TAG_VALUE_SECONDS << "." << TEST_TIME_TAG_VALUE_MILLISECONDS << "'," 
	<< TEST_TIME_TAG_SET_ID << ")";
	
	string sql = stringStream.str();
	
	db.executeSQLNoResults( sql );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupMonetDB::insertTestTagsDate_()
{
	CommonMonetDB db;
	MonetDBTestIds::TEST_DATE_TAG_ID = insertTestTag_( TEST_DATE_TAG_SET_ID, Tag::DATE );
	
	ostringstream stringStream;	
	stringStream << "insert into date_tag values(" << MonetDBTestIds::TEST_DATE_TAG_ID << "," 
	<<  "'" << TEST_DATE_TAG_VALUE_YEAR << "-0" << TEST_DATE_TAG_VALUE_MONTH << "-" << TEST_DATE_TAG_VALUE_DAY << "'," 
	<< TEST_DATE_TAG_SET_ID << ")";
	
	string sql = stringStream.str();
	
	db.executeSQLNoResults( sql );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupMonetDB::insertTestObjects_()
{
	ostringstream stringStream;	
	stringStream << "insert into object values(" << TEST_OBJECT_ID << ", '" << TestIds::TEST_OBJECT_PREFIX + TEST_OBJECT_NAME << "')";
	string sql = stringStream.str();
	CommonMonetDB db;
	db.executeSQLNoResults( sql );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupMonetDB::insertTestTagObjects_( int objectId, int tagId )
{
	ostringstream stringStream;	
	stringStream << "insert into object_tag(object_id, tag_id, upper_left_x, upper_left_y, lower_right_x, lower_right_y, confirmed ) \
	values(" << objectId << ", " << tagId << ", 0, 100, 100, 0, 1 )";
	string sql = stringStream.str();
	CommonMonetDB db;
	db.executeSQLNoResults( sql );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupMonetDB::insertTestDimensions_()
{
	
	ostringstream stringStream;	
	stringStream << "insert into dimension values("	<< TEST_HIERARCHY_ID << ", " 
	<< TEST_HIERARCHY_NODE_ID << ", " 
	<< TEST_ALPHANUMERICAL_TAG_SET_ID << ", " 
	<< MonetDBTestIds::TEST_ALPHANUMERICAL_TAG_ID << ", "
	<< "'Test child category name'" << ", "
	<< 1 << ", " << 2 << " )";
	string sql = stringStream.str();
	CommonMonetDB db;
	db.executeSQLNoResults( sql );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupMonetDB::refreshMaterializedViews_()
{
	CommonMonetDB db;
	db.executeSQLNoResults( "delete from dimension_tag_object" );
	db.executeSQLNoResults( "insert into dimension_tag_object select d.id as dimension_id, d.node_id, ot.tag_id, ot.object_id, ot.upper_left_x, ot.upper_left_y, ot.lower_right_x, ot.lower_right_y, ot.confirmed, d.left_border, d.right_border \
						   from dimension d, object_tag ot \
						   where d.tag_id = ot.tag_id \
						   order by d.node_id" );
}
//____________________________________________________________________________________________________________________________________________________________________________________

#endif