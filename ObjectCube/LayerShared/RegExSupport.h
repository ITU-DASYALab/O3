/*
 *  RegExSupport.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 6.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_REGEX_SUPPORT_
#define ObjectCube_REGEX_SUPPORT_

#include <string>
#include <regex.h>

using namespace std;

namespace ObjectCube 
{
	class RegExSupport
	{
	public:
		static bool patternFound( const string& data, const string& pattern, string& substringFound );
		
	private:
		static bool cleanup_( regex_t& re, bool retVal );
		
	};
	
}

#endif