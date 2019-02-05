/*
 *  TagFilter.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 6.11.2009.
 *  Copyright 2009 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_TAG_FILTER_
#define ObjectCube_TAG_FILTER_

#include "Filter.h"

namespace ObjectCube 
{
	class Tag;
	
	class TagFilter : public Filter
	{
	public:
		//Constructors
		TagFilter( const Tag* /*const*/ tag, int tagSetId );
		virtual ~TagFilter();
		
		//Get/Set
		int getTagId() const { return tagId_; } 
		
		//Operator overloading
		virtual Filter& operator=( const Filter& filter );
		
	protected:
		void setTagId_( int tagId );
		//Constructor, only for factory use
		TagFilter();
		
	private:
		void init_();
		string getSelectionPostfix_();
		
	protected:
		int tagId_;
		
		friend class FilterFactory;
	};
	
}

#endif