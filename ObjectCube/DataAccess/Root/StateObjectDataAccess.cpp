/*
 *  StateObjectDataAccess.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 18.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "StateObjectDataAccess.h"

#include "../../LayerShared/SharedDefinitions.h"
#include "../../LayerShared/MemoryManagement.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

StateObjectDataAccess::StateObjectDataAccess()
{
	id_ = INVALID_VALUE;
}
//____________________________________________________________________________________________________________________________________________________________________________________

StateObjectDataAccess::~StateObjectDataAccess()
{
	clearAndDestroy( tags_ );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void StateObjectDataAccess::addTag( StateTagDataAccess* tag )
{
	tags_.push_back( tag );
}
//____________________________________________________________________________________________________________________________________________________________________________________