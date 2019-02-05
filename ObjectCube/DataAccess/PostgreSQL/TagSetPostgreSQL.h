/*
* ObjectPostgreSQL.h
* Snorri Gíslason - 2018
*/


#if !defined(ObjectCube_TAG_SET_POSTGRESQL_) && defined(OC_POSTGRESQL)
//#ifndef ObjectCube_TAG_SET_POSTGRESQL_
#define ObjectCube_TAG_SET_POSTGRESQL_

#include "../Root/TagSetDataAccess.h"

namespace ObjectCube
{
	
	class TagSetPostgreSQL : public TagSetDataAccess
	{
	public:
		virtual TagSetDataAccess* create();
		virtual TagSetDataAccess* fetch( int id );
		virtual vector<int> fetchDimensionIds();
		virtual void erase();
	protected:
		virtual vector<TagDataAccess*> fetchTags_();
	};
	
}

#endif