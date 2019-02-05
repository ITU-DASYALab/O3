/*
 *  RGBTag.h
 *  ObjectCube
 *
 */

#ifndef ObjectCube_RGB_TAG_
#define ObjectCube_RGB_TAG_

#include <string>

#include "Tag.h"

using namespace std;

namespace ObjectCube
{	
	class RGBTag : public Tag
	{
		friend class TagSet;
		friend class RGBTagConverter;
	public:
		//Constructors & Destructor
		RGBTag();
		RGBTag( const string& name );
		
		virtual ~RGBTag();
		
		//Functions
		static RGBTag* fetch( int id );  //a faster version than the one in Tag
		static RGBTag* fetch( int tagSetId, const string& name );
		
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
		//friend class AlphanumericalTagTest;
		
	
	};

}

#endif