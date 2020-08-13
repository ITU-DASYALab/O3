/*
 *  PluginConverter.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 26.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_PLUGIN_CONVERTER_
#define ObjectCube_PLUGIN_CONVERTER_

#include <vector>
#include <memory>

#include "../Plugin/Plugin.h"

namespace ObjectCube 
{	
	class PluginDataAccess;
	
	class PluginConverter
	{
	public:
		static Plugin dataAccessToLogic( const PluginDataAccess* pluginDA );
		static unique_ptr<PluginDataAccess> logicToDataAccess( const Plugin& plugin );
		
		static vector<Plugin> dataAccessToLogic( const vector<PluginDataAccess*>& pluginsDA );
		static vector<PluginDataAccess*> logicToDataAccess( const vector<Plugin>& plugins );
		
	};
}

#endif