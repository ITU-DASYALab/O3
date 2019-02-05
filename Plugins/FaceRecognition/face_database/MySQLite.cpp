/*
 *  _db.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 10.11.2009.
 *  Copyright 2009 Reykjavik University. All rights reserved.
 *
 */

#include "MySQLite.h"

#include <sqlite3.h>
#include <stdio.h>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <iomanip>
#include <ctime>
#include <stdexcept>

#include "../../../ObjectCube/LayerShared/Parameters.h"
#include "../../../ObjectCube/Boundaries/Coordinate2D.h"
using namespace ObjectCube;



string MySQLite::dbNameParameter_ = "MySQLite";
sqlite3* MySQLite::db_=0;



MySQLite::MySQLite()
{
	Parameters *params = Parameters::getParameters();

	dbName_ = params->getValue("databasePath");

	noOfRows_ = 0 ;
	noOfColumns_ = 0 ;
	//db_ = 0;	
}


MySQLite::~MySQLite()
{
	if( db_ != 0)
	{
		//sqlite3_close( db_ );
	}
}

void MySQLite::closeDB()
{
	if( db_ != 0)
	{
		sqlite3_close( db_ );
	}
}


void MySQLite::openDb_()
{
	if( db_ != 0 )  // No reopening supported
	{
		return;
	}
	
	int open = sqlite3_open( dbName_.data(), &db_ );
	if( open )
	{
		//fprintf( stderr, "Can't open database: %s, path: %s \n", sqlite3_errmsg( db_ ), dbName_.data() );
		sqlite3_close( db_ );
		throw runtime_error( string("MySQLite::openDb_,Cannot open database, ") + sqlite3_errmsg( db_ ) );
	}	
}


char** MySQLite::getTable( const string& select )
{
	openDb_();
	
	char **result = 0;
	char* error = 0;
	int res = sqlite3_get_table(db_, 
								select.data(), 
								&result, 
								&noOfRows_, 
								&noOfColumns_, 
								&error );
	if( res != SQLITE_OK ) 
	{
		dbErr_ = string( error );
		sqlite3_free( error );
		
		//cerr << "Error from db (getTable): " << dbErr_.c_str() << ".\nSelect: " << select.c_str() << endl;
		//fprintf(stderr, "Error from db: %s \n", dbErr_.c_str() );
		throw runtime_error( string("MySQLite::getTable, ") + dbErr_ );
	}
	noOfRows_ += 1; //Telja ekki dálkanöfnin með
	return result;
}


void MySQLite::executeSQL_( const string& sql )
{
	openDb_();
	
	char* error = 0;
	int res = sqlite3_exec( db_, sql.data(), 0, 0, &error );
	
	if( res != SQLITE_OK ) 
	{
		dbErr_ = string( error );
		sqlite3_free( error );

		//cerr << "Error from db (executeSQL_): " << dbErr_.c_str() << ".\nSql: " << sql.c_str() << endl;
		throw runtime_error(string("MySQLite::getTable, ") + dbErr_ );
	}
}


void MySQLite::getTableCleanup( char** result )
{
	sqlite3_free_table( result );
}


int MySQLite::getCurrentId( const string& tableName, const string& columnName )
{
	stringstream sstream;
	sstream << "SELECT MAX(" << columnName << ") FROM " << tableName;
	string select = sstream.str();
	char** result = getTable( select );
	
	int sequence = 0; //initialized to no data in table
	//If there is no data in the table we get a NULL result
	if( result[ noOfColumns() ] != 0 )
	{
		sequence = atoi( result[ noOfColumns() ] );
	}

	getTableCleanup( result );
	return sequence;
}


int MySQLite::getCurrentSequence( const string& tableName )
{
	string select = string("select ifnull( seq, 0) from sqlite_sequence where name = lower('") + tableName + string("')");
	char** result = getTable( select );
	
	if( noOfRows() != 2 ) //Dálkaheiti og ein röð
	{
		stringstream stringStream;
		stringStream << "Rangur fjöldi af tögum í getCurrentSequence, las upp: " << noOfRows() << endl;

		throw runtime_error(string("MySQLite::nextSequence") + stringStream.str() );
		
	}
	int sequence = atoi( result[ noOfColumns() ] );
	getTableCleanup( result );
	return sequence;
}


void MySQLite::beginTransaction()
{
	executeSQL_( "begin transaction" );
}


void MySQLite::commitTransaction()
{
	executeSQL_( "commit transaction" );
}


void MySQLite::rollbackTransaction()
{
	executeSQL_( "rollback transaction" );
}


string MySQLite::toSQLString( int year, int month, int dayOfMonth )
{
	stringstream stringStream, ssYear, ssMonth, ssDayOfMonth;
	
	//Creating correct sized and zero filled versions
	ssYear << setw(4) << setfill('0') << right << year;
	ssMonth << setw(2) << setfill('0') << right << month;
	ssDayOfMonth << setw(2) << setfill('0') << right << dayOfMonth;
	
	stringStream << "strftime( \"%Y-%m-%d\", '" << ssYear.str() << "-" << ssMonth.str() << "-" << ssDayOfMonth.str() << "' )";
	return stringStream.str();
}


