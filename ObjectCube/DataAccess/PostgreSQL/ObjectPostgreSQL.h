/*
* ObjectPostgreSQL.h
* Snorri Gíslason - 2018
*/

#if !defined(ObjectCube_OBJECT_POSTGRESQL_) && defined(OC_POSTGRESQL)
#define ObjectCube_OBJECT_POSTGRESQL_

#include "../Root/ObjectDataAccess.h"

namespace ObjectCube
{
	class TagDataAccess;
	class CommonPostgreSQL;

	class ObjectPostgreSQL : public ObjectDataAccess
	{
	public:
		virtual ObjectDataAccess* fetch( int id );
		virtual ObjectDataAccess* fetch( const string& qualifiedName );
		virtual ObjectDataAccess* create();
		virtual void update();
		virtual void erase();
		virtual void updateFileTypeFromPluginResult();

		//virtual void addTag( int objectId, ObjectTagDataAccess* objectTag );
		virtual void addTag( ObjectTagDataAccess* objectTag );

		//virtual void removeTag( int objectId, int tagId );
		virtual void removeTag( ObjectTagDataAccess* objectTag );
		virtual vector<ObjectDataAccess*> fetchAllObjects();

	protected:
		virtual vector<ObjectTagDataAccess*> fetchTagInfo_( int objectId );

	/*private: 
		void processFetch_( pqxx::result r );
	*/};
}

#endif
