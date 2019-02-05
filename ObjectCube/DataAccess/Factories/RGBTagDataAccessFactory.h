/*
 *  RGBTagDataAccessFactory.h
 *  ObjectCube
 *
 */

#ifndef ObjectCube_RGB_TAG_DATA_ACCESS_FACTORY_
#define ObjectCube_RGB_TAG_DATA_ACCESS_FACTORY_

namespace ObjectCube
{
	class RGBTagDataAccess;
	
	class RGBTagDataAccessFactory
	{
	public:
		static RGBTagDataAccess* create();
	};
	
}

#endif