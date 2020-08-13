/*
 *  Framework.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 25.10.2009.
 *  Copyright 2009 Reykjavik University. All rights reserved.
 *
 */ 

#include <memory>
#include <sstream>
#include <fstream>
#include <iostream>

#include "Hub.h"


#include <string>


#include "Tag/Tag.h"
#include "TagSet/TagSet.h"
#include "TagSet/TagSetFactory.h"
#include "Tag/TagFactory.h"
#include "Object.h"
#include "ObjectTag.h"
#include "Filters/Filter.h"
#include "Tag/AlphanumericalTag.h"
#include "Hierarchy/Dimension.h"
#include "Hierarchy/PersistentDimension.h"
#include "Hierarchy/VirtualDimension.h"

#include "DataAccess/Root/HubDataAccess.h"
#include "DataAccess/Root/FilterDataAccess.h"
#include "DataAccess/Root/ObjectDataAccess.h"
#include "DataAccess/Root/StateObjectDataAccess.h"
#include "DataAccess/Root/SearchDataAccess.h"

#include "DataAccess/Factories/HubDataAccessFactory.h"
#include "DataAccess/Factories/ObjectDataAccessFactory.h"
#include "DataAccess/Factories/SearchDataAccessFactory.h"

#include "Converters/ObjectConverter.h"
#include "Converters/TagSetConverter.h"
#include "LayerShared/SharedDefinitions.h"
#include "Converters/StateObjectConverter.h"
#include "Converters/FilterConverter.h"


#include "LayerShared/Exception.h"

#include "Plugin/PluginCommon.h"
#include "Plugin/PluginTagSet.h"
#include "Plugin/PluginObject.h"
#include "Plugin/PluginServer.h"

#include "LayerShared/MemoryManagement.h"
#include "LayerShared/Parameters.h"
#include "LayerShared/LanguageCommon.h"
#include "LayerShared/DebugInfo.h"

using namespace ObjectCube;
using namespace std;

std::shared_ptr<Hub> Hub::instance_;

//____________________________________________________________________________________________________________________________________________________________________________________

Hub::Hub()
{
	tagSetDataAccessType_ = Hub::getDataAccessType();
}
//____________________________________________________________________________________________________________________________________________________________________________________

Hub::~Hub()
{
	cleanup_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

Hub* Hub::getHub()
{
	if( instance_ == 0 )
	{
		instance_.reset( new Hub() );
		//Override default values is supplied
		if( Parameters::getParameters()->contains( getDataAccessTypeParameterName() ) )
		{
			HubCommon::setDataAccessType( Parameters::getParameters()->getValueAsInt( getDataAccessTypeParameterName() ) );
		}
		if( Parameters::getParameters()->contains( LanguageCommon::getLanguageIdParameterName() ) )
		{
			setLanguageId( Parameters::getParameters()->getValueAsInt( LanguageCommon::getLanguageIdParameterName() ) );
		}
		init_();
	}
	if( Hub::getDataAccessType() != instance_->tagSetDataAccessType_ )
	{
		init_();
	}
	return instance_.get();
}
//____________________________________________________________________________________________________________________________________________________________________________________ 

void Hub::init_()
{
	instance_->tagSetDataAccessType_ = Hub::getDataAccessType();
	DebugInfo::getDebugInfo()->pushTimer( "Hub", "init_" );
	std::cout << "Hub::init_() -> instance_->loadPlugins_()" << std::endl;
	instance_->loadPlugins_();
	std::cout << "Hub::init_() -> instance_->loadPlugins_()" << std::endl;
	instance_->createMissingPluginTagSets_();
	std::cout << "Hub::init_() -> instance_->createMissingPluginTagSets_()" << std::endl;
	instance_->loadTagSets_();
	DebugInfo::getDebugInfo()->popTimer();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void Hub::destroy()
{
	instance_.reset();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void Hub::cleanup_()
{
	//TagSet::allTags_.clear();
	/*
	for( map<int, Tag*>::iterator itr = TagSet::allTags_.begin(); itr != TagSet::allTags_.end(); ++itr )
	{
		itr->second = 0; //This has to be set to 0 to stop the map from interfering with memory management
	}
	 */
	DebugInfo::getDebugInfo()->output( "Hub", "cleanup_", "Starting" );
	
	tagSets_.clear();
	TagSet::allTags_.clear();
	
	unique_ptr<HubDataAccess> dataAccess( HubDataAccessFactory::create() );
	dataAccess->disconnect();

	DebugInfo::getDebugInfo()->output( "Hub", "cleanup_", "Done" );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void Hub::loadTagSets_()
{
	DebugInfo::getDebugInfo()->output( "Hub", "loadTagSets_", "Loading tag-sets ..." );
	DebugInfo::getDebugInfo()->pushTimer( "Hub", "loadTagSets_" );
	cleanup_();
	
	DebugInfo::getDebugInfo()->pushTimer( "Hub", "loadTagSets_", "getting a list of tag-sets" );
	
	DebugInfo::getDebugInfo()->output( "Hub", "loadTagSets_", "getting a list of tag-sets" );
	unique_ptr<HubDataAccess> dataAccess( HubDataAccessFactory::create() );
	vector<TagSetDataAccess*> tagSetsDA = dataAccess->getTagSets();
DebugInfo::getDebugInfo()->output( "Hub", "loadTagSets_", "1" );
	tagSets_ = TagSetConverter::dataAccessToLogic( tagSetsDA );  //Þetta fall sækir einungis grunn upplýsingar, restin kemur úr fetch föllunum sem hver tegund yfirskrifar
DebugInfo::getDebugInfo()->output( "Hub", "loadTagSets_", "2" );
	clearAndDestroy( tagSetsDA );
	DebugInfo::getDebugInfo()->output( "Hub", "loadTagSets_", "3" );
	
	DebugInfo::getDebugInfo()->popTimer();
	DebugInfo::getDebugInfo()->output("Hub", "loadTagSets_", "no. tag-sets", tagSets_.size() );
	//Fetching the details
	DebugInfo::getDebugInfo()->pushTimer( "Hub", "loadTagSets_", "fetching the details (tags)" );
	DebugInfo::getDebugInfo()->output( "Hub", "loadTagSets_", "fetching details" );

	for( vector<std::shared_ptr<TagSet> >::iterator itr = tagSets_.begin(); itr != tagSets_.end(); ++itr)
	{
		(*itr)->fetch_( (*itr)->getId() );
	}
	DebugInfo::getDebugInfo()->popTimer();
	
	DebugInfo::getDebugInfo()->popTimer();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void Hub::loadPlugins_()
{
	DebugInfo::getDebugInfo()->output( "Hub", "loadPlugins_", "Loading plugins ..." );
	DebugInfo::getDebugInfo()->pushTimer( "Hub", "loadPlugins_" );
	pluginServer_.reset( new PluginServer() );
	DebugInfo::getDebugInfo()->popTimer();
}
//____________________________________________________________________________________________________________________________________________________________________________________ 

void Hub::createMissingPluginTagSets_()
{
	DebugInfo::getDebugInfo()->output( "Hub", "createMissingPluginTagSets_", "Creating missing plugin tag-sets ..." );
	DebugInfo::getDebugInfo()->pushTimer( "Hub", "createMissingPluginTagSets_" );
	
	ProcessObjectServer::ProcessObjectPluginsContainer& processObjectPlugins = pluginServer_->getProcessObjectServer().getProcessors();
	
	DebugInfo::getDebugInfo()->output( "Hub", "createMissingPluginTagSets_", "Got object plugins" );
	
	for( ProcessObjectServer::ProcessObjectPluginsContainer::iterator itr = processObjectPlugins.begin(); itr != processObjectPlugins.end(); ++itr )
	{
		DebugInfo::getDebugInfo()->output( "Hub", "createMissingPluginTagSets_", "In outer loop" );
		
		vector<PluginTagSet> pluginTagSets = (*itr)->getPluginTagSets();
		for( vector<PluginTagSet>::iterator tsItr = pluginTagSets.begin(); tsItr != pluginTagSets.end(); ++tsItr )
		{
			DebugInfo::getDebugInfo()->output( "Hub", "createMissingPluginTagSets_", "In inner loop" );
			if( (*tsItr).getTagSetId() == INVALID_VALUE )
			{
				(*tsItr).updateTagSetId( createPluginTagSet_( (*tsItr).getTagSetTypeId(), (*tsItr).getTagSetName() ) );
			}
		}
		(*itr)->setPluginTagSets_( pluginTagSets );
	}
	DebugInfo::getDebugInfo()->output( "Hub", "createMissingPluginTagSets_", "Done" );
	
	DebugInfo::getDebugInfo()->popTimer();
}
//____________________________________________________________________________________________________________________________________________________________________________________ 

int Hub::createPluginTagSet_( int tagSetType, const string& name )
{
	unique_ptr<TagSet> tagSet( TagSetFactory::create( tagSetType ) );
	tagSet->setName( name );
	tagSet->setDescription( "Automatically created tag-set, for a plugin." );
	tagSet->setAccessId_( TagSetCommon::SYSTEM );
	addTagSet( tagSet.get() );
	return tagSet->getId();
}
//____________________________________________________________________________________________________________________________________________________________________________________ 

TagSet* Hub::addTagSet( TagSet* /*const*/ tagSet )
{
	if( tagSet->getId() == INVALID_VALUE )
	{
		return tagSet->createImp_();
	}
	
	//We copy the TagSet to limit user action on the framework (and to simplify user memory management)
	std::shared_ptr<TagSet> tagSetCopy( TagSetFactory::create( tagSet->getTypeId() ) );
	*(tagSetCopy.get()) = *tagSet;
	tagSets_.push_back( tagSetCopy );
	return tagSetCopy.get();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void Hub::removeTagSet( TagSet* /*const*/ tagSet )
{
	for( vector<std::shared_ptr<TagSet> >::iterator itr = tagSets_.begin(); itr != tagSets_.end(); ++itr)
	{
		if( (*itr)->getId() == tagSet->getId() )
		{
			tagSets_.erase( itr );
			return;
		}
	}
	stringstream stringStream;
	stringStream << "Framework did not contain tag-set with id: " << tagSet->getId();
	throw Exception( "Hub::removeTagSet", stringStream.str() );		
	
	/*
	vector<TagSet*>::iterator itr = find_if( tagSets_.begin(), tagSets_.end(), dereference( tagSet ) );
	if( itr == tagSets_.end() )
	{
		stringstream stringStream;
		stringStream << "Framework did not contain tag-set with id: " << tagSet->getId();
		throw Exception( "Hub::removeTagSet", stringStream.str() );		
	}
	delete *itr; //All user pointers are now invalid !
	*itr = 0;
	tagSets_.erase( itr );
	 */
}
//____________________________________________________________________________________________________________________________________________________________________________________

void Hub::addObject( Object& object )
{
	/*
	 An uncategorized photo is a photo that has no user added tags.
	 
	 Using dimensions and tags for everything includes Uncategorized photos.  Uncategorized is a dimension that has one tag, uncategorized.  If a photo is added without a tag, uncategorized is added to it.
	 It is removed when a tag is added to the photo.
		Another way of doing this would be to use an outerjoin for photos that have no tags.  That would require special handling and it would not help in filtering only on uncatgorized photos.
	 */
	cout << "Hub::addObject" << endl;
	if( object.getId() == INVALID_VALUE )
	{
		object.create();
		return;
	}
	
	DebugInfo::getDebugInfo()->pushTimer( "Hub", "addObject" );
	
	//Retrieve object data
	unique_ptr<PluginObject> pluginObject( getPluginObject_( object ) );
	
	//Plugin processing
	vector<PluginTaggingProcessed> potentialTags = pluginServer_->getProcessObjectServer().process( *pluginObject );
	tagObject_( potentialTags, object );	
	cout << "Hub::addObject END" << endl;
	DebugInfo::getDebugInfo()->popTimer();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void dummy( int noProcessed )  //Used to call processAllObjects
{
	
}

//____________________________________________________________________________________________________________________________________________________________________________________

int Hub::processAllObjects( int pluginId )
{
	return processAllObjects( pluginId, 100000, dummy ); 
}

//____________________________________________________________________________________________________________________________________________________________________________________

int Hub::processAllObjects( int pluginId, int reportInterval, void (*funcPtr)(int) )
{
	unique_ptr<ObjectDataAccess> dataAccess( ObjectDataAccessFactory::create() );
	vector<ObjectDataAccess*> objectsDA = dataAccess->fetchAllObjects();
	vector<Object> objects = ObjectConverter::dataAccessToLogic( objectsDA );
	
	//Adding object tags
	/*
	vector<Object>::iterator itr = objects.begin();
	for( vector<ObjectDataAccess*>::iterator itrDA = objectsDA.begin(); itrDA != objectsDA.end() && itr != objects.end(); ++itrDA, ++itr )
	{
		if( (*itr).getId() != (*itrDA)->getId() )
		{
			throw Exception("Hub::processAllObjects", "Objects and ObjectsDA were not in synch!" );
		}
		(*itr).setTags_( getTags( (*itrDA)->getTagIds() ) );
	}
	*/
	
	clearAndDestroy( objectsDA );
	
	long noProcessed = 0;
	for( vector<Object>::iterator itr = objects.begin(); itr != objects.end(); ++itr )
	{
		unique_ptr<PluginObject> pluginObject( getPluginObject_( *itr ) );
		//map<PluginTagSet, string> potentialTags = pluginServer_->getProcessObjectServer().process( *pluginObject, pluginId );
		
		vector<PluginTaggingProcessed> potentialTags = pluginServer_->getProcessObjectServer().process( *pluginObject, pluginId );
		
		tagObject_( potentialTags, *itr );	
		++noProcessed;
		if( noProcessed % reportInterval == 0 )
		{
			funcPtr( noProcessed );
		}
	}
	return objects.size();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void Hub::tagObject_(  const vector<PluginTaggingProcessed>& potentialTags, Object& object )
{
	DebugInfo::getDebugInfo()->pushTimer( "Hub", "tagObject_", " (add tags from plugins)" );
	
	for( vector<PluginTaggingProcessed>::const_iterator itr = potentialTags.begin(); itr != potentialTags.end(); ++itr )
	{
		try 
		{
			TagSet* tagSet = getTagSet( itr->getTagSetId() );
			const Tag* tag = tagSet->fetchOrAddTag( itr->getTag() );
			ObjectTag objectTag( const_cast<Tag*>( tag ), itr->getBoundingBox() );
            objectTag.setConfirmed( itr->getConfirmed() ); //Put in constructor
            
			object.addTag( objectTag );
		}
		catch ( Exception e ) 
		{
			DebugInfo::getDebugInfo()->output( "Hub", "tagObject_", &e );
		}
	}
	DebugInfo::getDebugInfo()->popTimer();
}
//____________________________________________________________________________________________________________________________________________________________________________________

PluginObject* Hub::getPluginObject_( const Object& object ) const
{
	DebugInfo::getDebugInfo()->pushTimer( "Hub", "getPluginObject_", "(read object into memory)" );
	
	//ToDo:  Consider writing a FileServer plugin server and a plugin for each type (file, web service, database etc.)

    ifstream file( object.getName().data(), ios::in | ios::binary | ios::ate);
	if(!file.is_open() )
	{
		throw Exception("Hub::getPluginObject_", "Couldn't retrieve object from file", object.getName() );
	}
	
	long size = file.tellg();
	file.seekg (0, std::ios::beg);
	
	unique_ptr<char> data( new char[ size ] );
	file.read( data.get(), size );
	file.close();
	
	DebugInfo::getDebugInfo()->popTimer();
	return new PluginObject( object.getId(), object.getName(), data.release(), size );
}
//____________________________________________________________________________________________________________________________________________________________________________________

//Photo selection

void Hub::addFilter( Filter* /*const*/ filter )
{
	TagSet* tagSet = getTagSet( filter->getTagSetId() );
	tagSet->addFilter_( filter );
}
 
//____________________________________________________________________________________________________________________________________________________________________________________

void Hub::removeAllFilters()
{	
	for( vector<std::shared_ptr<TagSet> >::const_iterator itr = tagSets_.begin(); itr != tagSets_.end(); ++itr)
	{
		(*itr)->removeFilters_();
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________

void Hub::removeFilter( Filter* filter )
{
	TagSet* tagSet = getTagSet( filter->getTagSetId() );
	tagSet->removeFilter_( filter );
}
//____________________________________________________________________________________________________________________________________________________________________________________

const vector<Filter*> Hub::getFilters() const
{
	vector<Filter*> filters;
	for( vector<std::shared_ptr<TagSet> >::const_iterator itr = tagSets_.begin(); itr != tagSets_.end(); ++itr)
	{
		const vector<Filter*> tagSetFilters = (*itr)->getFilters();
		filters.insert( filters.end(), tagSetFilters.begin(), tagSetFilters.end() );
	}
	return filters;
}
//____________________________________________________________________________________________________________________________________________________________________________________

const vector<Filter*> Hub::getFilters( int filterType ) const
{
	vector<Filter*> filters;
	for( vector<std::shared_ptr<TagSet> >::const_iterator itr = tagSets_.begin(); itr != tagSets_.end(); ++itr)
	{
		const vector<Filter*> tagSetFilters = (*itr)->getFilters();
		for( vector<Filter*>::const_iterator fItr = tagSetFilters.begin(); fItr != tagSetFilters.end(); ++fItr )
		{
			if( (*fItr)->getTypeId() == filterType )
			{
				filters.push_back( *fItr );
			}
		}
	}
	return filters;
}
//____________________________________________________________________________________________________________________________________________________________________________________

State Hub::getState()
{

	DebugInfo::getDebugInfo()->pushTimer( "Hub", "getState" );
	
	vector<Filter*> filters = getFilters();
	
	unique_ptr<HubDataAccess> dataAccess( HubDataAccessFactory::create() );
	
	DebugInfo::getDebugInfo()->pushTimer( "Hub", "getState", "data access" );
	vector<FilterDataAccess*> filtersDA = FilterConverter::logicToDataAccess( filters );
	StateDataAccess stateDA = dataAccess->getState( filtersDA );
	clearAndDestroy( filtersDA );
	DebugInfo::getDebugInfo()->popTimer();
	lastGetObjectsQueryAsString_ = dataAccess->getObjectsQueryAsString();
	
	DebugInfo::getDebugInfo()->output( "Hub", "getState", "no. objects", stateDA.getObjects().size() );
	State retState;
	
	DebugInfo::getDebugInfo()->pushTimer( "Hub", "getState", "converting & adding tags" );
	
	//The looped code must perform well!
	vector<StateTag>::iterator tagItr;
	int tagIndex = 0;
	vector<StateObjectDataAccess*>& stateObjectsDA = stateDA.getObjects();
	for( vector<StateObjectDataAccess*>::iterator itr = stateObjectsDA.begin(); itr != stateObjectsDA.end(); ++itr )
	{
		StateObject stateObject = StateObjectConverter::dataAccessToLogic( *itr );
		
		tagIndex = 0;
		for( tagItr = stateObject.tags_.begin(); tagItr != stateObject.tags_.end(); ++tagItr )
		{
			//(*tagItr).setTag_( TagSet::allTags_[ (*itr)->getTags()[ tagIndex ]->getTagId() ].get() );
			(*tagItr).setTag_( TagSet::allTags_[ (*itr)->getTags()[ tagIndex ]->getTagId() ] );
			++tagIndex;
		}
		
		retState.objects_.push_back( stateObject );
	}
	DebugInfo::getDebugInfo()->popTimer();
	clearAndDestroy( stateObjectsDA );	
	retState.filterIdNodeIdObjectIds_ = stateDA.getHierarchyNodeObjectIds();
	
	DebugInfo::getDebugInfo()->popTimer();

	return retState;
}

const vector<int> Hub::searchText( const string& name ) 
{	
	unique_ptr<SearchDataAccess> dataAccess( SearchDataAccessFactory::create() );
	dataAccess->setName(name);

	return dataAccess->textSearch();
}

const vector<int> Hub::searchRGB( const string& name ) 
{	
	unique_ptr<SearchDataAccess> dataAccess( SearchDataAccessFactory::create() );
	dataAccess->setName(name); 
	
	return dataAccess->rgbSearch();
}



unsigned int Hub::getObjectCount()
{
	unique_ptr<HubDataAccess> dataAccess( HubDataAccessFactory::create() );
	return dataAccess->getObjectCount();
}

//____________________________________________________________________________________________________________________________________________________________________________________

vector<StateObject> Hub::getObjects()
{
	/*
	 Change the name of this function to getState
	 Change the DataAccess function to getState and have it return a StateDateAccess (not a vector of StateObject)
		Inside StateDataAccess is to be a map<int (filter_id), map<hierarchy_node_id, vector<object_id> > >
			This should fix the hierarchy slowdown
	 
	 
	 */
	DebugInfo::getDebugInfo()->pushTimer( "Hub", "getObjects" );

	vector<Filter*> filters = getFilters();
	
	unique_ptr<HubDataAccess> dataAccess( HubDataAccessFactory::create() );
	
	DebugInfo::getDebugInfo()->pushTimer( "Hub", "getObjects", "data access" );
	vector<FilterDataAccess*> filtersDA = FilterConverter::logicToDataAccess( filters );
	vector<StateObjectDataAccess*> stateObjectsDA = dataAccess->getObjects( filtersDA );
	clearAndDestroy( filtersDA );
	DebugInfo::getDebugInfo()->popTimer();
	
	lastGetObjectsQueryAsString_ = dataAccess->getObjectsQueryAsString();
	
	DebugInfo::getDebugInfo()->output( "Hub", "getObjects", "no. objects", stateObjectsDA.size() );
	
	vector<StateObject> stateObjects;
	DebugInfo::getDebugInfo()->pushTimer( "Hub", "getObjects", "adding tags" );

	//The looped code must perform well!
	vector<StateTag>::iterator tagItr;
	int tagIndex = 0;
	for( vector<StateObjectDataAccess*>::iterator itr = stateObjectsDA.begin(); itr != stateObjectsDA.end(); ++itr )
	{
		StateObject stateObject = StateObjectConverter::dataAccessToLogic( *itr );
		
		tagIndex = 0;
		for( tagItr = stateObject.tags_.begin(); tagItr != stateObject.tags_.end(); ++tagItr )
		{
			//(*tagItr).setTag_( TagSet::allTags_[ (*itr)->getTags()[ tagIndex ]->getTagId() ].get() );
			(*tagItr).setTag_( TagSet::allTags_[ (*itr)->getTags()[ tagIndex ]->getTagId() ] );
			++tagIndex;
		}
	
		/*
		for( unsigned int tagIndex = 0; tagIndex < stateObject.getTags().size(); ++tagIndex )
		{
			stateObject.tags_[ tagIndex ].setTag_( 
												  const_cast<Tag*>( getTag( (*itr)->getTags()[ tagIndex ]->getTagId() ) ) 
												  );
		}*/
		
		stateObjects.push_back( stateObject );
	}
	DebugInfo::getDebugInfo()->popTimer();
	clearAndDestroy( stateObjectsDA );	
	
	DebugInfo::getDebugInfo()->popTimer();
	return stateObjects;
}
//____________________________________________________________________________________________________________________________________________________________________________________

int Hub::getParentTagSetsAccessType( const Tag* /*const*/ tag ) const
{
	for( vector<std::shared_ptr<TagSet> >::const_iterator itr = tagSets_.begin(); itr != tagSets_.end(); ++itr)
	{
		if( (*itr)->getId() == tag->getTagSetId() )
		{
			return (*itr)->getAccessId();
		}
	}
	return TagSet::ACCESS_TYPE_UNKNOWN;
}
//____________________________________________________________________________________________________________________________________________________________________________________

const Tag * /*const*/ Hub::getUncategorizedTag() const
{
	TagSet* tagSet = 0;
	//Find the dimension
	for( vector<std::shared_ptr<TagSet> >::const_iterator itr = tagSets_.begin(); itr != tagSets_.end(); ++itr)
	{
		tagSet = (*itr).get();
		if( tagSet->getName() == Hub::getUncategorizedDimensionName() )
		{
			break;
		}
	}
	if( tagSet == 0) //Something very wrong
	{
		throw Exception( "Hub::getUncategorizedTag", "Could not find Uncategorized tag-set!" );
	}
	//Find the tag
	vector<Tag*> tags = tagSet->getTags();  //Debug
	for( vector<Tag*>::iterator itrT = tags.begin(); itrT != tags.end(); ++itrT )
	{
		Tag* tag = *itrT;
		if( tag->getTypeId() == TagCommon::ALPHANUMERICAL )
		{	
			AlphanumericalTag* anTag = dynamic_cast<AlphanumericalTag*>( *itrT );
			if( anTag->getName() == Hub::getUncategorizedTagName() )
			{
				return *itrT;
			}
		}
	}
	//Did not find it :@
	throw Exception( "Hub::getUncategorizedTag", "Could not find Uncategorized tag in Uncategorized tag-set!" );
}
//____________________________________________________________________________________________________________________________________________________________________________________

vector<TagSet*> Hub::getTagSets() const
{
	vector<TagSet*> tagSets;
	for( vector<std::shared_ptr<TagSet> >::const_iterator itr = tagSets_.begin(); itr != tagSets_.end(); ++itr)
	{
		tagSets.push_back( (*itr).get() );
	}
	return tagSets;
}
//____________________________________________________________________________________________________________________________________________________________________________________

TagSet* Hub::getTagSet( int id )
{
	for( vector<std::shared_ptr<TagSet> >::iterator itr = tagSets_.begin(); itr != tagSets_.end(); ++itr)
	{
		if( (*itr)->getId() == id )
		{
			return (*itr).get();
		}
	}
	//TagSet not found
	stringstream stringStream;
	stringStream << "Framework did not contain tag-set with id: " << id;
	throw Exception( "Hub::getTagSet(id)", stringStream.str() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

TagSet* Hub::getTagSet( const string& name )
{
	for( vector<std::shared_ptr<TagSet> >::iterator itr = tagSets_.begin(); itr != tagSets_.end(); ++itr)
	{
		if( (*itr)->getName() == name )
		{
			return (*itr).get();
		}
	}
	//TagSet not found
	stringstream stringStream;
	stringStream << "Framework did not contain tag-set with name: " << name;
	throw Exception( "Hub::getTagSet(name)", stringStream.str() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

const vector<PluginCommon*> Hub::getProcessObjectPlugins() const
{
	return (*pluginServer_).getProcessObjectServer().getProcessors();
} 
//____________________________________________________________________________________________________________________________________________________________________________________

const vector<Tag*> Hub::getTags( const vector<int>& tagIds ) const
{
	vector<Tag*> tags;
	for( vector<int>::const_iterator idItr = tagIds.begin(); idItr != tagIds.end(); ++idItr )
	{
		tags.push_back( const_cast<Tag*>( getTag( *idItr ) ) );
	}
	return tags;
}
//____________________________________________________________________________________________________________________________________________________________________________________

const vector<Tag*> Hub::getAllTags() const
{
	vector<Tag*> tags;
	for( vector<std::shared_ptr<TagSet> >::const_iterator itr = tagSets_.begin(); itr != tagSets_.end(); ++itr)
	{
		vector<Tag*> tempTags = (*itr)->getTags(); 
		tags.insert( tags.end(), tempTags.begin(), tempTags.end() );
	}
	return tags;
}
//____________________________________________________________________________________________________________________________________________________________________________________

const Tag* /*const*/ Hub::getTag( int id ) const
{
	map<int, Tag* >::iterator itr = TagSet::allTags_.find( id );
	//map<int, std::shared_ptr<Tag> >::iterator itr = TagSet::allTags_.find( id );
	if( itr == TagSet::allTags_.end() ) //Not found
	{
		throw Exception( "Hub::getTag", "Tag does not exist (id).", id );
	}
	//return (*itr).second.get();

	return (*itr).second;
}
//____________________________________________________________________________________________________________________________________________________________________________________

const vector<Dimension*> Hub::getDimensions() const
{
	vector<Dimension*> dimensions;
	for( vector<std::shared_ptr<TagSet> >::const_iterator itr = tagSets_.begin(); itr != tagSets_.end(); ++itr)
	{
		vector<Dimension*> tempDimensions = (*itr)->getDimensions();
		dimensions.insert( dimensions.end(), tempDimensions.begin(), tempDimensions.end() );
	}
	return dimensions;
}
//____________________________________________________________________________________________________________________________________________________________________________________

const vector<PersistentDimension*> Hub::getPersistentDimensions() const
{
	vector<PersistentDimension*> dimensions;
	for( vector<std::shared_ptr<TagSet> >::const_iterator itr = tagSets_.begin(); itr != tagSets_.end(); ++itr)
	{
		vector<PersistentDimension*> tempDimensions = (*itr)->getPersistentDimensions();
		dimensions.insert( dimensions.end(), tempDimensions.begin(), tempDimensions.end() );
	}
	return dimensions;
}
//____________________________________________________________________________________________________________________________________________________________________________________

const vector<VirtualDimension*> Hub::getVirtualDimensions() const
{
	vector<VirtualDimension*> dimensions;
	for( vector<std::shared_ptr<TagSet> >::const_iterator itr = tagSets_.begin(); itr != tagSets_.end(); ++itr)
	{
		vector<VirtualDimension*> tempDimensions = (*itr)->getVirtualDimensions();
		dimensions.insert( dimensions.end(), tempDimensions.begin(), tempDimensions.end() );
	}

	return dimensions;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void Hub::refreshMaterializedViews()
{
	unique_ptr<HubDataAccess> dataAccess( HubDataAccessFactory::create() );
	dataAccess->refreshMaterializedViews();
}










