/*
 *  Tag.h
 *  Prada
 *
 *  Created by Grímur Tómasson on 6.2.2010.
 *  Copyright 2010 RU. All rights reserved.
 *
 */

#ifndef ObjectCube_TAG_DATA_ACCESS_
#define ObjectCube_TAG_DATA_ACCESS_

#include <string>

using namespace std;

namespace ObjectCube
{

	class TagDataAccess
	{
	public:
		TagDataAccess();
		virtual ~TagDataAccess() {;}
		
		virtual TagDataAccess* fetch( int id ) = 0;
		virtual TagDataAccess* create( ) = 0;
		virtual int inUse( int id ) = 0;
		virtual void remove( int id ) = 0;
		
		int getId() const { return id_; }  
		int getTypeId() const { return typeId_; }
		int getTagSetId() const { return tagSetId_; }
		
		void setId( int id ) { id_ = id; }
		void setTypeId( int id ) { typeId_ = id; }
		void setTagSetId( int id ) { tagSetId_ = id; }
		
	protected:
		int id_;
		int typeId_;
		int tagSetId_;
	};

}

#endif