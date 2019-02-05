/*
* Snorri Gíslason - 2018
*/

#if !defined(ObjectCube_ALPHANUMERICAL_TAG_POSTGRESQL_) && defined(OC_POSTGRESQL)
//#ifndef ObjectCube_ALPHANUMERICAL_TAG_POSTGRESQL_
#define ObjectCube_ALPHANUMERICAL_TAG_POSTGRESQL_

#include "../Root/AlphanumericalTagDataAccess.h"
#include <pqxx/pqxx>

namespace ObjectCube
{
	
	class CommonPostgreSQL;
		
	class AlphanumericalTagPostgreSQL : public AlphanumericalTagDataAccess
	{
	public:
		virtual AlphanumericalTagDataAccess* fetch( int id );
		virtual AlphanumericalTagDataAccess* fetch( int tagSetId, const string& name );
		virtual AlphanumericalTagDataAccess* create();
		virtual void remove( int id );
		virtual int inUse( int id );
		
	private:
		void processFetch_( pqxx::result r );
	};
	
}

#endif