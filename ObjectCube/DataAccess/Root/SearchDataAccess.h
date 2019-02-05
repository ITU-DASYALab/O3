/*
 *  SearchDataAccess.h
 *
 */

#ifndef ObjectCube_SEARCH_DATA_ACCESS_
#define ObjectCube_SEARCH_DATA_ACCESS_

#include <string>
#include <vector>

using namespace std;

namespace ObjectCube
{	
	class SearchDataAccess
	{
	public:
		SearchDataAccess();
		virtual ~SearchDataAccess() {;}

		virtual vector<int> textSearch() = 0;
		virtual vector<int> rgbSearch() = 0;

		void setName( const string& name ) { name_ = name; }
		
		string getName() const { return name_; }
		

	protected: 
		string name_;
		
	};
	
}

#endif