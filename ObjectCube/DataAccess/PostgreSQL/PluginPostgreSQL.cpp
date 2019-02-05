/*
* Snorri Gíslason - 2018
*/

#ifdef OC_POSTGRESQL

#include "PluginPostgreSQL.h"

#include <sstream>
#include <memory>
#include <iostream>

#include "CommonPostgreSQL.h"
#include "PluginTagSetPostgreSQL.h"
#include "../Root/PluginTagSetDataAccess.h"
#include "../../LayerShared/Exception.h"

using namespace ObjectCube;
using namespace std;

//____________________________________________________________________________________________________________________________________________________________________________________

PluginDataAccess* PluginPostgreSQL::fetch( int id )
{
	CommonPostgreSQL db;
	
	stringstream stringStream;
	stringStream << "select p.id, p.qualified_library_name, p.description from plugin p where p.id = " << id;
	string sql = stringStream.str();

	pqxx::result resultsHandle = db.executeSQL( sql );
	
	if( resultsHandle.empty() )
	{
		throw Exception("PluginMonetDB::fetch", "No plugin retrieved" );
	}

	int id_ = resultsHandle[0][0].as<int>();

	setId( id_ );

	if(!resultsHandle[0][1].is_null()){
		setName( resultsHandle[0][1].as<string>() );	
	}
	if(!resultsHandle[0][2].is_null()){
		setDescription( resultsHandle[0][2].as<string>() );	
	}
	
	
	setPluginTagSets( fetchPluginTagSets_( id_ ) );
	
	return this;
}
//____________________________________________________________________________________________________________________________________________________________________________________

vector<PluginDataAccess*> PluginPostgreSQL::fetchAll()
{
	CommonPostgreSQL db;
	pqxx::result resultsHandle = db.executeSQL( "select p.id, p.qualified_library_name, p.description from plugin p" );
	vector<PluginDataAccess*> plugins;

	for(pqxx::result::const_iterator c = resultsHandle.begin(); c != resultsHandle.end(); ++c)
	{
		PluginDataAccess* plugin = new PluginPostgreSQL();
		plugin->setId( c[0].as<int>() );
		if(!c[1].is_null()){
			plugin->setName( c[1].as<string>() );
		}
		if(!c[2].is_null()){
			plugin->setDescription( c[2].as<string>() );
		}
		plugins.push_back( plugin );
	}
	return plugins;
}
//____________________________________________________________________________________________________________________________________________________________________________________

vector<PluginTagSetDataAccess*> PluginPostgreSQL::fetchPluginTagSets_( int pluginId )
{
	cout << "PluginPostgreSQL::fetchPluginTagSets_ = " << pluginId << endl;
	CommonPostgreSQL db;
	
	stringstream stringStream;
	stringStream << "select pt.id, pt.tag_set_type_id, pt.tag_type_id, pt.name, pt.tag_set_name, pt.tag_set_id from plugin_tag_set pt where pt.plugin_id = " << pluginId;
	string sql = stringStream.str();

	pqxx::result resultsHandle = db.executeSQL( sql );
	
	vector<PluginTagSetDataAccess*> pluginTagSets;

	for(pqxx::result::const_iterator c = resultsHandle.begin(); c != resultsHandle.end(); ++c)
	{
		PluginTagSetDataAccess* pluginTagSet = new PluginTagSetPostgreSQL();
		
		pluginTagSet->setId(c[0].as<int>());
		pluginTagSet->setPluginId( pluginId );
		pluginTagSet->setTagSetTypeId(c[1].as<int>());
		pluginTagSet->setTagTypeId(c[2].as<int>());
		if(!c[3].is_null()){
			pluginTagSet->setName( c[3].as<string>() );
		}
		if(!c[4].is_null()){
			pluginTagSet->setTagSetName( c[4].as<string>() );
		}
		if(!c[5].is_null()){
			pluginTagSet->setTagSetId(c[5].as<int>());	
		}
		
		pluginTagSets.push_back( pluginTagSet );
	}
	
	return pluginTagSets;
}
//____________________________________________________________________________________________________________________________________________________________________________________


#endif