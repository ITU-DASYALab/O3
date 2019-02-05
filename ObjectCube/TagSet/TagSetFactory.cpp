/*
 *  TagSetFactory.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 9.11.2009.
 *  Copyright 2009 Reykjavik University. All rights reserved.
 *
 */

#include "TagSetFactory.h"

#include <sstream>

#include "TagSet.h"
#include "AlphanumericalTagSet.h"
#include "NumericalTagSet.h"
#include "TimeTagSet.h"
#include "DateTagSet.h"
#include "RGBTagSet.h"
#include "../LayerShared/Exception.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

TagSet* TagSetFactory::create( int tagSetType)
{
	switch ( tagSetType ) 
	{
		case TagSet::ALPHANUMERICAL :
			return new AlphanumericalTagSet();
		case TagSet::NUMERICAL :
			return new NumericalTagSet();
		case TagSet::TIME :
			return new TimeTagSet();
		case TagSet::DATE :
			return new DateTagSet();
		case TagSet::RGB :
			return new RGBTagSet();	
		default:
			
			ostringstream stringstream;
			stringstream << "Unknown tag-set type: " << tagSetType;
			throw Exception("TagSetFactory::create", stringstream.str() );
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________