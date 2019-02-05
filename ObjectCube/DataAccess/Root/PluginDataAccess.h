/*
 *  PluginDataAccess.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 25.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_PLUGIN_DATA_ACCESS_
#define ObjectCube_PLUGIN_DATA_ACCESS_

#include <vector>
#include <string>

using namespace std;

namespace ObjectCube
{
	class PluginTagSetDataAccess;
	
	class PluginDataAccess
	{
	public:
		PluginDataAccess();
		virtual ~PluginDataAccess();
		
		virtual PluginDataAccess* fetch( int id ) = 0;
		virtual vector<PluginDataAccess*> fetchAll() = 0;
				
		int getId() const { return id_; }  
		string getName() const { return name_; }
		string getDescription() const { return description_; }
		vector<PluginTagSetDataAccess*> getPluginTagSets() const { return pluginTagSets_; }
		
		void setId( int id ) { id_ = id; }
		void setName( const string& name ) { name_ = name; }
		void setDescription( const string& description ) { description_ = description; }
		void setPluginTagSets( const vector<PluginTagSetDataAccess*>& pluginTagSets ) { pluginTagSets_ = pluginTagSets; }
		
	protected:
		int id_;
		string name_;
		string description_;
		vector<PluginTagSetDataAccess*> pluginTagSets_;
		
	private:
		virtual vector<PluginTagSetDataAccess*> fetchPluginTagSets_( int pluginId ) = 0;
		
	};
	
}

#endif