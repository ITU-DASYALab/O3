/*
 *  HubCommon.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 17.2.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_HUB_COMMON_
#define ObjectCube_HUB_COMMON_

#include <string>

using namespace std;

namespace ObjectCube
{
	
	class HubCommon 
	{
	public:
		HubCommon() {;}
		virtual ~HubCommon() {;}
		
		static int getDataAccessType() { return HubCommon::dataAccessType_; }
		static void setDataAccessType( int type ) { HubCommon::dataAccessType_ = type; } 

		static string getUncategorizedDimensionName() { return HubCommon::uncategorizedDimName_; }
		static string getUncategorizedTagName() { return HubCommon::uncategorizedTagName_; }
		static string getDataAccessTypeParameterName() { return dataAccessTypeParameterName_; }
		
	private:
		static int dataAccessType_;
		static string uncategorizedDimName_;
		static string uncategorizedTagName_;
		static string dataAccessTypeParameterName_;
		
	public:
		enum DATA_ACCESS_TYPE 
		{
			CANNED = 1,
			SQLITE = 2,
			MONETDB = 3,
			ORACLE = 4,
			POSTGRESQL = 5
		};
		
	};	
	
}

#endif
