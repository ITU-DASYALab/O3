/*
 *  Parameters.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 8.7.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_PARAMETERS_
#define ObjectCube_PARAMETERS_

#include <string>
#include <map>

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
	
	class Parameters //Singleton
	{
	public:
		virtual ~Parameters();
		
		static Parameters* getParameters();
		
		void process( const string& input, const string& keyPrefix = "-", const string& separator = " " );
		void process( int argc, char* const argv[], const string& keyPrefix = "-", const string& separator = " " );
		void add( const string& key, const string& value );
		void remove( const string& key );
		void update( const string& key, const string& newValue );
		
		const string getValue( const string& key );
		const int getValueAsInt( const string& key );
		bool contains( const string& key ) const;
		
	protected:
		Parameters() {;}
		Parameters& operator=( const Parameters& parameters ); //Intentionally not implemented
		Parameters( const Parameters& parameters ); //Intentionally not implemented
		
	private:
		static std::shared_ptr<Parameters> instance_;
		map<string,string> params_;
		
	};	
	
}

#endif