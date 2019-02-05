/*
 *  NumericalTag.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 27.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_NUMERICAL_TAG_
#define ObjectCube_NUMERICAL_TAG_

#include <string>

#include "Tag.h"

using namespace std;

namespace ObjectCube
{	
	class NumericalTag : public Tag
	{
		friend class TagSet;
		friend class NumericalTagConverter;
	public:
		//Constructors & Destructor
		NumericalTag();
		NumericalTag( long number );
		
		virtual ~NumericalTag();
		
		//Functions
		static NumericalTag* fetch( int id );  //a faster version than the one in Tag
		static NumericalTag* fetch( int tagSetId, long number );
		
		//Get/Set
		long getNumber() const { return number_; }
		void setNumber( long number ) { number_ = number; setNull_( false ); }
		bool isNull() const { return isNull_; } //Has the number been set?
		
	protected:
		virtual void fetchImp_();
		virtual void create_();  
		virtual void delete_();
		virtual const string valueAsString_() const;
		
	private: //Member functions
		virtual void init_();
		void setNull_( bool value ) { isNull_ = value; }
		
	private:  //Member variables
		long number_;
		bool isNull_;
		
	public: //Operator overloading
		virtual Tag& operator=( const Tag& tag );
		
		//For unit testing
		//For testing..... this needs refactoring !!!  Consider inheriting all logic classes and implementing public getters and setters for all member variables.
		friend class NumericalTagTest;
		
	};
	
}

#endif