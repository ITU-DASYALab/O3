/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/


#ifndef ObjectCube_DATE_RANGE_FILTER_DATA_ACCESS_
#define ObjectCube_DATE_RANGE_FILTER_DATA_ACCESS_

#include "FilterDataAccess.h"

namespace ObjectCube 
{	
	class DateRangeFilterDataAccess : public FilterDataAccess
	{
	public:
		DateRangeFilterDataAccess(); 
		virtual ~DateRangeFilterDataAccess();
		
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
		
	protected:
		virtual string getSelectionPredicate_();
		virtual string getFiltrationPredicate_();
		
	protected:
		
		int yearFrom_;
		int monthFrom_;
		int dayOfMonthFrom_;
		
		int yearTo_;
		int monthTo_;
		int dayOfMonthTo_;
		
	};
	
}

#endif