/*
* Snorri Gíslason - 2018
*/

#ifdef OC_POSTGRESQL

#include "RGBTagPostgreSQL.h"

#include <iostream>
#include <sstream>
#include <fstream>
#include <memory>
#include <algorithm>

#include "CommonPostgreSQL.h"
#include "TagPostgreSQL.h"
#include "../../LayerShared/Exception.h"
#include "../../LayerShared/StringSupport.h"

using namespace ObjectCube;
using namespace std;

//____________________________________________________________________________________________________________________________________________________________________________________

RGBTagDataAccess* RGBTagPostgreSQL::fetch( int id )
{
	CommonPostgreSQL db;
	stringstream stringStream;
	stringStream << "select t.id, t.tag_set_id, t.type_id, at.rgb from tag t, RGB_tag at where t.id = at.id and t.id = " << id;
	string sql = stringStream.str();
	
	
	pqxx::result resultsHandle = db.executeSQL( sql );
	
	processFetch_( resultsHandle );
	
	return this;
}
//____________________________________________________________________________________________________________________________________________________________________________________

RGBTagDataAccess* RGBTagPostgreSQL::fetch( int tagSetId, const string& name )
{
	CommonPostgreSQL db;
	string escapedName = StringSupport::neutralizeControlCharacters( name );

	stringstream stringStream;
	stringStream << "select t.id, t.tag_set_id, t.type_id, at.rgb from tag t, RGB_tag at where t.id = at.id and t.tag_set_id = " << tagSetId <<" and at.tag_string = '" << escapedName <<"'";
	string sql = stringStream.str();
	
	pqxx::result resultsHandle = db.executeSQL( sql );
	
	processFetch_( resultsHandle );	
	
	return this;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void RGBTagPostgreSQL::processFetch_( pqxx::result r )
{
	setId( r[0][0].as<int>() );
	setTagSetId( r[0][1].as<int>() );
	setTypeId( r[0][2].as<int>() );

	string rgb = r[0][3].as<string>();
	rgb = rgb.substr(1, rgb.size() - 2);
	replace(rgb.begin(), rgb.end(), ',', ';');
	rgb.erase(std::remove(rgb.begin(), rgb.end(), ' '), rgb.end());
	setName( rgb );
}
//____________________________________________________________________________________________________________________________________________________________________________________

RGBTagDataAccess* RGBTagPostgreSQL::create()
{
	CommonPostgreSQL db;
	db.beginTransaction(); 
	
	try 
	{
		setId( TagPostgreSQL::createTag( getTagSetId(), getTypeId() ) );
		//backslash all ' and " in original string
		const string escapedName = StringSupport::neutralizeControlCharacters( getName() );
		vector<string> rgb = StringSupport::split(escapedName, ';'); // TODO: take in vector

		stringstream stringStream;
		stringStream << "insert into RGB_tag (id, rgb, tag_set_id) values( " << getId() << ", cube(array[" << rgb[0] << "," << rgb[1] << "," << rgb[2] << "]), " << getTagSetId() << ")";
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

void RGBTagPostgreSQL::remove( int id )
{
	CommonPostgreSQL db;
	db.beginTransaction();
	
	try 
	{
		
		stringstream stringStream;
		stringStream << "delete from RGB_tag where id = " << id; 
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

int RGBTagPostgreSQL::inUse( int id )
{
	return TagPostgreSQL::tagInUse( id );
}
//____________________________________________________________________________________________________________________________________________________________________________________


#endif