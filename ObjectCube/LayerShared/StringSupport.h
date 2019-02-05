/*
 *  StringSupport.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 23.8.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_STRING_SUPPORT_
#define ObjectCube_STRING_SUPPORT_

#include <string>
#include <vector>

using namespace std;

namespace ObjectCube
{
	
	class StringSupport
	{
	public:
		StringSupport();
		~StringSupport() {;}
		
		static string neutralizeControlCharacters( const string& input );
		static string removeControlCharacterNeutralization( const string& input );
		
		static string trim( string& input, const string& remove = " " );
		static string toSimpleAscii( const string& input );
		static vector<string> split(const string& s, char delimiter);
		static string space2or(const string& input);
		
	private:
		static vector<string> controlChars_;
		static string escapeCharString_;
		
		static void init_();
		
	};
	

		
	
}

#endif