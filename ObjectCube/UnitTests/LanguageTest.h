/*
 *  LanguageTest.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 8.7.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include <cppunit/TestFixture.h>
#include <cppunit/extensions/HelperMacros.h>

using namespace CppUnit;

#ifndef ObjectCube_LANGUAGE_TEST_
#define ObjectCube_LANGUAGE_TEST_

namespace ObjectCube
{
	
	class LanguageTest : public TestFixture
	{
		CPPUNIT_TEST_SUITE( LanguageTest );
		
		//Canned
		#ifdef OC_CANNED
		CPPUNIT_TEST( testGetTranslatedTextCanned );
		#endif
		
		//SQLite
		#ifdef OC_SQLITE
		CPPUNIT_TEST( testGetTranslatedTextSQLite );
		#endif
		
		//MonetDB
		#ifdef OC_MONETDB
		CPPUNIT_TEST( testGetTranslatedTextMonetDB );
		#endif
		
		//Oracle
		#ifdef OC_ORACLE
		CPPUNIT_TEST( testGetTranslatedTextOracle );
		#endif
		
		CPPUNIT_TEST_SUITE_END();
		
	public:
		//getTag(id)
		//getTag(dimensionId, name)
		
		//Canned
		void testGetTranslatedTextCanned();
				
		//SQLite
		void testGetTranslatedTextSQLite();
		
		//MonetDB
		void testGetTranslatedTextMonetDB();
		
		//Oracle
		void testGetTranslatedTextOracle();

		
	private:
		void testGetTranslatedText_();
	};
	
}

#endif