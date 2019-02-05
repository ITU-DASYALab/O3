/*
* Snorri Gíslason - 2018
*/


#if !defined(ObjectCube_DATE_TAG_POSTGRESQL_) && defined(OC_POSTGRESQL)
//#ifndef ObjectCube_DATE_TAG_POSTGRESQL_
#define ObjectCube_DATE_TAG_POSTGRESQL_

#include "../Root/DateTagDataAccess.h"

#include <pqxx/pqxx>

namespace ObjectCube
{	
	class DateTagPostgreSQL : public DateTagDataAccess
	{
	public:
		virtual TagDataAccess* fetch( int id );
		virtual TagDataAccess* create( );
		virtual int inUse( int id );
		virtual void remove( int id );
		
		virtual DateTagDataAccess* fetch( int tagSetId, int year, int month, int dayOfMonth );  
		
		static void sqlDateToTag( DateTagDataAccess* tag, const string& dateAsString ); 
		
	private:
		void processFetch_( pqxx::result resultsHandle );
		
	};
	
}

#endif