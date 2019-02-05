/*
* Snorri Gíslason - 2018
*/


#if !defined(ObjectCube_LANGUAGE_POSTGRESQL_) && defined(OC_POSTGRESQL)
//#ifndef ObjectCube_LANGUAGE_POSTGRESQL_
#define ObjectCube_LANGUAGE_POSTGRESQL_

#include "../Root/LanguageDataAccess.h"

namespace ObjectCube
{
	
	class LanguagePostgreSQL : public LanguageDataAccess
	{
	public:
		const string getTranslatedText( const string& entityName, int entityType, int languageId );
		
	};
	
}

#endif