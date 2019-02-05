/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/


#ifndef ObjectCube_TIME_RANGE_FILTER_DATA_ACCESS_
#define ObjectCube_TIME_RANGE_FILTER_DATA_ACCESS_

#include "FilterDataAccess.h"

namespace ObjectCube 
{	
	
	class TimeRangeFilterDataAccess : public FilterDataAccess
	{
	public:
		//Constructors 
		TimeRangeFilterDataAccess();
		virtual ~TimeRangeFilterDataAccess();
		
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
		
	protected:
		virtual string getSelectionPredicate_();
		virtual string getFiltrationPredicate_();
		
	protected:
		int hoursFrom_;
		int minutesFrom_;
		int secondsFrom_;
		int millisecondsFrom_;
		
		int hoursTo_;
		int minutesTo_;
		int secondsTo_;
		int millisecondsTo_;
		
	};
	
}

#endif