/*
 *  RGBTagSet.h
 *  ObjectCube
 *
 */

#ifndef ObjectCube_RGB_TAG_SET_
#define ObjectCube_RGB_TAG_SET_

#include "TagSet.h"

using namespace std;

namespace ObjectCube
{
	class TagFilter;
	
	class RGBTagSet : public TagSet
	{
	public:
		
		//Constructors
		RGBTagSet();
		RGBTagSet( const string& name );
		RGBTagSet( const string& name, const string& description );
		
		RGBTagSet* create();
		
		const RGBTag* /*const*/ getRGBTag( string name ) const; //Const removed due to boost python limitation
		
		virtual const Tag* /*const*/ fetchOrAddTag( const string& value );
	protected:
		virtual void fetch_( int id ); 
		virtual TagSet* createImp_();  //Public interface, protected virtual pattern
	
	private: //Helper functions
		void init_();
		
		//DEBUG!!!
		friend class DebugTest;
	
	};
}

#endif