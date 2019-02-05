/*
 *  NumericalRangeFilterTest.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 1.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace CppUnit;

#ifndef ObjectCube_NUMERICAL_RANGE_FILTER_TEST_
#define ObjectCube_NUMERICAL_RANGE_FILTER_TEST_

namespace ObjectCube
{
	
	class NumericalRangeFilterTest : public TestFixture
	{
		CPPUNIT_TEST_SUITE( NumericalRangeFilterTest );
		
		//Canned
		#ifdef OC_CANNED
		CPPUNIT_TEST( testFilterCanned );
		#endif
		
		//SQLite
		#ifdef OC_SQLITE
		CPPUNIT_TEST( testFilterSQLite );
		#endif
		
		//MonetDB
		#ifdef OC_MONETDB
		CPPUNIT_TEST( testFilterMonetDB );
		#endif
		
		//Oracle
		#ifdef OC_ORACLE
		CPPUNIT_TEST( testFilterOracle );
		#endif

		CPPUNIT_TEST_SUITE_END();
		
	public:
		//Canned
		void testFilterCanned();
		
		//SQLite
		void testFilterSQLite();
		
		//MonetDB
		void testFilterMonetDB();
		
		//Oracle
		void testFilterOracle();
		
	private:
		void testFilter_();
		
	};
	
}

#endif