/*
 *  PluginCommon.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 11.8.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "PluginCommon.h"

#include "../LayerShared/SharedDefinitions.h"

//taka ut
#include <iostream>

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

PluginCommon::PluginCommon() 
{ 
	init_(); 
}
//____________________________________________________________________________________________________________________________________________________________________________________

PluginCommon::~PluginCommon() 
{

}
//____________________________________________________________________________________________________________________________________________________________________________________

void PluginCommon::init_() 
{ 
	id_ = INVALID_VALUE; 
	name_ = "Uninitialized!"; 
}
//____________________________________________________________________________________________________________________________________________________________________________________
/*
PluginTagSet PluginCommon::getPluginTagSet( const string& name ) const 
{
	for( vector<PluginTagSet>::const_iterator itr = pluginTagSets_.begin(); itr != pluginTagSets_.end(); ++itr)
	{
		if( (*itr).getName() == name )
		{
			return *itr;
		}
	}
	throw Exception( "PluginCommon::getPluginTagSet", "Tag set not found!", name );
}
*/
//____________________________________________________________________________________________________________________________________________________________________________________

