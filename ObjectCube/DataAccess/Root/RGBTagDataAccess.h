/*
 *  RGBTagDataAccess.h
 *  ObjectCube
 *
 */

#ifndef ObjectCube_RGB_TAG_DATA_ACCESS_
#define ObjectCube_RGB_TAG_DATA_ACCESS_

#include "TagDataAccess.h"
#include <string>


using namespace std;

namespace ObjectCube
{
	
	class RGBTagDataAccess : public TagDataAccess
	{
	public:
		RGBTagDataAccess();
		virtual ~RGBTagDataAccess();
		
		virtual TagDataAccess* fetch( int id ) = 0;
		virtual TagDataAccess* create( ) = 0;
		virtual int inUse( int id ) = 0;
		virtual void remove( int id ) = 0;
		
		virtual RGBTagDataAccess* fetch( int tagSetId, const string& name ) = 0;  //ATH
		
		string getName() const { return name_; }
		void setName( const string& name ) { name_ = name; }
		
	protected:
		string name_;
	};
	
}

#endif