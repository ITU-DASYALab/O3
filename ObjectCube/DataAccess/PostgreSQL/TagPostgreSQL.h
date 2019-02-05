/*
* Snorri Gíslason - 2018
*/

#if !defined(ObjectCube_TAG_POSTGRESQL_) && defined(OC_POSTGRESQL)
//#ifndef ObjectCube_TAG_POSTGRESQL_
#define ObjectCube_TAG_POSTGRESQL_

#include "../Root/TagDataAccess.h"

namespace ObjectCube
{
	
	class TagPostgreSQL : public TagDataAccess
	{
	public:
		virtual TagDataAccess* fetch( int id );
		virtual TagDataAccess* create();
		virtual int inUse( int id );
		virtual void remove( int id );
		
		//Support for tag types
		static int createTag( int tagSetId, int typeId );
		static void removeTag( int id );
		static int tagInUse( int id );
		
	};
	
}

#endif