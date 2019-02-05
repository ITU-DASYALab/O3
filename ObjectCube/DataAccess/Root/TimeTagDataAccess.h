/*
 *  TimeTagDataAccess.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 9.4.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_TIME_TAG_DATA_ACCESS_
#define ObjectCube_TIME_TAG_DATA_ACCESS_

#include "TagDataAccess.h"
#include <string>


using namespace std;

namespace ObjectCube
{
	
	class TimeTagDataAccess : public TagDataAccess
	{
	public:
		TimeTagDataAccess();
		virtual ~TimeTagDataAccess();
		
		virtual TagDataAccess* fetch( int id ) = 0;
		virtual TagDataAccess* create( ) = 0;
		virtual int inUse( int id ) = 0;
		virtual void remove( int id ) = 0;
		
		virtual TimeTagDataAccess* fetch( int tagSetId, int hours, int minutes, int seconds, int milliseconds ) = 0;  //ATH
		
		//Get/Set
		int getHours() const { return hours_; }
		int getMinutes() const { return minutes_; }
		int getSeconds() const { return seconds_; }
		int getMilliseconds() const { return milliseconds_; }
		
		void setHours( int hours ) { hours_ = hours; }
		void setMinutes( int minutes ) { minutes_ = minutes; }
		void setSeconds( int seconds ) { seconds_ = seconds; }
		void setMilliseconds( int milliseconds ) { milliseconds_ = milliseconds; }
		
	protected:
		int hours_;
		int minutes_;
		int seconds_;
		int milliseconds_;
	};
	
}

#endif