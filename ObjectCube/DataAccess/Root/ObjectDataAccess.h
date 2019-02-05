/*
 *  ObjectDataAccess.h
 *  Prada
 *
 *  Created by Grímur Tómasson on 6.2.2010.
 *  Copyright 2010 RU. All rights reserved.
 *
 */

#ifndef ObjectCube_OBJECT_DATA_ACCESS_
#define ObjectCube_OBJECT_DATA_ACCESS_

#include <string>
#include <vector>

#include "ObjectTagDataAccess.h"

using namespace std;

namespace ObjectCube
{	
	class TagDataAccess;
	
	class ObjectDataAccess
	{
	public:
		ObjectDataAccess();
		virtual ~ObjectDataAccess();
		
		virtual ObjectDataAccess* fetch( int id ) = 0;
		virtual ObjectDataAccess* fetch( const string& qualifiedName ) = 0;
		virtual ObjectDataAccess* create() = 0;
		virtual void update() = 0;
		virtual void erase() = 0;
		virtual void updateFileTypeFromPluginResult() = 0;
		
		virtual void addTag( ObjectTagDataAccess* objectTag ) = 0;
		
		virtual void removeTag( ObjectTagDataAccess* objectTag ) = 0;
		virtual vector<ObjectDataAccess*> fetchAllObjects() = 0;
	protected:
		virtual vector<ObjectTagDataAccess*> fetchTagInfo_( int objectId ) = 0;
		
	public:
		int getId() const { return id_; }
		string getName() const { return name_; }
		string getThumbnail() const  { return thumbnail_; }
		string getFileType() const { return fileType_; }
		vector<ObjectTagDataAccess*>& getTagInfo() { return objectTags_; } 

		void setId( int id ) { id_ = id; }
		void setName( const string& name ) { name_ = name; }
		void setThumbnail ( const string& thumbnail ) { thumbnail_ = thumbnail; }
		void setFileType ( const string& fileType ) { fileType_ = fileType; }
		void setTagInfo( vector<ObjectTagDataAccess*> tagInfo ) { objectTags_ = tagInfo; }

	protected: 
		int id_;
		string name_;
		string thumbnail_;
		string fileType_;
		vector<ObjectTagDataAccess*> objectTags_;
	};
	
}

#endif
