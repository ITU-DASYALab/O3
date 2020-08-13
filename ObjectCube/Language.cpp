/*
 *  Language.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 8.7.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "Language.h"

#include <memory>

#include "DataAccess/Root/LanguageDataAccess.h"
#include "DataAccess/Factories/LanguageDataAccessFactory.h"

using namespace ObjectCube;


//____________________________________________________________________________________________________________________________________________________________________________________

const string Language::asString( const string& entityName, int entityId )
{
	unique_ptr<LanguageDataAccess> dataAccess( LanguageDataAccessFactory::create() );
	//There is no converter, this is a simple utility function as of yet
	return dataAccess->getTranslatedText( entityName, entityId, getLanguageId_() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

