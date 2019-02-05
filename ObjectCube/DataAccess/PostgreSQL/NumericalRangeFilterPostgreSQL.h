/*
* Snorri Gíslason - 2018
*/



#if !defined(ObjectCube_NUMERICAL_RANGE_FILTER_POSTGRESQL_) && defined(OC_POSTGRESQL)
//#ifndef ObjectCube_NUMERICAL_RANGE_FILTER_POSTGRESQL_
#define ObjectCube_NUMERICAL_RANGE_FILTER_POSTGRESQL_

#include "../Root/NumericalRangeFilterDataAccess.h"

namespace ObjectCube 
{	
	class NumericalRangeFilterPostgreSQL : public NumericalRangeFilterDataAccess
	{
	public:
		//Constructors
		NumericalRangeFilterPostgreSQL() {;}
		virtual ~NumericalRangeFilterPostgreSQL() {;}
		
	protected:
		virtual string getSelectionPredicate_();
		virtual string getFiltrationPredicate_();
		
	private:
		string getSelectionPostfix_();
		
	};
	
}

#endif