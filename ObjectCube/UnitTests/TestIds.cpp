/*
 *  TestIds.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 23.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */


#include "TestIds.h"

#include "../LayerShared/Parameters.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

string TestIds::TEST_OBJECT_PREFIX_DEFAULT  = "Add -unitTestObjectPath to arguments! ";
string TestIds::TEST_OBJECT_PREFIX = TEST_OBJECT_PREFIX_DEFAULT;

int SQLiteTestIds::TEST_ALPHANUMERICAL_TAG_ID = -1;
int SQLiteTestIds::TEST_NUMERICAL_TAG_ID = -1;
int SQLiteTestIds::TEST_TIME_TAG_ID = -1;
int SQLiteTestIds::TEST_DATE_TAG_ID = -1;

int MonetDBTestIds::TEST_ALPHANUMERICAL_TAG_ID = -1;
int MonetDBTestIds::TEST_NUMERICAL_TAG_ID = -1;
int MonetDBTestIds::TEST_TIME_TAG_ID = -1;
int MonetDBTestIds::TEST_DATE_TAG_ID = -1;

int OracleTestIds::TEST_ALPHANUMERICAL_TAG_ID = -1;
int OracleTestIds::TEST_NUMERICAL_TAG_ID = -1;
int OracleTestIds::TEST_TIME_TAG_ID = -1;
int OracleTestIds::TEST_DATE_TAG_ID = -1;

//____________________________________________________________________________________________________________________________________________________________________________________

void TestIds::updateObjectPrefix()
{
	if( Parameters::getParameters()->contains( UNIT_TEST_OBJECT_PATH_PARAMETER ) )
	{
		TEST_OBJECT_PREFIX = Parameters::getParameters()->getValue( UNIT_TEST_OBJECT_PATH_PARAMETER );
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________



