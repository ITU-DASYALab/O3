/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/
#ifndef ObjectCube_STATE_DATA_ACCESS_
#define ObjectCube_STATE_DATA_ACCESS_

#include <string>
#include <vector>
#include <map>

#include "StateObjectDataAccess.h"

using namespace std;

namespace ObjectCube
{	
	class StateDataAccess
	{
	public:
		StateDataAccess();
		virtual ~StateDataAccess();
	
		vector<StateObjectDataAccess*>& getObjects() { return objects_; }
		map<int, map<int, vector<int> > >& getHierarchyNodeObjectIds() { return filterIdNodeIdObjectIds_; }
		
		void setObjects( const vector<StateObjectDataAccess*>& objects ) { objects_ = objects; }
		void setFilterIdNodeIdObjectsIds( const map<int, map<int, vector<int> > >& ids ) { filterIdNodeIdObjectIds_ = ids; }
				
	protected: 
		vector<StateObjectDataAccess*> objects_;
		map<int, map<int, vector<int> > > filterIdNodeIdObjectIds_;  //Used to add object_id's to hierarchies efficiently
	};
	
}

#endif