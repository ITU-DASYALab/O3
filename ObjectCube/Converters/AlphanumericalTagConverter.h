/*
 *  AlphanumericalTagConverter.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 23.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_ALPHANUMERICAL_TAG_CONVERTER_
#define ObjectCube_ALPHANUMERICAL_TAG_CONVERTER_

#ifdef __APPLE__
#include <memory>
using std::shared_ptr;
#else
#include <tr1/memory>
using std::shared_ptr;
#endif

#include "TagConverter.h"

using namespace std;

namespace ObjectCube 
{	
	class AlphanumericalTagDataAccess;
	
	class AlphanumericalTagConverter : public TagConverter
	{
	protected:
	        virtual std::shared_ptr<Tag> dataAccessToLogic_( const TagDataAccess* tagDA );
		virtual unique_ptr<TagDataAccess> logicToDataAccess_( const Tag* tag );
		
	};
}

#endif
