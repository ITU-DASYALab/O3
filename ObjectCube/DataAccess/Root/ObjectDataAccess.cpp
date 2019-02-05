/*
 *  ObjectDataAccess.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 16.2.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */


#include "ObjectDataAccess.h"
#include "../../LayerShared/SharedDefinitions.h"
#include "../../LayerShared/MemoryManagement.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

ObjectDataAccess::ObjectDataAccess()
{
	id_ = INVALID_VALUE;
}
//____________________________________________________________________________________________________________________________________________________________________________________

ObjectDataAccess::~ObjectDataAccess()
{
	clearAndDestroy( objectTags_ );
}
