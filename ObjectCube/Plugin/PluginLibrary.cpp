/*
 *  PluginLibrary.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 14.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "PluginLibrary.h"

#include <dlfcn.h>
#include <sstream>
#include <iostream>

#include "PluginServer.h"
#include "PluginObject.h"
#include "../LayerShared/Exception.h"
#include "../LayerShared/DebugInfo.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

PluginLibrary::PluginLibrary( const string& filename )
:	libraryReferenceCount_( 0 ),
	getPluginInterfaceVersion_( 0 ),
	registerPlugin_( 0 ),
	libraryHandle_( 0 )
{
	libraryHandle_ = dlopen( filename.data(), RTLD_NOW | RTLD_GLOBAL );
	if( !libraryHandle_ )
	{
		std::cout << "Filename: " << filename << std::endl;
		ostringstream stringStream;
		stringStream << "Failure to open plugin library, error: " << dlerror();
		throw Exception("PluginLibrary::PluginLibrary", stringStream.str(), filename);
	}
	
	try
	{
		void* dlsymReturnValue = dlsym( libraryHandle_, "getPluginInterfaceVersion" );
		if( dlsymReturnValue == 0 )
		{
			throw Exception("PluginLibrary::PluginLibrary", "getPluginInterfaceVersion function was not found in library");
		}
		getPluginInterfaceVersion_ = reinterpret_cast<fpGetPluginInterfaceVersion *>( dlsymReturnValue );
		if( !getPluginInterfaceVersion_ )
		{
			ostringstream stringStream;
			stringStream << "Failure to retrieve symbol: getPluginInterfaceVersion, error: " << dlerror();
			throw Exception("PluginLibrary::PluginLibrary", stringStream.str(), filename);
		}
		
		void* dlsymReturnValueRegister = dlsym( libraryHandle_, "registerPlugin" );
		if( dlsymReturnValueRegister == 0 )
		{
			throw Exception("PluginLibrary::PluginLibrary", "registerPlugin function was not found in library");
		}
		registerPlugin_ = reinterpret_cast<fpRegisterPlugin *>( dlsymReturnValueRegister );
		if( !registerPlugin_ )
		{
			ostringstream stringStream;
			stringStream << "Failure to retrieve symbol: registerPlugin, error: " << dlerror();
			throw Exception("PluginLibrary::PluginLibrary", stringStream.str(), filename);
		}
		
		//Interface version check
		if( getPluginInterfaceVersion_() != PLUGIN_INTERFACE_VERSION )  //Do we need exact?
		{
			stringstream stringStream;
			stringStream << "Plugin library interface version for plugin " << filename << " is out of date.  Current version: " << PLUGIN_INTERFACE_VERSION << ".  Plugin version: " << getPluginInterfaceVersion_();
			throw Exception( "PluginLibrary::PluginLibrary", stringStream.str() );
		}
	}
	catch(...)
	{
		DebugInfo::getDebugInfo()->output( "PluginLibrary", "constructor", "catch(...) when trying to load library" );
		dlclose( libraryHandle_ );
		throw;
	}
	
	libraryReferenceCount_ = new int(1);
}
//____________________________________________________________________________________________________________________________________________________________________________________

PluginLibrary::PluginLibrary( const PluginLibrary& plugin )
:	libraryReferenceCount_( plugin.libraryReferenceCount_ ),
	getPluginInterfaceVersion_( plugin.getPluginInterfaceVersion_ ),
	registerPlugin_( plugin.registerPlugin_ ),
	libraryHandle_( plugin.libraryHandle_ )
{
	++*libraryReferenceCount_;  //increase the reference count
}
//____________________________________________________________________________________________________________________________________________________________________________________

PluginLibrary::~PluginLibrary()
{
	if( libraryReferenceCount_ == 0 ) //Never initialized
	{
		return;
	}
	if( !--*libraryReferenceCount_ )  //Unload library if there are no more references
	{
		delete libraryReferenceCount_;
		dlclose( libraryHandle_ );
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________

PluginLibrary& PluginLibrary::operator=( const PluginLibrary& plugin )
{
	libraryReferenceCount_ = plugin.libraryReferenceCount_;
	getPluginInterfaceVersion_ = plugin.getPluginInterfaceVersion_;
	registerPlugin_ = plugin.registerPlugin_;
	libraryHandle_ = plugin.libraryHandle_;
	
	++*libraryReferenceCount_;

	return *this;
}
//____________________________________________________________________________________________________________________________________________________________________________________

double PluginLibrary::getPluginInterfaceVersion() const
{
	return getPluginInterfaceVersion_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void PluginLibrary::registerPlugin( const int id, PluginServer& pluginServer )
{
	return registerPlugin_( id, pluginServer );
}
//____________________________________________________________________________________________________________________________________________________________________________________

