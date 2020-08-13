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
using std::shared_ptr;
#endif

#include "../Tag/Tag.h"

namespace ObjectCube 
{	
	class TagDataAccess;
	
	class TagConverter
	{
	public:
		static std::shared_ptr<Tag> dataAccessToLogic( const TagDataAccess* tagDA );
		static unique_ptr<TagDataAccess> logicToDataAccess( const Tag* tag );
		
		static vector<std::shared_ptr<Tag> > dataAccessToLogic( const vector<TagDataAccess*>& tagsDA );
		static vector<TagDataAccess*> logicToDataAccess( const vector<Tag*>& tags );
		
	protected:
		virtual std::shared_ptr<Tag> dataAccessToLogic_( const TagDataAccess* tagDA ) = 0;
		virtual unique_ptr<TagDataAccess> logicToDataAccess_( const Tag* tag ) = 0;
		
	};
}

#endif