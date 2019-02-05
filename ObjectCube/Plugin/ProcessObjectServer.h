/*
 *  ProcessObjectServer.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 15.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_PROCESS_OBJECT_SERVER_
#define ObjectCube_PROCESS_OBJECT_SERVER_

#include <string>
#include <vector>
#include <map>
#include "PluginTagSet.h"
#include "PluginReply.h"
#include "PluginTaggingProcessed.h"
#include "../LayerShared/SharedDefinitions.h"

using namespace std;

namespace ObjectCube
{
	class ProcessObjectPlugin;
	class PluginObject;
	class PluginCommon;
	
	class ProcessObjectServer
	{
	public:
		~ProcessObjectServer();
		typedef vector<PluginCommon*> ProcessObjectPluginsContainer;
		
		void addObjectProcessor( PluginCommon* processor ) { processObjectPlugins_.push_back( processor ); }
	
		//map<PluginTagSet, string> process( const PluginObject& object );
		//map<PluginTagSet, string> process( const PluginObject& object, int pluginId );
		
		
		vector<PluginTaggingProcessed> process( const PluginObject& object );  
		vector<PluginTaggingProcessed> process( const PluginObject& object, int pluginId );
		vector<PluginTaggingProcessed> process( const PluginObject& object, const vector<BoundingBox>& boundingBoxes, int pluginId = INVALID_VALUE );
		 
		void confirmTagging( int objectId, const string& tagSetName,
							 const BoundingBox& boundingBox, const string& tag );
		
		void loadPluginInfo();
		
		ProcessObjectPluginsContainer& getProcessors() { return processObjectPlugins_; }
		
	private:
		//map<PluginTagSet, string> processPluginData_( const map<string, string>& nameTagPairs, const PluginCommon* plugin );
		vector<PluginTaggingProcessed> processPluginData_( const PluginReply& pluginReply, const PluginCommon* plugin );
		bool ignoreTag_( string& name, string& tag );
		bool turnPluginConsoleOutputOff_();
		
	private:
		ProcessObjectPluginsContainer processObjectPlugins_;
		static string PLUGIN_OUTPUT_PARAMETER_;
		
	};
}

#endif
