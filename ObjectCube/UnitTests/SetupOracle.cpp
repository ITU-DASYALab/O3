/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/

#ifdef OC_ORACLE

#include "SetupOracle.h"

#include <sstream>
#include <iostream> 
#include "../DataAccess/Oracle/CommonOracle.h"
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

SetupOracle::SetupOracle()
{
	TestIds::updateObjectPrefix();
}

void SetupOracle::setup()
{
	try
	{
		DebugInfo::getDebugInfo()->output( "SetupOracle", "setup", "Starting Oracle setup" );
		insertAlphanumericalTestTagSets_();
		insertNumericalTestTagSets_();
		insertTimeTestTagSets_();
		insertDateTestTagSets_();
		
		insertTestObjects_();
		
		insertTestTagsAlphanumerical_();
		insertTestTagObjects_( TEST_OBJECT_ID, OracleTestIds::TEST_ALPHANUMERICAL_TAG_ID );
		insertTestTagsNumerical_();
		insertTestTagObjects_( TEST_OBJECT_ID, OracleTestIds::TEST_NUMERICAL_TAG_ID );
		insertTestTagsTime_();
		insertTestTagObjects_( TEST_OBJECT_ID, OracleTestIds::TEST_TIME_TAG_ID );
		insertTestTagsDate_();
		insertTestTagObjects_( TEST_OBJECT_ID, OracleTestIds::TEST_DATE_TAG_ID );
		
		insertTestDimensions_();
	}
	catch(...)
	{
		cerr << "Error in Oracle setup" << endl;
		throw;
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupOracle::cleanup()
{
	try 
	{
		DebugInfo::getDebugInfo()->output( "SetupOracle", "cleanup", "Starting Oracle cleanup" );
		
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
		cerr << "Error in Oracle cleanup" << endl;
		throw;
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Delete ---------------------------------------------------------------------------------------------------
void SetupOracle::deleteTestObjectTags_()
{
	ostringstream sstream;
	sstream << "delete from object_tag where \"object_id\" in (select \"id\" from object where \"qualified_name\" like '" 
	<< TestIds::TEST_OBJECT_PREFIX << "%' or \"qualified_name\" like '" << TestIds::TEST_OBJECT_PREFIX_DEFAULT << "%')";
	CommonOracle db;
	db.executeUpdate( sstream.str() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupOracle::deleteAlphanumericalTags_()
{
	ostringstream sstream;
	sstream << "delete from alphanumerical_tag where \"tag_set_id\" in( select \"id\" from tag_set where \"name\" like '" << TEST_ORACLE_CLEANUP_PREFIX << "%')";
	CommonOracle db;
	db.executeUpdate( sstream.str() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupOracle::deleteNumericalTags_()
{
	ostringstream sstream;
	sstream << "delete from numerical_tag where \"tag_set_id\" in( select \"id\" from tag_set where \"name\" like '" << TEST_ORACLE_CLEANUP_PREFIX << "%')";
	CommonOracle db;
	db.executeUpdate( sstream.str() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupOracle::deleteDateTags_()
{
	ostringstream sstream;
	sstream << "delete from date_tag where \"tag_set_id\" in( select \"id\" from tag_set where \"name\" like '" << TEST_ORACLE_CLEANUP_PREFIX << "%')";
	CommonOracle db;
	db.executeUpdate( sstream.str() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupOracle::deleteTimeTags_()
{
	ostringstream sstream;
	sstream << "delete from time_tag where \"tag_set_id\" in( select \"id\" from tag_set where \"name\" like '" << TEST_ORACLE_CLEANUP_PREFIX << "%')";
	CommonOracle db;
	cout << sstream.str() << endl;
	db.executeUpdate( sstream.str() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupOracle::deleteTestTags_()
{
	ostringstream sstream;
	sstream << "delete from tag where \"tag_set_id\" in( select \"id\" from tag_set where \"name\" like '" << TEST_ORACLE_CLEANUP_PREFIX << "%')";
	CommonOracle db;
	db.executeUpdate( sstream.str() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupOracle::deleteTestObjects_()
{
	ostringstream sstream;
	sstream << "delete from object where \"qualified_name\" like '" << TestIds::TEST_OBJECT_PREFIX << "%' or \"qualified_name\" like '" << TestIds::TEST_OBJECT_PREFIX_DEFAULT << "%'";
	CommonOracle db;
	db.executeUpdate( sstream.str() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupOracle::deleteTestDimensions_()
{
	ostringstream sstream;
	sstream << "delete from dimension where \"tag_set_id\" in (select \"id\" from tag_set where \"name\" like '" << TEST_ORACLE_CLEANUP_PREFIX << "%')";
	CommonOracle db;
	db.executeUpdate( sstream.str() );
}
//____________________________________________________________________________________________________________________________________________________________________________________
void SetupOracle::deleteTestTagSets_()
{
	ostringstream sstream;
	sstream << "delete from tag_set where \"name\" like '" << TEST_ORACLE_CLEANUP_PREFIX << "%'";
	CommonOracle db;
	db.executeUpdate( sstream.str() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Insert ---------------------------------------------------------------------------------------------------
void SetupOracle::insertAlphanumericalTestTagSets_()
{
	ostringstream stringStream;
	stringStream << "insert into tag_set (\"id\", \"name\", \"description\", \"type_id\", \"access_id\") values(" << TEST_ALPHANUMERICAL_TAG_SET_ID << ", '" << TEST_ORACLE_CLEANUP_PREFIX << " Alphanumerical unit test tag-set','Throw away',1,2)";
	string sql = stringStream.str();
	CommonOracle db;
	db.executeUpdate( sql );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupOracle::insertNumericalTestTagSets_()
{
	ostringstream stringStream;
	stringStream << "insert into tag_set (\"id\", \"name\", \"description\", \"type_id\", \"access_id\") values(" << TEST_NUMERICAL_TAG_SET_ID << ", '" << TEST_ORACLE_CLEANUP_PREFIX << " Numerical unit test tag-set','Throw away',2,2)";
	string sql = stringStream.str();
	CommonOracle db;
	db.executeUpdate( sql );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupOracle::insertTimeTestTagSets_()
{
	ostringstream stringStream;
	stringStream << "insert into tag_set (\"id\", \"name\", \"description\", \"type_id\", \"access_id\") values(" << TEST_TIME_TAG_SET_ID << ", '" << TEST_ORACLE_CLEANUP_PREFIX << " Time unit test tag-set','Throw away',4,2)";
	string sql = stringStream.str();
	CommonOracle db;
	db.executeUpdate( sql );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupOracle::insertDateTestTagSets_()
{
	ostringstream stringStream;
	stringStream << "insert into tag_set (\"id\", \"name\", \"description\", \"type_id\", \"access_id\") values(" << TEST_DATE_TAG_SET_ID << ", '" << TEST_ORACLE_CLEANUP_PREFIX << " Date unit test tag-set','Throw away',3,2)";
	string sql = stringStream.str();
	CommonOracle db;
	db.executeUpdate( sql );
}
//____________________________________________________________________________________________________________________________________________________________________________________

int SetupOracle::insertTestTag_( int tagSetId, int typeId )
{
	ostringstream stringStream;	
	stringStream << "insert into tag (\"tag_set_id\", \"type_id\") values(" << tagSetId << "," << typeId << ")";
	string sql = stringStream.str();
	CommonOracle db;
	db.executeUpdate( sql );
	return db.getCurrentSequenceValue( "TAG_PK_SEQ" );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupOracle::insertTestTagsAlphanumerical_()
{
	CommonOracle db;
	OracleTestIds::TEST_ALPHANUMERICAL_TAG_ID = insertTestTag_( TEST_ALPHANUMERICAL_TAG_SET_ID, Tag::ALPHANUMERICAL );
	
	ostringstream stringStream;	
	stringStream << "insert into alphanumerical_tag values(" << OracleTestIds::TEST_ALPHANUMERICAL_TAG_ID << "," << "'" << TEST_ORACLE_CLEANUP_PREFIX << TEST_ALPHANUMERICAL_TAG_NAME << "'" << "," << TEST_ALPHANUMERICAL_TAG_SET_ID << ")";
	string sql = stringStream.str();
	
	db.executeUpdate( sql );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupOracle::insertTestTagsNumerical_()
{
	CommonOracle db;
	OracleTestIds::TEST_NUMERICAL_TAG_ID = insertTestTag_( TEST_NUMERICAL_TAG_SET_ID, Tag::NUMERICAL );
	
	ostringstream stringStream;	
	stringStream << "insert into numerical_tag values(" << OracleTestIds::TEST_NUMERICAL_TAG_ID << "," << TEST_NUMERICAL_TAG_VALUE << "," << TEST_NUMERICAL_TAG_SET_ID << ")";
	string sql = stringStream.str();
	
	db.executeUpdate( sql );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupOracle::insertTestTagsTime_()
{
	CommonOracle db;
	OracleTestIds::TEST_TIME_TAG_ID = insertTestTag_( TEST_TIME_TAG_SET_ID, Tag::TIME );
	
	ostringstream stringStream;	
	stringStream << "insert into time_tag values(" << OracleTestIds::TEST_TIME_TAG_ID << "," 
	<< "to_date('0001-01-01 " << TEST_TIME_TAG_VALUE_HOURS << ":" << TEST_TIME_TAG_VALUE_MINUTES << ":" << TEST_TIME_TAG_VALUE_SECONDS << "', 'YYYY-MM-DD HH24:MI:SS')," 
	<< TEST_TIME_TAG_SET_ID << ")";
	
	string sql = stringStream.str();
	
	db.executeUpdate( sql );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupOracle::insertTestTagsDate_()
{
	CommonOracle db;
	OracleTestIds::TEST_DATE_TAG_ID = insertTestTag_( TEST_DATE_TAG_SET_ID, Tag::DATE );
	
	ostringstream stringStream;	
	stringStream << "insert into date_tag values(" << OracleTestIds::TEST_DATE_TAG_ID << "," 
	<<  "to_date('" << TEST_DATE_TAG_VALUE_YEAR << "-0" << TEST_DATE_TAG_VALUE_MONTH << "-" << TEST_DATE_TAG_VALUE_DAY << "', 'YYYY-MM-DD')," 
	<< TEST_DATE_TAG_SET_ID << ")";
	
	string sql = stringStream.str();
	
	db.executeUpdate( sql );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupOracle::insertTestObjects_()
{
	ostringstream stringStream;	
	stringStream << "insert into object values(" << TEST_OBJECT_ID << ", '" << TestIds::TEST_OBJECT_PREFIX + TEST_OBJECT_NAME << "')";
	string sql = stringStream.str();
	CommonOracle db;
	db.executeUpdate( sql );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupOracle::insertTestTagObjects_( int objectId, int tagId )
{
	ostringstream stringStream;	
	stringStream << "insert into object_tag(\"object_id\", \"tag_id\") values(" << objectId << ", " << tagId << ")";
	string sql = stringStream.str();
	CommonOracle db;
	db.executeUpdate( sql );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupOracle::insertTestDimensions_()
{
	ostringstream stringStream;	
	stringStream << "insert into dimension values("	<< TEST_HIERARCHY_ID << ", " 
	<< TEST_HIERARCHY_NODE_ID << ", " 
	<< TEST_ALPHANUMERICAL_TAG_SET_ID << ", " 
	<< OracleTestIds::TEST_ALPHANUMERICAL_TAG_ID << ", "
	<< "'Test child category name'" << ", "
	<< 1 << ", " << 2 << " )";
	string sql = stringStream.str();
	CommonOracle db;
	db.executeUpdate( sql );
}
//____________________________________________________________________________________________________________________________________________________________________________________

#endif