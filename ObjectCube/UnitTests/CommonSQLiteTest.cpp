/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/

#include "CommonSQLiteTest.h"

#include <cppunit/extensions/HelperMacros.h>
#include <iostream>

//#include "../DataAccess/SQLite/CommonSQLite.h"
#include "../Hub.h"
#include "../LayerShared/Exception.h"


using namespace ObjectCube;

CPPUNIT_TEST_SUITE_REGISTRATION( CommonSQLiteTest );

//____________________________________________________________________________________________________________________________________________________________________________________

//  Canned tests --------------------------------------------------------------------------------------------------------------------

void CommonSQLiteTest::testToSQLStringCanned() 
{
	cerr << "\nCommonSQLiteTest::testToSQLStringCanned = ";
#ifdef OC_SQLITE
	CPPUNIT_ASSERT( CommonSQLite::toSQLString( 2010, 5, 4 ) == "strftime( \"%Y-%m-%d\", '2010-05-04' )" );
	CPPUNIT_ASSERT( CommonSQLite::toSQLString( 2010, 11, 21 ) == "strftime( \"%Y-%m-%d\", '2010-11-21' )" );
#endif
}
//____________________________________________________________________________________________________________________________________________________________________________________


