/*
 *  RegExSupportTest.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 6.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "RegExSupportTest.h"

#include <cppunit/extensions/HelperMacros.h>
#include <iostream>

#include "../LayerShared/RegExSupport.h"


using namespace ObjectCube;

CPPUNIT_TEST_SUITE_REGISTRATION( RegExSupportTest );

//____________________________________________________________________________________________________________________________________________________________________________________

//  Canned tests --------------------------------------------------------------------------------------------------------------------

void RegExSupportTest::testPatternFoundCanned()
{
	cerr << "\nRegExSupportTest::testPatternFoundCanned = ";

	string match, pattern, data;
	
	CPPUNIT_ASSERT( RegExSupport::patternFound( data, pattern, match ) == false );
	
	data = "2010-12-30";
	CPPUNIT_ASSERT( RegExSupport::patternFound( data, pattern, match ) == false );
	
	pattern = "-[0-9]{1}-";
	CPPUNIT_ASSERT( RegExSupport::patternFound( data, pattern, match ) == false );
	
	pattern = "-[0-9]{3}-";
	CPPUNIT_ASSERT( RegExSupport::patternFound( data, pattern, match ) == false );

	pattern = "-[0-9]{2}-";
	CPPUNIT_ASSERT( RegExSupport::patternFound( data, pattern, match ) == true );
	CPPUNIT_ASSERT( match == "-12-" );

}
//____________________________________________________________________________________________________________________________________________________________________________________

