/*
 *  Search.h
 *  ObjectCube
 */


#include <vector>

#ifdef __APPLE__
#include <memory>
#else
#include <tr1/memory>
#endif

#include <sstream>
#include <fstream>
#include <iostream>
#include <pqxx/pqxx> 
using namespace pqxx;
using namespace std;

namespace ObjectCube 
{
	class Search 
	{
	public:
		void searchString();
	protected:
		Search();
	private:
		int processSearchResult();
	
	};
}