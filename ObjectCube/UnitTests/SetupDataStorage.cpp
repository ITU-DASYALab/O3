/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/

#include "SetupDataStorage.h"

#include "SetUpSQLite.h"
#include "SetupMonetDB.h"
#include "SetupOracle.h"

#include "../LayerShared/MemoryManagement.h"

using namespace ObjectCube;
using namespace std;

//____________________________________________________________________________________________________________________________________________________________________________________

unique_ptr<SetupDataStorage> SetupDataStorage::instance_( 0 );

//____________________________________________________________________________________________________________________________________________________________________________________

SetupDataStorage::SetupDataStorage()
{
#ifdef OC_SQLITE
	dataStorages_.push_back( new SetupSQLite() );
#endif
#ifdef OC_MONETDB
	dataStorages_.push_back( new SetupMonetDB() );	
#endif
#ifdef OC_ORACLE
	dataStorages_.push_back( new SetupOracle() );	
#endif
	
}
//____________________________________________________________________________________________________________________________________________________________________________________

SetupDataStorage::~SetupDataStorage()
{
	clearAndDestroy( dataStorages_ );
}
//____________________________________________________________________________________________________________________________________________________________________________________

SetupDataStorage* SetupDataStorage::getSetupDataStorage()
{
	if( instance_.get() == 0 )
	{
		instance_.reset( new SetupDataStorage() );
	}
	return instance_.get();
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupDataStorage::setup()
{
	for( vector<Setup*>::iterator itr = dataStorages_.begin(); itr != dataStorages_.end(); ++itr )
	{
		(*itr)->setup();
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________

void SetupDataStorage::cleanup()
{
	for( vector<Setup*>::iterator itr = dataStorages_.begin(); itr != dataStorages_.end(); ++itr )
	{
		(*itr)->cleanup();
	}
}
//____________________________________________________________________________________________________________________________________________________________________________________






