/*
* Snorri Gíslason - 2018
*/



#if !defined(ObjectCube_NUMERICAL_TAG_POSTGRESQL_) && defined(OC_POSTGRESQL)
//#ifndef ObjectCube_NUMERICAL_TAG_POSTGRESQL_
#define ObjectCube_NUMERICAL_TAG_POSTGRESQL_

#include "../Root/NumericalTagDataAccess.h"

#include <pqxx/pqxx>

namespace ObjectCube
{
	class NumericalTagPostgreSQL : public NumericalTagDataAccess
	{
	public:
		virtual NumericalTagDataAccess* fetch( int id );
		virtual NumericalTagDataAccess* fetch( int tagSetId, long number );
		virtual NumericalTagDataAccess* create();
		virtual void remove( int id );
		virtual int inUse( int id );
		
	private:
		void processFetch_( pqxx::result resultsHandle );
		
	};
	
}

#endif