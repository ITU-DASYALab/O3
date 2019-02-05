/*
 *  PluginTagSetDataAccessFactory.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 26.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_PLUGIN_TAG_SET_DATA_ACCESS_FACTORY_
#define ObjectCube_PLUGIN_TAG_SET_DATA_ACCESS_FACTORY_

namespace ObjectCube
{
	class PluginTagSetDataAccess;
	
	class PluginTagSetDataAccessFactory
	{
	public:
		static PluginTagSetDataAccess* create();
		
	};
	
}

#endif