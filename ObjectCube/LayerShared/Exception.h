/*
 *  ObjectCubeException.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 18.2.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include <exception>
#include <string>

#ifndef ObjectCube_EXCEPTION_
#define ObjectCube_EXCEPTION_

using namespace std;

namespace ObjectCube
{	
	class Exception : public exception
	{
	public:
		Exception( const string where, const string message );
		Exception( const string where, const string message, const int inputValue );
		Exception( const string where, const string message, const string inputValue );
		
		virtual ~Exception() throw() { }
		
		virtual const char* what() const throw()
		{
			return message_.c_str();
		}
		
		virtual const char* where() const throw()
		{
			return where_.c_str();
		}
		
	private:
		string message_;
		string where_;
	};
}

#endif
