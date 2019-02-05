/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/


#if !defined(ObjectCube_SETUP_ORACLE_) && defined(OC_ORACLE)
#define ObjectCube_SETUP_ORACLE_

#include "Setup.h"

namespace ObjectCube
{	
    class SetupOracle : public Setup
	{
	public:
		SetupOracle();
		
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
		
		int insertTestTag_( int tagSetId, int typeId );
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