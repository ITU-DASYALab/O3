/*
* Snorri Gíslason - 2018
*/


#if !defined(ObjectCube_DATE_RANGE_FILTER_POSTGRESQL_) && defined(OC_POSTGRESQL)
//#ifndef ObjectCube_DATE_RANGE_FILTER_POSTGRESQL_
#define ObjectCube_DATE_RANGE_FILTER_POSTGRESQL_

#include "../Root/DateRangeFilterDataAccess.h"

namespace ObjectCube 
{	
	class DateRangeFilterPostgreSQL : public DateRangeFilterDataAccess
	{
	public:
		DateRangeFilterPostgreSQL() {;} 
		virtual ~DateRangeFilterPostgreSQL() {;}
		
	protected:
		virtual string getSelectionPredicate_();
		virtual string getFiltrationPredicate_();
		
	private:
		string getSelectionPostfix_();
		
	};
	
}

#endif