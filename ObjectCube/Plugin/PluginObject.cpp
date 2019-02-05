/*
 *  PluginObject.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 11.8.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */


#include "PluginObject.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

PluginObject::PluginObject( int id, const string& name, char* data, long dataSize ) 
{ 
	id_ = id; 
	name_ = name; 
	binaryData_ = data; 
	dataSize_ = dataSize; 
} 
//____________________________________________________________________________________________________________________________________________________________________________________

PluginObject::PluginObject( const PluginObject& object )
{
	copyValues_( object );
}
//____________________________________________________________________________________________________________________________________________________________________________________

PluginObject& PluginObject::operator=( const PluginObject& object )
{
	cleanup_();
	copyValues_( object );

	return *this;
}
//____________________________________________________________________________________________________________________________________________________________________________________

PluginObject::~PluginObject() 
{
	cleanup_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void PluginObject::cleanup_()
{
	if( binaryData_ != 0 )
	{
		delete [] (char*) binaryData_; 
	}
	binaryData_ = 0;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void PluginObject::copyValues_( const PluginObject& object )
{
	id_ = object.id_;
	name_ = object.name_;
	dataSize_ = object.dataSize_;
	
	if( dataSize_ > 0 )
	{
		binaryData_ = new char[ dataSize_ ];
		memcpy( binaryData_, object.binaryData_, dataSize_ );	
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________


