/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/

#ifndef ObjectCube_TAG_FILTER_DATA_ACCESS_
#define ObjectCube_TAG_FILTER_DATA_ACCESS_

#include "FilterDataAccess.h"

namespace ObjectCube 
{
	
	class TagFilterDataAccess : public FilterDataAccess
	{
	public:
		//Constructors
		TagFilterDataAccess();
		virtual ~TagFilterDataAccess();
		
		//Get/Set
		int getTagId() const { return tagId_; } 
		void setTagId( int tagId );
		
	protected:
		virtual string getSelectionPredicate_();
		virtual string getFiltrationPredicate_();
		
	protected:
		int tagId_;
		
	};
	
}

#endif