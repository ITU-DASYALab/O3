/*
 *  DefaultDimensionTest.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 5.7.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>
#include <string>

using namespace CppUnit;
using namespace std;

#ifndef ObjectCube_DEFAULT_DIMENSION_TEST_
#define ObjectCube_DEFAULT_DIMENSION_TEST_

namespace ObjectCube
{	
	class DefaultDimensionTest : public TestFixture
	{
		CPPUNIT_TEST_SUITE( DefaultDimensionTest );

		//Canned
		#ifdef OC_CANNED
		CPPUNIT_TEST( testInstantiateCanned );
		#endif
		
		//SQLite
		#ifdef OC_SQLITE
		CPPUNIT_TEST( testInstantiateSQLite );
		#endif
		
		//MonetDB
		#ifdef OC_MONETDB
		CPPUNIT_TEST( testInstantiateMonetDB );
		#endif
		
		//Oracle
		#ifdef OC_ORACLE
		CPPUNIT_TEST( testInstantiateOracle );
		#endif
		
		CPPUNIT_TEST_SUITE_END();
		
	public:
		//Canned
		void testInstantiateCanned();
		
		//SQLite
		void testInstantiateSQLite();
		
		//MonetDB
		void testInstantiateMonetDB();
		
		//Oracle
		void testInstantiateOracle();

	
	private:
		void testInstatiate_();
	};
	
}

#endif