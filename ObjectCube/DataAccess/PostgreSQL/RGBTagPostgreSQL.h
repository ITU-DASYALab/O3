/*
* Snorri Gíslason - 2018
*/

#if !defined(ObjectCube_RGB_TAG_POSTGRESQL_) && defined(OC_POSTGRESQL)
//#ifndef ObjectCube_RGB_TAG_POSTGRESQL_
#define ObjectCube_RGB_TAG_POSTGRESQL_

#include "../Root/RGBTagDataAccess.h"
#include <pqxx/pqxx>

namespace ObjectCube
{
	
	class CommonPostgreSQL;
		
	class RGBTagPostgreSQL : public RGBTagDataAccess
	{
	public:
		virtual RGBTagDataAccess* fetch( int id );
		virtual RGBTagDataAccess* fetch( int tagSetId, const string& name );
		virtual RGBTagDataAccess* create();
		virtual void remove( int id );
		virtual int inUse( int id );
		
	private:
		void processFetch_( pqxx::result r );
	};
	
}

#endif