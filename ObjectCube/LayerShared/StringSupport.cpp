/*
 *  StringSupport.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 23.8.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "StringSupport.h"

#include <sstream>

using namespace ObjectCube;
using namespace std;

//____________________________________________________________________________________________________________________________________________________________________________________

vector<string> StringSupport::controlChars_;
string StringSupport::escapeCharString_ = "\'";

//____________________________________________________________________________________________________________________________________________________________________________________

StringSupport::StringSupport()
{
}
//____________________________________________________________________________________________________________________________________________________________________________________

void StringSupport::init_()
{
	controlChars_.clear();
	//controlChars_.push_back( "\\" );	
	controlChars_.push_back( "\'" );
	//controlChars_.push_back( "\"" );
}
//____________________________________________________________________________________________________________________________________________________________________________________

string StringSupport::neutralizeControlCharacters( const string& input )
{
	init_();
	
	string output = input;
	for( vector<string>::iterator itr = controlChars_.begin(); itr != controlChars_.end(); ++itr )
	{
		string controlSymbol = *itr;
		int startingLocation = 0;
		while( ( startingLocation = output.find( controlSymbol, startingLocation ) ) != string::npos )
		{
			output.insert( startingLocation, escapeCharString_ );
			startingLocation += 2;
		}
	}
	
	return output;	
}
//____________________________________________________________________________________________________________________________________________________________________________________

string StringSupport::removeControlCharacterNeutralization( const string& input )
{
	init_();
	
	string output = input;
	for( vector<string>::iterator itr = controlChars_.begin(); itr != controlChars_.end(); ++itr )
	{
		string controlSymbol = *itr;
		string toFind = escapeCharString_ + controlSymbol;
		int startingLocation = 0;
		while( ( startingLocation = output.find( toFind, startingLocation ) ) != string::npos )
		{
			output.erase( startingLocation, escapeCharString_.length() );
			startingLocation += 2; //change
		}
	}
	
	return output;	
}
//____________________________________________________________________________________________________________________________________________________________________________________

string StringSupport::trim( string& input, const string& remove )
{
	string trimmed = input.erase( input.find_last_not_of( remove ) + 1) ;
	trimmed = trimmed.erase( 0, trimmed.find_first_not_of( remove ) );
	input = trimmed;
	return trimmed;
}
//____________________________________________________________________________________________________________________________________________________________________________________

string StringSupport::toSimpleAscii( const string& input )
{
	string simple;
	int length = input.length();
	char c = '0';
	for( int i = 0; i < length; ++i )
	{
		c = input[i];
		if( c >= 32 && c <= 126 )
		{
			simple.append( 1, c );
		}
		else 
		{
			simple += "_"; //Character not in the simple ascii set
		}
	}
	return simple;
}
//____________________________________________________________________________________________________________________________________________________________________________________

vector<string> StringSupport::split(const string& s, char delimiter)
{
   vector<string> tokens;
   string token;
   istringstream tokenStream(s);
   while (getline(tokenStream, token, delimiter))
   {
      tokens.push_back(token);
   }
   return tokens;
}

//____________________________________________________________________________________________________________________________________________________________________________________

string StringSupport::space2or(const string& input)
{
	string result = input;
	
	for(string::iterator it = result.begin(); it != result.end(); ++it){
		if(*it == ' '){
			*it = '|';
		}
	}

	return result;
} 

//____________________________________________________________________________________________________________________________________________________________________________________