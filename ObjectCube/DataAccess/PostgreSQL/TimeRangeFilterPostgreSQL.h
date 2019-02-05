/*
* Snorri Gíslason - 2018
*/


#if !defined(ObjectCube_TIME_RANGE_FILTER_POSTGRESQL_) && defined(OC_POSTGRESQL)
//#ifndef ObjectCube_TIME_RANGE_FILTER_POSTGRESQL_
#define ObjectCube_TIME_RANGE_FILTER_POSTGRESQL_

#include "../Root/TimeRangeFilterDataAccess.h"

namespace ObjectCube 
{	
	
	class TimeRangeFilterPostgreSQL : public TimeRangeFilterDataAccess
	{
	public:
		//Constructors 
		TimeRangeFilterPostgreSQL() {;}
		virtual ~TimeRangeFilterPostgreSQL() {;}
		
	protected:
		virtual string getSelectionPredicate_();
		virtual string getFiltrationPredicate_();
		
	private:
		string getSelectionPostfix_();
		
	};
	
}

#endif