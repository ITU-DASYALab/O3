/*
 *  LanguageTest.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 8.7.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "LanguageTest.h"

#include <cppunit/extensions/HelperMacros.h>

#include "../Hub.h"
#include "TestIds.h"
#include "Language.h"
#include "../LayerShared/SharedDefinitions.h"
#include "../LayerShared/Exception.h"

using namespace ObjectCube;

CPPUNIT_TEST_SUITE_REGISTRATION( LanguageTest );

//____________________________________________________________________________________________________________________________________________________________________________________

//  Canned tests --------------------------------------------------------------------------------------------------------------------

void LanguageTest::testGetTranslatedTextCanned()
{
	cerr << "\nLanguageTest::testGetTranslatedTextCanned = ";
	Hub::setDataAccessType( Hub::CANNED );

	const string translatedText = Language::asString( "TagType", 1 );
	
	CPPUNIT_ASSERT( translatedText.size() > 0 );
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  SQLite tests --------------------------------------------------------------------------------------------------------------------

void LanguageTest::testGetTranslatedTextSQLite()
{
	cerr << "\nLanguageTest::testGetTranslatedTextSQLite = ";
	Hub::setDataAccessType( Hub::SQLITE );
	
	testGetTranslatedText_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  MonetDB tests --------------------------------------------------------------------------------------------------------------------

void LanguageTest::testGetTranslatedTextMonetDB()
{
	cerr << "\nLanguageTest::testGetTranslatedTextMonetDB = ";
	Hub::setDataAccessType( Hub::MONETDB );
	
	testGetTranslatedText_();
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Oracle tests --------------------------------------------------------------------------------------------------------------------

void LanguageTest::testGetTranslatedTextOracle()
{
	cerr << "\nLanguageTest::testGetTranslatedTextOracle = ";
	Hub::setDataAccessType( Hub::ORACLE );
	
	testGetTranslatedText_();	
}
//____________________________________________________________________________________________________________________________________________________________________________________

//  Common --------------------------------------------------------------------------------------------------------------------

void LanguageTest::testGetTranslatedText_()
{
	const string test1 = Language::asString( "TagType", 1 );
	CPPUNIT_ASSERT_EQUAL( test1, TEST_ALPHANUMERICAL_TAG_TYPE_NAME_ENGLISH );
	
	Hub::setLanguageId( LanguageCommon::ICELANDIC );
	const string test2 = Language::asString( "TagType", 1 );
	CPPUNIT_ASSERT_EQUAL( test2, TEST_ALPHANUMERICAL_TAG_TYPE_NAME_ICELANDIC );
	
	Hub::setLanguageId( LanguageCommon::ENGLISH );
	const string test3 = Language::asString( "TagType", 1 );
	CPPUNIT_ASSERT_EQUAL( test3, TEST_ALPHANUMERICAL_TAG_TYPE_NAME_ENGLISH );
	
	CPPUNIT_ASSERT_THROW( Language::asString( "EntityDoesNotExist", 1 ), ObjectCube::Exception);
}
//____________________________________________________________________________________________________________________________________________________________________________________

