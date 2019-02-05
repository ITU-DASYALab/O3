/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2011. All rights reserved.
 **********************************************************************/

#ifndef ObjectCube_PLUGIN_TAGGING_PROCESSED_
#define ObjectCube_PLUGIN_TAGGING_PROCESSED_

#include "PluginTagging.h"

using namespace std;

namespace ObjectCube
{
	class PluginTaggingProcessed : public PluginTagging
	{
	public:
		PluginTaggingProcessed();
		PluginTaggingProcessed( int objectId, int tagSetId, const PluginTagging& pluginTagging );
		
		virtual ~PluginTaggingProcessed() {;}
		
		//Get
		int getObjectId() const { return objectId_; }
		int getTagSetId() const { return tagSetId_; }
		
		//Set
		void setObjectId( int objectId ) { objectId_ = objectId; }
		void setTagSetId( int tagSetId ) { tagSetId_ = tagSetId; }
		
	private:
		int objectId_;
		int tagSetId_;
		
	public:
		bool operator < ( const PluginTaggingProcessed& b ) const;
		bool operator==( PluginTaggingProcessed const& x) const;
	
	};
	
	
}

#endif
