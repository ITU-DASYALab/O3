/*
* Snorri Gíslason - 2018
*/



#if !defined(ObjectCube_HIERARCHY_NODE_POSTGRESQL_) && defined(OC_POSTGRESQL)
//#ifndef ObjectCube_HIERARCHY_NODE_POSTGRESQL_
#define ObjectCube_HIERARCHY_NODE_POSTGRESQL_

#include "../Root/HierarchyNodeDataAccess.h"

namespace ObjectCube
{
	
	class HierarchyNodePostgreSQL : public HierarchyNodeDataAccess
	{
	public:
		virtual HierarchyNodeDataAccess* create();
		virtual void update();
		virtual void remove();		
	};
	
}

#endif