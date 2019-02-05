/*
 *  ProcessObjectServer.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 15.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "ProcessObjectServer.h"

#include <iostream>
#include <algorithm>
#include <typeinfo>
#include <sstream>

#include "PluginObject.h"
#include "ProcessObjectPlugin.h"
#include "PluginCommon.h"
#include "Plugin.h"
#include "../LayerShared/Exception.h"
#include "../LayerShared/MemoryManagement.h"
#include "../LayerShared/DebugInfo.h"
#include "../LayerShared/Parameters.h"
#include "../LayerShared/SharedDefinitions.h"
#include "../LayerShared/StringSupport.h"

using namespace ObjectCube;
using namespace std;

//____________________________________________________________________________________________________________________________________________________________________________________

string ProcessObjectServer::PLUGIN_OUTPUT_PARAMETER_ = "pluginOutput";

//____________________________________________________________________________________________________________________________________________________________________________________

ProcessObjectServer::~ProcessObjectServer()
{
	clearAndDestroy( processObjectPlugins_ );
}
//____________________________________________________________________________________________________________________________________________________________________________________
/*
void ProcessObjectServer::addObjectProcessor( PluginCommon* processor )
{ 
	if( processor == 0 )
	{
		cout << "ProcessObjectServer::addObjectProcessor plugin == 0, entries: " << processObjectPlugins_.size() << endl;	
	throw Exception( "ProcessObjectServer::addObjectProcessor", "Plugin == 0." );
	}
	cerr << "ProcessObjectServer::addObjectProcessor  id: " << processor->getId() << " name: " << processor->getName() << endl;
	processObjectPlugins_.push_back( processor ); 
}
 */
//____________________________________________________________________________________________________________________________________________________________________________________

void ProcessObjectServer::loadPluginInfo()
{
	DebugInfo::getDebugInfo()->output("ProcessObjectServer", "loadPluginInfo", "" );
	cout << "Start ProcessObjectServer::loadPluginInfo()" << endl;
	
	for( ProcessObjectPluginsContainer::iterator itr = processObjectPlugins_.begin(); itr != processObjectPlugins_.end(); ++itr )
	{
		cout << "ProcessObjectServer::loadPluginInfo() 1" << endl;	
		*(*itr) = Plugin::fetch( (*itr)->getId() );
	}
	cout << "End ProcessObjectServer::loadPluginInfo()" << endl;
	DebugInfo::getDebugInfo()->output("ProcessObjectServer", "loadPluginInfo", "Done" );
}
//____________________________________________________________________________________________________________________________________________________________________________________

vector<PluginTaggingProcessed> ProcessObjectServer::process( const PluginObject& object )
{
	return process( object, INVALID_VALUE );
}
//____________________________________________________________________________________________________________________________________________________________________________________

vector<PluginTaggingProcessed> ProcessObjectServer::process( const PluginObject& object, int pluginId )
{	
	vector<BoundingBox> boundingBoxes;
	return process( object, boundingBoxes, pluginId );
}
//____________________________________________________________________________________________________________________________________________________________________________________

vector<PluginTaggingProcessed> ProcessObjectServer::process( const PluginObject& object, const vector<BoundingBox>& boundingBoxes, int pluginId )
{
	DebugInfo::getDebugInfo()->pushTimer( "ProcessObjectServer", "procesess(id)",  "(plugin time)" );
	
	vector<PluginTaggingProcessed> potentialTags;
	bool processedByCorrectPlugin = false;
    
    for( ProcessObjectPluginsContainer::iterator pluginsItr = processObjectPlugins_.begin(); pluginsItr != processObjectPlugins_.end(); ++pluginsItr )
	{
		ProcessObjectPlugin* poPlugin = static_cast<ProcessObjectPlugin*>( *pluginsItr );
		if( poPlugin == 0 )
		{
			throw Exception( "ProcessObjectServer::process( object, id )", "Plugin == 0." );
		}
		if( poPlugin->getId() != pluginId && pluginId != INVALID_VALUE )
		{
			continue;
		}
		
		processedByCorrectPlugin = true;
		
		PluginReply pluginReply;
        try 
        {
            if( boundingBoxes.size() )
            {
                pluginReply = poPlugin->process( object, boundingBoxes );
            }
            else
            {
                pluginReply = poPlugin->process( object );
            }
        } 
        catch( exception& e )
        {
            stringstream sStream;
            sStream << "Error in plugin: " << poPlugin->getName() << " : " << e.what();            
            DebugInfo::getDebugInfo()->output("ProcessObjectServer", "process", sStream.str() );
            //Plugin errors are not propagated
        }
        catch (...) 
        {
            stringstream sStream;
            sStream << "Unknown error in plugin: " << poPlugin->getName();            
            DebugInfo::getDebugInfo()->output("ProcessObjectServer", "process", sStream.str() );
            //Plugin errors are not propagated
        }
		
		vector<PluginTaggingProcessed> tempPotentialTags = processPluginData_( pluginReply, *pluginsItr);	
		potentialTags.insert( potentialTags.begin(), tempPotentialTags.begin(), tempPotentialTags.end() );
	}
	DebugInfo::getDebugInfo()->popTimer();
	
	if( !processedByCorrectPlugin && pluginId != INVALID_VALUE )  //There not being a plugin is not an error for process-by-all-plugins
	{
		throw Exception( "ProcessObjectServer::process( object, id )", "Plugin with input id not found.", pluginId);
	}
	return potentialTags;
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

vector<PluginTaggingProcessed> ProcessObjectServer::processPluginData_( const PluginReply& pluginReply, const PluginCommon* plugin )
{
	vector<PluginTaggingProcessed> processedTaggings;
	
	vector<PluginTagging> taggings = pluginReply.getTaggings();
	for( vector<PluginTagging>::iterator itr = taggings.begin(); itr != taggings.end(); ++itr )
	{
		try 
		{
			string tagSetName = (*itr).getTagSetName();
			string value = (*itr).getTag();
			if( ignoreTag_( tagSetName, value ) )
			{
				continue;
			}
			
			PluginTagSet pluginTagSet = plugin->getPluginTagSet( tagSetName );
			PluginTaggingProcessed tagging( pluginReply.getObjectId(), pluginTagSet.getTagSetId(), *itr );
			processedTaggings.push_back( tagging );
		}
		catch( Exception e ) 
		{
			//This should end up in a log
			//cerr << "Plugin tag-set not found for plugin: " << (*itr)->getName() << " with tag-set name: " << ntItr->first << endl; 
		}
	}
	return processedTaggings;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void ProcessObjectServer::confirmTagging( int objectId, const string& tagSetName,
										  const BoundingBox& boundingBox, const string& tag )
{
	for( ProcessObjectPluginsContainer::iterator pluginsItr = processObjectPlugins_.begin(); pluginsItr != processObjectPlugins_.end(); ++pluginsItr )
	{
		ProcessObjectPlugin* poPlugin = static_cast<ProcessObjectPlugin*>( *pluginsItr );

		if( poPlugin == 0 )
		{
			throw Exception( "ProcessObjectServer::process( object, id )", "Plugin == 0." );
		}
		poPlugin->confirmTagging( objectId, tagSetName, boundingBox, tag ); 
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________

bool ProcessObjectServer::ignoreTag_( string& name, string& tag )
{
	/*
	Laga þennan kóða þannig að ekkert sem er ekki basic ascii fari í gegn
	hreinsa eyður framan og aftan af, virðist ekki virka eins og það er 
	einungis skila þeim hluta strengins sem er ascii (t.d. engir séríslenskir stafir)
	
	gera þetta fyrir bæði tag-set name og value
	*/
	//We ignore items where either the key or the value is missing, plugins will be imperfect.
	
	StringSupport::trim( name ); //Remove leading and trailing whitespaces
	StringSupport::trim( tag );
	
	name = StringSupport::toSimpleAscii( name );
	tag = StringSupport::toSimpleAscii( tag );
	
	if( name.length() == 0 || tag.length() == 0 )
	{
		return true;
	}
	return false;
}
//____________________________________________________________________________________________________________________________________________________________________________________

bool ProcessObjectServer::turnPluginConsoleOutputOff_()
{
	if( !Parameters::getParameters()->contains( PLUGIN_OUTPUT_PARAMETER_ ) )
	{
		return false;
	}
	if( Parameters::getParameters()->getValueAsInt( PLUGIN_OUTPUT_PARAMETER_ ) != 0 )
	{
		return false;
	}
	return true;
}
//____________________________________________________________________________________________________________________________________________________________________________________

