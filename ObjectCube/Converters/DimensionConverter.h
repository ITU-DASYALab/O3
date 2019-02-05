/*
 *  DimensionConverter.h
 *  Prada
 *
 *  Created by Grímur Tómasson on 8.2.2010.
 *  Copyright 2010 RU. All rights reserved.
 *
 */

#ifndef ObjectCube_DIMENSION_CONVERTER_
#define ObjectCube_DIMENSION_CONVERTER_

#include <vector>
#include "../Hierarchy/PersistentDimension.h"

namespace ObjectCube 
{
	class DimensionDataAccess;
	
	class DimensionConverter
	{
	public:
		static PersistentDimension* dataAccessToLogic( DimensionDataAccess* dimensionHierarchyDA );
		static DimensionDataAccess* logicToDataAccess( const PersistentDimension* dimensionHierarchy );
		
		static vector<PersistentDimension*> dataAccessToLogic( vector<DimensionDataAccess*> dimensionHierarchiesDA );
		static vector<DimensionDataAccess*> logicToDataAccess( const vector<PersistentDimension*>& dimensionHierarchies );
	};
}

#endif