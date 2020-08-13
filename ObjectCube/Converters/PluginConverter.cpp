/*
 *  PluginConverter.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 26.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "PluginConverter.h"

#include "../DataAccess/Root/PluginDataAccess.h"
#include "../DataAccess/Factories/PluginDataAccessFactory.h"
#include "PluginTagSetConverter.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

Plugin PluginConverter::dataAccessToLogic( const PluginDataAccess* pluginDA )
{
	Plugin plugin;
	
	plugin.setId_( pluginDA->getId() );
	plugin.setName_( pluginDA->getName() );
	plugin.setDescription_( pluginDA->getDescription() );
	
	plugin.setPluginTagSets_( PluginTagSetConverter::dataAccessToLogic( pluginDA->getPluginTagSets() ) );
	
	return plugin;
}
//____________________________________________________________________________________________________________________________________________________________________________________

unique_ptr<PluginDataAccess> PluginConverter::logicToDataAccess( const Plugin& plugin )
{
	unique_ptr<PluginDataAccess> pluginDA( PluginDataAccessFactory::create() );
	
	pluginDA->setId( plugin.getId() );
	pluginDA->setName( plugin.getName() );
	pluginDA->setDescription( plugin.getDescription() );
	
	pluginDA->setPluginTagSets( PluginTagSetConverter::logicToDataAccess( plugin.getPluginTagSets() ) );
	
	return pluginDA;
}
//____________________________________________________________________________________________________________________________________________________________________________________

vector<Plugin> PluginConverter::dataAccessToLogic( const vector<PluginDataAccess*>& pluginsDA )
{
	vector<Plugin> plugins;
	for( vector<PluginDataAccess*>::const_iterator itr = pluginsDA.begin(); itr != pluginsDA.end(); ++itr )
	{
		plugins.push_back( PluginConverter::dataAccessToLogic( *itr ) );
	}
	return plugins;
}
//____________________________________________________________________________________________________________________________________________________________________________________

vector<PluginDataAccess*> PluginConverter::logicToDataAccess( const vector<Plugin>& plugins )
{
	vector<PluginDataAccess*> pluginsDA;
	for( vector<Plugin>::const_iterator itr = plugins.begin(); itr != plugins.end(); ++itr )
	{
		pluginsDA.push_back( PluginConverter::logicToDataAccess( *itr ).release() );
	}
	return pluginsDA;
}
//____________________________________________________________________________________________________________________________________________________________________________________

