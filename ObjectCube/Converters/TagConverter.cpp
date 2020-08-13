/*
 *  Tag.cpp
 *  Prada
 *
 *  Created by Grímur Tómasson on 6.2.2010.
 *  Copyright 2010 RU. All rights reserved.
 *
 */

#include "TagConverter.h"

#include "../DataAccess/Root/TagDataAccess.h"
#include "../DataAccess/Factories/TagDataAccessFactory.h"
#include "../Tag/TagFactory.h"
#include "TagConverterFactory.h"


using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

std::shared_ptr<Tag> TagConverter::dataAccessToLogic( const TagDataAccess* tagDA )
{
	std::shared_ptr<TagConverter> converter( TagConverterFactory::create( tagDA->getTypeId()) );
	return converter->dataAccessToLogic_( tagDA );
}
//____________________________________________________________________________________________________________________________________________________________________________________

unique_ptr<TagDataAccess> TagConverter::logicToDataAccess( const Tag* tag )
{
	unique_ptr<TagConverter> converter( TagConverterFactory::create( tag->getTypeId()) );
	return converter->logicToDataAccess_( tag );
}
//____________________________________________________________________________________________________________________________________________________________________________________

vector<std::shared_ptr<Tag> > TagConverter::dataAccessToLogic( const vector<TagDataAccess*>& tagsDA )
{
	vector<std::shared_ptr<Tag> > tags;
	for( vector<TagDataAccess*>::const_iterator itr = tagsDA.begin(); itr != tagsDA.end(); ++itr )
	{
		tags.push_back( TagConverter::dataAccessToLogic( *itr ) );
	}
	return tags;
}
//____________________________________________________________________________________________________________________________________________________________________________________

vector<TagDataAccess*> TagConverter::logicToDataAccess( const vector<Tag*>& tags )
{
	vector<TagDataAccess*> tagsDA;
	for( vector<Tag*>::const_iterator itr = tags.begin(); itr != tags.end(); ++itr )
	{
		tagsDA.push_back( TagConverter::logicToDataAccess( (*itr) ).release() );
	}
	return tagsDA;
}
//____________________________________________________________________________________________________________________________________________________________________________________

std::shared_ptr<Tag> TagConverter::dataAccessToLogic_( const TagDataAccess* tagDA )
{
	std::shared_ptr<Tag> tag( TagFactory::create( (int) tagDA->getTypeId() ) );
	
	tag->setId_( tagDA->getId() );
	tag->setTagSetId_( tagDA->getTagSetId() );
	tag->setTypeId_( tagDA->getTypeId() );
	
	return tag;
}
//____________________________________________________________________________________________________________________________________________________________________________________

unique_ptr<TagDataAccess> TagConverter::logicToDataAccess_( const Tag* tag )
{
	unique_ptr<TagDataAccess> tagDA( TagDataAccessFactory::create( tag->getTypeId() ) );
	
	tagDA->setId( tag->getId() );
	tagDA->setTagSetId( tag->getTagSetId() );
	tagDA->setTypeId( tag->getTypeId() );
	
	return tagDA;
}
//____________________________________________________________________________________________________________________________________________________________________________________

