/*
 *  DebugInfo.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 17.8.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include "DebugInfo.h"

#include <iostream>
#include <sstream>

#include <sys/time.h>

#include "Parameters.h"
#include "SharedDefinitions.h"
#include "Exception.h"

using namespace ObjectCube;
using namespace std;

//____________________________________________________________________________________________________________________________________________________________________________________

std::shared_ptr<DebugInfo> DebugInfo::instance_;
string DebugInfo::OUTPUT_DEBUG_INFO = "outputDebugInfo";
string DebugInfo::OUTPUT_CLASS_PREFIX = "outputDI_";
string DebugInfo::OUTPUT_FUNCTION_PREFIX = "::";
string DebugInfo::NULL_OUTPUT = "/dev/null";

//____________________________________________________________________________________________________________________________________________________________________________________

DebugInfo::~DebugInfo()
{
	turnCoutAndCerrOn();
}
//____________________________________________________________________________________________________________________________________________________________________________________

DebugInfo::DebugInfo()
{
	coutAndCerrOn_ = true;
	originalCerrBuffer_ = 0;
	originalCoutBuffer_ = 0;
}
//____________________________________________________________________________________________________________________________________________________________________________________

DebugInfo* DebugInfo::getDebugInfo()
{
	if( instance_.get() == 0 )
	{
		instance_.reset( new DebugInfo() );
	}
	return instance_.get();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DebugInfo::output( const string& originatingClass, const string& function, const string& info )
{
	if( !debugOn_( originatingClass, function ) )
	{
		return;
	}
	
	cerr << endl << originatingClass << "::" << function << ":\n" << info << endl;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DebugInfo::output( const string& originatingClass, const string& function, const string& what, int info )
{
	stringstream sstream;
	sstream << what << ": " << info;
	output( originatingClass, function, sstream.str() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DebugInfo::output( const string& originatingClass, const string& function, Exception* e )
{
	stringstream sstream;
	sstream << "Exception in: " << e->where() << ".  What: " << e->what() << endl;
	output( originatingClass, function, sstream.str() );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DebugInfo::pushTimer( const string& originatingClass, const string& function )
{
	pushTimer( originatingClass, function, "" );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DebugInfo::pushTimer( const string& originatingClass, const string& function, const string& info )
{
	if( !debugOn_( originatingClass, function ) )
	{
		return;
	}
	
	timers_.push( DebugInfoTimer( originatingClass, function, info ) );
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DebugInfo::popTimer()
{
	if( timers_.size() == 0 )
	{
		return;
	}
	
	DebugInfoTimer timer = timers_.top();
	if( !debugOn_( timer.getClass(), timer.getFunction() ) )
	{
		return;
	}
	timers_.pop();
	
	string indentation;
	for( int i = 0; i < timers_.size(); ++i )
	{
		indentation += "\t";
	}
	
	double endTime = DebugInfoTimer::getCurrTimeInMilliseconds();
	
	cout	<< endl << indentation << timer.getClass() << "::" << timer.getFunction() 
			<< ( timer.getInfo().length() > 0 ? " - " : "" )
			<< timer.getInfo() << " (cpu seconds): " << (double)  ( clock() - timer.getTimer() ) / CLOCKS_PER_SEC
	<< " (wall seconds): " << time( 0 ) - timer.getWallTimer() << " (wall milliseconds): " << endTime - timer.getMillisecondsStart();
}
//____________________________________________________________________________________________________________________________________________________________________________________

DebugInfo::DebugInfoTimer::DebugInfoTimer( const string& originatingClass, const string& function, const string& info )
{
	class_ = originatingClass;
	function_ = function;
	info_ = info;
	timer_ = clock();
	wallTimer_ = time( 0 );
	
	millisecondsStart_ = getCurrTimeInMilliseconds();
}
//____________________________________________________________________________________________________________________________________________________________________________________
													
double DebugInfo::DebugInfoTimer::getCurrTimeInMilliseconds()
{
	timeval timev;
	gettimeofday( &timev, 0 );
	return ( timev.tv_sec * 1000) + ( timev.tv_usec / 1000.0 );
}
//____________________________________________________________________________________________________________________________________________________________________________________

int DebugInfo::getParameterValue_( const string& param )
{
	if( !Parameters::getParameters()->contains( param ) )
	{
		return INVALID_VALUE;
	}
	return Parameters::getParameters()->getValueAsInt( param );
}
//____________________________________________________________________________________________________________________________________________________________________________________

bool DebugInfo::debugOn_( const string& originatingClass, const string& function )
{
	turnCoutAndCerrOn();  //Should only affect direct cout/cerr in code, not DebugInfo output
	
	if( getParameterValue_( OUTPUT_DEBUG_INFO ) == 1 ) //Trace is on, check for exclusion
	{
		if( getParameterValue_( OUTPUT_CLASS_PREFIX + originatingClass ) == 0 )
		{
			return false; // output for the class has been turned off
		}
		if( getParameterValue_( OUTPUT_CLASS_PREFIX + originatingClass + OUTPUT_FUNCTION_PREFIX + function ) == 0 )
		{
			return false; // output for the (class) function has been turned off
		}
		return true;
	}
	//trace is off, check for inclusion
	if( getParameterValue_( OUTPUT_CLASS_PREFIX + originatingClass ) == 1 )
	{
		return true; // output for the class has been turned on
	}
	if( getParameterValue_( OUTPUT_CLASS_PREFIX + originatingClass + OUTPUT_FUNCTION_PREFIX + function ) == 1 )
	{
		return true; // output for the (class) function has been turned on
	}
	return false;	
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DebugInfo::turnCoutAndCerrOff()
{
	if( !coutAndCerrOn_ )
	{
		return;
	}
	
	nullstream_.reset( new ofstream( DebugInfo::NULL_OUTPUT.c_str() ) );
	originalCerrBuffer_ = cerr.rdbuf( nullstream_->rdbuf() );
	originalCoutBuffer_ = cout.rdbuf( nullstream_->rdbuf() );
	
	coutAndCerrOn_ = false;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void DebugInfo::turnCoutAndCerrOn()
{
	if( coutAndCerrOn_ )
	{
		return;
	}
	
	cerr.rdbuf( originalCerrBuffer_ ); 
	cout.rdbuf( originalCoutBuffer_ );
	nullstream_->close();	
	nullstream_.reset();
	coutAndCerrOn_ = true;
}
//____________________________________________________________________________________________________________________________________________________________________________________
































