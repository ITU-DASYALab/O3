/*
 *  Language.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 8.7.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_LANGUAGE_
#define ObjectCube_LANGUAGE_

#include "LayerShared/LanguageCommon.h"

using namespace std;

namespace ObjectCube
{	

	class Language : public LanguageCommon
	{
	public:
		static const string asString( const string& entityName, int entityId );
	
	};
	
}

#endif