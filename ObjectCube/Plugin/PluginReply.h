/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2011. All rights reserved.
 **********************************************************************/

#ifndef ObjectCube_PLUGIN_REPLY_
#define ObjectCube_PLUGIN_REPLY_

#include <vector>
#include "PluginTagging.h"

using namespace std;

namespace ObjectCube
{
	class PluginReply
	{
	public:
		PluginReply();
		PluginReply( int objectId );
		PluginReply( int objectId, const vector<PluginTagging>& taggings );
		
		void addTagging( const PluginTagging& tagging ) { taggings_.push_back( tagging); }
		
		//Get
		int getObjectId() const { return objectId_; }
		vector<PluginTagging> getTaggings() const { return taggings_; }
		
		//Set
		void setObjectId( int objectId ) { objectId_ = objectId; }
		void setTaggings( const vector<PluginTagging>& taggings ) { taggings_ = taggings; }
	
	private:
		int objectId_;
		vector<PluginTagging> taggings_;
		
	};
	
	
}

#endif
