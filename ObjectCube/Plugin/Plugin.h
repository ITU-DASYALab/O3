/*
 *  Plugin.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 26.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_PLUGIN_
#define ObjectCube_PLUGIN_


#include "PluginCommon.h"

using namespace std;

namespace ObjectCube
{
	class Plugin : public PluginCommon  
	{
	public:
		Plugin();
		virtual ~Plugin() {;}
		
		static Plugin fetch( int id );
				
	private:
		virtual void makeAbstract() {;}
		
	private:
		friend class PluginConverter;
		
	};
	
}

#endif