/*
 *  StateTagConverter.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 19.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "StateTagConverter.h"

#include "BoundingBoxConverter.h"

#include "../DataAccess/Root/StateTagDataAccess.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

StateTag StateTagConverter::dataAccessToLogic( StateTagDataAccess* stateTagDA )
{
	StateTag stateTag( stateTagDA->getFilterAndDimensionNodeIds() );
	
	if( stateTagDA->hasBoundingBox() )
	{
		stateTag.boundingBox_.reset( new BoundingBox() );
		*stateTag.boundingBox_.get() = BoundingBoxConverter::dataAccessToLogic( *stateTagDA->getBoundingBox() );
	}	
	
	return stateTag;
}
//____________________________________________________________________________________________________________________________________________________________________________________

vector<StateTag> StateTagConverter::dataAccessToLogic( const vector<StateTagDataAccess*>& stateTagsDA )
{
	vector<StateTag> stateTags;
	for( vector<StateTagDataAccess*>::const_iterator itr = stateTagsDA.begin(); itr != stateTagsDA.end(); ++itr )
	{
		stateTags.push_back( StateTagConverter::dataAccessToLogic( *itr ) );
	}
	return stateTags;
}
//____________________________________________________________________________________________________________________________________________________________________________________

