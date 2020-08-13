/*
 *  Plugin.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 26.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "Plugin.h"

#include "../DataAccess/Root/PluginDataAccess.h"
#include "../DataAccess/Factories/PluginDataAccessFactory.h"
#include "../Converters/PluginConverter.h" 

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

Plugin::Plugin()
{

}
//____________________________________________________________________________________________________________________________________________________________________________________

Plugin Plugin::fetch( int id )
{
	unique_ptr<PluginDataAccess> dataAccess( PluginDataAccessFactory::create() );
	return PluginConverter::dataAccessToLogic( dataAccess->fetch( id ) );
}
//____________________________________________________________________________________________________________________________________________________________________________________


