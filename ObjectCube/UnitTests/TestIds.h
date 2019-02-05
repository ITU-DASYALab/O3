/*
 *  TestIds.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 16.2.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_TEST_IDS_
#define ObjectCube_TEST_IDS_

#include <string>

using namespace std;

namespace ObjectCube
{	
   enum TEST_IDS 
	{
		TEST_ALPHANUMERICAL_TAG_SET_ID = 10000,
		TEST_NUMERICAL_TAG_SET_ID = 15000,
		TEST_TIME_TAG_SET_ID = 20000,
		TEST_DATE_TAG_SET_ID = 25000,
		TEST_HIERARCHY_ID = 40000,
		TEST_HIERARCHY_NODE_ID = 45000,
		TEST_ALPHANUMERICAL_TAG_ID_CANNED = 500000,
		TEST_NUMERICAL_TAG_ID_CANNED = 520000,
		TEST_TIME_TAG_ID_CANNED = 540000,
		TEST_DATE_TAG_ID_CANNED = 560000,
		TEST_OBJECT_ID = 600000
	};
	
	class TestIds
	{
	public:
		static void updateObjectPrefix();
		
		static string TEST_OBJECT_PREFIX_DEFAULT;
		static string TEST_OBJECT_PREFIX;
	};
	
	class SQLiteTestIds
	{
	public:
		static int TEST_ALPHANUMERICAL_TAG_ID;
		static int TEST_NUMERICAL_TAG_ID;
		static int TEST_TIME_TAG_ID;
		static int TEST_DATE_TAG_ID;
/*		
		static int TEST_DIMENSION_ROOT_TAG_ID;
		static int TEST_DIMENSION_CHILD1_TAG_ID;
		static int TEST_DIMENSION_CHILD2_TAG_ID;
		static int TEST_DIMENSION_CHILD3_TAG_ID;
 */
	};
	
	class MonetDBTestIds
	{
	public:
		static int TEST_ALPHANUMERICAL_TAG_ID;
		static int TEST_NUMERICAL_TAG_ID;
		static int TEST_TIME_TAG_ID;
		static int TEST_DATE_TAG_ID;
	};
	
	class OracleTestIds
	{
	public:
		static int TEST_ALPHANUMERICAL_TAG_ID;
		static int TEST_NUMERICAL_TAG_ID;
		static int TEST_TIME_TAG_ID;
		static int TEST_DATE_TAG_ID;
	};
	
	static string TEST_SQLITE_CLEANUP_PREFIX = "SQLite test";
	static string TEST_MONETDB_CLEANUP_PREFIX = "MonetDB test";
	static string TEST_ORACLE_CLEANUP_PREFIX = "Oracle test";
	

	static string UNIT_TEST_OBJECT_PATH_PARAMETER = "unitTestObjectPath";
	
	static string TEST_OBJECT_NAME = "img4.jpg";
	static string TEST_ALPHANUMERICAL_TAG_NAME = " - Unit test";

	//Language
	static string TEST_ALPHANUMERICAL_TAG_TYPE_NAME_ENGLISH = "Alphanumerical tag";
	static string TEST_ALPHANUMERICAL_TAG_TYPE_NAME_ICELANDIC = "Texta tag";
	static string TEST_ALPHANUMERICAL_TAG_SET_TYPE_NAME_ENGLISH = "Alphanumerical tag-set";
	static string TEST_ALPHANUMERICAL_TAG_SET_TYPE_NAME_ICELANDIC = "Texta tag-sett";
	static string TEST_ACCESS_USER_ENGLISH = "User access";
	static string TEST_ACCESS_USER_ICELANDIC = "Notenda aðgangur";
	static string TEST_TAG_FILTER_TYPE_ENGLISH = "Tag filter";
	static string TEST_TAG_FILTER_TYPE_ICELANDIC = "Tag filter";
	
	static int TEST_NUMERICAL_TAG_VALUE = 12;
	
	//Time
	static int TEST_TIME_TAG_VALUE_HOURS = 14;
	static int TEST_TIME_TAG_VALUE_MINUTES = 37;
	static int TEST_TIME_TAG_VALUE_SECONDS = 48;
	static int TEST_TIME_TAG_VALUE_MILLISECONDS = 942;
	
	//Date
	static int TEST_DATE_TAG_VALUE_YEAR = 2010;
	static int TEST_DATE_TAG_VALUE_MONTH = 04;
	static int TEST_DATE_TAG_VALUE_DAY = 29;
	
	

	
}

#endif