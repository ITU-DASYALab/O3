/*
 *  PluginDataAccessFactory.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 25.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_PLUGIN_DATA_ACCESS_FACTORY_
#define ObjectCube_PLUGIN_DATA_ACCESS_FACTORY_

namespace ObjectCube
{
	class PluginDataAccess;
	
	class PluginDataAccessFactory
	{
	public:
		static PluginDataAccess* create();

	};
	
}

#endif