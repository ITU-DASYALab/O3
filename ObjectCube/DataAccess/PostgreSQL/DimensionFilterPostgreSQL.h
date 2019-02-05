/*
* Snorri Gíslason - 2018
*/

#if !defined(ObjectCube_DIMENSION_FILTER_POSTGRESQL_) && defined(OC_POSTGRESQL)
//#ifndef ObjectCube_DIMENSION_FILTER_POSTGRESQL_
#define ObjectCube_DIMENSION_FILTER_POSTGRESQL_

#include "../Root/DimensionFilterDataAccess.h"

#include <map>

namespace ObjectCube 
{
	
	class DimensionFilterPostgreSQL : public DimensionFilterDataAccess
	{
	public:
		//Constructors
		DimensionFilterPostgreSQL() {;}
		virtual ~DimensionFilterPostgreSQL() {;}
		
	protected:
		virtual string getSelectionPredicate_();
		virtual string getFiltrationPredicate_();
		
	private:
		string getSelectionPredicateUnions_();
		string getSelectionPredicateMV_();
		
		string getFiltrationPredicateIn_();
		string getFiltrationPredicateMV_();
		
		static string dimensionFilterVersion2Parameter_;
	};
	
}

#endif