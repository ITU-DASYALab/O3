/*
* SearchPostgreSQL.h
* Snorri Gíslason - 2018
*/

#if !defined(ObjectCube_OBJECT_POSTGRESQL_) && defined(OC_POSTGRESQL)
#define ObjectCube_OBJECT_POSTGRESQL_

#include "../Root/SearchDataAccess.h"
#include "../../Tag/Tag.h" 
#include <pqxx/pqxx>
#include <set>

namespace ObjectCube
{
	class CommonPostgreSQL;

	class SearchPostgreSQL : public SearchDataAccess
	{
	public:
		//Constuctors
		SearchPostgreSQL();
		
		virtual vector<int> textSearch();
		virtual vector<int> rgbSearch();
	protected:
		vector<int>  processTextSearch( pqxx::result r, const string& rankTagSet );
		vector<int> processRGBSearch( pqxx::result r, const string& distTagSet );
		void processAlphanumericalObject(const Tag* tag, int TagId);
		void processRGBObject(const Tag* tag, int TagId);
		void processObject(string sql);
		
		int getTagSetId(const string& tag);
		int getDimensionId(const string& tag);
		void removeDimension(const string& tag);
		
		void setObject(int id);
		bool existObject(int id);

		std::set<int> objectList;
		
	};
}

#endif