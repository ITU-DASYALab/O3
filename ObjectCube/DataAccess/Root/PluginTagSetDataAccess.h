/*
 *  PluginTagSetDataAccess.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 25.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_PLUGIN_TAG_SET_DATA_ACCESS_
#define ObjectCube_PLUGIN_TAG_SET_DATA_ACCESS_

#include <string>
#include <vector>

using namespace std;

namespace ObjectCube
{
	
	class PluginTagSetDataAccess
	{
	public:
		PluginTagSetDataAccess();
		virtual ~PluginTagSetDataAccess() {;}
		
		virtual void updateTagSetId( int id, int tagSetId ) = 0;
		
		//Get
		int getId() const			{ return id_; }
		int getPluginId() const		{ return pluginId_; }
		int getTagSetTypeId() const { return tagSetTypeId_; }
		int getTagTypeId() const	{ return tagTypeId_; }
		string getName() const		{ return name_; }
		string getTagSetName() const { return tagSetName_; }
		int getTagSetId() const		{ return tagSetId_; }
		
		//Set
		void setId( int id) { id_ = id; }
		void setPluginId( int pluginId ) { pluginId_ = pluginId; }
		void setTagSetTypeId( int tagSetTypeId ) { tagSetTypeId_ = tagSetTypeId; }
		void setTagTypeId( int tagTypeId ) { tagTypeId_ = tagTypeId; }
		void setName( const string& name) { name_ = name; }
		void setTagSetName( const string& tagSetName ) { tagSetName_ = tagSetName; }
		void setTagSetId( int tagSetId ) { tagSetId_ = tagSetId; }
		
	private:
		int id_;
		int pluginId_;
		int tagSetTypeId_;
		int tagTypeId_;
		string name_;
		string tagSetName_;
		int tagSetId_;
	};
	
}

#endif