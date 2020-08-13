/*
* SearchPostgreSQL.cpp
* Snorri Gíslason - 2018
*/

#ifdef OC_POSTGRESQL

#include "SearchPostgreSQL.h"

#include <sstream>
#include <memory>
#include <iostream>
#include <string>
//#include <time.h> // Tíma test fyrir 70.000 grunninn
//#include <stdio.h> 

#include "CommonPostgreSQL.h"
#include "../../LayerShared/Exception.h"
#include "../../LayerShared/DebugInfo.h"
#include "../../LayerShared/StringSupport.h"

#include "../../Tag/Tag.h"
#include "../../TagSet/TagSet.h"
#include "../../TagSet/AlphanumericalTagSet.h"
#include "../../TagSet/NumericalTagSet.h"
#include "../../Hierarchy/PersistentDimension.h"
#include "../../Hierarchy/HierarchyNode.h"

#include "../Factories/ObjectDataAccessFactory.h"
#include "../Factories/ObjectTagDataAccessFactory.h"
#include "../Factories/TagSetDataAccessFactory.h"
#include "../Root/ObjectDataAccess.h"
#include "../Root/ObjectTagDataAccess.h"
#include "../Root/TagSetDataAccess.h"

#include "../../Converters/TagSetConverter.h"


#include "../Root/BoundingBoxDataAccess.h"
#include "../../Boundaries/BoundingBox.h"

using namespace ObjectCube;
using namespace std;


//____________________________________________________________________________________________________________________________________________________________________________________

SearchPostgreSQL::SearchPostgreSQL() 
{
	objectList.insert(-1); // init 
}


vector<int> SearchPostgreSQL::textSearch()
{
	setObject(0);

	string escapedName = StringSupport::neutralizeControlCharacters( getName() );
	
	vector<string> input = StringSupport::split(escapedName, ';'); // TODO: take in vector

	stringstream rankStream;
	rankStream << "Rank:" << input[1] << ":View:" << input[3];
	string rank = rankStream.str();
	removeDimension(rank);
	
	string searchString = input[2];
	searchString = StringSupport::space2or(searchString);
	
	stringstream stringStream; 
	stringStream << "select id, round(ts_rank(tag_string, query)::numeric, 2) as rank from alphanumerical_tag_materialized_view, to_tsquery('" << searchString << "') as query where tag_string @@ query and tag_set_id = " << input[0] << " order by rank DESC;";
	string sql = stringStream.str();
	CommonPostgreSQL db;
	pqxx::result resultsHandle = db.executeSQL( sql );

	vector<int> Result = processTextSearch(resultsHandle, rank);
	
	return Result;
}

//____________________________________________________________________________________________________________________________________________________________________________________

vector<int> SearchPostgreSQL::processTextSearch( pqxx::result r, const string& rankTagSet)
{
	AlphanumericalTagSet* tagset = AlphanumericalTagSet(rankTagSet).create();
	PersistentDimension* rankDimension = tagset->createPersistentDimension( tagset->fetchOrAddTag(rankTagSet) );
	HierarchyNode* rankNode = rankDimension->getRoot();

	string lastDist;
	const Tag* tag;
	stringstream stringStream;

	CommonPostgreSQL db;
	int nodeId = rankNode->getId();
	int nextNodeId = nodeId;
	int dimensionId = db.getMaxValue("dimension", "id");
	stringstream SQLReturningInt;
	SQLReturningInt << "select id from tag_set where name = '" << rankTagSet << "'";
	int tagsetId = db.executeSQLReturningAnInteger(SQLReturningInt.str());
	int border = 1; 
	int nextTagId = db.executeSQLReturningAnInteger("select currval('tag_id_seq')");
	for(pqxx::result::const_iterator c = r.begin(); c != r.end(); c++)
	{
		string Dist = c[1].as<string>();
		if(lastDist != Dist){
			tag = tagset->fetchOrAddTag(Dist);
			HierarchyNode* node = rankDimension->addNode(nodeId, tag);
			nextTagId = tag->getId();
			/* Hraðara en bíða aðeins með vegna vesen með að birta í objectcube
			nextNodeId++;
			nextTagId++;
			stringStream << "insert into tag values (" << nextTagId <<", " << tagsetId << ", 1);"
			<< " insert into alphanumerical_tag values (" << nextTagId << "," << Dist << "," << tagsetId <<");"
			<< " insert into dimension values (" << dimensionId <<"," << nextNodeId << "," << tagsetId << ", "<< nextTagId <<", ' '," <<  border + 1 << "," << border + 2 <<");";
			border = border + 2;
			*/
		}

		stringStream << "insert into Object_tag(object_id, tag_id, upper_left_x, upper_left_y, lower_right_x, lower_right_y)"
		<< " select object_id, " << nextTagId <<" as tag_id, upper_left_x, upper_left_y, lower_right_x, lower_right_y"
		<< " from object_tag"
		<< " where tag_id = " << c[0].as<int>() << " ON CONFLICT DO NOTHING;";
		lastDist = Dist;
	}
	//stringStream << "update dimension set right_border = " << border + 1 << " where id = " << dimensionId << " and node_id = " << nodeId << ";"; //Hluti af hraðara
 	stringStream << "select setval('tag_id_seq', (SELECT MAX(id) FROM tag)+1);";
	//UPDATE DIMESNION WITH LOWEST left_border  how the right_border +1
	processObject(stringStream.str());



	vector<int> Result;
	Result.push_back(tagsetId);
	Result.push_back(dimensionId);

	return Result;
	/*
	cout << "---- Start SearchPostgreSQL::processTextSearch ----" << endl;
	AlphanumericalTagSet* tagset = AlphanumericalTagSet(rankTagSet).create();
	PersistentDimension* rankDimension = tagset->createPersistentDimension( tagset->fetchOrAddTag(rankTagSet) );
	HierarchyNode* rankNode = rankDimension->getRoot();
	string lastRank;
	const Tag* tag;
	for(pqxx::result::const_iterator c = r.begin(); c != r.end(); c++)
	{
		string rank = c[1].as<string>();
		if(lastRank != rank){
			tag = tagset->fetchOrAddTag(rank);
			HierarchyNode* node = rankDimension->addNode(rankNode->getId(), tag);
		}

		processAlphanumericalObject(tag, c[0].as<int>());
		lastRank = rank;
	}
	cout << "---- End SearchPostgreSQL::processTextSearch ----" << endl;
	*/
}

//____________________________________________________________________________________________________________________________________________________________________________________

void SearchPostgreSQL::processAlphanumericalObject(const Tag* tag, int TagId)
{
	cout << "---- Start SearchPostgreSQL::processAlphanumericalObject ----" << " newTagId = " << tag->getId() << " TagId = " << TagId << endl;
	stringstream stringStream;
	stringStream << "select o.qualified_name, o.id from object_tag ot, object o where o.id = ot.object_id and ot.tag_id = " << TagId;
	string sql = stringStream.str();
	CommonPostgreSQL db;
	pqxx::result r = db.executeSQL( sql );

	cout << "Size: " << r.size() << endl;
	int count = 0;
	for(pqxx::result::const_iterator c = r.begin(); c != r.end(); c++)
	{
		if(!existObject(c[1].as<int>())){
			count++;
			cout << "Mynd: " << c[0].as<string>() << " iter: " << count << endl;
			unique_ptr<ObjectDataAccess> objectDataAccess( ObjectDataAccessFactory::create() );
			unique_ptr<ObjectTagDataAccess> objectTagDataAccess( ObjectTagDataAccessFactory::create() );
			ObjectDataAccess* object = objectDataAccess->fetch(c[0].as<string>());
			int objectId = object->getId();
			objectTagDataAccess->setTagId(tag->getId());
			objectTagDataAccess->setObjectId(objectId);
			objectTagDataAccess->setConfirmed(true);

			Coordinate2DDataAccess upperLeft( 0, 100 );
			Coordinate2DDataAccess lowerRight( 100, 0 );

			BoundingBoxDataAccess* bBox = new BoundingBoxDataAccess( upperLeft, lowerRight );
			objectTagDataAccess->setBoundingBox( bBox );

			objectTagDataAccess->create();
		}
		
	}
	cout << "---- End SearchPostgreSQL::processAlphanumericalObject ----"  << endl;
}

//____________________________________________________________________________________________________________________________________________________________________________________

vector<int> SearchPostgreSQL::rgbSearch()
{    
	
	
	string escapedName = StringSupport::neutralizeControlCharacters( getName() );
	vector<string> rgb = StringSupport::split(escapedName, ';'); // TODO: take in vector
	stringstream limitStream;
	if(rgb[3] == "-1")
		limitStream << "5";
	else
		limitStream << rgb[3];

	stringstream distStream;
	distStream << "Dist:View:" << rgb[5];
	string dist = distStream.str();
	removeDimension(dist);
	string limit = limitStream.str();
	stringstream stringStream; 
	stringStream << "select id, round(rgb <-> cube(array[" << rgb[0] << "," << rgb[1] <<"," << rgb[2] << "])) as dist from rgb_tag where tag_set_id = " << rgb[4] << " order by dist LIMIT " << limit <<";";
	string sql = stringStream.str();

	CommonPostgreSQL db;   
	pqxx::result resultsHandle = db.executeSQL( sql );
	
	return processRGBSearch(resultsHandle, dist);
}

//____________________________________________________________________________________________________________________________________________________________________________________

vector<int> SearchPostgreSQL::processRGBSearch( pqxx::result r, const string& distTagSet)
{
	AlphanumericalTagSet* tagset = AlphanumericalTagSet(distTagSet).create();
	PersistentDimension* rankDimension = tagset->createPersistentDimension( tagset->fetchOrAddTag(distTagSet) );
	HierarchyNode* rankNode = rankDimension->getRoot();

	string lastDist;
	const Tag* tag;
	stringstream stringStream;

	CommonPostgreSQL db;
	int nodeId = rankNode->getId();
	int nextNodeId = nodeId;
	int dimensionId = db.getMaxValue("dimension", "id");
	stringstream tagsetStream;
	tagsetStream << "select id from tag_set where name = '" << distTagSet << "'"; 
	int tagsetId = db.executeSQLReturningAnInteger(tagsetStream.str());
	int border = 1; 
	int nextTagId = db.executeSQLReturningAnInteger("select currval('tag_id_seq')");

	for(pqxx::result::const_iterator c = r.begin(); c != r.end(); c++)
	{
		string Dist = c[1].as<string>();
		if(lastDist != Dist){
			tag = tagset->fetchOrAddTag(Dist);
			HierarchyNode* node = rankDimension->addNode(nodeId, tag);
			nextTagId = tag->getId();
			/*Hraðara en þarf aðeins að laga
			nextNodeId++;
			nextTagId++;
			stringStream << "insert into tag values (" << nextTagId <<", " << tagsetId << ", 1);"
			<< " insert into alphanumerical_tag values (" << nextTagId << "," << Dist << "," << tagsetId <<");"
			<< " insert into dimension values (" << dimensionId <<"," << nextNodeId << "," << tagsetId << ", "<< nextTagId <<", ' '," <<  border + 1 << "," << border + 2 <<");";
			border = border + 2;
			*/
		}
		stringStream << "insert into Object_tag(object_id, tag_id, upper_left_x, upper_left_y, lower_right_x, lower_right_y)"
		<< " select object_id, " << nextTagId <<" as tag_id, upper_left_x, upper_left_y, lower_right_x, lower_right_y"
		<< " from object_tag"
		<< " where tag_id = " << c[0].as<int>() << " ON CONFLICT DO NOTHING;";

		lastDist = Dist;
	}
	//UPDATE DIMESNION WITH LOWEST left_border  how the right_border +1
	//stringStream << "update dimension set right_border = " << border + 1 << " where id = " << dimensionId << " and node_id = " << nodeId << ";"; //Hluti af hraðara
	stringStream << "select setval('tag_id_seq', (SELECT MAX(id) FROM tag)+1);";
	processObject(stringStream.str());

	vector<int> Result;
	Result.push_back(tagsetId);
	Result.push_back(dimensionId);

	return Result;
}

//____________________________________________________________________________________________________________________________________________________________________________________

void SearchPostgreSQL::processRGBObject(const Tag* tag, int TagId)
{
	CommonPostgreSQL db;
	stringstream stringStream;
	stringStream << "insert into Object_tag(object_id, tag_id, upper_left_x, upper_left_y, lower_right_x, lower_right_y)"
	<< " select object_id," << tag->getId() << " as tag, upper_left_x, upper_left_y, lower_right_x, lower_right_y"
	<< " from object_tag"
	<< " where tag_id = " << TagId;
	string sql = stringStream.str();
	db.executeSQLNoResults(sql);
}

//____________________________________________________________________________________________________________________________________________________________________________________

void SearchPostgreSQL::processObject(string sql)
{
	CommonPostgreSQL db;   
	db.executeSQLNoResults(sql);
}

//____________________________________________________________________________________________________________________________________________________________________________________

int SearchPostgreSQL::getTagSetId(const string& tag)
{
	stringstream stringStream;
	stringStream << "select id from tag_set where name = '" << tag <<"'";
	string sql = stringStream.str();
	CommonPostgreSQL db;
	return db.executeSQLReturningAnInteger( sql );

}

//____________________________________________________________________________________________________________________________________________________________________________________

int SearchPostgreSQL::getDimensionId(const string& tag)
{
	stringstream stringStream;
	stringStream << "select d.id from dimension d, tag_set t where d.tag_set_id = t.id and t.name = '" << tag << "'";
	string sql = stringStream.str();
	CommonPostgreSQL db;
	return db.executeSQLReturningAnInteger( sql );
}

//____________________________________________________________________________________________________________________________________________________________________________________

void SearchPostgreSQL::removeDimension(const string& tag)
{
	int TagSetId = getTagSetId(tag);

	if(TagSetId != -1) // If tagsetid = -1, there is no rank dim 
	{
		unique_ptr<TagSetDataAccess> dataAccess( TagSetDataAccessFactory::create() );
		dataAccess->setId(TagSetId);
		dataAccess->erase();
	}
}

//____________________________________________________________________________________________________________________________________________________________________________________

void SearchPostgreSQL::setObject(int id)
{
	objectList.insert(id);
}

//____________________________________________________________________________________________________________________________________________________________________________________

bool SearchPostgreSQL::existObject(int id)
{
	if(objectList.find(id) != objectList.end()) {
	    // id is in set
		return true;
	}

	setObject(id);

	return false;
}

#endif