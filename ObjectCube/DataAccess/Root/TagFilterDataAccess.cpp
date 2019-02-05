/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/

#include "TagFilterDataAccess.h"

#include "../../LayerShared/SharedDefinitions.h"
#include "../../LayerShared/FilterCommon.h"
#include "../../LayerShared/Exception.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

TagFilterDataAccess::TagFilterDataAccess()
{
	setTypeId( FilterCommon::TAG_FILTER );
	tagId_ = INVALID_VALUE; 
}
//____________________________________________________________________________________________________________________________________________________________________________________

TagFilterDataAccess::~TagFilterDataAccess()
{
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagFilterDataAccess::setTagId( int tagId )
{ 
	tagId_ = tagId;
	setNullStatus( false );
}
//____________________________________________________________________________________________________________________________________________________________________________________

string TagFilterDataAccess::getSelectionPredicate_()
{
	throw Exception( "TagFilterDataAccess::getSelectionPredicate_", "This is only implemented in DB specific classes" );
}
//____________________________________________________________________________________________________________________________________________________________________________________

string TagFilterDataAccess::getFiltrationPredicate_()
{
	throw Exception( "TagFilterDataAccess::getFiltrationPredicate_", "This is only implemented in DB specific classes" );
}
//____________________________________________________________________________________________________________________________________________________________________________________

