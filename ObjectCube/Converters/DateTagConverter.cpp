/*
 *  DateTagConverter.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 10.4.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "DateTagConverter.h"

#include "../Tag/DateTag.h"
#include "../DataAccess/Root/DateTagDataAccess.h"
#include "../DataAccess/Factories/DateTagDataAccessFactory.h"
#include "TagConverter.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

std::shared_ptr<Tag> DateTagConverter::dataAccessToLogic_( const TagDataAccess* tagDA )
{
	std::shared_ptr<Tag> tag( TagConverter::dataAccessToLogic_( tagDA ) );
	DateTag* dTag =  dynamic_cast<DateTag*>( tag.get() );
	
	const DateTagDataAccess* dTagDA = dynamic_cast<const DateTagDataAccess*>( tagDA );
	if( dTagDA )
	{
		dTag->setYear( dTagDA->getYear() );
		dTag->setMonth( dTagDA->getMonth() );
		dTag->setDayOfMonth( dTagDA->getDayOfMonth() );
	}
	
	return tag;
}
//____________________________________________________________________________________________________________________________________________________________________________________

unique_ptr<TagDataAccess> DateTagConverter::logicToDataAccess_( const Tag* tag )
{
	unique_ptr<DateTagDataAccess> tagDA( dynamic_cast<DateTagDataAccess*>( TagConverter::logicToDataAccess_( tag ).release() ) );
	const DateTag* dTag = dynamic_cast<const DateTag*> ( tag );
	
	tagDA->setYear( dTag->getYear() );
	tagDA->setMonth( dTag->getMonth() );
	tagDA->setDayOfMonth( dTag->getDayOfMonth() );
	
	return unique_ptr<TagDataAccess>( tagDA.release() );
}
//____________________________________________________________________________________________________________________________________________________________________________________
