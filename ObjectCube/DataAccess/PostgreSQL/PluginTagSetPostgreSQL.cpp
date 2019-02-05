/*
* Snorri Gíslason - 2018
*/

#ifdef OC_POSTGRESQL

#include "PluginTagSetPostgreSQL.h"

#include <sstream>

#include "CommonPostgreSQL.h"
#include "../../LayerShared/Exception.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

void PluginTagSetPostgreSQL::updateTagSetId( int id, int tagSetId )
{
	CommonPostgreSQL db;

	stringstream stringStream;
	stringStream << "update plugin_tag_set set tag_set_id = " << tagSetId << " where id = " << id;
	string sql = stringStream.str();
	db.executeSQLNoResults( sql );
	
	return;
}
//____________________________________________________________________________________________________________________________________________________________________________________


#endif