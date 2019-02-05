/*
 *  TimeSupport.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 3.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_TIME_SUPPORT_
#define ObjectCube_TIME_SUPPORT_

#include <string>

using namespace std;

namespace ObjectCube 
{
	class TimeSupport
	{
	public:
		static bool validTime( int hours, int minutes, int seconds, int milliseconds );
		static string toSQLString( int hours, int minutes, int seconds, int milliseconds );
	
	};
	
}

#endif