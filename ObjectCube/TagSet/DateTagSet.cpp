/*
 *  DateTagSet.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 12.4.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "DateTagSet.h"

#include <sstream>
#include <iomanip>
#include <cstdlib>

#ifdef __APPLE__
#include <memory>
#else
#include <tr1/memory>
#endif

#include "TagSet.h"
#include "../Tag/Tag.h"
#include "../Tag/DateTag.h"
#include "../Filters/TagFilter.h"
#include "../LayerShared/Exception.h"
#include "../LayerShared/DateSupport.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

DateTagSet::DateTagSet()
: TagSet() 
{
	init_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

DateTagSet::DateTagSet( const string& name ) 
: TagSet( name ) 
{ 
	init_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

DateTagSet::DateTagSet( const string& name, const string& description ) 
: TagSet( name, description ) 
{ 
	init_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DateTagSet::init_()
{
	setTypeId_( TagSet::DATE );
	
	supportedTagTypes_.push_back( Tag::DATE );
	
	supportedFilterTypes_.push_back( Filter::DATE_RANGE_FILTER );
}
//____________________________________________________________________________________________________________________________________________________________________________________

TagSet* DateTagSet::createImp_()
{
	return TagSet::createImp_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

DateTagSet* DateTagSet::create()
{
	return dynamic_cast<DateTagSet*>( createImp_() );
}

//____________________________________________________________________________________________________________________________________________________________________________________

const DateTag* /*const*/ DateTagSet::getDateTag( int year, int month, int dayOfMonth ) const
{
	for( vector<std::shared_ptr<Tag> >::const_iterator itr = tags_.begin(); itr != tags_.end(); ++itr )
	{
		if( (*itr)->getTypeId() == TagCommon::DATE )
		{
			DateTag* tag = dynamic_cast<DateTag*>( (*itr).get() );
			if( tag->getYear() == year && tag->getMonth() == month && tag->getDayOfMonth() == dayOfMonth )
			{
				return tag;
			}
		}
	}
	
	throw Exception( "DateTagSet::getTag", "TagSet did not contain requested tag (year, month, dayOfMonth)." );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DateTagSet::fetch_( int id )
{
	TagSet::fetch_( id );
	
	if( getTypeId() != DATE )
	{
		throw Exception( "DateTagSet::fetch_", "Invalid tag set type in fetch.", getTypeId() );
	}
	loadVirtualDimensions_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

const Tag* /*const*/ DateTagSet::fetchOrAddTag( const string& value )
{
	//The only allowed format is YYYY-MM-DD (numerical year, numerical month, numerical day of month)
	
	int year = 0, month = 0, dayOfMonth = 0;
	int startPos = 0, delimiterPos = 0;
	try 
	{
			delimiterPos = value.find( '-', startPos );
			year = atoi( value.substr( startPos, delimiterPos - startPos ).data() );
			startPos = delimiterPos + 1;
			delimiterPos = value.find( '-', startPos );
			month = atoi( value.substr( startPos, delimiterPos - startPos ).data() );
			dayOfMonth = atoi( value.substr( delimiterPos + 1 ).data() );
		}
	catch ( ... ) 
	{
		throw Exception( "DateTagSet::fetchOrAddTag", "Cannot convert value to time.", value );
	}
	
	try
	{
		return getDateTag( year, month, dayOfMonth ); //DateTag::fetch( getId(), year, month, dayOfMonth );
	}
	catch( ... ) {}
	DateTag tag( year, month, dayOfMonth );
	return addTag( &tag );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DateTagSet::loadVirtualDimensions_()
{
	//Create virtual dimensions (Consider putting this in DB)
	
	// Month
	std::shared_ptr<VirtualDimension> monthVDimension( new VirtualDimension( getId(), "-[0-9]{2}-", "[0-9]{2}", "Month" ) );
	for( int i = 1; i < 13; i++ )
	{
		stringstream stringStream;
		stringStream << setw(2) << setfill('0') << right << i;
		monthVDimension.get()->addNode( monthVDimension.get()->getRoot()->getId(), stringStream.str() );
	}
	dimensions_.push_back( monthVDimension );
	
	// Day of month
	std::shared_ptr<VirtualDimension> dayOfMonthVDimension( new VirtualDimension( getId(), "-[0-9]{2}$", "[0-9]{2}$", "Day of month" ) );
	for( int i = 1; i < 32; i++ )
	{
		stringstream stringStream;
		stringStream << setw(2) << setfill('0') << right << i;
		dayOfMonthVDimension.get()->addNode( dayOfMonthVDimension.get()->getRoot()->getId(), stringStream.str() );
	}
	dimensions_.push_back( dayOfMonthVDimension );
	
	// Day of week (0-6) 
	std::shared_ptr<VirtualDimension> dayOfWeekVDimension( new VirtualDimension( getId(), &DateSupport::dayOfWeek, "Day of Week" ) );
	for( int i = 0; i < 7; i++ )
	{
		stringstream stringStream;
		stringStream << i;
		dayOfWeekVDimension.get()->addNode( dayOfWeekVDimension.get()->getRoot()->getId(), stringStream.str() );
	}
	dimensions_.push_back( dayOfWeekVDimension );
	
	// Week of year (1-53, ISO-8601)
	std::shared_ptr<VirtualDimension> weekOfYearVDimension( new VirtualDimension( getId(), &DateSupport::weekOfYear, "Week of Year" ) );
	for( int i = 1; i < 54; i++ )
	{
		stringstream stringStream;
		stringStream << i;
		weekOfYearVDimension.get()->addNode( weekOfYearVDimension.get()->getRoot()->getId(), stringStream.str() );
	}
	dimensions_.push_back( weekOfYearVDimension );
	
	// Quarter (1-4)
	std::shared_ptr<VirtualDimension> quarterVDimension( new VirtualDimension( getId(), &DateSupport::quarter, "Quarter" ) );
	for( int i = 1; i < 5; i++ )
	{
		stringstream stringStream;
		stringStream << i;
		quarterVDimension.get()->addNode( quarterVDimension.get()->getRoot()->getId(), stringStream.str() );
	}
	dimensions_.push_back( quarterVDimension );
	
	// Weekend (only filter using the root)
	std::shared_ptr<VirtualDimension> weekendVDimension( new VirtualDimension( getId(), &DateSupport::dayOfWeek, "Day of Week" ) );

	stringstream ssSaturday, ssSunday;
	ssSaturday << DateSupport::SATURDAY;
	ssSunday << DateSupport::SUNDAY;
	weekendVDimension.get()->addNode( weekendVDimension.get()->getRoot()->getId(), ssSaturday.str() );
	weekendVDimension.get()->addNode( weekendVDimension.get()->getRoot()->getId(), ssSunday.str() );
	
	dimensions_.push_back( weekendVDimension );
	
}
//____________________________________________________________________________________________________________________________________________________________________________________






















