/*
 *  Exception.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 18.2.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */


#include "Exception.h"	

#include <sstream>


using namespace ObjectCube;

Exception::Exception( const string where, const string message )
{
	where_ = where;  
	message_ = message; 
}

Exception::Exception( const string where, const string message, const int inputValue ) 
{ 
	where_ = where;  
	ostringstream stringStream;
	stringStream << message << " |  Input value: " << inputValue;
	message_ = stringStream.str();
}

Exception::Exception( const string where, const string message, const string inputValue ) 
{ 
	where_ = where;  
	ostringstream stringStream;
	stringStream << message << " |  Input value: " << inputValue;
	message_ = stringStream.str();	
} 

