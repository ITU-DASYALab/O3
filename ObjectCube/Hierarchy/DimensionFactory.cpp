/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/

#include "DimensionFactory.h"

#include <sstream>

#include "Dimension.h"

#include "PersistentDimension.h"
#include "VirtualDimension.h"
#include "DefaultDimension.h"

#include "../LayerShared/Exception.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

Dimension* DimensionFactory::create( int typeId )
{
	switch ( typeId ) 
	{
		case Dimension::PERSISTENT :
			return new PersistentDimension();
		case Dimension::VIRTUAL :
			return new VirtualDimension();
		case Dimension::DEFAULT :
			return new DefaultDimension();
		default:
			
			ostringstream stringstream;
			stringstream << "Unknown dimension type: " << typeId;
			throw Exception("DimensionFactory::create", stringstream.str() );
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________