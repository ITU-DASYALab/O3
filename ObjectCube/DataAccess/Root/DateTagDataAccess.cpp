/*
 *  DateTagDataAccess.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 10.4.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "DateTagDataAccess.h"

#include "../../LayerShared/SharedDefinitions.h"
#include "../../LayerShared/TagCommon.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

DateTagDataAccess::DateTagDataAccess()
: TagDataAccess()
{
	setYear( INVALID_VALUE );
	setMonth( INVALID_VALUE );
	setDayOfMonth( INVALID_VALUE );
	setTypeId( TagCommon::DATE );
}
//____________________________________________________________________________________________________________________________________________________________________________________

DateTagDataAccess::~DateTagDataAccess()
{
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

