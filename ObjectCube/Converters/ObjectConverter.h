/*
 *  ObjectConverter.h
 *  Prada
 *
 *  Created by Grímur Tómasson on 6.2.2010.
 *  Copyright 2010 RU. All rights reserved.
 *
 */

#ifndef ObjectCube_OBJECT_CONVERTER_
#define ObjectCube_OBJECT_CONVERTER_

#include <vector>
#include "../Object.h"

namespace ObjectCube 
{
	class ObjectDataAccess;
	
	class ObjectConverter
	{
	public:
		static Object dataAccessToLogic( ObjectDataAccess* objectDA );
		static ObjectDataAccess* logicToDataAccess( const Object* object );
		
		static vector<Object> dataAccessToLogic( vector<ObjectDataAccess*> objectsDA );
		static vector<ObjectDataAccess*> logicToDataAccess( const vector<Object>& objects );

	};
	
}

#endif
