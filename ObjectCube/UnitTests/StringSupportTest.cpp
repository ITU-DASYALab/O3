/*
 *  StringSupportTest.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 23.8.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "StringSupportTest.h"

#include <cppunit/extensions/HelperMacros.h>
#include <iostream>

#include "../LayerShared/StringSupport.h"


using namespace ObjectCube;

CPPUNIT_TEST_SUITE_REGISTRATION( StringSupportTest );

//____________________________________________________________________________________________________________________________________________________________________________________

//  Canned tests --------------------------------------------------------------------------------------------------------------------

void StringSupportTest::testNeutralizeControlSymbolsCanned()
{
	cerr << "\nStringSupportTest::testNeutralizeControlSymbolsCanned = ";
	
	string input1 = "abc'def";
	string output1 = "abc\''def";
	
	CPPUNIT_ASSERT( output1 == StringSupport::neutralizeControlCharacters( input1 ) );
	
	string input2 = "abc' de'fd";
	string output2 = "abc\'' de\''fd";
	
	CPPUNIT_ASSERT( output2 == StringSupport::neutralizeControlCharacters( input2 ) );
	
	string input3 = "''";
	string output3 = "\''\''";
	
	CPPUNIT_ASSERT( output3 == StringSupport::neutralizeControlCharacters( input3 ) );
	/*
	string input4 = "ab'\"d\\";
	string output4 = "ab\\'\\\"d\\\\";
	
	CPPUNIT_ASSERT( output4 == StringSupport::neutralizeControlCharacters( input4 ) );
	 */
}
//____________________________________________________________________________________________________________________________________________________________________________________

void StringSupportTest::testRemoveControlSymbolNeutralizationCanned()
{
	cerr << "\nStringSupportTest::testRemoveControlSymbolNeutralizationCanned = ";

	string input1 = "abc'def";
	string input1Neutralized = StringSupport::neutralizeControlCharacters( input1 );
	string input1Deneutralized = StringSupport::removeControlCharacterNeutralization( input1Neutralized );
	
	CPPUNIT_ASSERT( input1 ==  input1Deneutralized );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void StringSupportTest::testTrimCanned()
{
	cerr << "\nStringSupportTest::testTrimCanned = ";

	string input1 = " leading";
	string output1 = "leading";
	StringSupport::trim( input1 );
	CPPUNIT_ASSERT( input1 == output1 );
	
	string input2 = "trailing ";
	string output2 = "trailing";
	StringSupport::trim( input2 );
	CPPUNIT_ASSERT( input2 == output2 );
	
	string input3 = "    both  ";
	string output3 = "both";
	StringSupport::trim( input3 );
	CPPUNIT_ASSERT( input3 == output3 );
	
	string input4 = "__not whitespace _";
	string output4 = "not whitespace ";
	StringSupport::trim( input4, "_" );
	CPPUNIT_ASSERT( input4 == output4 );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void StringSupportTest::testToSimpleAsciiCanned()
{
	cerr << "\nStringSupportTest::testToSimpleAsciiCanned = ";
	
	string input1 = "Grímur Tómasson";
	string expectedOutput1 = "Gr__mur T__masson";
	string output1 = StringSupport::toSimpleAscii( input1 );
	
	CPPUNIT_ASSERT( expectedOutput1 == output1  );

}
//____________________________________________________________________________________________________________________________________________________________________________________

