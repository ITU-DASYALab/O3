/*
 *  DateTagSet.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 12.4.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_DATE_TAG_SET_
#define ObjectCube_DATE_TAG_SET_

#include "TagSet.h"

using namespace std;

namespace ObjectCube
{
	class TagFilter;
	class DateTag;
	
	class DateTagSet : public TagSet
	{
	public:
		//Constructors
		DateTagSet();
		DateTagSet( const string& name );
		DateTagSet( const string& name, const string& description );
		
		DateTagSet* create();
		
		const DateTag* /*const*/ getDateTag( int year, int month, int dayOfMonth ) const; //Const removed due to boost python limitation
		virtual const Tag* /*const*/ fetchOrAddTag( const string& value );
		
	protected:
		virtual void fetch_( int id ); 
		virtual TagSet* createImp_();  //Public interface, protected virtual pattern
		
		virtual void loadVirtualDimensions_();
		
	private: //Helper functions
		void init_();
		
		//For unit tests
		friend class DateTagSetTest;
		
		
	};
}

#endif