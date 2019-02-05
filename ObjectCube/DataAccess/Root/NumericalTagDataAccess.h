/*
 *  NumericalTagDataAccess.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 27.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_NUMERICAL_TAG_DATA_ACCESS_
#define ObjectCube_NUMERICAL_TAG_DATA_ACCESS_

#include "TagDataAccess.h"
#include <string>


using namespace std;

namespace ObjectCube
{
	
	class NumericalTagDataAccess : public TagDataAccess
	{
	public:
		NumericalTagDataAccess();
		virtual ~NumericalTagDataAccess();
		
		virtual TagDataAccess* fetch( int id ) = 0;
		virtual TagDataAccess* create( ) = 0;
		virtual int inUse( int id ) = 0;
		virtual void remove( int id ) = 0;
		
		virtual NumericalTagDataAccess* fetch( int tagSetId, long number ) = 0;  //ATH
		
		long getNumber() const { return number_; }
		void setNumber( long number ) { number_ = number; }
		
	protected:
		long number_;
	};
	
}

#endif