/*
* Snorri Gíslason - 2018
*/

#if !defined(ObjectCube_COMMON_POSTGRESQL_) && defined(OC_POSTGRESQL)
//#ifndef ObjectCube_COMMON_OC_POSTGRESQL_
#define ObjectCube_COMMON_POSTGRESQL_

#include <string>
#include <pqxx/pqxx>

using namespace std;

namespace ObjectCube
{
	class CommonPostgreSQL
	{
	public:
		//Constuctors
		CommonPostgreSQL();
		
		//Destructors
		~CommonPostgreSQL(); 

		//Transaction control
		void beginTransaction();
		void commitTransaction();
		void rollbackTransaction();

		pqxx::result executeSQL( const string& sql );
		void executeSQLNoResults( const string& sql );
		int executeSQLReturningAnInteger( const string& sql );

		int getMaxValue( const string& table, const string& column );

		void disconnect();

		static string dateToSQLString(int year, int month, int dayOfMonth);
		static string timeToSQLString(int hours, int minutes, int seconds, int milliseconds);
	

	protected:
		void connectToDb_();
	
	private:
		static pqxx::connection* connection_;
		static pqxx::nontransaction* trans_;
		static bool connected_;

		string host_;
		string port_;
		string database_;
		string user_;
		string password_;
	};
}

#endif
