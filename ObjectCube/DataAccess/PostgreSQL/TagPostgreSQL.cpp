/*
* Snorri Gíslason - 2018
*/

#ifdef OC_POSTGRESQL

#include "TagPostgreSQL.h"

#include <sstream>
#include "CommonPostgreSQL.h"
#include "../../LayerShared/Exception.h"

using namespace ObjectCube;
using namespace std;

//____________________________________________________________________________________________________________________________________________________________________________________

TagDataAccess* TagPostgreSQL::fetch( int id )
{
	CommonPostgreSQL db;
	
	stringstream stringStream;
	stringStream << "select t.id, t.tag_set_id, t.type_id from tag t where t.id = " << id;
	string sql = stringStream.str();
	
	pqxx::result resultsHandle = db.executeSQL( sql );

	setId( resultsHandle[0][0].as<int>() );
	setTagSetId( resultsHandle[0][1].as<int>() );
	setTypeId( resultsHandle[0][2].as<int>() );

	return this;
}
//____________________________________________________________________________________________________________________________________________________________________________________

TagDataAccess* TagPostgreSQL::create()
{
	setId( TagPostgreSQL::createTag( getTagSetId(), getTypeId() ) );
	return this;
}
//____________________________________________________________________________________________________________________________________________________________________________________
int TagPostgreSQL::inUse( int id )
{
	return TagPostgreSQL::tagInUse( id );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagPostgreSQL::remove( int id )
{
	TagPostgreSQL::removeTag( id );
}
//____________________________________________________________________________________________________________________________________________________________________________________

int TagPostgreSQL::createTag( int tagSetId, int typeId )
{
	stringstream stringStream;
	stringStream << "insert into tag (tag_set_id, type_id) values ( " << tagSetId << ", " << typeId << ") returning id;";
	string sql = stringStream.str();
	
	CommonPostgreSQL db;
	
	int id = db.executeSQLReturningAnInteger( sql );

	return id;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagPostgreSQL::removeTag( int id )
{
	CommonPostgreSQL db;
	
	stringstream stringStream;
	stringStream << "delete from tag where id = " << id;
	string sql = stringStream.str();


	db.executeSQLNoResults( sql );
	stringstream stringStream2;
	string sql2;
	stringStream2 << "delete from dimension_tag_object where tag_id = " << id;
	sql2 = stringStream2.str();

	db.executeSQLNoResults( sql2 );
}
//____________________________________________________________________________________________________________________________________________________________________________________

int TagPostgreSQL::tagInUse( int id )
{
	CommonPostgreSQL db;
	
	stringstream stringStream;
	stringStream << "select count(tag_id) from object_tag where tag_id = " << id;
	string sql = stringStream.str();

	int count = db.executeSQLReturningAnInteger( sql );
	
	return count;
}
//____________________________________________________________________________________________________________________________________________________________________________________



#endif