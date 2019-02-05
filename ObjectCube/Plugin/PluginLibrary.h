/*
 *  ObjectCubePlugin.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 14.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_PLUGIN_LIBRARY_
#define ObjectCube_PLUGIN_LIBRARY_

#include <string>

using namespace std;

namespace ObjectCube
{ 
	class PluginObject;
	class PluginServer;
	
	class PluginLibrary 
	{
	public:
		PluginLibrary( const string& filename );
		PluginLibrary( const PluginLibrary& plugin );  // Copy constructor
		virtual ~PluginLibrary();
		
		double getPluginInterfaceVersion() const;
		void registerPlugin( const int id, PluginServer& pluginServer );
		
	private:
		PluginLibrary& operator=( const PluginLibrary& plugin ); //Assignment operator
		
		typedef double fpGetPluginInterfaceVersion();  // Version query function signature
		typedef void fpRegisterPlugin( const int id, PluginServer& pluginServer ); // PluginLibrary registration function signature
		
		int* libraryReferenceCount_;
		fpGetPluginInterfaceVersion* getPluginInterfaceVersion_;
		fpRegisterPlugin* registerPlugin_;
		void* libraryHandle_;
		
	};
}

#endif
