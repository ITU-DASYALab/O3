/*
 *  StateObjectDataAccess.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 18.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_STATE_OBJECT_DATA_ACCESS_
#define ObjectCube_STATE_OBJECT_DATA_ACCESS_

#include <string>
#include <vector>

#include "StateTagDataAccess.h"

using namespace std;

namespace ObjectCube
{	
	class StateObjectDataAccess
	{
	public:
		StateObjectDataAccess();
		virtual ~StateObjectDataAccess();
	
		int getId() const { return id_; }
		string getName() const { return name_; }
		vector<StateTagDataAccess*>& getTags() { return tags_; } 
		
		void setId( int id ) { id_ = id; }
		void setName( const string& name ) { name_ = name; }
		void setTags( const vector<StateTagDataAccess*>& tags ) { tags_ = tags; }
		
		void addTag( StateTagDataAccess* tag );
		
	private: 
		int id_;
		string name_;
		vector<StateTagDataAccess*> tags_;
		
	};
	
}

#endif