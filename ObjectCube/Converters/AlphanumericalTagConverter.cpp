/*
 *  AlphanumericalTagConverter.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 23.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "AlphanumericalTagConverter.h"

#include "../Tag/AlphanumericalTag.h"
#include "../DataAccess/Root/AlphanumericalTagDataAccess.h"
#include "../DataAccess/Factories/AlphanumericalTagDataAccessFactory.h"
#include "TagConverter.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

std::shared_ptr<Tag> AlphanumericalTagConverter::dataAccessToLogic_( const TagDataAccess* tagDA )
{
	std::shared_ptr<Tag> tag( TagConverter::dataAccessToLogic_( tagDA ) );
	AlphanumericalTag* aTag = dynamic_cast<AlphanumericalTag*>( tag.get() );
	
	const AlphanumericalTagDataAccess* aTagDA = dynamic_cast<const AlphanumericalTagDataAccess*>( tagDA );
	if( aTagDA != 0 )  //To support reading only base type info (tag-set loading mechanism)
	{
		aTag->setName( aTagDA->getName() );
	}
	
	return tag ;
}
//____________________________________________________________________________________________________________________________________________________________________________________

unique_ptr<TagDataAccess> AlphanumericalTagConverter::logicToDataAccess_( const Tag* tag )
{
	unique_ptr<TagDataAccess> tagDA(TagConverter::logicToDataAccess_( tag ) );
	AlphanumericalTagDataAccess* aTagDA = dynamic_cast<AlphanumericalTagDataAccess*>( tagDA.get() );
	
	aTagDA->setName( dynamic_cast<const AlphanumericalTag*>( tag )->getName() );
	
	return tagDA;
}
//____________________________________________________________________________________________________________________________________________________________________________________
