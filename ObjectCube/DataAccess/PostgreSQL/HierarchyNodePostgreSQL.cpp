/*
* Snorri Gíslason - 2018
*/

#ifdef OC_POSTGRESQL

#include "HierarchyNodePostgreSQL.h"

#include <sstream>

#include "CommonPostgreSQL.h"

using namespace ObjectCube;
using namespace std;

//____________________________________________________________________________________________________________________________________________________________________________________

HierarchyNodeDataAccess* HierarchyNodePostgreSQL::create()
{
	CommonPostgreSQL db;
	setId( db.getMaxValue( "dimension", "node_id") + 1 );
	stringstream stringStream;
	stringStream << "insert into dimension values( " << getDimensionId() << ", " << getId() << ", " << getTagSetId() << ", " << 
	getTagId() << ", '" << getChildCategoryTitle() << "', " << getLeftBorder() << ", " << getRightBorder() << ")";
	string sql = stringStream.str();
	
	db.beginTransaction();
	try 
	{
		db.executeSQLNoResults( sql );
		/*
		int dimension_tag_object_id = db.getMaxValue( "dimension_tag_object", "id") + 1;

		
		stringstream stringStream2;
		string sql2;
		stringStream2 << "insert into dimension_tag_object \
			select " << dimension_tag_object_id << " as id, d.id as dimension_id, d.node_id, ot.tag_id, ot.object_id, \
			ot.upper_left_x, ot.upper_left_y, ot.lower_right_x, ot.lower_right_y, ot.confirmed, \
			d.left_border, d.right_border \
			from dimension d, object_tag ot \
			where d.tag_id = ot.tag_id and node_id = " << getId();
		
		sql2 = stringStream2.str();
		db.executeSQLNoResults( sql2 );
		*/
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

void HierarchyNodePostgreSQL::update()
{
	stringstream stringStream;
	stringStream << "update dimension set left_border = " << getLeftBorder() 
	<<  ", right_border = " << getRightBorder()
	<< " where id = " << getDimensionId()
	<< " and node_id = " << getId();
	
	string sql =  stringStream.str();
	
	CommonPostgreSQL db;
	db.beginTransaction();
	try 
	{
		db.executeSQLNoResults( sql );	
		
		//This should be a trigger, MonetDB has limited support
		stringstream stringStreamMV;
		stringStreamMV << "update dimension_tag_object set left_border = " << getLeftBorder() 
		<<  ", right_border = " << getRightBorder() << "where dimension_id = " << getDimensionId()
		<< " and node_id = " << getId();
		db.executeSQLNoResults( stringStreamMV.str() );
		
		db.commitTransaction();
	}
	catch( ... ) 
	{
		db.rollbackTransaction();
		throw;
	}
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void HierarchyNodePostgreSQL::remove()
{
	stringstream stringStream;
	stringStream << "delete from dimension where id = " << getDimensionId() << " and node_id = " << getId();
	string sql =  stringStream.str();
	
	
	CommonPostgreSQL db;
	db.beginTransaction();
	try 
	{
		db.executeSQLNoResults( sql );
		//This should be in a trigger, MonetDB has limited support
		
		stringstream stringStream2;
		string sql2;
		stringStream2 << "delete from dimension_tag_object where dimension_id = " << hierarchyId_ <<" and node_id = " << id_;
		sql2 = stringStream2.str();
		db.executeSQLNoResults( sql2 );
		
		db.commitTransaction();
	}
	catch( ... ) 
	{
		db.rollbackTransaction();
		throw;
	}
	
	setId( INVALID );
}
//____________________________________________________________________________________________________________________________________________________________________________________


#endif
