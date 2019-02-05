/*
* Snorri Gíslason - 2018
*/


#ifdef OC_POSTGRESQL

#include "NumericalTagPostgreSQL.h"

#include <sstream>
#include <memory>

#include "CommonPostgreSQL.h"
#include "TagPostgreSQL.h"
#include "../../LayerShared/Exception.h"

using namespace ObjectCube;
using namespace std;

//____________________________________________________________________________________________________________________________________________________________________________________

NumericalTagDataAccess* NumericalTagPostgreSQL::fetch( int id )
{
	CommonPostgreSQL db;
	
	stringstream stringStream;
	stringStream << "select t.id, t.tag_set_id, t.type_id, nt.number from tag t, numerical_tag nt where t.id = nt.id and t.id = " << id;
	string sql = stringStream.str();
	
	pqxx::result resultsHandle = db.executeSQL( sql );
	
	
	processFetch_( resultsHandle );
	
	return this;
}
//____________________________________________________________________________________________________________________________________________________________________________________

NumericalTagDataAccess* NumericalTagPostgreSQL::fetch( int tagSetId, long number )
{
	CommonPostgreSQL db;
	
	stringstream stringStream;
	stringStream << "select t.id, t.tag_set_id, t.type_id, nt.number from tag t, numerical_tag nt where t.id = nt.id and t.tag_set_id = " << tagSetId << " and nt.number = " << number;
	string sql = stringStream.str();

	pqxx::result resultsHandle = db.executeSQL( sql );
	
	processFetch_( resultsHandle );	
	
	return this;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void NumericalTagPostgreSQL::processFetch_( pqxx::result resultsHandle )
{	
	if( resultsHandle.empty() )
	{
		throw Exception("NumericalTagPostgreSQL::processFetch_", "No tag retrieved" );
	}

	setId( resultsHandle[0][0].as<int>() );
	setTagSetId( resultsHandle[0][1].as<int>() );
	setTypeId( resultsHandle[0][2].as<int>() );
	setNumber( resultsHandle[0][3].as<int>() );
}
 //____________________________________________________________________________________________________________________________________________________________________________________

NumericalTagDataAccess* NumericalTagPostgreSQL::create()
{
	CommonPostgreSQL db;
	db.beginTransaction();
	
	try 
	{
		setId( TagPostgreSQL::createTag( getTagSetId(), getTypeId() ) );
		
		stringstream stringStream;
		stringStream << "insert into numerical_tag (id, number, tag_set_id) values( " << getId() << ", '" << getNumber() << "', " << getTagSetId() << ")";
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

void NumericalTagPostgreSQL::remove( int id )
{
	CommonPostgreSQL db;
	db.beginTransaction();
	
	try 
	{
		stringstream stringStream;
		stringStream << "delete from numerical_tag where id = " << id;
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

int NumericalTagPostgreSQL::inUse( int id )
{
	return TagPostgreSQL::tagInUse( id );
}
//____________________________________________________________________________________________________________________________________________________________________________________


#endif