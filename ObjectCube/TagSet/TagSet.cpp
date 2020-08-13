/*
 *  dimension.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 25.10.2009.
 *  Copyright 2009 Reykjavik University. All rights reserved.
 *
 */

#include "TagSet.h"

#include <iostream>
#include <memory>
#include <sstream>

#include "../DataAccess/Factories/TagSetDataAccessFactory.h"
#include "../DataAccess/Root/TagSetDataAccess.h"
#include "../Converters/TagSetConverter.h"

#include "../Object.h"
#include "../Tag/Tag.h" 
#include "../Tag/AlphanumericalTag.h"
#include "../Hub.h"
#include "../Filters/Filter.h"
#include "../LayerShared/SharedDefinitions.h"
#include "../LayerShared/Exception.h"
#include "../Tag/TagFactory.h"
#include "../Filters/FilterFactory.h"
#include "../Hierarchy/DefaultDimension.h"
#include "../Hierarchy/DimensionFactory.h"
#include "../LayerShared/MemoryManagement.h"
#include "../Language.h"
#include "../LayerShared/DebugInfo.h"


using namespace ObjectCube;
using namespace std;

//____________________________________________________________________________________________________________________________________________________________________________________

//map<int, std::shared_ptr<Tag> > TagSet::allTags_;
map<int, Tag*> TagSet::allTags_;

//____________________________________________________________________________________________________________________________________________________________________________________

TagSet::TagSet()
{
	init_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

TagSet::TagSet( const string& name ) 
{ 
	init_();
	setName( name ); 
}
//____________________________________________________________________________________________________________________________________________________________________________________

TagSet::TagSet( const string& name, const string& description ) 
{ 
	init_();
	setName( name );
	setDescription( description ); 
}
//____________________________________________________________________________________________________________________________________________________________________________________

TagSet::TagSet( const TagSet& tagSet )
{
	copyValues_( tagSet );
}
//____________________________________________________________________________________________________________________________________________________________________________________

TagSet& TagSet::operator=( const TagSet& tagSet )
{
	if( this == &tagSet )  //No overwriting of self
	{
		return *this;
	}

	copyValues_( tagSet );
	
	return *this;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSet::copyValues_( const TagSet& tagSet )  //A helper function for = operator and copy constructor
{
	cleanup_();
	
	setId_( tagSet.getId() );
	setTypeId_( tagSet.getTypeId() );
	setAccessId_( tagSet.getAccessId() );
	setName( tagSet.getName() );
	setDescription( tagSet.getDescription() );
	
	supportedFilterTypes_ = tagSet.supportedFilterTypes_;
	supportedTagTypes_ = tagSet.supportedTagTypes_;
	
	//Tags
	/*
	const vector<Tag*> tags = tagSet.getTags();
	for( vector<Tag*>::const_iterator tagItr = tags.begin(); tagItr != tags.end(); ++tagItr )
	{
		std::shared_ptr<Tag> tag( TagFactory::create( (*tagItr)->getTypeId() ) );
		*tag.get() = *(*tagItr);
		tags_.push_back( tag );
	}

	//Filters
	const vector<Filter*> filters = tagSet.getFilters();
	for( vector<Filter*>::const_iterator filterItr = filters.begin(); filterItr != filters.end(); ++filterItr )
	{
		std::shared_ptr<Filter> filter( FilterFactory::create( (*filterItr)->getTypeId() ) );
		*filter.get() = *(*filterItr);
		filters_.push_back( filter );
	}
	
	//Dimensions
	const vector<Dimension*> dimensions = tagSet.getDimensions();
	for( vector<Dimension*>::const_iterator dimensionItr = dimensions.begin(); dimensionItr != dimensions.end(); ++dimensionItr )
	{
		std::shared_ptr<Dimension> dimension( DimensionFactory::create( (*dimensionItr)->getTypeId() ) );
		*dimension.get() = *(*dimensionItr);
		dimensions_.push_back( dimension );
	}
	 */
	
	tags_ = tagSet.tags_;
	filters_ = tagSet.filters_;
	dimensions_ = tagSet.dimensions_;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSet::cleanup_()
{
	tags_.clear();
	filters_.clear();
	dimensions_.clear();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSet::init_()
{
	id_ = INVALID_VALUE;
	typeId_ = INVALID_VALUE;
	accessId_ = INVALID_VALUE;
	
	setAccessId_( TagSet::USER );  //All tag-sets are by default user access level
	
	//Supported by all TagSet types
	supportedFilterTypes_.push_back( Filter::TAG_FILTER ); 
	supportedFilterTypes_.push_back( Filter::DIMENSION_FILTER );
}
//____________________________________________________________________________________________________________________________________________________________________________________

TagSet::~TagSet()
{
	cleanup_();	
}
//____________________________________________________________________________________________________________________________________________________________________________________

TagSet* TagSet::create()
{
	return createImp_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

PersistentDimension* TagSet::createPersistentDimension( const Tag* tag )
{
	creationTest_();
	//Validate that the tag has been created and belongs to the dimension
	getTag( tag->getId() );  //Throws exception if it does not belong to this dimension
	//Create the Dimension
	std::shared_ptr<PersistentDimension> persistentDimension( new PersistentDimension( getId(), tag ) );
	persistentDimension->create_();
	int dimensionId = persistentDimension->getId();
	dimensions_.push_back( persistentDimension );
	return getPersistentDimension( dimensionId );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSet::deleteDimension( int id )
{
	for( vector<std::shared_ptr<Dimension> >::iterator itr = dimensions_.begin(); itr != dimensions_.end(); ++itr )
	{
		if( (*itr)->getId() == id )
		{
			(*itr)->delete_();
			//This delete causes invalid read errors in Valgrind, ToDo:  Find out why
			dimensions_.erase( itr );	
			return;
		}
	}
	
	throw Exception( "TagSet::deleteDimension", "Dimension does not belong to tag-set.", id );
}
//____________________________________________________________________________________________________________________________________________________________________________________

Dimension* TagSet::getDimension( int dimensionId )
{
	for( vector<std::shared_ptr<Dimension> >::const_iterator itr = dimensions_.begin(); itr != dimensions_.end(); ++itr )
	{
		if( (*itr)->getId() == dimensionId )
		{
			return (*itr).get();
		}
	}
	throw Exception( "TagSet::getDimension", "TagSet did not contain the requested dimension.", dimensionId );
}
//____________________________________________________________________________________________________________________________________________________________________________________

Dimension* TagSet::getDimension( const string& name )
{
	for( vector<std::shared_ptr<Dimension> >::const_iterator itr = dimensions_.begin(); itr != dimensions_.end(); ++itr )
	{
		if( (*itr)->getRoot()->getName() == name )
		{
			return (*itr).get();
		}
	}
	throw Exception( "TagSet::getDimension", "TagSet did not contain the requested dimension.", name );
}
//____________________________________________________________________________________________________________________________________________________________________________________

const Dimension* TagSet::getDimension( int dimensionId ) const
{
	for( vector<std::shared_ptr<Dimension> >::const_iterator itr = dimensions_.begin(); itr != dimensions_.end(); ++itr )
	{
		if( (*itr)->getId() == dimensionId )
		{
			return (*itr).get();
		}
	}
	throw Exception( "TagSet::getDimension", "TagSet did not contain the requested dimension.", dimensionId );
}
//____________________________________________________________________________________________________________________________________________________________________________________

const Dimension* TagSet::getDimension( const string& name ) const 
{
	for( vector<std::shared_ptr<Dimension> >::const_iterator itr = dimensions_.begin(); itr != dimensions_.end(); ++itr )
	{
		if( (*itr)->getRoot()->getName() == name )
		{
			return (*itr).get();
		}
	}
	throw Exception( "TagSet::getDimension", "TagSet did not contain the requested dimension.", name );
}

//____________________________________________________________________________________________________________________________________________________________________________________

PersistentDimension* TagSet::getPersistentDimension( int dimensionId )
{
	return dynamic_cast<PersistentDimension*>( getDimension( dimensionId ) );
}
//____________________________________________________________________________________________________________________________________________________________________________________

PersistentDimension* TagSet::getPersistentDimension( const string& name )  
{
	return dynamic_cast<PersistentDimension*>( getDimension( name ) );
}
//____________________________________________________________________________________________________________________________________________________________________________________

const VirtualDimension* TagSet::getVirtualDimension( int dimensionId ) const
{
	return dynamic_cast<const VirtualDimension*>( getDimension( dimensionId ) );
}
//____________________________________________________________________________________________________________________________________________________________________________________

const VirtualDimension* TagSet::getVirtualDimension( const string& name ) const
{
	return dynamic_cast<const VirtualDimension*>( getDimension( name ) );
}
//____________________________________________________________________________________________________________________________________________________________________________________

const vector<Dimension*> TagSet::getDimensions() const
{
	vector<Dimension*> dimensions;
	for( vector<std::shared_ptr<Dimension> >::const_iterator itr = dimensions_.begin(); itr != dimensions_.end(); ++itr )
	{
		dimensions.push_back( (*itr).get() );
	}
	return dimensions;
}
//____________________________________________________________________________________________________________________________________________________________________________________
const DefaultDimension* TagSet::getDefaultDimension() const
{
	for( vector<std::shared_ptr<Dimension> >::const_iterator itr = dimensions_.begin(); itr != dimensions_.end(); ++itr )
	{
		if( (*itr)->getTypeId() == Dimension::DEFAULT )
		{
			return dynamic_cast<DefaultDimension*>( (*itr).get() );
		}
	}
	throw Exception( "TagSet::getDefaultDimension", "TagSet did not contain a default dimesion." );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

const vector<PersistentDimension*> TagSet::getPersistentDimensions() const
{
	vector<PersistentDimension*> dimensions;
	for( vector<std::shared_ptr<Dimension> >::const_iterator itr = dimensions_.begin(); itr != dimensions_.end(); ++itr )
	{
		if( (*itr)->getTypeId() == Dimension::PERSISTENT )
		{
			dimensions.push_back( dynamic_cast<PersistentDimension*>( (*itr).get()  ) );
		}
	}
	return dimensions;
}
//____________________________________________________________________________________________________________________________________________________________________________________

const vector<VirtualDimension*> TagSet::getVirtualDimensions() const
{
	vector<VirtualDimension*> dimensions;
	for( vector<std::shared_ptr<Dimension> >::const_iterator itr = dimensions_.begin(); itr != dimensions_.end(); ++itr )
	{
		if( (*itr)->getTypeId() == Dimension::VIRTUAL )
		{
			dimensions.push_back( dynamic_cast<VirtualDimension*>( (*itr).get()  ) );
		}
	}
	return dimensions;
}
//____________________________________________________________________________________________________________________________________________________________________________________

const Tag* /*const*/ TagSet::getTag( int id ) const
{
	//map<int, std::shared_ptr<Tag> >::iterator itr = TagSet::allTags_.find( id );
	//map<int, std::shared_ptr<Tag> >::iterator itr = TagSet::allTags_.find( id );
	map<int, Tag*>::iterator itr = TagSet::allTags_.find( id );
	if( itr == TagSet::allTags_.end() ) //Not found
	{
		throw Exception( "TagSet::getTag", "TagSet did not contain requested tag (id).", id );
	}
	if( (*itr).second->getTagSetId() != getId() )
	{
		throw Exception( "TagSet::getTag", "TagSet did not contain requested tag, but the tag does exist in another tag-set.  Tag id.", id );
	}
	//return (*itr).second.get();
	return (*itr).second;
}
//____________________________________________________________________________________________________________________________________________________________________________________

const vector<Tag*> TagSet::getTags( const vector<int>& tagIds ) const
{
	vector<Tag*> tags;
	for( vector<int>::const_iterator idItr = tagIds.begin(); idItr != tagIds.end(); ++idItr )
	{
		tags.push_back( const_cast<Tag*>( getTag( *idItr ) ) );
	}
	return tags;	
}
//____________________________________________________________________________________________________________________________________________________________________________________

const vector<Tag*> TagSet::getTags() const
{
	vector<Tag*> tags;
	for( vector< std::shared_ptr<Tag> >::const_iterator itr = tags_.begin(); itr != tags_.end(); ++itr )
	{
		tags.push_back( (*itr).get() );
	}
	//Sort the tags according to value, use a comparison functor
	//sort( tags.begin(), tags.end(), someComparisonFunctor );
	return tags;
}
//____________________________________________________________________________________________________________________________________________________________________________________

const Tag* /*const*/ TagSet::addTag( const Tag* /*const*/ tag)
{
	creationTest_();
	
	if( !supportedTagType_( tag ) )
	{
		stringstream stringStream;
		stringStream << "TagSet of type " << getTypeId() << " does not support tagType " << tag->getTypeId();
		throw Exception( "TagSet::addTag",  stringStream.str() );
	}
	//We copy the tag to limit the affects of user actions on the framework.  It also simplifies user memory management.
	std::shared_ptr<Tag> tagCopy( TagFactory::create( tag->getTypeId() ) );
	//Tag* tagCopy = TagFactory::create( tag->getTypeId() );
	//*tagCopy = *tag;
	*tagCopy.get() = *tag;
	tagCopy->setTagSetId_( getId() );
	tagCopy->create_();
	tags_.push_back( tagCopy );
	//std::shared_ptr<Tag> tagMap( tagCopy );
//	TagSet::allTags_.insert( pair<int, std::shared_ptr<Tag> >( tagCopy->getId(), tagCopy ) );
	TagSet::allTags_.insert( pair<int, Tag*>( tagCopy->getId(), tagCopy.get() ) );
	loadDefaultDimension_();  //Add the tag, brute force
	
	return tagCopy.get();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSet::erase()
{
	//erase all tags of the tag-set from objects
	//erase all persistent dimensions of the tag-set
	//erase all tags of the tag-set
	//erase the tag-set itself & remove it from the hub
	
	//Do all the DB deletions in one transaction, this is all or nothing operation
	
	unique_ptr<TagSetDataAccess> dataAccess( TagSetConverter::logicToDataAccess( this ) );
	dataAccess->erase();
	
	for( vector<std::shared_ptr<Tag> >::iterator itr = tags_.begin(); itr != tags_.end(); ++itr )
	{
		TagSet::allTags_.erase( (*itr)->getId() );
	}
	
	Hub* hub = Hub::getHub();
	hub->removeTagSet( this );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSet::deleteTag( const Tag* /*const*/ tag ) 
{
	getTag( tag->getId() ); //Throws an error if it is not found
	
	/*
	vector<Tag*>::iterator itr = find_if( tags_.begin(), tags_.end(), dereference( tag ) );
	if( itr == tags_.end() )  //Was not found
	{
		throw Exception( "TagSet::deleteTag", "Tag was not found!", tag->getId() );
	}
	 */
	if( tag->inUse() )
	{
		throw Exception( "TagSet::deleteTag", "The tag is in use, remove it from all objects before deleting it!", tag->getId() );
	}
	
	for( vector<std::shared_ptr<Tag> >::iterator itr = tags_.begin(); itr != tags_.end(); ++itr )
	{
		if( (*itr)->getId() == tag->getId() )
		{
			(*itr)->delete_();
			
			//TagSet::allTags_[ (*itr)->getId() ] = 0;
			TagSet::allTags_.erase( (*itr)->getId() );
			
			tags_.erase( itr );	
			
			loadDefaultDimension_(); //Remove the tag, brute force
			
			return;
		}
	}

	throw Exception( "TagSet::deleteTag", "Tag was not found!", tag->getId() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

TagSet* TagSet::createImp_()
{
	unique_ptr<TagSetDataAccess> dataAccess( TagSetConverter::logicToDataAccess( this ) );
	std::shared_ptr<TagSet> tagSet( TagSetConverter::dataAccessToLogic( dataAccess->create() ) );
	*this = *tagSet.get();
	
	// hs: Added for reloading dimensions, when new tagset is added.
	loadDefaultDimension_();
	return Hub::getHub()->addTagSet( this );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSet::creationTest_()
{
	if( getId() == INVALID_VALUE ) //Has not been created
	{
		throw Exception( "TagSet::creationTest_", "Requested operation could not be completed since the tag-set has not been created!" );
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSet::fetch_( int id )
{ 	
	DebugInfo::getDebugInfo()->output( "TagSet", "fetch_", "id: ", id );
	DebugInfo::getDebugInfo()->pushTimer( "TagSet", "fetch_" );
	DebugInfo::getDebugInfo()->pushTimer( "TagSet", "fetch_", "fetch tag-set" );
	setId_( id );
	unique_ptr<TagSetDataAccess> dataAccess( TagSetDataAccessFactory::create() );
	std::shared_ptr<TagSet> tagSet( TagSetConverter::dataAccessToLogic( dataAccess->fetch( id ) ) );
	*this = *tagSet.get();
	
	for( vector<std::shared_ptr<Tag> >::iterator it = tags_.begin(); it != tags_.end(); ++it )
	{
		//ToDo: Stop taking a copy!  It is done due to a nasty memory clean-up error.
/*
		std::shared_ptr<Tag> mapTag( TagFactory::create( (*it)->getTypeId() ) );
		*(mapTag.get()) = *( (*it).get() );  
		TagSet::allTags_.insert( pair<int, std::shared_ptr<Tag> >( mapTag.get()->getId(), mapTag ) );
*/
		//TagSet::allTags_.insert( pair<int, std::shared_ptr<Tag> >( (*it)->getId(), (*it) ) );
		TagSet::allTags_.insert( pair<int, Tag*>( (*it)->getId(), (*it).get() ) );
	}
	
	DebugInfo::getDebugInfo()->popTimer();
	
	loadDefaultDimension_();
		
	DebugInfo::getDebugInfo()->pushTimer( "TagSet", "fetch_", "persistent dimensions" );
	vector<int> hierarchyIds = dataAccess->fetchDimensionIds();
	for( vector<int>::iterator itr = hierarchyIds.begin(); itr != hierarchyIds.end(); ++itr )
	{
		dimensions_.push_back( std::shared_ptr<Dimension>( PersistentDimension::fetch_( *itr ) ) );
	}
	DebugInfo::getDebugInfo()->popTimer();
	
	DebugInfo::getDebugInfo()->popTimer();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSet::loadDefaultDimension_()
{
	try 
	{
		const DefaultDimension* defaultDim = getDefaultDimension();
		deleteDimension( defaultDim->getId() );
	}
	catch ( ... ) {}
	
	DebugInfo::getDebugInfo()->pushTimer( "TagSet", "fetch_", "default dimension" );
	
	std::shared_ptr<DefaultDimension> defaultDimension( new DefaultDimension( getId(), getTags() ) );
	dimensions_.push_back( defaultDimension );
	
	DebugInfo::getDebugInfo()->popTimer();	
}
//____________________________________________________________________________________________________________________________________________________________________________________

const vector<Filter*> TagSet::getFilters() const
{
	vector<Filter*> filters;
	for( vector< std::shared_ptr<Filter> >::const_iterator itr = filters_.begin(); itr != filters_.end(); ++itr )
	{
		filters.push_back( (*itr).get() );
	}
	return filters;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSet::addFilter_( Filter* /*const*/ filter )
{
	creationTest_();
	
	if( !supportedFilter_( filter ) )
	{
		throw Exception( "TagSet::addFilter_", "Filter type not supported!" ); 
	}
	//There is currently no checking against adding the same filter more than once.
	
	filter->fillInAndValidateValues();
	
	//We copy the filter so that the memory mangement of the framework is less affected by the users actions.
	/*
	unique_ptr<Filter> filterCopy( FilterFactory::create( filter->getTypeId() ) );
	*(filterCopy.get()) = *filter;
	filters_.push_back( filterCopy.release() );
	*/
	
	std::shared_ptr<Filter> filterCopy( FilterFactory::create( filter->getTypeId() ) );
	*(filterCopy.get()) = *filter;
	filters_.push_back( filterCopy );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSet::removeFilter_( Filter* filter )
{
	//ToDo:  Use this type of logic instead of looping through the containers.	 
	/*
	vector< std::shared_ptr<Filter> >::iterator itr = find_if( filters_.begin(), filters_.end(), dereference( filter ) );
	if( itr == filters_.end() )
	{
		throw Exception( "TagSet::removeFilter_", "Filter was not found!" );
	}
//	delete *itr;
//	*itr = 0;
	filters_.erase( itr );
	 */
	
	for( vector< std::shared_ptr<Filter> >::iterator itr = filters_.begin(); itr != filters_.end(); ++itr )
	{
		if( (*itr)->getId() == filter->getId() )
		{
			filters_.erase( itr );
			return;
		}
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSet::removeFilters_()
{
	//clearAndDestroy( filters_ );
	filters_.clear();
}
//____________________________________________________________________________________________________________________________________________________________________________________

bool TagSet::supportedFilter_( const Filter* /*const*/ filter )
{
	return count( supportedFilterTypes_.begin(), supportedFilterTypes_.end(), filter->getTypeId() ) > 0;
}
//____________________________________________________________________________________________________________________________________________________________________________________

bool TagSet::supportedTagType_( const Tag* /*const*/ tag )
{
	return count( supportedTagTypes_.begin(), supportedTagTypes_.end(), tag->getTypeId() ) > 0;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSet::loadVirtualDimensions_()
{
	throw Exception( "TagSet::loadVirtualDimensions_", "Not implemented for base class!" ); 
}
//____________________________________________________________________________________________________________________________________________________________________________________

const string TagSet::typeAsString() const
{
	return Language::asString( "TagSetType", getTypeId() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

const string TagSet::typeAsString( int tagSetTypeId )
{
	return Language::asString( "TagSetType", tagSetTypeId );
}
//____________________________________________________________________________________________________________________________________________________________________________________

const string TagSet::accessTypeAsString() const
{
	return Language::asString( "TagSetAccessType", getAccessId() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

const string TagSet::accessTypeAsString( int tagSetAccessTypeId )
{
	return Language::asString( "TagSetAccessType", tagSetAccessTypeId );
}
//____________________________________________________________________________________________________________________________________________________________________________________


























