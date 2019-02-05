#include <iostream>
#include <sstream>
#include <fstream>
#include <pqxx/pqxx> 
#include <algorithm>

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

result executeSQLWithout( const string& sql )
{
	const char* sqlPointer = sql.c_str();
	result r = trans_->exec(sqlPointer);

	return r;	
}

int executeInsertSQL ( const string& sql )
{
	const char* sqlPointer = sql.c_str();
	result r = trans_->exec(sqlPointer);
	return r[0][0].as<int>();
} 

//____________________________________________________________________________________________________________________________________________________________________________________

void beginTransaction()
{
	executeSQL("begin;");
}


//____________________________________________________________________________________________________________________________________________________________________________________

void commitTransaction()
{
	executeSQL("commit;");
}


//____________________________________________________________________________________________________________________________________________________________________________________

void rollbackTransaction()
{
	executeSQL("rollback;");
}

//____________________________________________________________________________________________________________________________________________________________________________________

void checkConnection()
{
	if(connection_->is_open()){
		cout << "Opened database successfully: " << connection_->dbname() << endl;
      	} else {
        	cout << "Can't open database" << endl;
      	}
}

//____________________________________________________________________________________________________________________________________________________________________________________

void selectTestTable()
{
	result R( trans_->exec( "SELECT * from testtable" ));
	for (result::const_iterator c = R.begin(); c != R.end(); ++c) {
		cout << "ID = " << c[0].as<int>() << endl;
		cout << "Name = " << c[1].as<string>() << endl;
		cout << "Age = " << c[2].as<string>() << endl;
	}
	connection_->disconnect ();
}

//____________________________________________________________________________________________________________________________________________________________________________________

void connectToDb_()
{
	connection_ = new connection("dbname = testdb user = object password = object hostaddr = 127.0.0.1 port = 5432");
	//connection_ = new connection("dbname = objectcube user = object password = object hostaddr = 127.0.0.1 port = 5432");
	trans_ = new nontransaction(*connection_);
}

//____________________________________________________________________________________________________________________________________________________________________________________



void selectCube()
{
	cout << "****************----------------Start selectCube----------------****************" << endl;
	
	stringstream stringStream;
	stringStream << "select id, rgb from cubegist";
	string sql = stringStream.str();
	pqxx::result r = executeSQLWithout(sql);


	for(pqxx::result::const_iterator c = r.begin(); c != r.end(); c++)
	{
		cout << "id " << c[0].as<int>() << " rgb " << c[1] << endl;
		string rgb = c[1].as<string>();
		//rgb.replace(rgb.begin(), )
		//cout << rgb.end() << endl;
		rgb = rgb.substr(1, rgb.size() - 2);
		cout << "substr: " << rgb << endl;
		//ReplaceAll(rgb, "(", "");
		//vector<int> hallo = rgb;
		replace(rgb.begin(), rgb.end(), ',', ';');
		rgb.erase(remove(rgb.begin(), rgb.end(), ' '), rgb.end());
		cout << "replace: " << rgb << endl;
	}

	cout << "****************----------------End selectCube----------------****************" << endl;
}

void selectKNN()
{
	cout << "****************----------------Start selectCube----------------****************" << endl;
	
	stringstream stringStream;
	stringStream << "select *, rgb <-> cube(array[50,50,50]) as dist from cubegist order by dist LIMIT 10;";
	
	string sql = stringStream.str();
	pqxx::result r = executeSQLWithout(sql);


	for(pqxx::result::const_iterator c = r.begin(); c != r.end(); c++)
	{
		cout << "id " << c[0].as<int>() << " rgb " << c[1] << endl;
		string rgb = c[1].as<string>();
		//rgb.replace(rgb.begin(), )
		//cout << rgb.end() << endl;
		rgb = rgb.substr(1, rgb.size() - 2);
		cout << "substr: " << rgb << endl;
		//ReplaceAll(rgb, "(", "");
		//vector<int> hallo = rgb;
		replace(rgb.begin(), rgb.end(), ',', ';');
		rgb.erase(remove(rgb.begin(), rgb.end(), ' '), rgb.end());
		cout << "replace: " << rgb << endl;
	}

	cout << "****************----------------End selectCube----------------****************" << endl;
}

vector<string> split(const string& s, char delimiter)
{
   vector<string> tokens;
   string token;
   istringstream tokenStream(s);
   while (getline(tokenStream, token, delimiter))
   {
      tokens.push_back(token);
   }
   return tokens;
}

void insertCube()
{
	const string rgbString = "24;24;24";
	char delimiter = ';';

	vector<string> rgb = split(rgbString, ';');
	stringstream sstream;
	sstream << "INSERT INTO cubegist values (13, cube(array[" << rgb[0] << "," << rgb[1] << "," << rgb[2] << "]))";
	string sql = sstream.str();
	
	cout << sql << endl;
	cout << "Start" << endl;
	executeSQL(sql);
	cout << "End" << endl;
}

void insertCube()
{
	stringstream sstream;
	sstream << 	"insert into cubegist values (1, cube(array[0, 0, 100])); \
	insert into cubegist values (2, cube(array[100, 0, 100])); \
	insert into cubegist values (3, cube(array[0, 100, 100])); \
	insert into cubegist values (4, cube(array[50, 50, 100])); \
	insert into cubegist values (5, cube(array[0, 50, 50])); \
	insert into cubegist values (6, cube(array[50, 50, 0])); \
	insert into cubegist values (7, cube(array[30, 30, 30])); \
	insert into cubegist values (8, cube(array[40, 40, 40])); \
	insert into cubegist values (9, cube(array[50, 50, 50])); \
	insert into cubegist values (10, cube(array[100, 0, 0]));";
	string sql = sstream.str();
	
	cout << sql << endl;
	cout << "Start" << endl;
	executeSQL(sql);
	cout << "End" << endl;
}

int main() {
	
   try {
	connectToDb_();
	//selectCube();
	//insertCube();
	return 1;
	
   } catch (const std::exception &e) {
      cerr << e.what() << std::endl;
      return 1;
   }
}


