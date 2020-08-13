/*
 *  PluginServer.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 15.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include <memory>
#include <iostream>

#include "PluginServer.h"

#include "../DataAccess/Root/PluginDataAccess.h"
#include "../DataAccess/Factories/PluginDataAccessFactory.h"
#include "../LayerShared/MemoryManagement.h"
#include "PluginCommon.h"
#include "../LayerShared/DebugInfo.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

PluginServer::PluginServer()
{
	init_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void PluginServer::init_()
{
	DebugInfo::getDebugInfo()->output("PluginServer", "init_", "1" );
	
	unique_ptr<PluginDataAccess> dataAccess( PluginDataAccessFactory::create() );
	std::cout << "PluginServer::init_() 1" << std::endl;
	vector<PluginDataAccess*> plugins = dataAccess->fetchAll();  //Using the data access class here is dirty, but we have no implementation classes for abstract class ProcessObjectPlugin
	
	DebugInfo::getDebugInfo()->output("PluginServer", "init_", "2" );
	std::cout << "PluginServer::init_() 2" << std::endl;
	vector<PluginDataAccess*>::iterator itr;
	std::cout << "PluginServer::init_() 3" << std::endl;
	for( itr = plugins.begin(); itr != plugins.end(); itr++ )
	{
		std::cout << "PluginServer::init_() 3.1" << std::endl;
		DebugInfo::getDebugInfo()->output("PluginServer", "init_", "3" );
		loadPlugin_( (*itr)->getId(), (*itr)->getName() );
	}
	std::cout << "PluginServer::init_() 4" << std::endl;
	clearAndDestroy( plugins );
	std::cout << "PluginServer::init_() 5 x" << std::endl;
	DebugInfo::getDebugInfo()->output("PluginServer", "init_", "4" );
	processObjectServer_.loadPluginInfo();
	std::cout << "PluginServer::init_() 6" << std::endl;
	DebugInfo::getDebugInfo()->output("PluginServer", "init_", "Done" );
}
//____________________________________________________________________________________________________________________________________________________________________________________
/*
void PluginServer::addProcessObjectPlugin( PluginCommon* plugin ) 
{ 
	getProcessObjectServer().addObjectProcessor( plugin ); 
}
 */
//____________________________________________________________________________________________________________________________________________________________________________________

void PluginServer::loadPlugin_( const int id, const string& libraryName ) 
{
	std::cout << "Start PluginServer::loadPlugin_" << std::endl;
	if( plugins_.find( libraryName ) == plugins_.end() )
	{
		std::cout << "PluginServer::loadPlugin_ 1" << std::endl;
		PluginLibrary library( libraryName );
		std::cout << "PluginServer::loadPlugin_ 1.1" << std::endl;
		std::cout << "PluginServer::loadPlugin_ 2" << std::endl;
		library.registerPlugin( id, *this );
		std::cout << "PluginServer::loadPlugin_ 3" << std::endl;
		plugins_.insert( map<string, PluginLibrary>::value_type( libraryName, library ) );
		PluginCommon* processor = processObjectServer_.getProcessors()[0];
	}
	std::cout << "End PluginServer::loadPlugin_" << std::endl;
}
//____________________________________________________________________________________________________________________________________________________________________________________

