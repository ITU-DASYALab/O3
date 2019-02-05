/*
 *  SearchDataAccessFactory.h
 *
 */

#ifndef ObjectCube_SEARCHDATAACCESSFACTORY_
#define ObjectCube_SEARCHDATAACCESSFACTORY_

namespace ObjectCube
{
	class SearchDataAccess;
	
	class SearchDataAccessFactory
	{
	public:
		static SearchDataAccess* create();
	};
	
}

#endif
