/*
 *  NumericalTagDataAccess.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 27.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "NumericalTagDataAccess.h"

#include "../../LayerShared/SharedDefinitions.h"
#include "../../LayerShared/TagCommon.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

NumericalTagDataAccess::NumericalTagDataAccess()
: TagDataAccess()
{
	setNumber( INVALID_VALUE );
	setTypeId( TagCommon::NUMERICAL );
}
//____________________________________________________________________________________________________________________________________________________________________________________

NumericalTagDataAccess::~NumericalTagDataAccess()
{
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

