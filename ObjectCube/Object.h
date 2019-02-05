/*
 *  Photo.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 25.10.2009.
 *  Copyright 2009 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_OBJECT_
#define ObjectCube_OBJECT_

#include <string>
#include <vector>

#include "ObjectTag.h"

using namespace std;

namespace ObjectCube 
{
	class Tag;
	
	class Object
	{
		friend class ObjectConverter;
		friend class Hub;
		
	public:
		//Constructors
		Object();
		Object( const string& path );
		//Destructor
		~Object();
		
		//Public interface
		Object& create();
		Object& create( const string& path );
		
		static Object fetch( int id );
		static Object fetch( const string& qualifiedName );
		
		void update();
		void erase();
		
		void addTag( ObjectTag& tag );
		void removeTag( ObjectTag& tag );
        void updateTagging( ObjectTag& tagging, const Tag* tag );
        
        void pluginProcess();
		
		//A part of a public interface?  It is at least harmless.
		bool hasUserTags();
		bool hasTag( int id );
		
 		//Get/Set
		int getId() const { return id_; }
		string getName() const { return name_; }
		string getThumbnail() const { return thumbnail_; }
		string getFileType() const { return fileType_; }
		const vector<ObjectTag> getTags() const { return tags_; } 
		const ObjectTag getTag( int id ) const; 
		
		void setName( const string& name ) { name_ = name; }
		void setThumbnail (const string& thumbnail ) { thumbnail_ = thumbnail; }
		void setFileType ( const string& fileType ) { fileType_ = fileType; }

	protected:
		void setId_( int id ) { id_ = id; }
		void setTags_( const vector<ObjectTag>& tags ) { tags_ = tags; }
	private:
		void init_();
		void validateCreate_();
		void updateFileType();
		
	private: 
		//Variables
		int id_;
		string name_;
		string thumbnail_;
		string fileType_;
		vector<ObjectTag> tags_;
		
	public:
		//Boost Python support
		bool operator==( Object const& x) const { return this->getId() == x.getId(); }
		bool operator!=( Object const& x) const { return this->getId() != x.getId(); }		
		
		//For unit testing
		friend class ObjectTest;
	};
}

#endif


