/*
 *  AlphanumericalTagSet.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 25.10.2009.
 *  Copyright 2009 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_ALPHANUMERICAL_TAG_SET_
#define ObjectCube_ALPHANUMERICAL_TAG_SET_

#include "TagSet.h"

using namespace std;

namespace ObjectCube
{
	class TagFilter;
	
	class AlphanumericalTagSet : public TagSet
	{
	public:
		
		//Constructors
		AlphanumericalTagSet();
		AlphanumericalTagSet( const string& name );
		AlphanumericalTagSet( const string& name, const string& description );
		
		AlphanumericalTagSet* create();
		
		const AlphanumericalTag* /*const*/ getAlphanumericalTag( string name ) const; //Const removed due to boost python limitation
		
		virtual const Tag* /*const*/ fetchOrAddTag( const string& value );
	protected:
		virtual void fetch_( int id ); 
		virtual TagSet* createImp_();  //Public interface, protected virtual pattern
	
	private: //Helper functions
		void init_();
		
		//For unit tests
		friend class AlphanumericalTagSetTest;
		//DEBUG!!!
		friend class DebugTest;
	
	};
}

#endif