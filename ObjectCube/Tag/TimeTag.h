/*
 *  TimeTag.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 9.4.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_TIME_TAG_
#define ObjectCube_TIME_TAG_

#include <string>

#include "Tag.h"

using namespace std;

namespace ObjectCube
{	
	class TimeTag : public Tag
	{
		friend class TagSet;
		friend class TimeTagConverter;
	public:
		//Constructors & Destructor
		TimeTag();
		TimeTag( int hours, int minutes, int seconds, int milliseconds );
		
		virtual ~TimeTag();
		
		//Functions
		static TimeTag* fetch( int id );  //a faster version than the one in Tag
		static TimeTag* fetch( int tagSetId, int hours, int minutes, int seconds, int milliseconds );
		
		//Get/Set
		int getHours() const { return hours_; }
		int getMinutes() const { return minutes_; }
		int getSeconds() const { return seconds_; }
		int getMilliseconds() const { return milliseconds_; }
		
		bool isNull() const { return isNull_; } //Has the number been set?
		
		void setHours( int hours ) { hours_ = hours; setNull_(false); }
		void setMinutes( int minutes ) { minutes_ = minutes; setNull_(false); }
		void setSeconds( int seconds ) { seconds_ = seconds; setNull_(false); }
		void setMilliseconds( int milliseconds ) { milliseconds_ = milliseconds; setNull_(false); }
		
	protected:
		virtual void fetchImp_();
		virtual void create_();  
		virtual void delete_();
		virtual const string valueAsString_() const;
		
	private: //Member functions
		virtual void init_();
		void setNull_( bool value ) { isNull_ = value; }
		
	private:  //Member variables
		int hours_;
		int minutes_;
		int seconds_;
		int milliseconds_;
		bool isNull_;
		
	public: //Operator overloading
		virtual Tag& operator=( const Tag& tag );
		
		static bool compare( const TimeTag* a, const TimeTag* b );

		//For unit testing
		//For testing..... this needs refactoring !!!  Consider inheriting all logic classes and implementing public getters and setters for all member variables.
		friend class TimeTagTest;
		friend class TimeTagSetTest;
		
	};
	
}

#endif
