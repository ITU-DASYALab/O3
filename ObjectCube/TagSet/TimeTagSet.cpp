/*
 *  TimeTagSet.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 12.4.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "TimeTagSet.h"

#include <sstream>
#include <iomanip>
#include <cstdlib>

#ifdef __APPLE__
#include <memory>
using std::shared_ptr;
#else
#include <tr1/memory>
using std::shared_ptr;
#endif

#include "TagSet.h"
#include "../Tag/Tag.h"
#include "../Tag/TimeTag.h"
#include "../Filters/TagFilter.h"
#include "../Filters/TimeRangeFilter.h"
#include "../LayerShared/Exception.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

TimeTagSet::TimeTagSet()
: TagSet() 
{
	init_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

TimeTagSet::TimeTagSet( const string& name ) 
: TagSet( name ) 
{ 
	init_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

TimeTagSet::TimeTagSet( const string& name, const string& description ) 
: TagSet( name, description ) 
{ 
	init_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TimeTagSet::init_()
{
	setTypeId_( TagSet::TIME );
	
	supportedTagTypes_.push_back( Tag::TIME );
	
	supportedFilterTypes_.push_back( Filter::TIME_RANGE_FILTER );
}
//____________________________________________________________________________________________________________________________________________________________________________________

TagSet* TimeTagSet::createImp_()
{
	return TagSet::createImp_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

TimeTagSet* TimeTagSet::create()
{
	return dynamic_cast<TimeTagSet*>( createImp_() );
}

//____________________________________________________________________________________________________________________________________________________________________________________

const TimeTag* /*const*/ TimeTagSet::getTimeTag( int hours, int minutes, int seconds, int milliseconds ) const
{
	for( vector<std::shared_ptr<Tag> >::const_iterator itr = tags_.begin(); itr != tags_.end(); ++itr )
	{
		if( (*itr)->getTypeId() == TagCommon::TIME )
		{
			TimeTag* tag = dynamic_cast<TimeTag*>( (*itr).get() );
			if( tag->getHours() == hours && tag->getMinutes() == minutes && tag->getSeconds() == seconds && tag->getMilliseconds() == milliseconds )
			{
				return tag;
			}
		}
	}
	
	throw Exception( "TimeTagSet::getTag", "TagSet did not contain requested tag (hours, minutes, seconds, milliseconds)." );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TimeTagSet::fetch_( int id )
{
	TagSet::fetch_( id );
	
	if( getTypeId() != TIME )
	{
		throw Exception( "TimeTagSet::fetch_", "Invalid tag set type in fetch.", getTypeId() );
	}
	loadVirtualDimensions_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

const Tag* /*const*/ TimeTagSet::fetchOrAddTag( const string& value )
{
	//The only allowed format is HH:MM:SS(.mmm)?	(hours (24):minutes:seconds.milliseconds)
	
	int hours = 0, minutes = 0, seconds = 0, milliseconds = 0;
	int startPos = 0, delimiterPos = 0;
	try 
	{
		delimiterPos = value.find( ':', startPos );
		hours = atoi( value.substr( startPos, delimiterPos - startPos ).data() );
		startPos = delimiterPos + 1;
		delimiterPos = value.find( ':', startPos );
		minutes = atoi( value.substr( startPos, delimiterPos - startPos ).data() );
		startPos = delimiterPos + 1;
		delimiterPos = value.find( '.', startPos );
		if( delimiterPos != string::npos )
		{
			seconds = atoi( value.substr( startPos, delimiterPos - startPos ).data() );
			milliseconds = atoi( value.substr( delimiterPos + 1 ).data() );
		}
		else
		{
			seconds = atoi( value.substr(startPos ).data() );
		}
	}
	catch ( ... ) 
	{
		throw Exception( "TimeTagSet::fetchOrAddTag", "Cannot convert value to time.", value );
	}
	
	try
	{
		return getTimeTag( hours, minutes, seconds, milliseconds ); //TimeTag::fetch( getId(), hours, minutes, seconds, milliseconds );
	}
	catch( ... ) {}
	TimeTag tag( hours, minutes, seconds, milliseconds );
	return addTag( &tag );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TimeTagSet::loadVirtualDimensions_()
{
	//Create virtual dimensions (Consider putting this in DB)
	// Hour
	
	std::shared_ptr<VirtualDimension> hourVDimension( new VirtualDimension( getId(), "[0-9]{2}:", "[0-9]{2}", "Hour"  ) );
	for( int i = 0; i < 24; i++ )
	{
		stringstream stringStream;
		stringStream << setw(2) << setfill('0') << right << i;
		hourVDimension.get()->addNode( hourVDimension.get()->getRoot()->getId(), stringStream.str() );
	}
	dimensions_.push_back( hourVDimension );
	
	// Minute
	std::shared_ptr<VirtualDimension> minuteVDimension( new VirtualDimension( getId(), ":[0-9]{2}:", "[0-9]{2}", "Minute" ) );
	for( int i = 0; i < 60; i++ )
	{
		stringstream stringStream;
		stringStream << setw(2) << setfill('0') << right << i;
		minuteVDimension.get()->addNode( minuteVDimension.get()->getRoot()->getId(), stringStream.str() );
	}
	dimensions_.push_back( minuteVDimension );
	
	// Second
	std::shared_ptr<VirtualDimension> secondVDimension( new VirtualDimension( getId(), ":[0-9]{2}.", "[0-9]{2}", "Second" ) );
	for( int i = 0; i < 60; i++ )
	{
		stringstream stringStream;
		stringStream << setw(2) << setfill('0') << right << i;
		secondVDimension.get()->addNode( secondVDimension.get()->getRoot()->getId(), stringStream.str() );
	}
	dimensions_.push_back( secondVDimension );	
	 
}
//____________________________________________________________________________________________________________________________________________________________________________________

