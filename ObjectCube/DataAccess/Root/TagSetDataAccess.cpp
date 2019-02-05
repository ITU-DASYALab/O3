/*
 *  TagSetDataAccess.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 16.2.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */


#include "TagSetDataAccess.h"
#include "../../LayerShared/SharedDefinitions.h"
#include "../../LayerShared/MemoryManagement.h"
#include "TagDataAccess.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

TagSetDataAccess::TagSetDataAccess()
{
	id_ = INVALID_VALUE;
	accessId_ = INVALID_VALUE;
	typeId_ = INVALID_VALUE;
}
//____________________________________________________________________________________________________________________________________________________________________________________

TagSetDataAccess::~TagSetDataAccess()
{
	clearAndDestroy( tags_ );
}
//____________________________________________________________________________________________________________________________________________________________________________________



