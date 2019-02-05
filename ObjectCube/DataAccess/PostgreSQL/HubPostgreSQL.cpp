/*
* Snorri Gíslason - 2018
*/


#ifdef OC_POSTGRESQL

#include "HubPostgreSQL.h"

#include <iostream>
#include <string.h>
#include <sstream>
#include <memory>

#include "CommonPostgreSQL.h"
#include "../Root/ObjectDataAccess.h"
#include "../Root/TagSetDataAccess.h"
#include "TagSetPostgreSQL.h"
#include "../Root/TagDataAccess.h"
#include "../Root/FilterDataAccess.h"
#include "../../LayerShared/SharedDefinitions.h"
#include "../../LayerShared/DebugInfo.h"


using namespace ObjectCube;
using namespace std;

//____________________________________________________________________________________________________________________________________________________________________________________

vector<StateObjectDataAccess*> HubPostgreSQL::getObjects( const string& select )
{
	vector<StateObjectDataAccess*> objectsDA;
	CommonPostgreSQL db;
	pqxx::result resultsHandle = db.executeSQL( select );
	
	int objectId = 0, tagId = 0, filterId = 0, dimensionNodeId = 0;
	
	StateObjectDataAccess* stateObjectDA = 0; 
	StateTagDataAccess* stateTagDA = 0;
	
	int lastObjectId = 0, lastTagId = 0;
	for(pqxx::result::const_iterator c = resultsHandle.begin(); c != resultsHandle.end(); ++c)
	{
		objectId = c[0].as<int>();
		if( objectId != lastObjectId ) //New object
		{
			if( stateObjectDA != 0 )
			{
				objectsDA.push_back( stateObjectDA );
			}
			lastObjectId = objectId;
			lastTagId = 0; //New iteration
			
			stateObjectDA = new StateObjectDataAccess();
			stateObjectDA->setId( objectId );
		}
		tagId = c[2].as<int>();
		if( stateObjectDA != 0 && tagId != lastTagId)
		{
			lastTagId = tagId;
			stateTagDA = new StateTagDataAccess();
			stateTagDA->setTagId( tagId );
			stateObjectDA->addTag( stateTagDA );
			
			//Sækjum tögin í application lagi (úr tag-set, ekki DB).
		} 
		filterId = c[3].as<int>();
		dimensionNodeId = c[4].as<int>();
		if( stateTagDA != 0 && filterId != INVALID_VALUE )
		{
			stateTagDA->addFilterAndDimensionNodeId( filterId, dimensionNodeId );		
		}
		if( stateObjectDA != 0 && !c[1].is_null() )
		{
			stateObjectDA->setName( c[1].as<string>() );
		}
	}

	if( stateObjectDA != 0 )
	{
		objectsDA.push_back( stateObjectDA);
	}
	
	return objectsDA;
}
//____________________________________________________________________________________________________________________________________________________________________________________

vector<StateObjectDataAccess*> HubPostgreSQL::getObjects( const vector<FilterDataAccess*>& filters )
{
	string select = filtersToSelect_( filters );
	DebugInfo::getDebugInfo()->output( "HubPostgreSQL", "getObjects", "select:\n" + select );
	
	return getObjects( select );
}
//____________________________________________________________________________________________________________________________________________________________________________________

string HubPostgreSQL::filtersToSelect_( const vector<FilterDataAccess*>& filters )
{
	string select = "SELECT c.ID, c.QUALIFIED_NAME, c.TAG_ID, c.FILTER_ID, c.DIMENSION_NODE_ID, c.UPPER_LEFT_X, c.UPPER_LEFT_Y, c.LOWER_RIGHT_X, c.LOWER_RIGHT_Y\nFROM\n(\n\tSELECT b.ID, b.QUALIFIED_NAME, b.TAG_ID, b.FILTER_ID, b.DIMENSION_NODE_ID, b.UPPER_LEFT_X, b.UPPER_LEFT_Y, b.LOWER_RIGHT_X, b.LOWER_RIGHT_Y\n\tFROM\n\t(\n";	
	
	string filtrationSubSelect;
	bool connectRestrictions = false;
	
	for( vector<FilterDataAccess*>::const_iterator itr = filters.begin(); itr != filters.end(); ++itr )
	{
		string restriction = (*itr)->getSelectionPredicate();
		string filtration = (*itr)->getFiltrationPredicate();
		if( connectRestrictions )
		{
			select += "\n\t\tUNION ALL\n"; 
			filtrationSubSelect += "\n\t\tINTERSECT\n";
		}
		connectRestrictions = true;
		select += restriction;
		filtrationSubSelect += filtration;
	}
	//Having gone through all filters
	
	if( filtrationSubSelect.length() == 0 ) //No filters in effect
	{
		stringstream stringStream;
		stringStream	<< "select o.id, o.qualified_name, ot.tag_id, " << INVALID_VALUE << " as filter_id, " << INVALID_VALUE << " as dimension_node_id, ot.upper_left_x, ot.upper_left_y, ot.lower_right_x, ot.lower_right_y "
		<< "from object o, object_tag ot "
		<< "where o.id = ot.object_id "
		<< "order by ID, TAG_ID, FILTER_ID desc";
		select = stringStream.str();
	}
	else 
	{
		select += "\n\t) as b,\n\t(\n";
		select += filtrationSubSelect;
		select += "\n\t) as a\n\twhere b.id = a.id\n\tUNION ALL\n";
		
		stringstream additionalTagsStream;
		additionalTagsStream << "select	ot.object_id as id, '' as qualified_name, ot.tag_id, " << INVALID_VALUE << " as filter_id, " << INVALID_VALUE << " as dimension_node_id, ot.upper_left_x, ot.upper_left_y, ot.lower_right_x, ot.lower_right_y "
		<< " from object_tag ot where ot.object_id in ( " <<  filtrationSubSelect << "\n\t)\n) as c\norder by c.ID, c.TAG_ID, c.FILTER_ID desc";
		
		select += additionalTagsStream.str();
	}
	
	setObjectQueryAsString( select );
	return select;
}
//____________________________________________________________________________________________________________________________________________________________________________________

StateDataAccess HubPostgreSQL::getState( const string& select )
{
	vector<StateObjectDataAccess*> objectsDA;
	map<int, map<int, vector<int> > > filterIdNodeIdObjectIds;
	
	CommonPostgreSQL db;
	pqxx::result resultsHandle = db.executeSQL( select );

	int objectId = 0, tagId = 0, filterId = 0, dimensionNodeId = 0;
	
	StateObjectDataAccess* stateObjectDA = 0; 
	StateTagDataAccess* stateTagDA = 0;
	
	int lastObjectId = 0, lastTagId = 0;

	for(pqxx::result::const_iterator c = resultsHandle.begin(); c != resultsHandle.end(); ++c)
	{
		objectId = c[0].as<int>();
		if( objectId != lastObjectId ) //New object
		{
			if( stateObjectDA != 0 )
			{
				DebugInfo::getDebugInfo()->output( "HubPostgreSQL", "getState", "name:\n" + stateObjectDA->getName() );
				objectsDA.push_back( stateObjectDA);
			}
			lastObjectId = objectId;
			lastTagId = 0; //New iteration
			
			stateObjectDA = new StateObjectDataAccess();
			stateObjectDA->setId( objectId );
		}

		tagId = c[2].as<int>();
		if( stateObjectDA != 0 && tagId != lastTagId)
		{
			lastTagId = tagId;
			stateTagDA = new StateTagDataAccess();
			stateTagDA->setTagId( tagId );
			stateObjectDA->addTag( stateTagDA );
			
			//Sækjum tögin í application lagi (úr tag-set, ekki DB).
		}

		filterId = c[3].as<int>();
		dimensionNodeId = c[4].as<int>();
		if( stateTagDA != 0 && filterId != INVALID_VALUE )
		{
			stateTagDA->addFilterAndDimensionNodeId( filterId, dimensionNodeId );		
			
			filterIdNodeIdObjectIds[ filterId ][dimensionNodeId].push_back( objectId );
		}	

		if( stateObjectDA != 0 && !c[1].is_null() && c[1].as<string>() != "")
		{
			stateObjectDA->setName( c[1].as<string>() );
		}

		
	}
	
	if( stateObjectDA != 0 )
	{
		DebugInfo::getDebugInfo()->output( "HubPostgreSQL", "getState", "name:\n" + stateObjectDA->getName() );
		objectsDA.push_back( stateObjectDA );
	}
	StateDataAccess retState;
	retState.setObjects( objectsDA );
	retState.setFilterIdNodeIdObjectsIds( filterIdNodeIdObjectIds );
	return retState;	
}
//____________________________________________________________________________________________________________________________________________________________________________________

StateDataAccess HubPostgreSQL::getState( const vector<FilterDataAccess*>& filters  )
{
	string select = filtersToSelect_( filters );
	DebugInfo::getDebugInfo()->output( "HubPostgreSQL", "getState", "select:\n" + select );
	
	return getState( select );		
}

//____________________________________________________________________________________________________________________________________________________________________________________
unsigned int HubPostgreSQL::getObjectCount()
{
	CommonPostgreSQL db;

	pqxx::result resultsHandle = db.executeSQL( "select count(id) from object");
	int count = resultsHandle[0][0].as<int>();

	return count;
}

//____________________________________________________________________________________________________________________________________________________________________________________

vector<TagSetDataAccess*> HubPostgreSQL::getTagSets()
{
	DebugInfo::getDebugInfo()->output( "HubPostgreSQL", "getTagSets", "Start" );
	
	CommonPostgreSQL db;
	pqxx::result resultsHandle = db.executeSQL( "select t.id, t.name, t.description, t.type_id, t.access_id from tag_set t" );
	
	DebugInfo::getDebugInfo()->output( "HubPostgreSQL", "getTagSets", "1" );
	
	int id, typeId, accessId;
	
	DebugInfo::getDebugInfo()->output( "HubPostgreSQL", "getTagSets", "2" );

	vector<TagSetDataAccess*> tagSetsDA;
	for(pqxx::result::const_iterator c = resultsHandle.begin(); c != resultsHandle.end(); ++c)
	{
		DebugInfo::getDebugInfo()->output( "HubPostgreSQL", "getTagSets", "3" );
		TagSetDataAccess* tagSetDA = new TagSetPostgreSQL();

		DebugInfo::getDebugInfo()->output( "HubPostgreSQL", "getTagSets", "3 - before id" );
		id = c[0].as<int>();
		tagSetDA->setId( id );
		DebugInfo::getDebugInfo()->output( "HubPostgreSQL", "getTagSets", "3 - before name" );
		if( c[1].is_null()  )
		{
			tagSetDA->setName( c[1].as<string>() );
		}
		DebugInfo::getDebugInfo()->output( "HubPostgreSQL", "getTagSets", "3 - before description" );
		if( c[2].is_null() )
		{
			tagSetDA->setDescription( c[2].as<string>() );
		}
		DebugInfo::getDebugInfo()->output( "HubPostgreSQL", "getTagSets", "3 - before type id" );
		typeId = c[3].as<int>();
		tagSetDA->setTypeId( typeId );
		DebugInfo::getDebugInfo()->output( "HubPostgreSQL", "getTagSets", "3 - before access id" );
		accessId = c[4].as<int>();
		tagSetDA->setAccessId( accessId );
		DebugInfo::getDebugInfo()->output( "HubPostgreSQL", "getTagSets", "3 - before push back of item" );
		
		tagSetsDA.push_back( tagSetDA );
	}

	DebugInfo::getDebugInfo()->output( "HubPostgreSQL", "getTagSets", "Done" );
	return tagSetsDA;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void HubPostgreSQL::disconnect()
{
	CommonPostgreSQL db;
	db.disconnect();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void HubPostgreSQL::refreshMaterializedViews()
{
	/* Tek út í bili, enginn tafla heitir dimension_tag_object og skrítið sql 
	CommonPostgreSQL db;
	db.executeSQLNoResults( "delete from dimension_tag_object" );

	
	db.executeSQLNoResults( "insert into dimension_tag_object \
								  select d.id as dimension_id, d.node_id, ot.tag_id, ot.object_id, ot.upper_left_x, ot.upper_left_y, ot.lower_right_x, ot.lower_right_y, d.left_border, d.right_border \
								  from dimension d, object_tag ot \
								  where d.tag_id = ot.tag_id \
								  order by d.node_id" );

	*/
}
//____________________________________________________________________________________________________________________________________________________________________________________

#endif
