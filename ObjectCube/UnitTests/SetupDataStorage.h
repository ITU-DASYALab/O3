/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/


#ifndef ObjectCube_SETUP_DATA_STORAGE_
#define ObjectCube_SETUP_DATA_STORAGE_

#include <vector>
#include <memory>

#include "Setup.h"

using namespace std;

namespace ObjectCube
{	
	
    class SetupDataStorage //Singleton
	{
	public:
		virtual ~SetupDataStorage();
		
		static SetupDataStorage* getSetupDataStorage();
		
		void setup();
		void cleanup();
	
	private:
		SetupDataStorage();
		vector<Setup*> dataStorages_;
		static unique_ptr<SetupDataStorage> instance_;
		
	};
	
}

#endif