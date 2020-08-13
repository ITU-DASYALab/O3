/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/


#ifndef ObjectCube_OBJECTTAG_
#define ObjectCube_OBJECTTAG_

#ifdef __APPLE__
#include <memory>
using std::shared_ptr;
#else
#include <tr1/memory>
using std::shared_ptr;
#endif

#include "Boundaries/BoundingBox.h"

using namespace std;

namespace ObjectCube 
{
	class Tag;
	class BoundingBox;
	
	class ObjectTag
	{
	public:
		//Constructors
		ObjectTag( Tag* tag );
		ObjectTag( const Tag* tag );
		ObjectTag( Tag* tag, BoundingBox boundingBox );
		ObjectTag( const Tag* tag, BoundingBox boundingBox );
	
		//Copy constructor
		ObjectTag( const ObjectTag& objectTag );
		
		~ObjectTag();
		
		void confirmTagging();
		
		//Get
		const Tag* getTag() const { return tag_; }
		bool getConfirmed() const { return confirmed_; }
		BoundingBox getBoundingBox() const;
		
		//Set
		void setBoundingBox( const BoundingBox& boundingBox ) { boundingBox_ = boundingBox; }
		void setConfirmed( bool confirmed ) { confirmed_ = confirmed; }
		
		bool operator()( const ObjectTag& x ) const;
		bool operator==( const ObjectTag& x ) const;
		bool operator!=( ObjectTag const& x ) const; 
		bool operator < ( const ObjectTag& x ) const;
		
		ObjectTag& operator=( const ObjectTag& objectTag );
		
	protected:
		int getObjectId_() const { return objectId_; }
		void setObjectId_( int objectId ) { objectId_ = objectId; }
		
	private:
		Tag* tag_;
		int objectId_;
		bool confirmed_;
		BoundingBox boundingBox_;
		
		void cleanup_();
		void copyValues_( const ObjectTag& objectTag );
	
		friend class ObjectTagConverter;
		friend class Object;
	};

}

#endif

