/*
* ObjectTagPostgreSQL.cpp
* Snorri Gíslason - 2018
*/

#ifdef OC_POSTGRESQL

#include "ObjectTagPostgreSQL.h"

#include <sstream>

#include "CommonPostgreSQL.h"
#include "../Root/BoundingBoxDataAccess.h"


using namespace ObjectCube;
using namespace std;

//____________________________________________________________________________________________________________________________________________________________________________________

void ObjectTagPostgreSQL::create()
{	
	int tagId = getTagId();
	int objectId = getObjectId();
	bool confirmed = getConfirmed();
	
	double upperLeftX = getBoundingBox()->getUpperLeftCorner().getX();
	double upperLeftY = getBoundingBox()->getUpperLeftCorner().getY();
	double lowerRightX = getBoundingBox()->getLowerRightCorner().getX();
	double lowerRightY = getBoundingBox()->getLowerRightCorner().getY();
	
	CommonPostgreSQL db;
	db.beginTransaction();
	try 
	{
		stringstream stringStream;
		stringStream << "insert into object_tag ( object_id, tag_id, confirmed, upper_left_x, upper_left_y, lower_right_x, lower_right_y ) values ( " << objectId << ", "<< tagId <<", " << confirmed <<"," << upperLeftX << ", " << upperLeftY << ", " << lowerRightX << " , " << lowerRightY << " )";
		string sql = stringStream.str();
		db.executeSQLNoResults( sql );
		
		addToMaterializedView_( &db );
		
		db.commitTransaction();
	}
	catch( ... ) 
	{
		db.rollbackTransaction();
		//throw; Take out because in search we can have two or more picture with same object_id and tag_id. Example if two magnus are on same picture
		//Todo: Find another way
	}
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void ObjectTagPostgreSQL::erase()
{
	int tagId = getTagId();
	int objectId = getObjectId();
	
	double upperLeftX = getBoundingBox()->getUpperLeftCorner().getX();
	double upperLeftY = getBoundingBox()->getUpperLeftCorner().getY();
	double lowerRightX = getBoundingBox()->getLowerRightCorner().getX();
	double lowerRightY = getBoundingBox()->getLowerRightCorner().getY();
	
	CommonPostgreSQL db;
	db.beginTransaction();
	try 
	{							
		stringstream stringStream;
		string sql;
		stringStream << "delete from object_tag where object_id = " << objectId <<" and tag_id = " << tagId <<" and upper_left_x = " << upperLeftX <<" and \
									upper_left_y = " << upperLeftY << " and lower_right_x = " << lowerRightX <<" and lower_right_y = " << lowerRightY; 
		sql = stringStream.str();
		db.executeSQLNoResults( sql );
        
		stringstream stringStream2;
		string sql2;
		
		stringStream2 << "delete from dimension_tag_object where object_id = " << objectId << " and tag_id = " << tagId << " and upper_left_x = " << upperLeftX <<" and \
									upper_left_y = " << upperLeftY << " and lower_right_x = " << lowerRightX << " and lower_right_y = " << lowerRightY; 
		sql2 = stringStream2.str();
		db.executeSQLNoResults( sql2 );
		db.commitTransaction();
	}
	catch( ... ) 
	{
		db.rollbackTransaction();
		throw;
	}
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void ObjectTagPostgreSQL::modify() //Confirmed is the only column not in the primary key
{
	int tagId = getTagId();
	int objectId = getObjectId();
	bool confirmed = getConfirmed();
	
	double upperLeftX = getBoundingBox()->getUpperLeftCorner().getX();
	double upperLeftY = getBoundingBox()->getUpperLeftCorner().getY();
	double lowerRightX = getBoundingBox()->getLowerRightCorner().getX();
	double lowerRightY = getBoundingBox()->getLowerRightCorner().getY();
	
	CommonPostgreSQL db;
	db.beginTransaction();
	try 
	{
		stringstream stringStream;
		string sql;
		stringStream << "update object_tag set confirmed = " << confirmed <<" where object_id = " << objectId <<" and tag_id = "<< tagId <<" and upper_left_x = " << upperLeftX <<" and \
									upper_left_y = " << upperLeftY <<" and lower_right_x = " << lowerRightX <<" and lower_right_y = " << lowerRightY; 
		sql = stringStream.str();
		db.executeSQLNoResults( sql );
		db.commitTransaction();
	}
	catch( ... ) 
	{
		db.rollbackTransaction();
		throw;
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________

void ObjectTagPostgreSQL::addToMaterializedView_( CommonPostgreSQL* db )
{	/* Śé ekki tilgang með þessu, skoða betur síðast
	int tagId = getTagId();
	int objectId = getObjectId();
	
	double upperLeftX = getBoundingBox()->getUpperLeftCorner().getX();
	double upperLeftY = getBoundingBox()->getUpperLeftCorner().getY();
	double lowerRightX = getBoundingBox()->getLowerRightCorner().getX();
	double lowerRightY = getBoundingBox()->getLowerRightCorner().getY();
								 
	stringstream stringStream;
	string sql;
	stringStream << "insert into dimension_tag_object \
						 select	d.id as dimension_id, d.node_id, ot.tag_id, ot.object_id, ot.upper_left_x, \
						 ot.upper_left_y, ot.lower_right_x, ot.lower_right_y, ot.confirmed, d.left_border, d.right_border \
						 from	dimension d, object_tag ot \
						 where	ot.tag_id = " << tagId <<" and d.tag_id = ot.tag_id and ot.object_id = " << objectId <<" and ot.upper_left_x = " << upperLeftX <<" and \
						 ot.upper_left_y = " << upperLeftY << " and ot.lower_right_x = " << lowerRightX << " and ot.lower_right_y = " << lowerRightY; 
	sql = stringStream.str();
	db->executeSQLNoResults( sql );
	*/
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

#endif