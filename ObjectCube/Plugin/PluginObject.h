/*
 *  PluginObject.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 14.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_PLUGIN_OBJECT_
#define ObjectCube_PLUGIN_OBJECT_

#include <string>
#include <memory>
#include <cstring>

using namespace std;

namespace ObjectCube
{
	class PluginObject
	{
	public:
		PluginObject( int id, const string& name, char* data, long dataSize );
		PluginObject( const PluginObject& object );
		PluginObject& operator=( const PluginObject& object );
		
		~PluginObject();
		
		//Get/Set
		int getId() const { return id_; }
		string getName() const { return name_; }
		char* getBinaryData() const { return binaryData_;} 
		long getDataSizeInBytes() const { return dataSize_; }
	
	private:
		void cleanup_();
		void copyValues_( const PluginObject& object );
		
	private:
		int id_;
		string name_;
		char* binaryData_;
		long dataSize_; // size in bytes
		
		
	};
}

#endif
