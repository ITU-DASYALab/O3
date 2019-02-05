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
	std::ifstream t("databasePostgreSQL.txt");
	std::stringstream buffer;
	buffer << t.rdbuf();
	string sql = buffer.str();
	
	cout << "Start" << endl;
	executeSQL(sql);
	cout << "End" << endl;
}

void insertPlugin()
{
	std::ifstream t("insertPlugin.txt");
	std::stringstream buffer;
	buffer << t.rdbuf();
	string sql = buffer.str();
	
	cout << "Start" << endl;
	executeSQL(sql);
	cout << "End" << endl;
}

int main() {
	
   try {
	connectToDb_();
	insertDB();
	insertPlugin();
	return 1;
	
   } catch (const std::exception &e) {
      cerr << e.what() << std::endl;
      return 1;
   }
}


