/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2011. All rights reserved.
 **********************************************************************/

#ifndef ObjectCube_PLUGIN_TAGGING_
#define ObjectCube_PLUGIN_TAGGING_

#include <string>
#include "../Boundaries/BoundingBox.h"
#include <vector>

using namespace std;

namespace ObjectCube
{
	class PluginTagging
	{
	public:
		PluginTagging();
		PluginTagging( string tagSetName, string tag, BoundingBox boundingBox, bool confirmed );
		virtual ~PluginTagging() {;}
		
		//Get
		string getTagSetName() const { return tagSetName_; }
		string getTag() const { return tag_; }
		BoundingBox getBoundingBox() const { return boundingBox_; }
		bool getConfirmed() const { return confirmed_; }

		vector<string> getSuggestedTags() const { return suggestedTags_; }
		
		//Set
		void setTagSetName( const string& tagSetName ) { tagSetName_ = tagSetName; }
		void setTag( const string& tag ) { tag_ = tag; }
		void setBoundingBox( const BoundingBox& boundingBox ) { boundingBox_ = boundingBox; }
		void setConfirmed( bool confirmed ) { confirmed_ = confirmed; }

		void setSuggestedTags(const vector<string> suggestedTags) { suggestedTags_ = suggestedTags; }

	protected:
		string tagSetName_;
		string tag_;
		vector<string> suggestedTags_; //Not supported in OC atm.
		BoundingBox boundingBox_; 
		bool confirmed_;
	};

	
}

#endif
