/*
* Snorri Gíslason - 2018
*/


#if !defined(ObjectCube_PLUGIN_TAG_SET_POSTGRESQL_) && defined(OC_POSTGRESQL)
//#ifndef ObjectCube_PLUGIN_TAG_SET_POSTGRESQL_
#define ObjectCube_PLUGIN_TAG_SET_POSTGRESQL_

#include "../Root/PluginTagSetDataAccess.h"

using namespace std;

namespace ObjectCube
{
	
	class PluginTagSetPostgreSQL : public PluginTagSetDataAccess
	{
	public:
		virtual void updateTagSetId( int id, int tagSetId );
		
	};
	
}

#endif