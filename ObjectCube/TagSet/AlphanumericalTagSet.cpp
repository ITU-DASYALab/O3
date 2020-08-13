/*
 *  AlphanumericalTagSet.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 25.10.2009.
 *  Copyright 2009 Reykjavik University. All rights reserved.
 *
 */

#include <iostream>

#include "AlphanumericalTagSet.h"

#include "../Hub.h"
#include "../Tag/Tag.h"
#include "../Tag/AlphanumericalTag.h"
#include "../Filters/TagFilter.h"
#include "../LayerShared/Exception.h"
#include "../LayerShared/DebugInfo.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

AlphanumericalTagSet::AlphanumericalTagSet()
: TagSet() 
{
	init_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

AlphanumericalTagSet::AlphanumericalTagSet( const string& name ) 
: TagSet( name ) 
{ 
	init_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

AlphanumericalTagSet::AlphanumericalTagSet( const string& name, const string& description ) 
: TagSet( name, description ) 
{ 
	init_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void AlphanumericalTagSet::init_()
{
	setTypeId_( TagSet::ALPHANUMERICAL );
	
	supportedTagTypes_.push_back( Tag::ALPHANUMERICAL );
}
//____________________________________________________________________________________________________________________________________________________________________________________

TagSet* AlphanumericalTagSet::createImp_()
{
	TagSet::createImp_();
	
	//Specific things here
	return Hub::getHub()->getTagSet( getId() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

AlphanumericalTagSet* AlphanumericalTagSet::create()
{
	createImp_();
	return dynamic_cast<AlphanumericalTagSet*>( Hub::getHub()->getTagSet( getId() ) );
}

//____________________________________________________________________________________________________________________________________________________________________________________

const AlphanumericalTag* /*const*/ AlphanumericalTagSet::getAlphanumericalTag( string name ) const
{
	for( vector<std::shared_ptr<Tag> >::const_iterator itr = tags_.begin(); itr != tags_.end(); ++itr )
	{
		if( (*itr)->getTypeId() == TagCommon::ALPHANUMERICAL )
		{
			AlphanumericalTag* tag = dynamic_cast<AlphanumericalTag*>( (*itr).get() );
			if( tag->getName() == name )
			{
				return tag;
			}
		}
	}
	
	throw Exception( "AlphanumericalTagSet::getTag", "TagSet did not contain requested tag (name).", name );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void AlphanumericalTagSet::fetch_( int id )
{
	TagSet::fetch_( id );
	
	if( getTypeId() != ALPHANUMERICAL )
	{
		throw Exception( "AlphanumericalTagSet::fetch_", "Invalid tag set type in fetch.", getTypeId() );
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________

const Tag* /*const*/ AlphanumericalTagSet::fetchOrAddTag( const string& value )
{
	//DebugInfo::getDebugInfo()->output("AlphanumericalTagSet", "fetchOrAddTag", "Trying to fetch!");
	try 
	{
		return getAlphanumericalTag( value ); //AlphanumericalTag::fetch( getId(), value );
	}
	catch ( ... ) {}
	//DebugInfo::getDebugInfo()->output("AlphanumericalTagSet", "fetchOrAddTag", "Could not fetch, trying to create!");
	AlphanumericalTag tag( value );
	return addTag( &tag );
}

//____________________________________________________________________________________________________________________________________________________________________________________











