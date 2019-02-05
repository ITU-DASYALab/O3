/*
* Snorri Gíslason - 2018
*/

#if !defined(ObjectCube_TIME_TAG_POSTGRESQL_) && defined(OC_POSTGRESQL)
//#ifndef ObjectCube_TIME_TAG_POSTGRESQL_
#define ObjectCube_TIME_TAG_POSTGRESQL_

#include "../Root/TimeTagDataAccess.h"

#include <pqxx/pqxx>

using namespace std;

namespace ObjectCube
{

	class TimeTagPostgreSQL : public TimeTagDataAccess
	{
	public:
		
		virtual TagDataAccess* fetch( int id );
		virtual TagDataAccess* create( );
		virtual int inUse( int id );
		virtual void remove( int id );
		
		virtual TimeTagDataAccess* fetch( int tagSetId, int hours, int minutes, int seconds, int milliseconds );  //ATH
		static void sqlTimeToTag( TimeTagDataAccess* tag, const string& timeAsString );
		
	private:
		void processFetch_( pqxx::result resultsHandle );
	};
	
}

#endif