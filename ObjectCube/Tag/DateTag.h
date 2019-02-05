/*
 *  DateTag.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 10.4.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_DATE_TAG_
#define ObjectCube_DATE_TAG_

#include <string>

#include "Tag.h"

using namespace std;

namespace ObjectCube
{	
	class DateTag : public Tag
	{
		friend class TagSet;
		friend class DateTagConverter;
	public:
		//Constructors & Destructor
		DateTag();
		DateTag( int year, int month, int dayOfMonth );
		
		virtual ~DateTag();
		
		//Functions
		static DateTag* fetch( int id );  //a faster version than the one in Tag
		static DateTag* fetch( int tagSetId, int year, int month, int dayOfMonth );
		
		//Get/Set
		int getYear() const { return year_; }
		int getMonth() const { return month_; }
		int getDayOfMonth() const { return dayOfMonth_; }
		
		bool isNull() const { return isNull_; } //Has the number been set?
		
		void setYear( int year ) { year_ = year; setNull_(false); }
		void setMonth( int month ) { month_ = month; setNull_(false); }
		void setDayOfMonth( int dayOfMonth ) { dayOfMonth_ = dayOfMonth; setNull_(false); }
		
	protected:
		virtual void fetchImp_();
		virtual void create_();  
		virtual void delete_();
		virtual const string valueAsString_() const;
		
	private: //Member functions
		virtual void init_();
		void setNull_( bool value ) { isNull_ = value; }
		
	private:  //Member variables
		int year_;
		int month_;
		int dayOfMonth_;
		bool isNull_;
		
	public: //Operator overloading
		virtual Tag& operator=( const Tag& tag );
		
		static bool compare( const DateTag* a, const DateTag* b );

		//For unit testing
		//For testing..... this needs refactoring !!!  Consider inheriting all logic classes and implementing public getters and setters for all member variables.
		friend class DateTagTest;
		friend class DateTagSetTest;
		
	};
	
}

#endif
