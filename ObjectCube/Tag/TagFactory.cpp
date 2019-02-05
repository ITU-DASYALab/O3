/*
 *  TagFactory.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 20.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "TagFactory.h"

#include <sstream>

#include "Tag.h"
#include "AlphanumericalTag.h"
#include "NumericalTag.h"
#include "TimeTag.h"
#include "DateTag.h"
#include "RGBTag.h"

#include "../LayerShared/Exception.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

Tag* TagFactory::create( int tagType)
{
	switch ( tagType ) 
	{
		case Tag::ALPHANUMERICAL :
			return new AlphanumericalTag();
		case Tag::NUMERICAL :
			return new NumericalTag();
		case Tag::TIME :
			return new TimeTag();
		case Tag::DATE :
			return new DateTag();
		case Tag::RGB :
			return new RGBTag();
		default:
			
			ostringstream stringstream;
			stringstream << "Unknown tag type: " << tagType;
			throw Exception("TagFactory::create", stringstream.str() );
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________