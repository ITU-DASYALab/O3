/*
 *  DateSupport.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 3.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_DATE_SUPPORT_
#define ObjectCube_DATE_SUPPORT_

#include <string>

using namespace std;

namespace ObjectCube 
{
	class DateSupport
	{
	public:
		static bool validDate( int year, int month, int dayOfMonth );
		static string toString( int year, int month, int dayOfMonth ); 
		
		static int getMinimumYear();
		static bool isALeapYear( int year );
		static int lastDayOfMonth( int year, int month );
		static int dayOfWeek( int year, int month, int day );
		static bool weekend( int year, int month, int day );
		static int weekOfYear( int year, int month, int day );
		static int daysBetween( int yearFrom, int monthFrom, int dayFrom, int yearTo, int monthTo, int dayTo );
		static int quarter( int year, int month, int day );
		
		enum DAY_OF_WEEK
		{
			SUNDAY = 0,
			MONDAY = 1,
			TUESDAY = 2,
			WEDNESDAY = 3,
			THURSDAY = 4,
			FRIDAY = 5,
			SATURDAY = 6
		};
		
	private:
		static int minimumYear_;
		static int daysInMonth_[12];
	};

}

#endif