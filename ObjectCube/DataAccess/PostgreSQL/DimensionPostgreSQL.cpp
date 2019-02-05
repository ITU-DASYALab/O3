/*
* Snorri Gíslason - 2018
*/

#ifdef OC_POSTGRESQL

#include "DimensionPostgreSQL.h"

#include <iostream>
#include <sstream>
#include <memory>

#include "CommonPostgreSQL.h"
#include "../Root/HierarchyNodeDataAccess.h"
#include "HierarchyNodePostgreSQL.h"

using namespace ObjectCube;
using namespace std;

//____________________________________________________________________________________________________________________________________________________________________________________

int DimensionPostgreSQL::nextId()
{
	CommonPostgreSQL db;
	return db.getMaxValue( "dimension", "id" ) + 1;
}
//____________________________________________________________________________________________________________________________________________________________________________________

vector<HierarchyNodeDataAccess*> DimensionPostgreSQL::fetch( int id )
{
	CommonPostgreSQL db;
	stringstream stringStream;
	stringStream << "select d.id, d.node_id, d.tag_set_id, d.tag_id, d.child_category_title, d.left_border, d.right_border from dimension d where d.id = " << id << " order by d.left_border asc";
	string sql = stringStream.str();
	
	pqxx::result resultsHandle = db.executeSQL( sql );
		
	vector<HierarchyNodeDataAccess*> nodes;

	for(pqxx::result::const_iterator c = resultsHandle.begin(); c != resultsHandle.end(); ++c)
	{
		HierarchyNodeDataAccess* node = new HierarchyNodePostgreSQL();
		node->setHierarchyId( c[0].as<int>() );
		node->setId( c[1].as<int>() );
		node->setTagSetId( c[2].as<int>() );
		node->setTagId( c[3].as<int>() );
		node->setChildCategoryTitle( c[4].as<string>() );
		node->setLeftBorder( c[5].as<int>() );
		node->setRightBorder( c[6].as<int>() );


		nodes.push_back( node );
	}
	
	return nodes;	
}
//____________________________________________________________________________________________________________________________________________________________________________________


#endif