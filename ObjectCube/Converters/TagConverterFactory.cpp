/*
 *  TagConverterFactory.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 29.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "TagConverterFactory.h"

#include <sstream>

#include "../LayerShared/TagCommon.h"
#include "TagConverter.h"
#include "AlphanumericalTagConverter.h"
#include "NumericalTagConverter.h"
#include "TimeTagConverter.h"
#include "DateTagConverter.h"
#include "RGBTagConverter.h"
#include "../LayerShared/Exception.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

TagConverter* TagConverterFactory::create( int tagTypeId )
{
	switch ( tagTypeId  ) 
	{
		case TagCommon::ALPHANUMERICAL :
			return new AlphanumericalTagConverter();
		case TagCommon::NUMERICAL :
			return new NumericalTagConverter();
		case TagCommon::TIME :
			return new TimeTagConverter();
		case TagCommon::DATE :
			return new DateTagConverter();
		case TagCommon::RGB :
			return new RGBTagConverter();
		default:
			stringstream stringStream;
			stringStream << "Unknown tag type: " << tagTypeId;
			throw Exception( "TagConverterFactory::create", stringStream.str() );
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________