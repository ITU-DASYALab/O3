/*
 *  AlphanumericalTag.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 20.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_ALPHANUMERICAL_TAG_
#define ObjectCube_ALPHANUMERICAL_TAG_

#include <string>

#include "Tag.h"

using namespace std;

namespace ObjectCube
{	
	class AlphanumericalTag : public Tag
	{
		friend class TagSet;
		friend class AlphanumericalTagConverter;
	public:
		//Constructors & Destructor
		AlphanumericalTag();
		AlphanumericalTag( const string& name );
		
		virtual ~AlphanumericalTag();
		
		//Functions
		static AlphanumericalTag* fetch( int id );  //a faster version than the one in Tag
		static AlphanumericalTag* fetch( int tagSetId, const string& name );
		
		//Get/Set
		string getName() const { return name_; }
		void setName( string name );
		
	protected:
		virtual void fetchImp_();
		virtual void create_();  
		virtual void delete_();
		virtual const string valueAsString_() const;
		
	private: //Member functions
		virtual void init_();
		
	private:  //Member variables
		string name_;
		
	public: //Operator overloading
		virtual Tag& operator=( const Tag& tag );
		
		//For unit testing
		//For testing..... this needs refactoring !!!  Consider inheriting all logic classes and implementing public getters and setters for all member variables.
		friend class AlphanumericalTagTest;
		
	
	};

}

#endif