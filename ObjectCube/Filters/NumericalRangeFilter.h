/*
 *  NumericalRangeFilter.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 1.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_NUMERICAL_RANGE_FILTER_
#define ObjectCube_NUMERICAL_RANGE_FILTER_

#include "Filter.h"

namespace ObjectCube 
{	
	class NumericalRangeFilter : public Filter
	{
	public:
		//Constructors
		NumericalRangeFilter( long numberFrom, long numberTo, int tagSetId );
		virtual ~NumericalRangeFilter();
		
		//Get/Set
		long getNumberFrom() const { return numberFrom_; }
		long getNumberTo() const { return numberTo_; }
		
		//Operator overloading
		virtual Filter& operator=( const Filter& filter );
		
	protected:
		void setNumberFrom_( long numberFrom );
		void setNumberTo_( long numberTo );
		
		//Constructor for factory
		NumericalRangeFilter();
		
	private:
		void init_();
		
	protected:
		long numberFrom_;
		long numberTo_;
		
		// There are no illegal values so we need null checking using other variables
		bool numberFromIsNull_;
		bool numberToIsNull_;
		
		
		friend class FilterFactory;
		friend class NumericalRangeFilterConverter;
	};
	
}

#endif