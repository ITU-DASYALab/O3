/*
 *  StateTagConverter.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 19.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_STATE_TAG_CONVERTER_
#define ObjectCube_STATE_TAG_CONVERTER_

#include <vector>
#include "../State/StateTag.h"

namespace ObjectCube 
{
	class StateTagDataAccess;
	
	class StateTagConverter
	{
	public:
		static StateTag dataAccessToLogic( StateTagDataAccess* stateTagDA );
		static vector<StateTag> dataAccessToLogic( const vector<StateTagDataAccess*>& stateTagsDA );
	};
	
}

#endif