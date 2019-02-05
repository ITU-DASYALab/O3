/*
 *  TagSetDataAccess.h
 *  Prada
 *
 *  Created by Grímur Tómasson on 8.2.2010.
 *  Copyright 2010 RU. All rights reserved.
 *
 */

#ifndef ObjectCube_TAG_SET_DATA_ACCESS_
#define ObjectCube_TAG_SET_DATA_ACCESS_

#include <string>
#include <vector>

#include "../../LayerShared/TagSetCommon.h"

using namespace std;

namespace ObjectCube
{
	class TagDataAccess;
	
	class TagSetDataAccess : public TagSetCommon
	{
	public:
		TagSetDataAccess();
		virtual ~TagSetDataAccess();
		
		virtual TagSetDataAccess* create() = 0;
		virtual TagSetDataAccess* fetch( int id ) = 0;
		virtual vector<int> fetchDimensionIds() = 0;
		virtual void erase() = 0;
	protected:
		virtual vector<TagDataAccess*> fetchTags_() = 0;
		
	public:
		int getId() const { return id_; }
		string getName() const { return name_; }
		string getDescription() const { return description_; }
		int getTypeId() const { return typeId_; }
		int getAccessId() const { return accessId_; }
		vector<TagDataAccess*> getTags() const { return tags_; }
		
		void setId( int id ) { id_ = id; }
		void setName( const string& name ) { name_ = name; }
		void setDescription( const string& description ) { description_ = description; }
		void setTypeId( int typeId) { typeId_ = typeId; }
		void setAccessId( int accessId ) { accessId_ = accessId; }
		void setTags( vector<TagDataAccess*> tags ) { tags_ = tags; }
	
	protected:
		int id_;
		string name_;
		string description_;
		int typeId_;
		int accessId_;
		vector<TagDataAccess*> tags_;
		
	};
	
}

#endif