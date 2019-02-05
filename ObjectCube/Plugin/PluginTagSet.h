/*
 *  PluginTagSet.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 25.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_PLUGIN_TAG_SET_
#define ObjectCube_PLUGIN_TAG_SET_

#include <string>

using namespace std;

namespace ObjectCube
{
	
	class PluginTagSet
	{
	public:
		
		void updateTagSetId( int tagSetId );
		
		//Get
		int getId() const			{ return id_; }
		int getTagSetTypeId() const { return tagSetTypeId_; }
		int getTagTypeId() const	{ return tagTypeId_; }
		string getName() const		{ return name_; }
		string getTagSetName() const { return tagSetName_; }
		int getTagSetId() const		{ return tagSetId_; }
		
	protected:
		//Set
		void setId_( int id) { id_ = id; }
		void setTagSetTypeId_( int tagSetTypeId ) { tagSetTypeId_ = tagSetTypeId; }
		void setTagTypeId_( int tagTypeId ) { tagTypeId_ = tagTypeId; }
		void setName_( const string& name) { name_ = name; }
		void setTagSetName_( const string& tagSetName ) { tagSetName_ = tagSetName; }
		void setTagSetId_( int tagSetId ) { tagSetId_ = tagSetId; }
		
	private:
		int getPluginId_() const { return pluginId_; }
		void setPluginId_( int pluginId ) { pluginId_ = pluginId; }
		
	private:
		int id_;
		int tagSetTypeId_;
		int tagTypeId_;
		string name_;
		string tagSetName_;
		int tagSetId_;
		int pluginId_;
		
	private:
		friend class PluginTagSetConverter;
		
	public:
		bool operator < ( const PluginTagSet& b ) const;
		
	};
	
	
}

#endif