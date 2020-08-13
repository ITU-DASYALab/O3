/*
 *  NumericalTagConverter.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 27.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_NUMERICAL_TAG_CONVERTER_
#define ObjectCube_NUMERICAL_TAG_CONVERTER_

#include <memory>

#include "TagConverter.h"

namespace ObjectCube 
{	
	class NumericalTagDataAccess;
	
	class NumericalTagConverter : public TagConverter
	{
	protected:
		virtual std::shared_ptr<Tag> dataAccessToLogic_( const TagDataAccess* tagDA );
		virtual unique_ptr<TagDataAccess> logicToDataAccess_( const Tag* tag );
		
	};
}

#endif