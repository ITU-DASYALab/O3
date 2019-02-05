/*
 *  AlphanumericalTagDataAccess.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 22.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_ALPHANUMERICAL_TAG_DATA_ACCESS_
#define ObjectCube_ALPHANUMERICAL_TAG_DATA_ACCESS_

#include "TagDataAccess.h"
#include <string>


using namespace std;

namespace ObjectCube
{
	
	class AlphanumericalTagDataAccess : public TagDataAccess
	{
	public:
		AlphanumericalTagDataAccess();
		virtual ~AlphanumericalTagDataAccess();
		
		virtual TagDataAccess* fetch( int id ) = 0;
		virtual TagDataAccess* create( ) = 0;
		virtual int inUse( int id ) = 0;
		virtual void remove( int id ) = 0;
		
		virtual AlphanumericalTagDataAccess* fetch( int tagSetId, const string& name ) = 0;  //ATH
		
		string getName() const { return name_; }
		void setName( const string& name ) { name_ = name; }
		
	protected:
		string name_;
	};
	
}

#endif