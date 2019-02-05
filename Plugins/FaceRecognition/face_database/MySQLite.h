/*
 *  _db.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 10.11.2009.
 *  Copyright 2009 Reykjavik University. All rights reserved.
 *
 */

#ifndef __MYSQLITE_H__
#define __MYSQLITE_H__

#include <string>

using namespace std;

struct sqlite3;

	class MySQLite 
	{
	public:

		char** getTable( const string& select );
		void getTableCleanup( char** result );
		
		int getCurrentId( const string& tableName, const string& columnName );
		int getCurrentSequence( const string& tableName );
		
		//Transaction control
		void beginTransaction();
		void commitTransaction();
		void rollbackTransaction();
		
		//Get/Set
		int noOfRows() { return noOfRows_; }
		int noOfColumns() { return noOfColumns_; }
		string dbError() { return dbErr_; }
		
		//Utility
		string neutralizeControlCharacters( const string& input );
		static string toSQLString( int year, int month, int dayOfMonth ); 

		// Static
		static void closeDB();
		
		//Constructors
		MySQLite();
		
		//Destructors
		~MySQLite();
		
	protected:
		void openDb_();
		void executeSQL_( const string& sql );
		
	private:
		int noOfRows_;
		int noOfColumns_;
		string dbName_;
		static string dbNameParameter_;
		static sqlite3* db_;
		string dbErr_;
	};

#endif
