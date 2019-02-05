/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/

#include "FilterDataAccess.h"

#include "../../LayerShared/SharedDefinitions.h"
#include "../../LayerShared/Exception.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

FilterDataAccess::FilterDataAccess()
{
	setId( INVALID_VALUE );
	setTypeId( INVALID_VALUE );
	setTagSetId( INVALID_VALUE );
	isNull_ = true;	
}
//____________________________________________________________________________________________________________________________________________________________________________________

FilterDataAccess::~FilterDataAccess()
{
}
//____________________________________________________________________________________________________________________________________________________________________________________

string FilterDataAccess::getSelectionPredicate()
{
	if( isNull() )
	{
		throw Exception( "Filter::getSelectionPredicate", "Attempt to get predicate from an uninitialized filter" );
	}
	return getSelectionPredicate_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

string FilterDataAccess::getFiltrationPredicate()
{
	if( isNull() )
	{
		throw Exception( "Filter::getFiltrationPredicate", "Attempt to get predicate from an uninitialized filter" );
	}
	return getFiltrationPredicate_();	
}
//____________________________________________________________________________________________________________________________________________________________________________________

