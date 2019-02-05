/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/


#ifndef ObjectCube_BOUNDINGBOX_CONVERTER_
#define ObjectCube_BOUNDINGBOX_CONVERTER_

#include <vector>
#include "../Boundaries/BoundingBox.h"
#include "../DataAccess/Root/BoundingBoxDataAccess.h"

namespace ObjectCube 
{
	class BoundingBoxDataAccess;
	
	class BoundingBoxConverter
	{
	public:
		static BoundingBox dataAccessToLogic( BoundingBoxDataAccess boundingBoxDA );
		static BoundingBoxDataAccess logicToDataAccess( BoundingBox boundingBox );
		
	//	static vector<BoundingBox> dataAccessToLogic( vector<BoundingBoxDataAccess*> objectsDA );
	//	static vector<BoundingBoxDataAccess*> logicToDataAccess( const vector<BoundingBox>& objects );
		
	};
	
}

#endif
