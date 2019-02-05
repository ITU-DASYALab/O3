/*
 *  SetupSQLite.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 16.2.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#if !defined(ObjectCube_SETUPMONETDB_) && defined(OC_SQLITE)
//#ifndef ObjectCube_SETUPSQLITE_
#define ObjectCube_SETUPSQLITE_

#include "Setup.h"

namespace ObjectCube
{	
	class CommonSQLite;
	
    class SetupSQLite : public Setup
	{
	public:
		SetupSQLite();
		
		virtual void setup();
		virtual void cleanup();
		
	protected:
		//Delete
		void deleteTestObjectTags_();
		
		void deleteAlphanumericalTags_();
		void deleteNumericalTags_();
		void deleteDateTags_();
		void deleteTimeTags_();
		void deleteTestTags_();
		
		void deleteTestObjects_();
		void deleteTestTagSets_();
		void deleteTestDimensions_();
		
		//Insert
		void insertAlphanumericalTestTagSets_();
		void insertNumericalTestTagSets_();
		void insertTimeTestTagSets_();
		void insertDateTestTagSets_();
		
		int insertTestTag_( int tagSetId, int typeId, CommonSQLite& db );
		void insertTestTagsAlphanumerical_();
		void insertTestTagsNumerical_();
		void insertTestTagsTime_();
		void insertTestTagsDate_();
		
		void insertTestObjects_();
		void insertTestTagObjects_( int objectId, int tagId );
		void insertTestDimensions_();
		
	};
}

#endif