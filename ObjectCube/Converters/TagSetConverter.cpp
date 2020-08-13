/*
 *  TagSetConverter.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 9.2.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "TagSetConverter.h"

#include "../DataAccess/Root/TagSetDataAccess.h"
#include "../DataAccess/Factories/TagSetDataAccessFactory.h"
#include "../TagSet/TagSetFactory.h"
#include "TagConverter.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

std::shared_ptr<TagSet> TagSetConverter::dataAccessToLogic( TagSetDataAccess* tagSetDA )
{
	std::shared_ptr<TagSet> dimension( TagSetFactory::create( tagSetDA->getTypeId() ) );
	
	dimension->setId_( tagSetDA->getId() );
	dimension->setName( tagSetDA->getName() );
	dimension->setDescription( tagSetDA->getDescription() );
	dimension->setTypeId_( tagSetDA->getTypeId() );
	dimension->setAccessId_( tagSetDA->getAccessId() );
	dimension->setTags_( TagConverter::dataAccessToLogic( tagSetDA->getTags() ) );
	
	return dimension;
}
//____________________________________________________________________________________________________________________________________________________________________________________

TagSetDataAccess* TagSetConverter::logicToDataAccess( const TagSet* dimension )
{
	TagSetDataAccess* tagSetDA = TagSetDataAccessFactory::create();
	
	tagSetDA->setId( dimension->getId() );
	tagSetDA->setName( dimension->getName() );
	tagSetDA->setDescription( dimension->getDescription() );
	tagSetDA->setTypeId( dimension->getTypeId() );
	tagSetDA->setAccessId( dimension->getAccessId() );
	tagSetDA->setTags( TagConverter::logicToDataAccess( dimension->getTags() ) );
	
	return tagSetDA;
}
//____________________________________________________________________________________________________________________________________________________________________________________

vector<std::shared_ptr<TagSet> > TagSetConverter::dataAccessToLogic( vector<TagSetDataAccess*> dimensionsDA )
{
	vector<std::shared_ptr<TagSet> > dimensions;
	for( vector<TagSetDataAccess*>::iterator itr = dimensionsDA.begin(); itr != dimensionsDA.end(); ++itr )
	{
		dimensions.push_back( TagSetConverter::dataAccessToLogic( *itr ) );
	}
	return dimensions;
}
//____________________________________________________________________________________________________________________________________________________________________________________

vector<TagSetDataAccess*> TagSetConverter::logicToDataAccess( const vector<TagSet*>& dimensions )
{
	vector<TagSetDataAccess*> dimensionsDA;
	vector<TagSet*>::const_iterator itr;
	
	for( itr = dimensions.begin(); itr != dimensions.end(); itr++ )
	{
		dimensionsDA.push_back( TagSetConverter::logicToDataAccess( *itr ) );
	}
	return dimensionsDA;
}
//____________________________________________________________________________________________________________________________________________________________________________________

