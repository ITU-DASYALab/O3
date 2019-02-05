/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/

#include "DimensionFilterDataAccess.h"

#include "../../LayerShared/SharedDefinitions.h"
#include "../../LayerShared/Exception.h"
#include "../../LayerShared/FilterCommon.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

DimensionFilterDataAccess::DimensionFilterDataAccess()
{
	setTypeId( FilterCommon::DIMENSION_FILTER );
	setDimensionId( INVALID_VALUE );
	setLeftBorder( INVALID_VALUE );
	setRightBorder( INVALID_VALUE );
	setDimensionTypeId( INVALID_VALUE );
}
//____________________________________________________________________________________________________________________________________________________________________________________

DimensionFilterDataAccess::~DimensionFilterDataAccess()
{
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DimensionFilterDataAccess::setTagAndDimensionNodeIds( const map<int, int>& tagAndDimensionNodeIds ) 
{ 
	tagAndDimensionNodeIds_ = tagAndDimensionNodeIds; 
	setNullStatus( false );
}
//____________________________________________________________________________________________________________________________________________________________________________________

string DimensionFilterDataAccess::getSelectionPredicate_()
{
	throw Exception( "DimensionFilterDataAccess::getSelectionPredicate_", "This is only implemented in DB specific classes" );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

string DimensionFilterDataAccess::getFiltrationPredicate_()
{
	throw Exception( "DimensionFilterDataAccess::getFiltrationPredicate_", "This is only implemented in DB specific classes" );	
}
//____________________________________________________________________________________________________________________________________________________________________________________


