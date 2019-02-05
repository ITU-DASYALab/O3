/*
 *  StateObject.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 17.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "StateObject.h"

#include "../LayerShared/SharedDefinitions.h"
#include "../Tag/Tag.h"
#include "../Hub.h"
#include "../LayerShared/TagSetCommon.h"
#include "../LayerShared/Exception.h"
#include <iostream>
using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

StateObject::StateObject()
{
	init_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void StateObject::init_()
{
	id_ = INVALID_VALUE;
}
//____________________________________________________________________________________________________________________________________________________________________________________

bool StateObject::hasTag( int id ) const
{
	for( vector<StateTag>::const_iterator itr = tags_.begin(); itr != tags_.end(); ++itr )
	{
		if( (*itr).getTag()->getId() == id )
		{
			return true;
		}
	}
	return false;
}
//____________________________________________________________________________________________________________________________________________________________________________________

bool StateObject::hasUserTags()
{
	Hub* hub = Hub::getHub();
	
	vector<StateTag>::iterator itr;
	for( itr = tags_.begin(); itr != tags_.end(); itr++ )
	{
		if( hub->getParentTagSetsAccessType( (*itr).getTag() ) == TagSetCommon::USER )
		{
			return true;
		}
	}
	return false;	
}
//____________________________________________________________________________________________________________________________________________________________________________________

const vector<StateTag> StateObject::getTags( int tagSetId ) const
{
	vector<StateTag> tagsInTagSet;
	for( vector<StateTag>::const_iterator itr = tags_.begin(); itr != tags_.end(); ++itr )
	{
		if( (*itr).getTag()->getTagSetId() == tagSetId )
		{
			tagsInTagSet.push_back( *itr );
		}
	}
	return tagsInTagSet;
}
//____________________________________________________________________________________________________________________________________________________________________________________

const StateTag StateObject::getTag( int id ) const
{
	vector<StateTag>::const_iterator itr;
	for( itr = tags_.begin(); itr != tags_.end(); itr++ )
	{
		if( (*itr).getTag()->getId() == id )
		{
			return *itr;
		}
	}
	throw Exception("StateObject::getTag(id)", "Tag requested is not attached to this state object.", id);
}
//____________________________________________________________________________________________________________________________________________________________________________________

