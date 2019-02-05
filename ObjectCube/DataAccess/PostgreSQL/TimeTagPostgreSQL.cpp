/*
* Snorri Gíslason - 2018
*/

#ifdef OC_POSTGRESQL

#include "TimeTagPostgreSQL.h"

#include <sstream>
#include <memory>
#include <stdlib.h>

#include "CommonPostgreSQL.h"
#include "TagPostgreSQL.h"
#include "../../LayerShared/Exception.h"
#include "../../LayerShared/TimeSupport.h"

using namespace ObjectCube;
using namespace std;

//____________________________________________________________________________________________________________________________________________________________________________________

TagDataAccess* TimeTagPostgreSQL::fetch( int id )
{
	CommonPostgreSQL db;
	
	stringstream stringStream;
	stringStream << "select t.id, t.tag_set_id, t.type_id, tt.tag_time from tag t, time_tag tt where t.id = tt.id and t.id = " << id;
	string sql = stringStream.str();

	pqxx::result resultsHandle = db.executeSQL( sql );
	
	processFetch_( resultsHandle );
	
	return this;	
}
//____________________________________________________________________________________________________________________________________________________________________________________

TimeTagDataAccess* TimeTagPostgreSQL::fetch( int tagSetId, int hours, int minutes, int seconds, int milliseconds )
{
	string formattedTime = CommonPostgreSQL::timeToSQLString( hours, minutes, seconds, milliseconds );
	
	CommonPostgreSQL db;
	
	stringstream stringStream;
	stringStream << "select t.id, t.tag_set_id, t.type_id, tt.tag_time from tag t, time_tag tt where t.id = tt.id and tt.tag_set_id = " << tagSetId << " and tt.tag_time = " << formattedTime;
	string sql = stringStream.str();
	
	pqxx::result resultsHandle = db.executeSQL( sql );
	
	processFetch_( resultsHandle );	
	
	return this;	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TimeTagPostgreSQL::processFetch_( pqxx::result resultsHandle )
{
	if( resultsHandle.empty() )
	{
		throw Exception("TimeTagMonetDB::processFetch_", "No tag retrieved" );
	}

	setId( resultsHandle[0][0].as<int>() );
	setTagSetId( resultsHandle[0][1].as<int>() );
	setTypeId( resultsHandle[0][2].as<int>() );

	if( !resultsHandle[0][3].is_null() )
	{
		TimeTagPostgreSQL::sqlTimeToTag( this, resultsHandle[0][3].c_str() );
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TimeTagPostgreSQL::sqlTimeToTag( TimeTagDataAccess* tag, const string& timeAsString )
{
	int startPos = 0, delimiterPos = 0;
	try 
	{
		delimiterPos = timeAsString.find( ':', startPos );
		tag->setHours( atoi( timeAsString.substr( startPos, delimiterPos - startPos ).data() ) );
		startPos = delimiterPos + 1;
		delimiterPos = timeAsString.find( ':', startPos );
		tag->setMinutes( atoi( timeAsString.substr( startPos, delimiterPos - startPos ).data() ) );
		startPos = delimiterPos + 1;
		delimiterPos = timeAsString.find( '.', startPos );
		tag->setSeconds( atoi( timeAsString.substr( startPos, delimiterPos - startPos ).data() ) );
		tag->setMilliseconds( atoi( timeAsString.substr( delimiterPos + 1 ).data() ) );
	}
	catch (exception& e) 
	{
		throw Exception( "TimeTagPostgreSQL::sqlTimeToTag", e.what() );
	}
	catch( ... )
	{
		throw Exception( "TimeTagPostgreSQL::sqlTimeToTag", "Unknown error in converting string to TimeTag!" );
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________

TagDataAccess* TimeTagPostgreSQL::create( )
{
	CommonPostgreSQL db;
	db.beginTransaction();
	
	try 
	{
		setId( TagPostgreSQL::createTag( getTagSetId(), getTypeId() ) ); //MÖGULEGA DEADLOCK	
		
		stringstream stringStream;
		stringStream << "insert into time_tag (id, tag_set_id, tag_time) values( " << getId() << ", " << getTagSetId() 
		<< ", " << CommonPostgreSQL::timeToSQLString( getHours(), getMinutes(), getSeconds(), getMilliseconds() ) << " )";
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

int TimeTagPostgreSQL::inUse( int id )
{
	return TagPostgreSQL::tagInUse( id );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TimeTagPostgreSQL::remove( int id )
{
	CommonPostgreSQL db;
	db.beginTransaction();
	
	try 
	{
		stringstream stringStream;
		stringStream << "delete from time_tag where id = " << id;
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