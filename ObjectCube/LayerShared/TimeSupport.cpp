/*
 *  TimeSupport.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 3.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "TimeSupport.h"

#include <sstream>
#include <iomanip>

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

bool TimeSupport::validTime( int hours, int minutes, int seconds, int milliseconds )
{
	if( hours < 0 || hours > 23 )
	{
		return false;
	}
	if( minutes < 0 || minutes > 59 )
	{
		return false;
	}
	if( seconds < 0 || seconds > 59 )
	{
		return false;
	}
	if( milliseconds < 0 || milliseconds > 999 )
	{
		return false;
	}
	return true;
}
//____________________________________________________________________________________________________________________________________________________________________________________

string TimeSupport::toSQLString( int hours, int minutes, int seconds, int milliseconds )
{
	stringstream stringStream, ssHours, ssMinutes, ssSeconds, ssMilliseconds;
	
	ssHours << setw(2) << setfill('0') << right << hours;
	ssMinutes << setw(2) << setfill('0') << right << minutes;
	ssSeconds << setw(2) << setfill('0') << right << seconds;
	ssMilliseconds << setw(3) << setfill('0') << right << milliseconds;	
	
	stringStream << "strftime( \"%H:%M:%f\", '" << ssHours.str() << ":" << ssMinutes.str() << ":" << ssSeconds.str() << "." << ssMilliseconds.str() << "' )"; 
	
	return stringStream.str();
}
//____________________________________________________________________________________________________________________________________________________________________________________

