/*
 *  NumericalTagSet.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 27.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_NUMERICAL_TAG_SET_
#define ObjectCube_NUMERICAL_TAG_SET_

#include "TagSet.h"

using namespace std;

namespace ObjectCube
{
	class TagFilter;
	class NumericalTag;
	
	class NumericalTagSet : public TagSet
	{
	public:
		//Constructors
		NumericalTagSet();
		NumericalTagSet( const string& name );
		NumericalTagSet( const string& name, const string& description );
		
		NumericalTagSet* create();
		
		const NumericalTag* /*const*/ getNumericalTag( long number ) const; //Const removed due to boost python limitation
		virtual const Tag* /*const*/ fetchOrAddTag( const string& value );
	protected:
		virtual void fetch_( int id ); 
		virtual TagSet* createImp_();  //Public interface, protected virtual pattern
		
	private: //Helper functions
		void init_();
		
		//For unit tests
		friend class NumericalTagSetTest;
		
		//DEBUG !!!
		friend class DebugTest;
		
	
	};
}

#endif