/*
 *  Plugin.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 26.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_PLUGIN_COMMON_
#define ObjectCube_PLUGIN_COMMON_

#include <string>
#include <vector>

#include "PluginTagSet.h"
#include "../LayerShared/Exception.h"

using namespace std;

namespace ObjectCube
{
	
	class PluginCommon 
	{
	public:
		
		PluginCommon();
		virtual ~PluginCommon();
		
		//Get
		int getId() const			{ return id_; }
		string getName() const		{ return name_; }
		string getDescription() const { return description_; }
		vector<PluginTagSet> getPluginTagSets() const { return pluginTagSets_; }
		
		PluginTagSet getPluginTagSet( const string& name ) const
		{
			for( vector<PluginTagSet>::const_iterator itr = pluginTagSets_.begin(); itr != pluginTagSets_.end(); ++itr)
			{
				if( (*itr).getName() == name )
				{
					return *itr;
				}
			}
			throw Exception( "PluginCommon::getPluginTagSet", "Tag set not found!", name );
		}
		
		
	protected:
		//Set
		void setId_( int id) { id_ = id; }
		void setName_( const string& name) { name_ = name; }
		void setDescription_( const string& description ) { description_ = description; }
		void setPluginTagSets_( const vector<PluginTagSet>& pluginTagSets ) { pluginTagSets_ = pluginTagSets; }
		
	private:
		void init_();
		virtual void makeAbstract() = 0;

	private:
		int id_;
		string name_;
		string description_;
		vector<PluginTagSet> pluginTagSets_;
		
		friend class Hub;
		
	};
}

#endif