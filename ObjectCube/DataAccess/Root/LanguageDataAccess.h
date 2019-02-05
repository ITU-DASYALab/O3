/*
 *  LanguageDataAccess.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 8.7.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_LANGUAGE_DATA_ACCESS_
#define ObjectCube_LANGUAGE_DATA_ACCESS_

#include <string>

using namespace std;


namespace ObjectCube
{
	
	class LanguageDataAccess
	{
	public:
		LanguageDataAccess();
		virtual ~LanguageDataAccess();
		
		virtual const string getTranslatedText( const string& entityName, int entityType, int languageId ) = 0;
	
	};
	
}

#endif