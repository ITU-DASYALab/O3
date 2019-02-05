/*
 *  DimensionDataAccess.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 16.2.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */


#include "DimensionDataAccess.h"
#include "../../LayerShared/SharedDefinitions.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

DimensionDataAccess::DimensionDataAccess()
{
	id_ = INVALID_VALUE;
	tagSetId_ = INVALID_VALUE;
	root_ = 0;
}
//____________________________________________________________________________________________________________________________________________________________________________________

DimensionDataAccess::~DimensionDataAccess()
{
	if( root_ != 0 )
	{
		delete root_;
		root_ = 0;
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________

