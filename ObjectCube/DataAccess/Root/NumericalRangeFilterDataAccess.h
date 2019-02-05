/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/


#ifndef ObjectCube_NUMERICAL_RANGE_FILTER_DATA_ACCESS_
#define ObjectCube_NUMERICAL_RANGE_FILTER_DATA_ACCESS_

#include "../Root/FilterDataAccess.h"

namespace ObjectCube 
{	
	class NumericalRangeFilterDataAccess : public FilterDataAccess
	{
	public:
		//Constructors
		NumericalRangeFilterDataAccess();
		virtual ~NumericalRangeFilterDataAccess();
		
		//Get/Set
		long getNumberFrom() const { return numberFrom_; }
		long getNumberTo() const { return numberTo_; }
		void setNumberFrom( long numberFrom );
		void setNumberTo( long numberTo );
		
	protected:
		virtual string getSelectionPredicate_();
		virtual string getFiltrationPredicate_();
			
	protected:
		long numberFrom_;
		long numberTo_;
		
		// There are no illegal values so we need null checking using other variables
		bool numberFromIsNull_;
		bool numberToIsNull_;
		
		friend class NumericalRangeFilterConverter;
		
	};
	
}

#endif