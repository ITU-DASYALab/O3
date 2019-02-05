/*
 *  HubDataAccess.h
 *  Prada
 *
 *  Created by Grímur Tómasson on 8.2.2010.
 *  Copyright 2010 RU. All rights reserved.
 *
 */

#ifndef ObjectCube_HUB_DATA_ACCESS_
#define ObjectCube_HUB_DATA_ACCESS_

#include <vector>

#include "StateObjectDataAccess.h"
#include "TagSetDataAccess.h"
#include "StateDataAccess.h"

using namespace std;

namespace ObjectCube
{
	class ObjectDataAccess;
	class TagSetDataAccess;
	class FilterDataAccess;
	
	class HubDataAccess
	{
	public:
		HubDataAccess();
		virtual ~HubDataAccess();
		
		//Obsolete, remove
		virtual vector<StateObjectDataAccess*> getObjects( const string& select ) = 0;
		virtual vector<StateObjectDataAccess*> getObjects( const vector<FilterDataAccess*>& filters  ) = 0;
		
		virtual StateDataAccess getState( const string& select ) = 0;
		virtual StateDataAccess getState( const vector<FilterDataAccess*>& filters  ) = 0;

		virtual unsigned int getObjectCount() = 0;

		virtual vector<TagSetDataAccess*> getTagSets() = 0;
		
		virtual void disconnect() = 0;
		
		virtual void refreshMaterializedViews() {;}
		
		string getObjectsQueryAsString() { return getObjectsQueryAsString_; }
		
	protected:
		void setObjectQueryAsString( const string& query ) { getObjectsQueryAsString_ = query; }
		
	private:
		string getObjectsQueryAsString_;
	};
	
}

#endif
