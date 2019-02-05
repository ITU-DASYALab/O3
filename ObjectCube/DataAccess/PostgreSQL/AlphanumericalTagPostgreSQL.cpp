/*
* Snorri Gíslason - 2018
*/

#ifdef OC_POSTGRESQL

#include "AlphanumericalTagPostgreSQL.h"

#include <iostream>
#include <sstream>
#include <memory>

#include "CommonPostgreSQL.h"
#include "TagPostgreSQL.h"
#include "../../LayerShared/Exception.h"
#include "../../LayerShared/StringSupport.h"

using namespace ObjectCube;
using namespace std;

//____________________________________________________________________________________________________________________________________________________________________________________

AlphanumericalTagDataAccess* AlphanumericalTagPostgreSQL::fetch( int id )
{
	CommonPostgreSQL db;
	stringstream stringStream;
	stringStream << "select t.id, t.tag_set_id, t.type_id, at.tag_string from tag t, alphanumerical_tag at where t.id = at.id and t.id = " << id;
	string sql = stringStream.str();
	
	
	pqxx::result resultsHandle = db.executeSQL( sql );
	
	processFetch_( resultsHandle );
	
	return this;
}
//____________________________________________________________________________________________________________________________________________________________________________________

AlphanumericalTagDataAccess* AlphanumericalTagPostgreSQL::fetch( int tagSetId, const string& name )
{
	CommonPostgreSQL db;
	string escapedName = StringSupport::neutralizeControlCharacters( name );

	stringstream stringStream;
	stringStream << "select t.id, t.tag_set_id, t.type_id, at.tag_string from tag t, alphanumerical_tag at where t.id = at.id and t.tag_set_id = " << tagSetId <<" and at.tag_string = '" << escapedName <<"'";
	string sql = stringStream.str();
	
	pqxx::result resultsHandle = db.executeSQL( sql );
	
	processFetch_( resultsHandle );	
	
	return this;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void AlphanumericalTagPostgreSQL::processFetch_( pqxx::result r )
{
	setId( r[0][0].as<int>() );
	setTagSetId( r[0][1].as<int>() );
	setTypeId( r[0][2].as<int>() );
	setName( r[0][3].as<string>() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

AlphanumericalTagDataAccess* AlphanumericalTagPostgreSQL::create()
{
	CommonPostgreSQL db;
	db.beginTransaction(); 
	
	try 
	{
		setId( TagPostgreSQL::createTag( getTagSetId(), getTypeId() ) );
		
		//backslash all ' and " in original string
		string escapedName = StringSupport::neutralizeControlCharacters( getName() );
		
		stringstream stringStream;
		stringStream << "insert into alphanumerical_tag (id, tag_string, tag_set_id) values( " << getId() << ", '" << escapedName << "', " << getTagSetId() << ")";
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

void AlphanumericalTagPostgreSQL::remove( int id )
{
	CommonPostgreSQL db;
	db.beginTransaction();
	
	try 
	{
		
		stringstream stringStream;
		stringStream << "delete from alphanumerical_tag where id = " << id; 
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

int AlphanumericalTagPostgreSQL::inUse( int id )
{
	return TagPostgreSQL::tagInUse( id );
}
//____________________________________________________________________________________________________________________________________________________________________________________


#endif