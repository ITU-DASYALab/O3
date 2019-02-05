/*
* Snorri Gíslason - 2018
*/

#ifdef OC_POSTGRESQL

#include "DateTagPostgreSQL.h"

#include <sstream>
#include <memory>
#include <stdlib.h>

#include "CommonPostgreSQL.h"
#include "TagPostgreSQL.h"
#include "../../LayerShared/Exception.h"
#include "../../LayerShared/DateSupport.h"

using namespace ObjectCube;
using namespace std;

//____________________________________________________________________________________________________________________________________________________________________________________

TagDataAccess* DateTagPostgreSQL::fetch( int id )
{
	CommonPostgreSQL db;
	
	stringstream stringStream;
	stringStream << "select t.id, t.tag_set_id, t.type_id, dt.tag_date from tag t, date_tag dt where t.id = dt.id and t.id = " << id;
	string sql = stringStream.str();
	
	
	pqxx::result resultsHandle = db.executeSQL( sql );
	
	processFetch_( resultsHandle );
	
	return this;
}
//____________________________________________________________________________________________________________________________________________________________________________________

DateTagDataAccess* DateTagPostgreSQL::fetch( int tagSetId, int year, int month, int dayOfMonth )
{
	string formattedDate = CommonPostgreSQL::dateToSQLString( year, month, dayOfMonth );
	
	CommonPostgreSQL db;

	stringstream stringStream;
	stringStream << "select t.id, t.tag_set_id, t.type_id, dt.tag_date from tag t, date_tag dt where t.id = dt.id and t.tag_set_id = " << tagSetId <<"  and tag_date = " << formattedDate;
	string sql = stringStream.str();
	
	
	pqxx::result resultsHandle = db.executeSQL( sql );
	
	processFetch_( resultsHandle );	
	
	return this;			
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DateTagPostgreSQL::processFetch_( pqxx::result resultsHandle )
{
	if( resultsHandle.empty() )
	{
		throw Exception("DateTagPostgreSQL::processFetch_", "No tag retrieved" );
	}

	setId( resultsHandle[0][0].as<int>() );
	setTagSetId( resultsHandle[0][1].as<int>() );
	setTypeId( resultsHandle[0][2].as<int>() );
	
	if( !resultsHandle[0][3].is_null() )
	{
		DateTagPostgreSQL::sqlDateToTag( this, resultsHandle[0][3].c_str() );
	}	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DateTagPostgreSQL::sqlDateToTag( DateTagDataAccess* tag, const string& dateAsString )
{
	int startPos = 0, delimiterPos = 0;
	try 
	{
		delimiterPos = dateAsString.find( '-', startPos );
		tag->setYear( atoi( dateAsString.substr( startPos, delimiterPos - startPos ).data() ) );
		startPos = delimiterPos + 1;
		delimiterPos = dateAsString.find( '-', startPos );
		tag->setMonth( atoi( dateAsString.substr( startPos, delimiterPos - startPos ).data() ) );
		tag->setDayOfMonth( atoi( dateAsString.substr( delimiterPos + 1 ).data() ) );
	}
	catch (exception& e) 
	{
		throw Exception( "DateTagPostgreSQL::sqlDateToTag", e.what() );
	}
	catch( ... )
	{
		throw Exception( "DateTagPostgreSQL::sqlDateToTag", "Unknown error in converting string to DateTag!" );
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________

TagDataAccess* DateTagPostgreSQL::create( )
{
	CommonPostgreSQL db;
	db.beginTransaction();
	
	try 
	{
		setId( TagPostgreSQL::createTag( getTagSetId(), getTypeId() ) );
		
		stringstream stringStream;
		stringStream << "insert into date_tag (id, tag_set_id, tag_date) values( " << getId() << ", " << getTagSetId() 
														   << ", " << CommonPostgreSQL::dateToSQLString( getYear(), getMonth(), getDayOfMonth() ) << " )";
		string sql = stringStream.str();
		
		db.executeSQLNoResults( sql );
		db.commitTransaction();
	}
	catch( ... ) 
	{
		db.rollbackTransaction();
		throw;
	}

	return this;	
}
//____________________________________________________________________________________________________________________________________________________________________________________

int DateTagPostgreSQL::inUse( int id )
{
	return TagPostgreSQL::tagInUse( id );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DateTagPostgreSQL::remove( int id )
{
	CommonPostgreSQL db;
	db.beginTransaction();
	
	try 
	{
		stringstream stringStream;
		stringStream << "delete from date_tag where id = " << id; 
		string sql = stringStream.str();
		db.executeSQLNoResults( sql );
		
		TagPostgreSQL::removeTag( id );
		
		db.commitTransaction();
	}
	catch( ... ) 
	{
		db.rollbackTransaction();
		throw;
	}
	
}
//____________________________________________________________________________________________________________________________________________________________________________________


#endif