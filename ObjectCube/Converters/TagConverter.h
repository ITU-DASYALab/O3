/*
 *  Tag.h
 *  Prada
 *
 *  Created by Grímur Tómasson on 6.2.2010.
 *  Copyright 2010 RU. All rights reserved.
 *
 */

#ifndef ObjectCube_TAG_CONVERTER_
#define ObjectCube_TAG_CONVERTER_

#include <vector>

#ifdef __APPLE__
#include <memory>
using std::shared_ptr;
#else
#include <tr1/memory>
using std::tr1::shared_ptr;
#endif

#include "../Tag/Tag.h"

namespace ObjectCube 
{	
	class TagDataAccess;
	
	class TagConverter
	{
	public:
		static shared_ptr<Tag> dataAccessToLogic( const TagDataAccess* tagDA );
		static auto_ptr<TagDataAccess> logicToDataAccess( const Tag* tag );
		
		static vector<shared_ptr<Tag> > dataAccessToLogic( const vector<TagDataAccess*>& tagsDA );
		static vector<TagDataAccess*> logicToDataAccess( const vector<Tag*>& tags );
		
	protected:
		virtual shared_ptr<Tag> dataAccessToLogic_( const TagDataAccess* tagDA ) = 0;
		virtual auto_ptr<TagDataAccess> logicToDataAccess_( const Tag* tag ) = 0;
		
	};
}

#endif