/*
 *  PluginServer.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 15.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_PLUGIN_SERVER_
#define ObjectCube_PLUGIN_SERVER_

#include <map>
#include "PluginLibrary.h"
#include "ProcessObjectServer.h" //Specific to processing objects (tagging)

/*
 The plugin architecture borrows heavily from: 
	http://www.nuclex.org/articles/5-cxx/4-building-a-better-plugin-architecture
 */

using namespace std;

const double PLUGIN_INTERFACE_VERSION = 0.1;

namespace ObjectCube
{
	class PluginCommon;
	
	class PluginServer //A generic plugin server that can support many plugin types (multiple interfaces)
	{
	public:
		PluginServer();
		
		ProcessObjectServer& getProcessObjectServer() { return processObjectServer_; }
		
		void addProcessObjectPlugin( PluginCommon* plugin ) { getProcessObjectServer().addObjectProcessor( plugin ); };
		
	private:
		void init_();
		void loadPlugin_( const int id, const string& libraryName );
		
	private:
		map<string, PluginLibrary> plugins_;
		
		ProcessObjectServer processObjectServer_;
		
	};
}

#endif