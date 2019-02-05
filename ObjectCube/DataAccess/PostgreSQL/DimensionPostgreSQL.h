/*
* Snorri Gíslason - 2018
*/


#if !defined(ObjectCube_DIMENSION_POSTGRESQL_) && defined(OC_POSTGRESQL)
//#ifndef ObjectCube_DIMENSION_POSTGRESQL_
#define ObjectCube_DIMENSION_POSTGRESQL_

#include "../Root/DimensionDataAccess.h"

namespace ObjectCube
{
	
	class DimensionPostgreSQL : public DimensionDataAccess
	{
	public:
		virtual int nextId();
		virtual vector<HierarchyNodeDataAccess*> fetch( int id );
		
	};
	
}

#endif