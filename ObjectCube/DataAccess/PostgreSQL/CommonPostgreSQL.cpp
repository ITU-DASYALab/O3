/*
* Snorri G�slason - 2018
*/

#ifdef OC_POSTGRESQL

#include "CommonPostgreSQL.h"

#include <sstream>
#include <memory>
#include <iomanip>
#include <stdio.h>
#include <string.h>
#include <iostream> //for debug

#include "../../LayerShared/Exception.h"
#include "../../LayerShared/Parameters.h"
#include "../../LayerShared/DebugInfo.h"

using namespace ObjectCube;
using namespace std;

//____________________________________________________________________________________________________________________________________________________________________________________

pqxx::connection* CommonPostgreSQL::connection_;
pqxx::nontransaction* CommonPostgreSQL::trans_;
bool CommonPostgreSQL::connected_ = false;

//____________________________________________________________________________________________________________________________________________________________________________________


CommonPostgreSQL::CommonPostgreSQL()
{
	host_ = "127.0.0.1";
	port_ = "5432";
	database_ = "RGB10000";
	user_ =  "object";
	password_ = "object";
}


//____________________________________________________________________________________________________________________________________________________________________________________

CommonPostgreSQL::~CommonPostgreSQL()
{

}


//____________________________________________________________________________________________________________________________________________________________________________________

void CommonPostgreSQL::executeSQLNoResults(const string& sql)
{
	connectToDb_();

	const char* sqlPointer = sql.c_str();
	trans_ -> exec(sqlPointer);
}

//____________________________________________________________________________________________________________________________________________________________________________________

pqxx::result CommonPostgreSQL::executeSQL(const string& sql)
{
	connectToDb_();

	const char* sqlPointer = sql.c_str();
	
	pqxx::result r = trans_ -> exec(sqlPointer);

	return r;
}

//____________________________________________________________________________________________________________________________________________________________________________________

int CommonPostgreSQL::executeSQLReturningAnInteger(const string& sql)
{
	int result = -1;
	
	connectToDb_();
	
	const char* sqlPointer = sql.c_str();
	pqxx::result r = trans_ -> exec(sqlPointer);
	if(!r[0][0].is_null()){
		result = r[0][0].as<int>();
	}

	return result;
}

//____________________________________________________________________________________________________________________________________________________________________________________

void CommonPostgreSQL::beginTransaction()
{
	connectToDb_();
	executeSQL("begin;");
}

//____________________________________________________________________________________________________________________________________________________________________________________

void CommonPostgreSQL::commitTransaction()
{
	connectToDb_();
	executeSQL("commit;");
}

//____________________________________________________________________________________________________________________________________________________________________________________

void CommonPostgreSQL::rollbackTransaction()
{
	connectToDb_();
	executeSQL("rollback;");
}

//____________________________________________________________________________________________________________________________________________________________________________________

int CommonPostgreSQL::getMaxValue( const string& table, const string& column )
{
	connectToDb_();
	
	stringstream stringStream;
	stringStream << "SELECT MAX(" << column << ") FROM " << table;
	pqxx::result hdl = executeSQL( stringStream.str() );
	
	int id = -1;

	if(!hdl[0][0].is_null()){
		id = hdl[0][0].as<int>();
	}

	return id;
}

//____________________________________________________________________________________________________________________________________________________________________________________

void CommonPostgreSQL::connectToDb_()
{
	if( !connected_ )
	{
		stringstream sstream;
		sstream << "dbname = " << database_ << " user = " << user_ << " password =  " << password_ << " hostaddr = " << host_ << " port = " << port_;
		string connectionString = sstream.str();
		//connection_ = new connection(connectionString);
		connection_ = new pqxx::connection("dbname = objectcube user = object password = object hostaddr = 127.0.0.1 port = 5432");
		trans_ = new pqxx::nontransaction(*connection_);
		
		connected_ = true;	
	}
}


//____________________________________________________________________________________________________________________________________________________________________________________

void CommonPostgreSQL::disconnect()
{
	if( connected_ )
	{
		connected_ = false;
		//connection_->disconnect();
	}
}

//____________________________________________________________________________________________________________________________________________________________________________________

string CommonPostgreSQL::dateToSQLString(int year, int month, int dayOfMonth)
{
	stringstream stringStream, ssYear, ssMonth, ssDayOfMonth;
	
	//Creating correct sized and zero filled versions
	ssYear << setw(4) << setfill('0') << right << year;
	ssMonth << setw(2) << setfill('0') << right << month;
	ssDayOfMonth << setw(2) << setfill('0') << right << dayOfMonth;
	
	stringStream << "'" << ssYear.str() << "-" << ssMonth.str() << "-" << ssDayOfMonth.str() << "'";
	return stringStream.str();
}

//____________________________________________________________________________________________________________________________________________________________________________________

string CommonPostgreSQL::timeToSQLString(int hours, int minutes, int seconds, int milliseconds)
{
	stringstream stringStream, ssHours, ssMinutes, ssSeconds, ssMilliseconds;
	ssHours << setw(2) << setfill('0') << right << hours;
	ssMinutes << setw(2) << setfill('0') << right << minutes;
	ssSeconds << setw(2) << setfill('0') << right << seconds;
	ssMilliseconds << setw(3) << setfill('0') << right << milliseconds;	
	
	stringStream << "'" << ssHours.str() << ":" << ssMinutes.str() << ":" << ssSeconds.str() << "." << ssMilliseconds.str() << "'"; 
	
	return stringStream.str();
}

//____________________________________________________________________________________________________________________________________________________________________________________

#endif
