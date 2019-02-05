/*
 *  StateTagDataAccess.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 18.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "StateTagDataAccess.h"

#include "../../LayerShared/SharedDefinitions.h"
#include "../../LayerShared/Exception.h"
#include "BoundingBoxDataAccess.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

StateTagDataAccess::StateTagDataAccess()
{
	tagId_ = 0;
	boundingBox_ = 0;
}
//____________________________________________________________________________________________________________________________________________________________________________________

StateTagDataAccess::~StateTagDataAccess()
{
	if( boundingBox_ )
	{
		delete boundingBox_;
		boundingBox_ = 0;
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________

BoundingBoxDataAccess* StateTagDataAccess::getBoundingBox() const
{
	if( !boundingBox_ )
	{
		throw Exception( "StateTagDataAccess::getBoundingBox", "Attempt to get a non-existing bounding box!" );
	}
	return boundingBox_;
}
//____________________________________________________________________________________________________________________________________________________________________________________

bool StateTagDataAccess::hasBoundingBox()
{
	return boundingBox_ == 0 ? false : true;
}
//____________________________________________________________________________________________________________________________________________________________________________________

