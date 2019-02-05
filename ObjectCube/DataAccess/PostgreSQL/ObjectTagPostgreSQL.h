/*
* ObjectTagPostgreSQL.h
* Snorri Gíslason - 2018
*/

#if !defined(ObjectCube_OBJECT_POSTGRESQL_) && defined(OC_POSTGRESQL)
#define ObjectCube_OBJECT_POSTGRESQL_

#include "../Root/ObjectTagDataAccess.h"

namespace ObjectCube
{
	class CommonPostgreSQL;
	
	class ObjectTagPostgreSQL : public ObjectTagDataAccess
	{
		virtual void create();
		virtual void erase();
		virtual void modify();

	private: 
		void addToMaterializedView_( CommonPostgreSQL* db );
	};
}

#endif