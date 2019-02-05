/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/


#ifndef ObjectCube_OBJECT_TAG_CONVERTER_
#define ObjectCube_OBJECT_TAG_CONVERTER_

#include <vector>

#include "../ObjectTag.h"

using namespace std;

namespace ObjectCube 
{
	class ObjectTagDataAccess;
	
	class ObjectTagConverter
	{
	public:
		static ObjectTag dataAccessToLogic( ObjectTagDataAccess* objectTagDA );
		static ObjectTagDataAccess* logicToDataAccess( const ObjectTag& objectTag );
		
		static vector<ObjectTag> dataAccessToLogic( vector<ObjectTagDataAccess*> objectTagsDA );
		static vector<ObjectTagDataAccess*> logicToDataAccess( const vector<ObjectTag>& objectTags );
		
	};
	
}

#endif
