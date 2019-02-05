/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/

#ifndef ObjectCube_FILTER_DATA_ACCESS_
#define ObjectCube_FILTER_DATA_ACCESS_

#include <string>

using namespace std;

namespace ObjectCube 
{
	//Base class for all types of photo filters
	class FilterDataAccess
	{
	public:
		
		FilterDataAccess();
		virtual ~FilterDataAccess();
		
		//Get/Set
		int getId() const { return id_; }
		int getTypeId() const { return typeId_; }  
		int getTagSetId() const { return tagSetId_; }
		string getSelectionPredicate();
		string getFiltrationPredicate();
		bool isNull() const { return isNull_; }
		
		void setId( int id ) { id_ = id; }
		void setTypeId( int typeId ) { typeId_ = typeId; }
		void setTagSetId( int tagSetId ) { tagSetId_ = tagSetId; }
		void setNullStatus( bool isNull ) { isNull_ = isNull; }
		
		virtual string getSelectionPredicate_() = 0;
		virtual string getFiltrationPredicate_() = 0;
		
	private:  //Variables
		int id_;
		int typeId_;
		int tagSetId_;
		bool isNull_;
		
	};
	
}

#endif