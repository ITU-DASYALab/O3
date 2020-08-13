/*
 *  dimension.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 25.10.2009.
 *  Copyright 2009 Reykjavik University. All rights reserved.
 *
 */
#ifndef ObjectCube_TAG_SET_
#define ObjectCube_TAG_SET_

#include <string>
#include <vector>
#include <map>

#include "../LayerShared/TagSetCommon.h"

#include "../Hierarchy/PersistentDimension.h"
#include "../Hierarchy/VirtualDimension.h"


using namespace std;

namespace ObjectCube 
{
	
	//class Tag;
	class Object;
	class Filter;
	class Tag;
	class AlphanumericalTag;
	class RGBTag;
	class Dimension;
	class DefaultDimension;
	
	//Abstract
	class TagSet : public TagSetCommon
	{
		friend class Hub;
		friend class TagSetConverter;
				
	public:
		TagSet(); 
		TagSet( const string& name );
		TagSet( const string& name, const string& description );
		TagSet( const TagSet& tagSet ); //Copy constructor
		
		virtual TagSet& operator=( const TagSet& tagSet );

		virtual ~TagSet();
		
		TagSet* create();
		virtual void erase();
		
		const Tag* /*const*/ addTag( const Tag* /*const*/ tag); //Const removed due to boost python limitation
		void deleteTag( const Tag* /*const*/ tag );
		
		PersistentDimension* createPersistentDimension( const Tag* tag );
		void deleteDimension( int id );
		
		//Get/Set
		int getId() const { return id_; }
		string getName() const { return name_; }
		string getDescription() const { return description_; }
		int getTypeId() const { return typeId_; }
		int getAccessId() const { return accessId_; }
		
		const string typeAsString() const;
		static const string typeAsString( int tagSetTypeId );

		const string accessTypeAsString() const;
		static const string accessTypeAsString( int tagSetAccessTypeId );
		
		const Tag* /*const*/ getTag( int id ) const; //Const removed due to boost python limitation
		
		virtual const Tag* /*const*/ fetchOrAddTag( const string& value ) = 0;
		
		const vector<Tag*> getTags() const;
		const vector<Tag*> getTags( const vector<int>& tagIds ) const;
		const vector<Filter*> getFilters() const;
		
		PersistentDimension* getPersistentDimension( int dimensionId );
		PersistentDimension* getPersistentDimension( const string& name ); 
		const vector<PersistentDimension*> getPersistentDimensions() const;
		
		const VirtualDimension* getVirtualDimension( int dimensionId ) const;
		const VirtualDimension* getVirtualDimension( const string& name ) const;
		const vector<VirtualDimension*> getVirtualDimensions() const;
		
		Dimension* getDimension( int dimensionId );
		Dimension* getDimension( const string& name );
		const Dimension* getDimension( int dimensionId ) const;
		const Dimension* getDimension( const string& name ) const;
		
		const vector<Dimension*> getDimensions() const;
		
		const DefaultDimension* getDefaultDimension() const ;

		void setName( const string& name ) { name_ = name; }
		void setDescription( const string& description ) { description_ = description; }
		
		bool operator==( TagSet const& x) const { return getId() == x.getId(); }
		
	protected:
		virtual TagSet* createImp_(); //Public interface, protected virtual pattern
		virtual void fetch_( int id ); 
		virtual void loadVirtualDimensions_();
		
		void setId_( int id ) { id_ = id; }
		void setTypeId_( int typeId ) { typeId_ = typeId; }
		void setAccessId_( int accessId ) { accessId_ = accessId; }
		void setTags_( vector<std::shared_ptr<Tag> > tags ) { tags_ = tags; }

	//Framework support functionality
		virtual void addFilter_( Filter* /*const*/ filter );
		virtual void removeFilter_( Filter* filter );
		virtual void removeFilters_();
				
	private:  //Helper functions
		virtual void init_();
		bool supportedFilter_( const Filter* /*const*/ filter );
		bool supportedTagType_( const Tag* /*const*/ tag );
		void creationTest_();
		void loadDefaultDimension_();
		
		//Memory management
		void copyValues_( const TagSet& tagSet );
		void cleanup_();
		
	protected: //Variables
		int id_;
		string name_;
		string description_;
		int typeId_;
		int accessId_;
		
		vector<std::shared_ptr<Tag> > tags_;
		vector<std::shared_ptr<Dimension> > dimensions_;
		
		vector<std::shared_ptr<Filter> > filters_;
		vector<int> supportedFilterTypes_;
		vector<int> supportedTagTypes_;
		
		//Change to normal pointers, may be causing double memory cleanup
		//static map<int, std::shared_ptr<Tag> > allTags_;  //This is here only for performance reasons, the pointers are memory managed in a std::shared_ptr vector
		static map<int, Tag*> allTags_;
		//static map<int, std::shared_ptr<Tag> > allTags_;
		
		//For unit tests
		friend class TagSetTest;
		friend class ObjectTest;
		
		//DEBUG!!!
		friend class DebugTest;
	};
	
}

#endif