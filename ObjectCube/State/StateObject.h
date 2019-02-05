/*
 *  StateObject.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 17.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_STATE_OBJECT_
#define ObjectCube_STATE_OBJECT_

#include <string>
#include <vector>

#include "StateTag.h"

using namespace std;

namespace ObjectCube 
{	
	class StateObject
	{
		friend class Hub;
		friend class StateObjectConverter;
		
	public:
		//Constructors
		StateObject();
		//Destructor
		~StateObject() {;}
		
		bool hasUserTags();
		bool hasTag( int id ) const;
		const vector<StateTag> getTags( int tagSetId ) const;
		
 		//Get/Set
		int getId() const { return id_; }
		string getName() const { return name_; }
		const vector<StateTag> getTags() const { return tags_; } 
		const StateTag getTag( int id ) const;
		
	protected:
		void setId_( int id ) { id_ = id; }
		void setName_( const string& name ) { name_ = name; }
		void setTags_( const vector<StateTag>& tags ) { tags_ = tags; }
	private:
		void init_();
		
	private: 
		//Variables
		int id_;
		string name_;
		vector<StateTag> tags_;
		
	public:
		bool operator==( StateObject const& x) const { return this->getId() == x.getId(); }
		bool operator!=( StateObject const& x) const { return this->getId() != x.getId(); }		
	};
}

#endif
