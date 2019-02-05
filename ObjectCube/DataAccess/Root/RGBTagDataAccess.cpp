/*
 *  AlphanumericalTagDataAccess.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 22.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "RGBTagDataAccess.h"

#include "../../LayerShared/SharedDefinitions.h"
#include "../../LayerShared/TagCommon.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

RGBTagDataAccess::RGBTagDataAccess()
: TagDataAccess()
{
	name_ = "Not initialized!";
	setTypeId( TagCommon::RGB );
}
//____________________________________________________________________________________________________________________________________________________________________________________

RGBTagDataAccess::~RGBTagDataAccess()
{

}
//____________________________________________________________________________________________________________________________________________________________________________________

