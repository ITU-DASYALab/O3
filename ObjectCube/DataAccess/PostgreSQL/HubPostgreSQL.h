/*
* Snorri Gíslason - 2018
*/

#if !defined(ObjectCube_HUBPOSTGRESQL_) && defined(OC_POSTGRESQL)
//#ifndef ObjectCube_HUBPOSTGRESQL_
#define ObjectCube_HUBPOSTGRESQL__

#include "../Root/HubDataAccess.h"

namespace ObjectCube
{
	class StateObjectDataAccess;
	class TagSetDataAccess;
	
	class HubPostgreSQL : public HubDataAccess
	{
	public:
		virtual vector<StateObjectDataAccess*> getObjects( const string& select );
		virtual vector<StateObjectDataAccess*> getObjects( const vector<FilterDataAccess*>& filters );
		
		virtual StateDataAccess getState( const string& select );
		virtual StateDataAccess getState( const vector<FilterDataAccess*>& filters  );

		virtual unsigned int getObjectCount();

		virtual vector<TagSetDataAccess*> getTagSets();
		
		
		virtual void disconnect();
		virtual void refreshMaterializedViews();
		
	private:
		string filtersToSelect_( const vector<FilterDataAccess*>& filters );

	};
	
}

#endif
