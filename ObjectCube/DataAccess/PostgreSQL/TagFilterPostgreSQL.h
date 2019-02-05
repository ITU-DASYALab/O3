/*
* Snorri Gíslason - 2018
*/

#if !defined(ObjectCube_TAG_FILTER_POSTGRESQL_) && defined(OC_POSTGRESQL)
//#ifndef ObjectCube_TAG_FILTER_POSTGRESQL_
#define ObjectCube_TAG_FILTER_POSTGRESQL_

#include "../Root/TagFilterDataAccess.h"

#include <string>

using namespace std;

namespace ObjectCube 
{
	
	class TagFilterPostgreSQL : public TagFilterDataAccess 
	{
	public:
		//Constructors
		TagFilterPostgreSQL() {;}
		virtual ~TagFilterPostgreSQL() {;}
		
	protected:
		virtual string getSelectionPredicate_();
		virtual string getFiltrationPredicate_();
		
	private:
		string getSelectionPostfix_();
		
	};
	
}

#endif