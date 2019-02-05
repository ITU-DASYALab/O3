/***********************************************************************
 ** Reykjavik University
 ** Gr�mur T�masson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/

#ifndef Color_Plugin_
#define Color_Plugin_

// The classes below are exported 
#pragma GCC visibility push(default)

#include <map>
#include <string>
#include "../../ObjectCube/Plugin/ProcessObjectPlugin.h"

using namespace std;
using namespace ObjectCube;

class Color_Plugin : public ProcessObjectPlugin
  {
  public:
	  Color_Plugin( const int id );
	  virtual ~Color_Plugin() {;}
	  
	  virtual PluginReply process( const PluginObject& object );
	  virtual PluginReply process( const PluginObject& object, const vector<BoundingBox>& boundingBoxes );
	  void renameTag(const string& tagSetName, const string& oldTagName, const string& newTagName );
	  void mergeTags(const string& tagSetName, const string& oldTagName, const string& newTagName );
	  void confirmTagging(int objectId, const string& tagSetName, const BoundingBox& boundingBox, const string& tag );
	  void deleteTagging(int objectId,const string& tagSetName, const BoundingBox& boundingBox, const string& tag );
	  void updateTagging(int objectId, const string& tagSetName, const BoundingBox& boundingBox, const string& oldTag, const string& newTag);
	  void taggingNotification(int objectId, const string& tagSetName, const BoundingBox& boundingBox, const string& tag );

	  
  };

#pragma GCC visibility pop
#endif
