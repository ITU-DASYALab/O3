/*
 *  DateRangeFilter.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 3.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_DATE_RANGE_FILTER_
#define ObjectCube_DATE_RANGE_FILTER_

#include "Filter.h"

namespace ObjectCube 
{	
	// Year from has to be set (by the user).
	// If the following values are not set they will be set to the following values:
	//	Month from = 01 (january)
	//	Day of month from = 01 (first day of the month)
	//	Month to = 12 (december)
	// Day of month to = last day of the month. 
	class DateRangeFilter : public Filter
	{
	public:
		//Constructors 
		//Dates in comments are formatted as follows: (YYYY-MM-DD)
		DateRangeFilter( int tagSetId );  // Unlike the simpler filters this one can be created without values, it requires more flexibility
		DateRangeFilter( int yearFrom, int tagSetId );  // yearFrom-01-01 - current date
		DateRangeFilter( int yearFrom, int yearTo, int tagSetId ); // yearFrom-01-01 - yearTo-12-lastDayOfMonth
		DateRangeFilter( int yearFrom, int monthFrom, int yearTo, int monthTo, int tagSetId ); // yearFrom-monthFrom-01 - yearTo-monthTo-lastDayOfMonth
		DateRangeFilter( int yearFrom, int monthFrom, int dayOfMonthFrom, int yearTo, int monthTo, int dayOfMonthTo, int tagSetId );
		
		virtual ~DateRangeFilter();
		
		//Get
		int getYearFrom() const { return yearFrom_; }
		int getMonthFrom() const { return monthFrom_; }
		int getDayOfMonthFrom() const { return dayOfMonthFrom_; }
		
		int getYearTo() const { return yearTo_; }
		int getMonthTo() const { return monthTo_; }
		int getDayOfMonthTo() const { return dayOfMonthTo_; }
		
		//Set
		void setYearFrom( int year );
		void setMonthFrom( int month );
		void setDayOfMonthFrom( int dayOfMonth );
		
		void setYearTo( int year );
		void setMonthTo( int month );
		void setDayOfMonthTo( int dayOfMonth );
		
		
		virtual void fillInAndValidateValues();
		
		//Operator overloading
		virtual Filter& operator=( const Filter& filter );
		
	protected:
		
		//Constructor for factory use
		DateRangeFilter();
		
	private:
		void init_();
		
	protected:
		
		int yearFrom_;
		int monthFrom_;
		int dayOfMonthFrom_;
		
		int yearTo_;
		int monthTo_;
		int dayOfMonthTo_;
		
		friend class FilterFactory;
	};
	
}

#endif