/*
 *  TimeRangeFilter.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 3.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_TIME_RANGE_FILTER_
#define ObjectCube_TIME_RANGE_FILTER_

#include "Filter.h"

namespace ObjectCube 
{	
	// Hour from and to have to be set.
	// If the following values are not set they will be set to the following values:
	//	Minutes from = 0
	//	Seconds from = 0
	//	Milliseconds from = 0
	//	Minutes to = 59
	//	Seconds to = 59
	//	Milliseconds to = 999
	class TimeRangeFilter : public Filter
	{
	public:
		//Constructors 
		TimeRangeFilter( int tagSetId );
		TimeRangeFilter( int hoursFrom, int hoursTo, int tagSetId );
		
		virtual ~TimeRangeFilter();
		
		//Get
		int getHoursFrom() const { return hoursFrom_; }
		int getMinutesFrom() const { return minutesFrom_; }
		int getSecondsFrom() const { return secondsFrom_; }
		int getMillisecondsFrom() const { return millisecondsFrom_; }
		
		int getHoursTo() const { return hoursTo_; }
		int getMinutesTo() const { return minutesTo_; }
		int getSecondsTo() const { return secondsTo_; }
		int getMillisecondsTo() const { return millisecondsTo_; }
		
		//Set
		void setHoursFrom( int hours );
		void setMinutesFrom( int minutes );
		void setSecondsFrom( int seconds );
		void setMillisecondsFrom( int milliseconds );
		
		void setHoursTo( int hours );
		void setMinutesTo( int minutes );
		void setSecondsTo( int seconds );
		void setMillisecondsTo( int milliseconds );
		
		
		void fillInAndValidateValues();
		
		//Operator overloading
		virtual Filter& operator=( const Filter& filter );
		
	protected:
		//Constructor for factory use
		TimeRangeFilter();
		
	private:
		void init_();
		
	protected:
		
		int hoursFrom_;
		int minutesFrom_;
		int secondsFrom_;
		int millisecondsFrom_;
		
		int hoursTo_;
		int minutesTo_;
		int secondsTo_;
		int millisecondsTo_;
		
		
		friend class FilterFactory;
	};
	
}

#endif