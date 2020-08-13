/*
 *  Parameters.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 8.7.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "Parameters.h"

#include <cstdlib>

#include "Exception.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

std::shared_ptr<Parameters> Parameters::instance_;

//____________________________________________________________________________________________________________________________________________________________________________________

Parameters::~Parameters()
{

}
//____________________________________________________________________________________________________________________________________________________________________________________

Parameters* Parameters::getParameters()
{
	if( instance_.get() == 0 )
	{
		instance_.reset( new Parameters );
	}
	return instance_.get();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void Parameters::process( const string& input, const string& keyPrefix, const string& separator )
{
	string localInput = input;
	
	while( localInput.length() )
	{
		string key, value;
		
		//Key
		int prefixStarts = localInput.find( keyPrefix );
		if( prefixStarts != 0 )
		{
			throw Exception( "Parameters::process", "Input string was not correctly formed, key prefix was misplaced" );
		}
		int keyEnds = localInput.find( separator );
		if( keyEnds <= 0 )
		{
			throw Exception( "Parameters::process", "Input string was not correctly formed, separator(1) was misplaced" ); 
		}
		key = localInput.substr( keyPrefix.length(), keyEnds - keyPrefix.length() );
		localInput = localInput.substr( keyEnds + 1 );
		
		//Value
		int valueEnds = localInput.find( separator );
		if( valueEnds < 0 ) //A separator is optional at the end
		{
			value = localInput;
			localInput = "";
		}
		else 
		{
			value = localInput.substr(0, valueEnds );
			localInput = localInput.substr( valueEnds + 1 );
		}
		
		params_.insert( pair<string, string>( key, value ) );
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________

void Parameters::process( int argc, char* const argv[], const string& keyPrefix, const string& separator )
{
	string input;
	for( int i = 1; i < argc; ++i )
	{
		input += string( argv[i] ) + separator;
	}
	process( input, keyPrefix, separator );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void Parameters::add( const string& key, const string& value )
{
	params_.insert( pair<string, string>( key, value ) );
}
//____________________________________________________________________________________________________________________________________________________________________________________

const string Parameters::getValue( const string& key ) 
{
	if( !contains( key ) )
	{
	
	}
	return params_[ key ];
}
//____________________________________________________________________________________________________________________________________________________________________________________

const int Parameters::getValueAsInt( const string& key )
{
	return atoi( getValue( key ).c_str() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

bool Parameters::contains( const string& key ) const
{
	return params_.count( key ) > 0;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void Parameters::remove( const string& key )
{
	params_.erase( key );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void Parameters::update( const string& key, const string& newValue )
{
	remove( key );
	add( key, newValue );
}
//____________________________________________________________________________________________________________________________________________________________________________________


