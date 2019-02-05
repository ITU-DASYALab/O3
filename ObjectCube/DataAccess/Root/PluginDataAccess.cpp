/*
 *  PluginDataAccess.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 25.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "PluginDataAccess.h"

#include "PluginTagSetDataAccess.h"
#include "../../LayerShared/SharedDefinitions.h"
#include "../../LayerShared/MemoryManagement.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

PluginDataAccess::PluginDataAccess()
{
	setId( INVALID_VALUE );
}
//____________________________________________________________________________________________________________________________________________________________________________________

PluginDataAccess::~PluginDataAccess()
{
	clearAndDestroy( pluginTagSets_ );
}