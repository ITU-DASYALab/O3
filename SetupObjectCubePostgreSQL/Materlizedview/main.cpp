#include <iostream>
#include <sstream>
#include <fstream>
#include <pqxx/pqxx> 

using namespace std;
using namespace pqxx;

connection* connection_;
nontransaction* trans_;
bool connected_ = true;

//____________________________________________________________________________________________________________________________________________________________________________________

void executeSQL( const string& sql )
{
	const char* sqlPointer = sql.c_str();
	trans_->exec(sqlPointer);
}

//____________________________________________________________________________________________________________________________________________________________________________________

void connectToDb_()
{
	connection_ = new connection("dbname = objectcube user = object password = object hostaddr = 127.0.0.1 port = 5432");
	trans_ = new nontransaction(*connection_);
}

//____________________________________________________________________________________________________________________________________________________________________________________

void insertDB()
{
	cout << "Start" << endl;
	executeSQL("refresh materialized view alphanumerical_tag_materialized_view ;");
	cout << "End" << endl;
}

int main() {
	
   try {
	connectToDb_();
	insertDB();
	return 1;
	
   } catch (const std::exception &e) {
      cerr << e.what() << std::endl;
      return 1;
   }
}


