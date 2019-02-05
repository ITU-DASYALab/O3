/*
 *  NumericalRangeFilter.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 1.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "NumericalRangeFilter.h"

#include <sstream>

#include "../LayerShared/SharedDefinitions.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

NumericalRangeFilter::NumericalRangeFilter()
{
	init_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

NumericalRangeFilter::NumericalRangeFilter( long numberFrom, long numberTo, int tagSetId )
: Filter( tagSetId )
{
	init_();
	setNumberFrom_( numberFrom );
	setNumberTo_( numberTo );
}
//____________________________________________________________________________________________________________________________________________________________________________________

NumericalRangeFilter::~NumericalRangeFilter()
{
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void NumericalRangeFilter::init_()
{
	setTypeId_( Filter::NUMERICAL_RANGE_FILTER );
	numberFrom_ = 0;
	numberTo_ = 0;
	numberFromIsNull_ = true;
	numberToIsNull_ = true;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void NumericalRangeFilter::setNumberFrom_( long numberFrom ) 
{ 
	numberFrom_ = numberFrom;
	numberFromIsNull_ = false;
	setNullStatus_( numberFromIsNull_ || numberToIsNull_ ); 
}
//____________________________________________________________________________________________________________________________________________________________________________________

void NumericalRangeFilter::setNumberTo_( long numberTo ) 
{ 
	numberTo_ = numberTo; 
	numberToIsNull_ = false;
	setNullStatus_( numberFromIsNull_ || numberToIsNull_ ); 
}
//____________________________________________________________________________________________________________________________________________________________________________________

Filter& NumericalRangeFilter::operator=( const Filter& filter )
{
	assignValues_( filter );
	const NumericalRangeFilter* nrFilter = dynamic_cast<const NumericalRangeFilter*>( &filter );
	setNumberFrom_( nrFilter->getNumberFrom() );
	setNumberTo_( nrFilter->getNumberTo() );
	
	return *this;
}
//____________________________________________________________________________________________________________________________________________________________________________________


