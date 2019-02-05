/*
 *  DateTagDataAccess.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 10.4.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_DATE_TAG_DATA_ACCESS_
#define ObjectCube_DATE_TAG_DATA_ACCESS_

#include "TagDataAccess.h"
#include <string>


using namespace std;

namespace ObjectCube
{
	
	class DateTagDataAccess : public TagDataAccess
	{
	public:
		DateTagDataAccess();
		virtual ~DateTagDataAccess();
		
		virtual TagDataAccess* fetch( int id ) = 0;
		virtual TagDataAccess* create( ) = 0;
		virtual int inUse( int id ) = 0;
		virtual void remove( int id ) = 0;
		
		virtual DateTagDataAccess* fetch( int tagSetId, int year, int month, int dayOfMonth ) = 0;  
		
		//Get/Set
		int getYear() const { return year_; }
		int getMonth() const { return month_; }
		int getDayOfMonth() const { return dayOfMonth_; }
		
		void setYear( int year ) { year_ = year; }
		void setMonth( int month ) { month_ = month; }
		void setDayOfMonth( int dayOfMonth ) { dayOfMonth_ = dayOfMonth; }
		
	protected:
		int year_;
		int month_;
		int dayOfMonth_;
		
	};
	
}

#endif