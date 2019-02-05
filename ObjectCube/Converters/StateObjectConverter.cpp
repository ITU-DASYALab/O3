/*
 *  StateObjectConverter.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 19.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "StateObjectConverter.h"

#include "../DataAccess/Root/StateObjectDataAccess.h"
#include "StateTagConverter.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

StateObject StateObjectConverter::dataAccessToLogic( StateObjectDataAccess* stateObjectDA )
{
	StateObject stateObject;
	stateObject.setId_( stateObjectDA->getId() );
	stateObject.setName_( stateObjectDA->getName() ); 
	stateObject.setTags_( StateTagConverter::dataAccessToLogic( stateObjectDA->getTags() ) );
	return stateObject;
}
//____________________________________________________________________________________________________________________________________________________________________________________

vector<StateObject> StateObjectConverter::dataAccessToLogic( vector<StateObjectDataAccess*> stateObjectsDA )
{
	vector<StateObject> stateObjects;
	for( vector<StateObjectDataAccess*>::iterator itr = stateObjectsDA.begin(); itr != stateObjectsDA.end(); ++itr )
	{
		stateObjects.push_back( StateObjectConverter::dataAccessToLogic( *itr ) );
	}
	return stateObjects;
}
//____________________________________________________________________________________________________________________________________________________________________________________

