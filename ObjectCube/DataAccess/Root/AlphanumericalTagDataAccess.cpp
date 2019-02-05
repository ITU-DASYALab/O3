/*
 *  AlphanumericalTagDataAccess.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 22.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "AlphanumericalTagDataAccess.h"

#include "../../LayerShared/SharedDefinitions.h"
#include "../../LayerShared/TagCommon.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

AlphanumericalTagDataAccess::AlphanumericalTagDataAccess()
: TagDataAccess()
{
	name_ = "Not initialized!";
	setTypeId( TagCommon::ALPHANUMERICAL );
}
//____________________________________________________________________________________________________________________________________________________________________________________

AlphanumericalTagDataAccess::~AlphanumericalTagDataAccess()
{

}
//____________________________________________________________________________________________________________________________________________________________________________________

