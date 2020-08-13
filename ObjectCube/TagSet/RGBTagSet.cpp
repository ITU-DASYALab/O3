/*
 *  AlphanumericalTagSet.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 25.10.2009.
 *  Copyright 2009 Reykjavik University. All rights reserved.
 *
 */

#include <iostream>

#include "RGBTagSet.h"

#include "../Hub.h"
#include "../Tag/Tag.h"
#include "../Tag/RGBTag.h"
#include "../Filters/TagFilter.h"
#include "../LayerShared/Exception.h"
#include "../LayerShared/DebugInfo.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

RGBTagSet::RGBTagSet()
: TagSet() 
{
	init_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

RGBTagSet::RGBTagSet( const string& name ) 
: TagSet( name ) 
{ 
	init_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

RGBTagSet::RGBTagSet( const string& name, const string& description ) 
: TagSet( name, description ) 
{ 
	init_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void RGBTagSet::init_()
{
	setTypeId_( TagSet::RGB );
	
	supportedTagTypes_.push_back( Tag::RGB );
}
//____________________________________________________________________________________________________________________________________________________________________________________

TagSet* RGBTagSet::createImp_()
{
	TagSet::createImp_();
	
	//Specific things here
	return Hub::getHub()->getTagSet( getId() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

RGBTagSet* RGBTagSet::create()
{
	createImp_();
	return dynamic_cast<RGBTagSet*>( Hub::getHub()->getTagSet( getId() ) );
}

//____________________________________________________________________________________________________________________________________________________________________________________

const RGBTag* /*const*/ RGBTagSet::getRGBTag( string name ) const
{
	for( vector<std::shared_ptr<Tag> >::const_iterator itr = tags_.begin(); itr != tags_.end(); ++itr )
	{
		if( (*itr)->getTypeId() == TagCommon::RGB )
		{
			RGBTag* tag = dynamic_cast<RGBTag*>( (*itr).get() );
			if( tag->getName() == name )
			{
				return tag;
			}
		}
	}
	
	throw Exception( "RGBTagSet::getTag", "TagSet did not contain requested tag (name).", name );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void RGBTagSet::fetch_( int id )
{
	TagSet::fetch_( id );
	
	if( getTypeId() != RGB )
	{
		throw Exception( "RGBTagSet::fetch_", "Invalid tag set type in fetch.", getTypeId() );
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________

const Tag* /*const*/ RGBTagSet::fetchOrAddTag( const string& value )
{
	//DebugInfo::getDebugInfo()->output("AlphanumericalTagSet", "fetchOrAddTag", "Trying to fetch!");
	try 
	{
		return getRGBTag( value ); //RGBTag::fetch( getId(), value );
	}
	catch ( ... ) {}
	//DebugInfo::getDebugInfo()->output("RGBTagSet", "fetchOrAddTag", "Could not fetch, trying to create!");
	RGBTag tag( value );
	return addTag( &tag );
}

//____________________________________________________________________________________________________________________________________________________________________________________











