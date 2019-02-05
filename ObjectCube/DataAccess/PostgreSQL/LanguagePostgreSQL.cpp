/*
* Snorri Gíslason - 2018
*/

#ifdef OC_POSTGRESQL

#include "LanguagePostgreSQL.h"

#include <sstream>
#include <memory>

#include "CommonPostgreSQL.h"
#include "../../LayerShared/Exception.h"

using namespace ObjectCube;
using namespace std;


//____________________________________________________________________________________________________________________________________________________________________________________

const string LanguagePostgreSQL::getTranslatedText( const string& entityName, int entityType, int languageId )
{
	CommonPostgreSQL db;

	stringstream stringStream;
	stringStream << "select translated_text from translation where entity_name = '" << entityName << "' and entity_id = "<< entityType << "and language_id = " << languageId;
	string sql = stringStream.str();
	
	pqxx::result resultsHandle = db.executeSQL( sql );

	if( resultsHandle.empty() )
	{
		stringstream stringStream;
		stringStream << "No text was found for entityName = " << entityName << ", entityType = " << entityType << ", languageId = " << languageId << endl;
		throw Exception( "LanguageMonetDB::getTranslatedText", stringStream.str() );
	}

	string translated = resultsHandle[0][0].as<string>();
	
	return translated;
}
//____________________________________________________________________________________________________________________________________________________________________________________


#endif