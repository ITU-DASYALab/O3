/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/

#include "NumericalRangeFilterDataAccess.h"

#include <sstream>

#include "../../LayerShared/SharedDefinitions.h"
#include "../../LayerShared/FilterCommon.h"
#include "../../LayerShared/Exception.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

NumericalRangeFilterDataAccess::NumericalRangeFilterDataAccess()
{
	setTypeId( FilterCommon::NUMERICAL_RANGE_FILTER );
	numberFrom_ = 0;
	numberTo_ = 0;
	numberFromIsNull_ = true;
	numberToIsNull_ = true;
}
//____________________________________________________________________________________________________________________________________________________________________________________

NumericalRangeFilterDataAccess::~NumericalRangeFilterDataAccess()
{
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void NumericalRangeFilterDataAccess::setNumberFrom( long numberFrom ) 
{ 
	numberFrom_ = numberFrom;
	numberFromIsNull_ = false;
	setNullStatus( numberFromIsNull_ || numberToIsNull_ ); 
}
//____________________________________________________________________________________________________________________________________________________________________________________

void NumericalRangeFilterDataAccess::setNumberTo( long numberTo ) 
{ 
	numberTo_ = numberTo; 
	numberToIsNull_ = false;
	setNullStatus( numberFromIsNull_ || numberToIsNull_ ); 
}
//____________________________________________________________________________________________________________________________________________________________________________________

string NumericalRangeFilterDataAccess::getSelectionPredicate_()
{
	throw Exception( "NumericalRangeFilterDataAccess::getSelectionPredicate_", "This is only implemented in DB specific classes" );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

string NumericalRangeFilterDataAccess::getFiltrationPredicate_()
{
	throw Exception( "NumericalRangeFilterDataAccess::getFiltrationPredicate_", "This is only implemented in DB specific classes" );	
}
//____________________________________________________________________________________________________________________________________________________________________________________

