/*
 *  PluginTagSet.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 25.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "PluginTagSet.h"

#include <memory>

#include "../DataAccess/Root/PluginTagSetDataAccess.h"
#include "../DataAccess/Factories/PluginTagSetDataAccessFactory.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

void PluginTagSet::updateTagSetId( int tagSetId )
{
	unique_ptr<PluginTagSetDataAccess> dataAccess( PluginTagSetDataAccessFactory::create() );
	dataAccess->updateTagSetId( getId(), tagSetId );
	setTagSetId_( tagSetId );
}
//____________________________________________________________________________________________________________________________________________________________________________________

bool PluginTagSet::operator < ( const PluginTagSet& b ) const  //for std::map
{ 
	return b.getId() < getId(); 
} 
//____________________________________________________________________________________________________________________________________________________________________________________

