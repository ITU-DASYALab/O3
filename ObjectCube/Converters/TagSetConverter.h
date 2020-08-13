/*
 *  TagSetConverter.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 9.2.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_TAG_SET_CONVERTER_
#define ObjectCube_TAG_SET_CONVERTER_

#ifdef __APPLE__
#include <memory>
using std::shared_ptr;
#else
#include <tr1/memory>
using std::shared_ptr;
#endif

#include <vector>
#include "../TagSet/TagSet.h"

namespace ObjectCube 
{
	class TagSetDataAccess;
	
	class TagSetConverter
	{
	public:
		static std::shared_ptr<TagSet> dataAccessToLogic( TagSetDataAccess* tagSetDA );
		static TagSetDataAccess* logicToDataAccess( const TagSet* dimension );
		
		static vector<std::shared_ptr<TagSet> > dataAccessToLogic( vector<TagSetDataAccess*> dimensionsDA );
		static vector<TagSetDataAccess*> logicToDataAccess( const vector<TagSet*>& dimensions );
				
	};
}

#endif