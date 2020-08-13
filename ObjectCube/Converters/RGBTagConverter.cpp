/*
 *  RGBTagConverter.cpp
 *  ObjectCube
 */

#include "RGBTagConverter.h"

#include "../Tag/RGBTag.h"
#include "../DataAccess/Root/RGBTagDataAccess.h"
#include "../DataAccess/Factories/RGBTagDataAccessFactory.h"
#include "TagConverter.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

std::shared_ptr<Tag> RGBTagConverter::dataAccessToLogic_( const TagDataAccess* tagDA )
{
	std::shared_ptr<Tag> tag( TagConverter::dataAccessToLogic_( tagDA ) );
	RGBTag* aTag = dynamic_cast<RGBTag*>( tag.get() );
	
	const RGBTagDataAccess* aTagDA = dynamic_cast<const RGBTagDataAccess*>( tagDA );
	if( aTagDA != 0 )  //To support reading only base type info (tag-set loading mechanism)
	{
		aTag->setName( aTagDA->getName() );
	}
	
	return tag ;
}
//____________________________________________________________________________________________________________________________________________________________________________________

unique_ptr<TagDataAccess> RGBTagConverter::logicToDataAccess_( const Tag* tag )
{
	unique_ptr<TagDataAccess> tagDA(TagConverter::logicToDataAccess_( tag ) );
	RGBTagDataAccess* aTagDA = dynamic_cast<RGBTagDataAccess*>( tagDA.get() );
	
	aTagDA->setName( dynamic_cast<const RGBTag*>( tag )->getName() );
	
	return tagDA;
}
//____________________________________________________________________________________________________________________________________________________________________________________
