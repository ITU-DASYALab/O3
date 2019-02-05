/*
 *  Filter.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 6.11.2009.
 *  Copyright 2009 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_FILTER_
#define ObjectCube_FILTER_

#include <string>
#include "../LayerShared/FilterCommon.h"

using namespace std;

namespace ObjectCube 
{
	//Base class for all types of photo filters
	class Filter : public FilterCommon
	{
	public:
		
		Filter();
		Filter( int tagSetId );
		virtual ~Filter();
		
		//Get/Set
		int getId() const { return id_; }
		int getTypeId() const { return typeId_; }  
		int getTagSetId() const { return tagSetId_; }
		string getSelectionPredicate();
		string getFiltrationPredicate();
		bool isNull() const { return isNull_; }
		
		const string typeAsString() const;
		static const string typeAsString( int filterTypeId );
		
		virtual void fillInAndValidateValues();
		
		//Operator overloading
		virtual Filter& operator=( const Filter& filter ) = 0;
		virtual bool operator==( const Filter& filter );
		virtual bool operator==( const Filter* /*const*/ filter );
		
	protected:
		void setId_( int id ) { id_ = id; }
		void setTypeId_( int typeId ) { typeId_ = typeId; }
		void setTagSetId_( int tagSetId ) { tagSetId_ = tagSetId; }
		void assignValues_( const Filter& filter );
		void setNullStatus_( bool isNull ) { isNull_ = isNull; }

	private: //Functions
		void init_();
		
	private:  //Variables
		int id_;
		int typeId_;
		int tagSetId_;
		bool isNull_;
		
		static int idCounter_;
	};
	
}

#endif
