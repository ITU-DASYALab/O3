
#include "Search.h"
#include "Hub.h"
#include "TagSet/TagSet.h"
#include "TagSet/AlphanumericalTagSet.h"
#include "Tag/Tag.h"
#include "Tag/AlphanumericalTag.h"
#include "Hierarchy/PersistentDimension.h"
#include "Hierarchy/Dimension.h"
#include "Hierarchy/HierarchyNodeFactory.h"
#include <pqxx/pqxx> 

using namespace pqxx;
using namespace ObjectCube;

connection* connection_;
nontransaction* trans_;

//____________________________________________________________________________________________________________________________________________________________________________________

Search::Search()
{
	
}

void connectToDb_()
{
	connection_ = new connection("dbname = objectcube user = object password = object hostaddr = 127.0.0.1 port = 5432");
	trans_ = new nontransaction(*connection_);
}

result executeSQL( const string& sql )
{
	const char* sqlPointer = sql.c_str();
	pqxx::result r = trans_->exec(sqlPointer);

	return r;
}

int processSearchResult()
{
	/*
	cout << "--Start processSearchResult--" << endl;
	AlphanumericalTagSet alphanumericalTagSet ( "Rank" );
	cout << "processSearchResult Hub::getHub()" << endl;
	Hub* hub = Hub::getHub();
	cout << "processSearchResult hub->getTagSet()" << endl;
	TagSet* rankTagSet = hub->getTagSet("Rank");
	cout << "processSearchResult hub->addTagSet( rankTagSet )" << endl;
	TagSet* tagSet = hub->addTagSet( rankTagSet );
	cout << "processSearchResult tagSet->createPersistentDimension(tagSet->fetchOrAddTag()" << endl;
	PersistentDimension* rankDim = tagSet->createPersistentDimension(tagSet->fetchOrAddTag( "Rank" ));
	cout << "processSearchResult rankDim->getRoot()" << endl;
	HierarchyNode* rankNode = rankDim->getRoot();

	for(pqxx::result::const_iterator c = r.begin(); c != r.end(); c++)
	{
		cout << "rankTagSet->fetchOrAddTag()" << c[1].as<string>() << endl;
		rankDim->addNode(rankNode->getId(), rankTagSet->fetchOrAddTag(c[1].as<string>()));
	}

	cout << "--End processSearchResult--" << endl;
	*/
	return 1;
} 

void Search::searchString()
{
	cout << "****************----------------TOKST----------------****************" << endl;
	
	stringstream stringStream;
	stringStream << "select id, tag_string, tag_set_id, text, ts_rank_cd(text, query, 32) as rank from search_index, to_tsquery('magnus| (magnus & yngri)') as query where text @@ query order by rank DESC;";
	string sql = stringStream.str();
	pqxx::result r = executeSQL(sql);
	//int dimensionId = processSearchResult(r);
	
	cout << "--Start processSearchResult--" << endl;
	AlphanumericalTagSet alphanumericalTagSet ( "Rank" );
	cout << "processSearchResult Hub::getHub()" << endl;
	Hub* hub = Hub::getHub();
	cout << "processSearchResult hub->getTagSet()" << endl;
	TagSet* rankTagSet = hub->getTagSet("Rank");
	cout << "processSearchResult hub->addTagSet( rankTagSet )" << endl;
	TagSet* tagSet = hub->addTagSet( rankTagSet );
	cout << "processSearchResult tagSet->createPersistentDimension(tagSet->fetchOrAddTag()" << endl;
	PersistentDimension* rankDim = tagSet->createPersistentDimension(tagSet->fetchOrAddTag( "Rank" ));
	cout << "processSearchResult rankDim->getRoot()" << endl;
	HierarchyNode* rankNode = rankDim->getRoot();

	for(pqxx::result::const_iterator c = r.begin(); c != r.end(); c++)
	{
		cout << "rankTagSet->fetchOrAddTag()" << c[1].as<string>() << endl;
		rankDim->addNode(rankNode->getId(), rankTagSet->fetchOrAddTag(c[1].as<string>()));
	}

	cout << "--End processSearchResult--" << endl;
	
	
}
