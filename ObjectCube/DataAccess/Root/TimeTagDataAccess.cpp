/*
 *  TimeTagDataAccess.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 9.4.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "TimeTagDataAccess.h"

#include "../../LayerShared/SharedDefinitions.h"
#include "../../LayerShared/TagCommon.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

TimeTagDataAccess::TimeTagDataAccess()
: TagDataAccess()
{
	setHours( INVALID_VALUE );
	setMinutes( INVALID_VALUE );
	setSeconds( INVALID_VALUE );
	setMilliseconds( INVALID_VALUE );
	setTypeId( TagCommon::TIME );
}
//____________________________________________________________________________________________________________________________________________________________________________________

TimeTagDataAccess::~TimeTagDataAccess()
{
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

