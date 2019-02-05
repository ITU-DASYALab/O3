/*
 *  StateObjectConverter.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 19.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_STATE_OBJECT_CONVERTER_
#define ObjectCube_STATE_OBJECT_CONVERTER_

#include <vector>
#include "../State/StateObject.h"

namespace ObjectCube 
{
	class StateObjectDataAccess;
	
	class StateObjectConverter
	{
	public:
		static StateObject dataAccessToLogic( StateObjectDataAccess* stateObjectDA );
		static vector<StateObject> dataAccessToLogic( vector<StateObjectDataAccess*> stateObjectsDA );
		
	};
	
}

#endif