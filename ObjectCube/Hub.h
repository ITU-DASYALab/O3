/*
 *  Framework.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 25.10.2009.
 *  Copyright 2009 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_HUB_
#define ObjectCube_HUB_

#include <vector>

#ifdef __APPLE__
#include <memory>
using std::shared_ptr;
#else
#include <tr1/memory>
using std::shared_ptr;
#endif

#include "LayerShared/HubCommon.h"
#include "Object.h"
#include "State/StateObject.h"
#include "State/State.h"
#include "LayerShared/LanguageCommon.h"
#include "Plugin/PluginTaggingProcessed.h"

using namespace std;

namespace ObjectCube 
{
	class TagSet;
	class Tag;
	class Filter;
	class PluginObject;
	class PluginServer;
	class PluginCommon;
	class PluginTagSet;
	class Dimension;
	class PersistentDimension;
	class VirtualDimension;
	
	/*
	 This class is not a part of the public interface
	 */
	class Hub : public HubCommon //Singleton
	{
	public:
		static Hub* getHub();
		
		TagSet* addTagSet( TagSet* /*const*/ tagSet );
		void removeTagSet( TagSet* /*const*/ tagSet );
		//Setja inn addSystemDimension fall, á ekki heima í TagSet tréinu
		
		void addObject( Object& object );
		
		//The next two functions are to process all objects by a certain plugin (and thereby tag them)
		int processAllObjects( int pluginId );
		int processAllObjects( int pluginId, int reportInterval, void (*funcPtr)(int) );
				
		int getParentTagSetsAccessType( const Tag* /*const*/ tag ) const;  //Helper function, Tags only have access by association with dimensions (inheritance)
		const Tag* /*const*/ getUncategorizedTag() const;  //The one and only uncategorized tag from the uncategorized dimension.
		
		//Object selection
		void addFilter( Filter* /*const*/ filter );
		void removeFilter( Filter* filter );
		void removeAllFilters();
		const vector<Filter*> getFilters() const;
		const vector<Filter*> getFilters( int filterType ) const;
		
		vector<StateObject> getObjects();
		State getState();

		//Search objects
		static const vector<int> searchText( const string& name );
		static const vector<int> searchRGB( const string& name );
		
		unsigned int getObjectCount();

		vector<TagSet*> getTagSets() const;
		TagSet* getTagSet( int id );
		TagSet* getTagSet( const string& name );
		
		const vector<Dimension*> getDimensions() const;
		const vector<PersistentDimension*> getPersistentDimensions() const;
		const vector<VirtualDimension*> getVirtualDimensions() const;
		
		const vector<PluginCommon*> getProcessObjectPlugins() const;
		
		const vector<Tag*> getTags( const vector<int>& tagIds ) const; //Objects only store pointers to tags, the tag-sets own and manage tag memory.
		const vector<Tag*> getAllTags() const; //All tags in the system
		const Tag* /*const*/ getTag( int id ) const;
		
		static int getLanguageId() { return LanguageCommon::getLanguageId_(); }
		static void setLanguageId( int languageId ) { LanguageCommon::setLanguageId_( languageId ); }
		
		std::shared_ptr<PluginServer> getPluginServer() { return pluginServer_; }
		
		const string getLastObjectsQueryAsString() { return lastGetObjectsQueryAsString_; }  //For debugging and experiments

		void destroy();
		void refreshMaterializedViews();
		
		~Hub();
	protected:
		Hub();
		Hub( const Hub& hub ); //Not implemented on purpose
		Hub& operator=( const Hub& hub ); //Not implemented on purpose
		
		void loadTagSets_(); //Get all the dimensions, currently in the system, from persistent storage
		void loadPlugins_();
		
	private:
		static void init_();	
		void createMissingPluginTagSets_();
		int createPluginTagSet_( int tagSetType, const string& name );
		PluginObject* getPluginObject_( const Object& object ) const;
		void tagObject_(  const vector<PluginTaggingProcessed>& potentialTags, Object& object );
		
		//Memory management
		void cleanup_();
		
	private:
		int tagSetDataAccessType_;
		string lastGetObjectsQueryAsString_;
		
		vector<std::shared_ptr<TagSet> > tagSets_;
		std::shared_ptr<PluginServer> pluginServer_;
		
		static std::shared_ptr<Hub> instance_;
		
		friend class HubTest;
	};
}

#endif
