/*
 *  NumericalTagSet.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 27.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "NumericalTagSet.h"

#include "TagSet.h"
#include "../Tag/Tag.h"
#include "../Tag/NumericalTag.h"
#include "../Filters/TagFilter.h"
#include "../LayerShared/Exception.h"

#include <cstdlib>

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

NumericalTagSet::NumericalTagSet()
: TagSet() 
{
	init_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

NumericalTagSet::NumericalTagSet( const string& name ) 
: TagSet( name ) 
{ 
	init_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

NumericalTagSet::NumericalTagSet( const string& name, const string& description ) 
: TagSet( name, description ) 
{ 
	init_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void NumericalTagSet::init_()
{
	setTypeId_( TagSet::NUMERICAL );
	
	supportedTagTypes_.push_back( Tag::NUMERICAL );
	
	supportedFilterTypes_.push_back( Filter::NUMERICAL_RANGE_FILTER );
}
//____________________________________________________________________________________________________________________________________________________________________________________

TagSet* NumericalTagSet::createImp_()
{
	return TagSet::createImp_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

NumericalTagSet* NumericalTagSet::create()
{
	return dynamic_cast<NumericalTagSet*>( createImp_() );
}

//____________________________________________________________________________________________________________________________________________________________________________________

const NumericalTag* /*const*/ NumericalTagSet::getNumericalTag( long number ) const
{
	for( vector<std::shared_ptr<Tag> >::const_iterator itr = tags_.begin(); itr != tags_.end(); ++itr )
	{
		if( (*itr)->getTypeId() == TagCommon::NUMERICAL )
		{
			NumericalTag* tag = dynamic_cast<NumericalTag*>( (*itr).get() );
			if( tag->getNumber() == number )
			{
				return tag;
			}
		}
	}
	
	throw Exception( "NumericalTagSet::getTag", "TagSet did not contain requested tag (number).", number );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void NumericalTagSet::fetch_( int id )
{
	TagSet::fetch_( id );
	
	if( getTypeId() != NUMERICAL )
	{
		throw Exception( "NumericalTagSet::fetch_", "Invalid tag set type in fetch.", getTypeId() );
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________

const Tag* /*const*/ NumericalTagSet::fetchOrAddTag( const string& value )
{
	long lValue = 0;
	try 
	{
		//Only integer support for now, consider making the number of a NumericalTag a real number.
		int slashLocation = value.find( "/" );
		if( slashLocation != string::npos )
		{
			string numerator = value.substr( 0, slashLocation );
			string denominator = value.substr( slashLocation + 1, value.length() - (slashLocation + 1) );
			long lNumerator = atoi( numerator.data() );
			long lDenominator = atoi( denominator.data() );
			if( lNumerator == 0 || lDenominator == 0 )
			{
				throw Exception( "NumericalTagSet::fetchOrAddTag", "Illegal number, either denominator or numerator = 0" );
			}
			lValue = lNumerator / lDenominator;
		}
		else 
		{
			lValue = atoi( value.data() );
		}
	}
	catch ( ... ) 
	{
		throw Exception( "NumericalTagSet::fetchOrAddTag", "Cannot convert value to an integer.", value );
	}
	
	try
	{
		return getNumericalTag( lValue ); //NumericalTag::fetch( getId(), lValue );
	}
	catch( ... ) {}
	NumericalTag tag( lValue );
	return addTag( &tag );
}
//____________________________________________________________________________________________________________________________________________________________________________________

