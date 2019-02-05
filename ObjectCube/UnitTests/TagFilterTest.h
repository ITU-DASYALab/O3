/*
 *  TagFilterTest.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 14.4.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace CppUnit;

#ifndef ObjectCube_TAG_FILTER_TEST_
#define ObjectCube_TAG_FILTER_TEST_

namespace ObjectCube
{
	
	class TagFilterTest : public TestFixture
	{
		CPPUNIT_TEST_SUITE( TagFilterTest );
		
		//Canned
		#ifdef OC_CANNED
		CPPUNIT_TEST( testFilterCanned );
		#endif		
		
		//SQLite
		#ifdef OC_SQLITE
		CPPUNIT_TEST( testFilterSQLite );
		CPPUNIT_TEST( testFilterTypeAsStringSQLite );
		#endif
		
		//MonetDB
		#ifdef OC_MONETDB
		CPPUNIT_TEST( testFilterMonetDB );
		CPPUNIT_TEST( testFilterTypeAsStringMonetDB );
		#endif
		
		//Oracle
		#ifdef OC_ORACLE
		CPPUNIT_TEST( testFilterOracle );
		CPPUNIT_TEST( testFilterTypeAsStringOracle );
		#endif
		
		
		CPPUNIT_TEST_SUITE_END();
		
	public:
		//getTag(id)
		//getTag(dimensionId, name)
		
		//Canned
		void testFilterCanned();
				
		//SQLite
		void testFilterSQLite();
		void testFilterTypeAsStringSQLite();
		
		//MonetDB
		void testFilterMonetDB();
		void testFilterTypeAsStringMonetDB();
	
		//Oracle
		void testFilterOracle();
		void testFilterTypeAsStringOracle();

		
	private:
		void testFilter_( int alphanumericalTagId, int numericalTagId );
		void testFilterTypeAsString_( int tagId );

		
	};
	
}

#endif