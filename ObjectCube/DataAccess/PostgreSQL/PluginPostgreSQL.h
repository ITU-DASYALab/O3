/*
* Snorri Gíslason - 2018
*/

#if !defined(ObjectCube_PLUGIN_POSTGRESQL_) && defined(OC_POSTGRESQL)
//#ifndef ObjectCube_PLUGIN_POSTGRESQL_
#define ObjectCube_PLUGIN_POSTGRESQL_

#include "../Root/PluginDataAccess.h"

using namespace std;

namespace ObjectCube
{
	
	class PluginPostgreSQL : public PluginDataAccess
	{
	public:
		virtual PluginDataAccess* fetch( int id );
		virtual vector<PluginDataAccess*> fetchAll();
		
	private:
		virtual vector<PluginTagSetDataAccess*> fetchPluginTagSets_( int pluginId );
		
	};
	
}

#endif