/*
 *  PluginTagSetDataAccess.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 25.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "PluginTagSetDataAccess.h"

#include "../../LayerShared/SharedDefinitions.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

PluginTagSetDataAccess::PluginTagSetDataAccess()
{
	setId( INVALID_VALUE );
	setPluginId( INVALID_VALUE );
	setTagSetTypeId( INVALID_VALUE );
	setTagTypeId( INVALID_VALUE );
	setName( UNINITIALIZED );
	setTagSetName( UNINITIALIZED );
	setTagSetId( INVALID_VALUE );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

