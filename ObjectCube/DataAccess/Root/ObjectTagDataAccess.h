/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/


#ifndef ObjectCube_OBJECT_TAG_DATA_ACCESS_
#define ObjectCube_OBJECT_TAG_DATA_ACCESS_

namespace ObjectCube 
{
	class BoundingBoxDataAccess;
	
	class ObjectTagDataAccess
	{
	public:

		ObjectTagDataAccess();
		ObjectTagDataAccess( const ObjectTagDataAccess& objectTag ); //Copy constructor
		ObjectTagDataAccess& operator=( const ObjectTagDataAccess& objectTag );
		
		virtual ~ObjectTagDataAccess();
		
		virtual void create() = 0;
		virtual void erase() = 0;
		virtual void modify() = 0;
		
		//Get
		int getTagId() const { return tagId_; }
		int getObjectId() const { return objectId_; }
		bool getConfirmed() const { return confirmed_; }
		BoundingBoxDataAccess* getBoundingBox() const;
		
		bool hasBoundingBox() const;
		
		void setTagId( int tagId ) { tagId_ = tagId; }
		void setObjectId( int objectId ) { objectId_ = objectId; }
		void setConfirmed( bool confirmed ) { confirmed_ = confirmed; }
		void setBoundingBox( BoundingBoxDataAccess* boundingBox ) { boundingBox_ = boundingBox; }
		
	private:
		int tagId_;
		int objectId_;
		bool confirmed_;
		BoundingBoxDataAccess* boundingBox_;
		
		void cleanup_();
		void copyValues_( const ObjectTagDataAccess& objectTag );
		
	};
	
}

#endif
