/*
 *  PluginTagSetConverter.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 26.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "PluginTagSetConverter.h"

#include "../DataAccess/Root/PluginTagSetDataAccess.h"
#include "../DataAccess/Factories/PluginTagSetDataAccessFactory.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

PluginTagSet PluginTagSetConverter::dataAccessToLogic( const PluginTagSetDataAccess* pluginTagSetDA )
{
	PluginTagSet pluginTagSet;
	
	pluginTagSet.setId_( pluginTagSetDA->getId() );
	pluginTagSet.setTagSetTypeId_( pluginTagSetDA->getTagSetTypeId() );
	pluginTagSet.setTagTypeId_( pluginTagSetDA->getTagTypeId() );
	pluginTagSet.setName_( pluginTagSetDA->getName() );
	pluginTagSet.setTagSetName_( pluginTagSetDA->getTagSetName() );
	pluginTagSet.setTagSetId_( pluginTagSetDA->getTagSetId() );
	pluginTagSet.setPluginId_( pluginTagSetDA->getPluginId() );
	
	return pluginTagSet;
}
//____________________________________________________________________________________________________________________________________________________________________________________

unique_ptr<PluginTagSetDataAccess> PluginTagSetConverter::logicToDataAccess( const PluginTagSet& pluginTagSet )
{
	unique_ptr<PluginTagSetDataAccess> pluginTagSetDA( PluginTagSetDataAccessFactory::create() );
	
	pluginTagSetDA->setId( pluginTagSet.getId() );
	pluginTagSetDA->setTagSetTypeId( pluginTagSet.getTagSetTypeId() );
	pluginTagSetDA->setTagTypeId( pluginTagSet.getTagTypeId() );
	pluginTagSetDA->setName( pluginTagSet.getName() );
	pluginTagSetDA->setTagSetName( pluginTagSet.getTagSetName() );
	pluginTagSetDA->setTagSetId( pluginTagSet.getTagSetId() );
	pluginTagSetDA->setPluginId( pluginTagSet.getPluginId_() );
	
	return pluginTagSetDA;
}
//____________________________________________________________________________________________________________________________________________________________________________________

vector<PluginTagSet> PluginTagSetConverter::dataAccessToLogic( const vector<PluginTagSetDataAccess*>& pluginTagSetsDA )
{
	vector<PluginTagSet> pluginTagSets;
	for( vector<PluginTagSetDataAccess*>::const_iterator itr = pluginTagSetsDA.begin(); itr != pluginTagSetsDA.end(); ++itr )
	{
		pluginTagSets.push_back( PluginTagSetConverter::dataAccessToLogic( *itr ) );
	}
	return pluginTagSets;	
}
//____________________________________________________________________________________________________________________________________________________________________________________

vector<PluginTagSetDataAccess*> PluginTagSetConverter::logicToDataAccess( const vector<PluginTagSet>& pluginTagSets )
{
	vector<PluginTagSetDataAccess*> pluginTagSetsDA;
	for( vector<PluginTagSet>::const_iterator itr = pluginTagSets.begin(); itr != pluginTagSets.end(); itr++ )
	{
		pluginTagSetsDA.push_back( PluginTagSetConverter::logicToDataAccess( *itr ).release() );
	}
	return pluginTagSetsDA;
}
//____________________________________________________________________________________________________________________________________________________________________________________

