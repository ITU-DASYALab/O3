/*
 *  PluginTagSetConverter.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 26.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_PLUGIN_TAG_SET_CONVERTER_
#define ObjectCube_PLUGIN_TAG_SET_CONVERTER_

#include <vector>
#include <memory>

#include "../Plugin/PluginTagSet.h"

namespace ObjectCube 
{	
	class PluginTagSetDataAccess;
	
	class PluginTagSetConverter
	{
	public:
		static PluginTagSet dataAccessToLogic( const PluginTagSetDataAccess* pluginTagSetDA );
		static unique_ptr<PluginTagSetDataAccess> logicToDataAccess( const PluginTagSet& pluginTagSet );
		
		static vector<PluginTagSet> dataAccessToLogic( const vector<PluginTagSetDataAccess*>& pluginTagSetsDA );
		static vector<PluginTagSetDataAccess*> logicToDataAccess( const vector<PluginTagSet>& pluginTagSets );
		
	};
}

#endif