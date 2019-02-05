/*
 *  Tag.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 25.10.2009.
 *  Copyright 2009 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_TAG_
#define ObjectCube_TAG_

#include <string>
#include "../LayerShared/TagCommon.h"

using namespace std;

namespace ObjectCube
{	
	class Tag : public TagCommon
	{
		friend class TagConverter;
		friend class TagSet;
		friend class PersistentHierarchyNode;
		
	public:
		//Constructors & destructor
		Tag();
		virtual ~Tag();
		
		const string valueAsString() const;  
		const string typeAsString() const;
		static const string typeAsString( int tagTypeId );
		
		int inUse() const;
		
		//Get/Set
		int getId() const { return id_; } 
		int getTagSetId() const { return tagSetId_; }
		int getTypeId() const { return typeId_; }
		
	protected:
		static Tag* fetch_( int id );
		virtual void fetchImp_() = 0;
		virtual void create_() = 0;  //Cannot exist standalone, only in a dimension.  The only way to create a tag is through a dimension
		virtual void delete_() = 0;
		virtual const string valueAsString_() const = 0;
		
		void setId_( int id ) { id_ = id; } //Used for testing
		void setTagSetId_( int tagSetId ) { tagSetId_ = tagSetId; }
		void setTypeId_( int typeId ) { typeId_ = typeId; }
		void assignValues_( const Tag& tag );
		
	private:
		virtual void init_();
		
	private:
		int id_;
		int tagSetId_;
		int typeId_;
		
	public: //Operators
		bool operator==( Tag const& x ) const;
		bool operator!=( Tag const& x ) const; 
		bool operator < ( const Tag& x ) const;
		
		static bool compareByValueAsString( Tag* tag1, Tag* tag2 );
		
		virtual Tag& operator=( const Tag& tag ) = 0;
		
		//For unit testing
		//For testing..... this needs refactoring !!!  Consider inheriting all logic classes and implementing public getters and setters for all member variables.
		friend class TagTest;
		friend class AlphanumericalTagTest;
        friend class NumericalTagTest;
        friend class DateTagTest;
        friend class TimeTagTest;
		friend class TagSetTest;
		friend class AlphanumericalTagSetTest;
		friend class NumericalTagSetTest;
		friend class HubTest;
		friend class ObjectTest;
		friend class PersistentDimensionTest;
		friend class PersistentHierarchyNodeTest;		
		
	};
	
}

#endif
