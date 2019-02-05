/*
* ObjectPostgreSQL.cpp
* Snorri Gíslason - 2018
*/

#ifdef OC_POSTGRESQL

#include "ObjectPostgreSQL.h"

#include <sstream>
#include <memory>

#include "CommonPostgreSQL.h"
#include "../Factories/TagDataAccessFactory.h"
#include "../Factories/ObjectTagDataAccessFactory.h"
#include "../Root/TagDataAccess.h"
#include "../Root/BoundingBoxDataAccess.h"
#include "../../LayerShared/Exception.h"
#include "../../LayerShared/DebugInfo.h"

using namespace ObjectCube;
using namespace std;

//____________________________________________________________________________________________________________________________________________________________________________________

ObjectDataAccess* ObjectPostgreSQL::fetch( int id )
{
	stringstream stringStream;
	stringStream << "select p.id, p.qualified_name, p.thumbnail, p.file_type from object p where p.id = " << id;
	string select = stringStream.str(); 

	CommonPostgreSQL db;
	pqxx::result resultsHandle = db.executeSQL( select );
	//processFetch_( resultsHandle );
	setId( resultsHandle[0][0].as<int>() );
	setName( resultsHandle[0][1].as<string>() );
	setThumbnail ( resultsHandle[0][2].as<string>() );
	setFileType ( resultsHandle[0][3].as<string>() );
	setTagInfo( fetchTagInfo_( getId() ) );
	DebugInfo::getDebugInfo()->output( "ObjectMonetDB", "fetch(id)", "Done" );

	return this;
}

//____________________________________________________________________________________________________________________________________________________________________________________

ObjectDataAccess* ObjectPostgreSQL::fetch( const string& qualifiedName )
{
	stringstream stringStream;
	stringStream << "select p.id, p.qualified_name, p.thumbnail, p.file_type from object p where p.qualified_name = '" << qualifiedName << "'";
	string select = stringStream.str(); 

	CommonPostgreSQL db;
	pqxx::result resultsHandle = db.executeSQL( select );
	//processFetch_( resultsHandle );

	if(!resultsHandle.empty()){
		setId( resultsHandle[0][0].as<int>() );
		setName( resultsHandle[0][1].as<string>() );
		setThumbnail ( resultsHandle[0][2].as<string>() );
		setFileType ( resultsHandle[0][3].as<string>() );
		setTagInfo( fetchTagInfo_( getId() ) );
	}
	
	DebugInfo::getDebugInfo()->output( "ObjectMonetDB", "fetch(name)", "Done" );

	return this;
}

//____________________________________________________________________________________________________________________________________________________________________________________

/*void ObjectPostgreSQL::processFetch_( pqxx::result r)
{
	setId( r[0][0].as<int>() );
	setName( r[0][1].as<string>() );
}*/

//____________________________________________________________________________________________________________________________________________________________________________________

ObjectDataAccess* ObjectPostgreSQL::create()
{
	stringstream stringStream;
	stringStream << "insert into object ( qualified_name, thumbnail, file_type ) values ('" << getName() << "', '" << getThumbnail() << "', '" << getFileType() << "') returning id;";
	string insert = stringStream.str();

	CommonPostgreSQL db;
	setId( db.executeSQLReturningAnInteger( insert ) );
	return this;
}

//____________________________________________________________________________________________________________________________________________________________________________________

void ObjectPostgreSQL::update()
{
	stringstream stringStream;
	stringStream << "update object set qualified_name = '" << getName()
			<<  "', thumbnail = '" << getThumbnail()
			<< "', file_type = '" << getFileType()
			<< "' where id = " << getId();
	string update = stringStream.str();

	CommonPostgreSQL db;
	db.executeSQLNoResults(update);
}

//____________________________________________________________________________________________________________________________________________________________________________________

void ObjectPostgreSQL::erase()
{
	for( vector<ObjectTagDataAccess*>::iterator itr = objectTags_.begin(); itr != objectTags_.end(); ++itr ) //Remove all tags (notice that this is less fault tolerant than deleting all tags, using only object id )
	{
		//removeTag( id_, (*itr)->getTagId() );
		removeTag( (*itr) );
	}

	stringstream stringStream;
	stringStream << "delete from object where id = " << getId() ;
	string del = stringStream.str();

	CommonPostgreSQL db;
	db.executeSQLNoResults(del);
}

//____________________________________________________________________________________________________________________________________________________________________________________

void ObjectPostgreSQL::updateFileTypeFromPluginResult()
{
	stringstream stringStream;
	stringStream << "select at.tag_string "
			<< "from object_tag ot left "
			<< "join alphanumerical_tag at on ot.tag_id = at.id "
			<< "left join plugin_tag_set pts on at.tag_set_id = pts.tag_set_id "
			<< "where pts.name = 'FileType' "
			<< "and ot.object_id = " << getId();
	string select = stringStream.str();

	CommonPostgreSQL db;
	pqxx::result resultsHandle = db.executeSQL( select );

	if(!resultsHandle.empty()){
		setFileType ( resultsHandle[0][0].as<string>() );
		update();
	}
}

//____________________________________________________________________________________________________________________________________________________________________________________

vector<ObjectTagDataAccess*> ObjectPostgreSQL::fetchTagInfo_( int objectId )
{
	//Confirm er í monetdb en ekki í oracle og sqlite. Hef ekki í postgreSQL
	stringstream stringStream;
	stringStream << "select tag_id, upper_left_x, upper_left_y, lower_right_x, lower_right_y from object_tag where object_id = " << objectId << " order by tag_id";
	string sql = stringStream.str();
	
	CommonPostgreSQL db;
	pqxx::result resultsHandle = db.executeSQL( sql );

	vector<ObjectTagDataAccess*> tagInfo;
	for(pqxx::result::const_iterator c = resultsHandle.begin(); c != resultsHandle.end(); ++c)
	{
		ObjectTagDataAccess* objectTag = ObjectTagDataAccessFactory::create();
		objectTag->setTagId( c[0].as<int>() );

		Coordinate2DDataAccess upperLeft( c[1].as<int>(), c[2].as<int>() );
		Coordinate2DDataAccess lowerRight( c[3].as<int>(), c[4].as<int>() );

		BoundingBoxDataAccess* bBox = new BoundingBoxDataAccess( upperLeft, lowerRight );
		objectTag->setBoundingBox( bBox );

		tagInfo.push_back( objectTag );
	}

	return tagInfo;
}

//____________________________________________________________________________________________________________________________________________________________________________________

/*void ObjectPostgreSQL::addTag( int objectId, ObjectTagDataAccess* objectTag)
{
	stringstream stringStream;
	stringStream << "insert into object_tag ( object_id, tag_id, upper_left_x, upper_left_y, lower_right_x, lower_right_y ) values ( " << objectId << ", " << objectTag->getTagId();
	if( objectTag->hasBoundingBox() )
	{
		stringStream << ", " << objectTag->getBoundingBox()->getUpperLeftCorner().getX()
					<< ", " << objectTag->getBoundingBox()->getUpperLeftCorner().getY()
					<< ", " << objectTag->getBoundingBox()->getLowerRightCorner().getX()
					<< ", " << objectTag->getBoundingBox()->getLowerRightCorner().getY();
	}	
	else
	{
		stringStream << ", null, null, null, null";
	}

	stringStream << " )";
	string insert = stringStream.str();

	CommonPostgreSQL db;
	db.executeSQLNoResults( insert );
}*/
void ObjectPostgreSQL::addTag( ObjectTagDataAccess* objectTag )
{
	objectTag->create();
}

//____________________________________________________________________________________________________________________________________________________________________________________

/*void ObjectPostgreSQL::removeTag( int objectId, int tagId )
{
	stringstream stringStream;
	stringStream << "delete from object_tag where object_id " << objectId << " and tag_id = " << tagId;
	string del = stringStream.str();

	CommonPostgreSQL db;
	db.executeSQLNoResults(del); 
}*/

void ObjectPostgreSQL::removeTag( ObjectTagDataAccess* objectTag ) 
{
	objectTag->erase();
}

//____________________________________________________________________________________________________________________________________________________________________________________

vector<ObjectDataAccess*> ObjectPostgreSQL::fetchAllObjects()
{
	CommonPostgreSQL db;
	pqxx::result resultSet = db.executeSQL( "select p.id, p.qualified_name from object p" );

	vector<ObjectDataAccess*> objectsDA;
	/*
	error: invalid new-expression of abstract class type ‘ObjectCube::ObjectPostgreSQL’
   	ObjectPostgreSQL* objectDA = new ObjectPostgreSQL();
	*/
	for( pqxx::result::const_iterator c = resultSet.begin(); c != resultSet.end(); ++c )
	{
		ObjectPostgreSQL* objectDA = new ObjectPostgreSQL();

		objectDA->setId( c[0].as<int>() );
		objectDA->setName( c[1].as<string>() );

		objectsDA.push_back( objectDA );
	}
	
	return objectsDA;
}
//____________________________________________________________________________________________________________________________________________________________________________________

#endif
