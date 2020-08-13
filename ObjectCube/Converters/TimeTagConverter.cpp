/*
 *  TimeTagConverter.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 10.4.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "TimeTagConverter.h"

#include "../Tag/TimeTag.h"
#include "../DataAccess/Root/TimeTagDataAccess.h"
#include "../DataAccess/Factories/TimeTagDataAccessFactory.h"
#include "TagConverter.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

std::shared_ptr<Tag> TimeTagConverter::dataAccessToLogic_( const TagDataAccess* tagDA )
{
	std::shared_ptr<Tag> tag( TagConverter::dataAccessToLogic_( tagDA ) );
	TimeTag* tTag = dynamic_cast<TimeTag*>( tag.get() );
	
	const TimeTagDataAccess* tTagDA = dynamic_cast<const TimeTagDataAccess*>( tagDA );
	if( tTagDA )
	{
		tTag->setHours( tTagDA->getHours() );
		tTag->setMinutes( tTagDA->getMinutes() );
		tTag->setSeconds( tTagDA->getSeconds() );
		tTag->setMilliseconds( tTagDA->getMilliseconds() );
	}
	
	return tag;
}
//____________________________________________________________________________________________________________________________________________________________________________________

unique_ptr<TagDataAccess> TimeTagConverter::logicToDataAccess_( const Tag* tag )
{
	unique_ptr<TimeTagDataAccess> tagDA( dynamic_cast<TimeTagDataAccess*>( TagConverter::logicToDataAccess_( tag ).release() ) );
	const TimeTag* tTag = dynamic_cast<const TimeTag*> ( tag );
	
	tagDA->setHours( tTag->getHours() );
	tagDA->setMinutes( tTag->getMinutes() );
	tagDA->setSeconds( tTag->getSeconds() );
	tagDA->setMilliseconds( tTag->getMilliseconds() );
	
	return unique_ptr<TagDataAccess>( tagDA.release() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

