/*
 *  DebugInfo.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 17.8.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_DEBUG_INFO_
#define ObjectCube_DEBUG_INFO_

#include <string>
#include <stack>
#include <fstream>

#ifdef __APPLE__
#include <memory>
using std::shared_ptr;
#else
#include <tr1/memory>
using std::shared_ptr;
#endif

using namespace std;

namespace ObjectCube
{
	
	/*
	 To turn on add the following to input parameters: -outputDebugInfo 1
	 It can also be turned on by adding it on the fly using the Parameters class
	 
	 To turn off leave it out of parameters or modify the value to 0
	 
	 If output is turned on:
		Exclude output from a specific class X by adding the parameter:  -outputDI_X 0
		Exclude output from a specific function Y in a class X by adding the parameter: -outputDI_X::Y 0
	 
	 If output is turned off:
		Include output from a specific class X by adding the parameter:  -outputDI_X 1
		Include output from a specific function Y in a class X by adding the parameter: -outputDI_X::Y 1
	 
	 Use the output, pushTimer and pop timer in your code to generate output.
	 */
	
	class Exception;
	
	class DebugInfo //Singleton
	{
	public:
		virtual ~DebugInfo();
		
		static DebugInfo* getDebugInfo();
		
		void output( const string& originatingClass, const string& function, const string& info );
		
		//Using Exception instead of exception is less than optimal, but since dynamic casting seems to be bugged using GCC on Linux it will be left this way for now.
		void output( const string& originatingClass, const string& function, Exception* e );
		void output( const string& originatingClass, const string& function, const string& what, int info );
		
		void pushTimer( const string& originatingClass, const string& function );
		void pushTimer( const string& originatingClass, const string& function, const string& info );
		void popTimer();
		
		void turnCoutAndCerrOff();
		void turnCoutAndCerrOn();
		
	protected:
		DebugInfo();
		DebugInfo( const DebugInfo& debugInfo ); //Intentionally not implemented
		DebugInfo& operator=( const DebugInfo& debugInfo ); //Intentionally not implemented
		
		bool debugOn_( const string& originatingClass, const string& function );
		int getParameterValue_( const string& param );
		
		class DebugInfoTimer
		{
		public:
			DebugInfoTimer( const string& originatingClass, const string& function, const string& info );
			
			static double getCurrTimeInMilliseconds();
			
			string getClass() { return class_; }
			string getFunction() { return function_; }
			string getInfo() { return info_; }
			clock_t getTimer() { return timer_; }
			time_t getWallTimer() { return wallTimer_; }
			double getMillisecondsStart() { return millisecondsStart_; }
		private:
			string class_;
			string function_;
			string info_;
			clock_t timer_;
			time_t wallTimer_;
			double millisecondsStart_;
		};
		
	private:
		static std::shared_ptr<DebugInfo> instance_;
		static string OUTPUT_DEBUG_INFO;
		static string OUTPUT_CLASS_PREFIX;
		static string OUTPUT_FUNCTION_PREFIX;
		static string NULL_OUTPUT;
		
		stack<DebugInfoTimer> timers_;
		
		bool coutAndCerrOn_;
		std::shared_ptr<ofstream> nullstream_;
		streambuf* originalCerrBuffer_;
		streambuf* originalCoutBuffer_;
	};	
	
}

#endif