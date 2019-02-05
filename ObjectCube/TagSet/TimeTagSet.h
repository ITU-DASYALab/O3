/*
 *  TimeTagSet.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 12.4.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_TIME_TAG_SET_
#define ObjectCube_TIME_TAG_SET_

#include "TagSet.h"

using namespace std;

namespace ObjectCube
{
	class TagFilter;
	class TimeTag;
	
	class TimeTagSet : public TagSet
	{
	public:
		//Constructors
		TimeTagSet();
		TimeTagSet( const string& name );
		TimeTagSet( const string& name, const string& description );
		
		TimeTagSet* create();
		
		const TimeTag* /*const*/ getTimeTag( int hours, int minutes, int seconds, int milliseconds ) const; //Const removed due to boost python limitation
		virtual const Tag* /*const*/ fetchOrAddTag( const string& value );
		
	protected:
		virtual void fetch_( int id ); 
		virtual TagSet* createImp_();  //Public interface, protected virtual pattern
		
		virtual void loadVirtualDimensions_();
		
	private: //Helper functions
		void init_();
		
		//For unit tests
		friend class TimeTagSetTest;
		
		
		
	};
}

#endif