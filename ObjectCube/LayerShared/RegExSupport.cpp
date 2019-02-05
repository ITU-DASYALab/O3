/*
 *  RegExSupport.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 6.5.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "RegExSupport.h"

#include <iostream>

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

//The value in substringFound is the first substring found.  This function only looks for the first match.
bool RegExSupport::patternFound( const string& data, const string& pattern, string& substringFound )
{
	// BSD library stuff
	//http://developer.apple.com/iphone/library/documentation/System/Conceptual/ManPages_iPhoneOS/man3/regex.3.html
	//http://publibn.boulder.ibm.com/doc_link/en_US/a_doc_lib/aixprggd/genprogc/internationalized_reg_expression_subr.htm
	
	if( !data.size() || !pattern.size() )
	{
		return false;
	}
	
	int status;
	int eflag = 0;
	regex_t regularExpression;
	regmatch_t pmatch[50];
	
	setlocale(LC_ALL, "");
	
	if( ( status = regcomp( &regularExpression, pattern.c_str(), REG_EXTENDED ) ) != 0 )
	{
		char errorBuffer[200];
		regerror( status, &regularExpression, errorBuffer, 200 );
		cerr << "Error compiling regular expression pattern: " << errorBuffer << endl;
		return cleanup_( regularExpression, false ); //Throw?
	}
	
	status = regexec( &regularExpression, data.c_str(), 1, pmatch, eflag );
	
	if( status != 0 )
	{
		return cleanup_( regularExpression, false );
	}
	
	substringFound = data.substr( pmatch[0].rm_so, pmatch[0].rm_eo - pmatch[0].rm_so );
	
	return cleanup_( regularExpression, true );
}
//____________________________________________________________________________________________________________________________________________________________________________________

bool RegExSupport::cleanup_( regex_t& re, bool retVal )
{
	regfree( &re );
	return retVal;
}
//____________________________________________________________________________________________________________________________________________________________________________________
