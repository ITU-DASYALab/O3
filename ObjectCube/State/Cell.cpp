/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/

#include "Cell.h"

#include "../Tag/DateTag.h"
#include "../Tag/TimeTag.h"
#include "../TagSet/TagSet.h"
#include "StateObject.h"
#include "../LayerShared/Exception.h"

#include <algorithm>

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

Cell::Cell()
{

}
//____________________________________________________________________________________________________________________________________________________________________________________

Cell::Cell( vector<vector<Tag*> > dimensionTags, vector<string> displayLabels )
{
	dimensionTags_ = dimensionTags;
	displayLabels_ = displayLabels;
}
//____________________________________________________________________________________________________________________________________________________________________________________

bool Cell::belongs( const StateObject& object )
{	
	//We have to find at least one match per dimension, we can exit if we do not find a match for a dimension
	
	for( unsigned int outerIndex = 0; outerIndex < dimensionTags_.size(); ++outerIndex )  //Dimension
	{
		bool matchFound = false;
		for( unsigned int innerIndex = 0; innerIndex < dimensionTags_[ outerIndex ].size(); ++innerIndex ) //Tags per dimension (potentially multiple for hierarchies)
		{
			//DEBUG !!!
			//Tag* debugTag = dimensionTags_[ outerIndex ][ innerIndex ];
			
			Tag* tempTag = dimensionTags_[ outerIndex ][ innerIndex ];
			int tagId = tempTag->getId();
			if( object.hasTag( tagId ) )
			{
				matchFound = true;
			}
		}
		if( !matchFound )
		{
			return false;
		}
	}
	
	//The object belongs in this cell!
	//objects_.push_back( const_cast<StateObject*>( &object ) );
	objects_.push_back( object );
	return true;
}
//____________________________________________________________________________________________________________________________________________________________________________________

string Cell::getAxisLabel( unsigned int axisNo ) const
{
	if( displayLabels_.size() < axisNo )
	{
		throw Exception( "Cell::getAxisTag", "Axis does not exist!", axisNo );
	}
	return displayLabels_[ axisNo ];
}
//____________________________________________________________________________________________________________________________________________________________________________________

struct CellSort
{
    TagSet* ts_;

    CellSort(TagSet* ts)
    {
        ts_ = ts;
    }

    const Tag* getTagByTagSetId( const StateObject& object, int id )
    {
        const Tag* tag;

        const vector<StateTag> tags = object.getTags();
        unsigned int objSize = tags.size();
        for( unsigned int i = 0; i < objSize; ++i )
        {
            const Tag* t = tags.at(i).getTag();
            int tagSetId = t->getTagSetId();

            if( tagSetId == id )
            {
                return t;
            }
        }

        return NULL;
    }
};

struct CellDateTimeSort : public CellSort
{
    TagSet* ts2_;

    CellDateTimeSort(TagSet* ts, TagSet* ts2): CellSort(ts)
    {
        ts2_ = ts2;
    }

    bool operator()( const StateObject& a, const StateObject& b )
    {
        const DateTag* aDateTag = dynamic_cast<const DateTag*>(getTagByTagSetId(a, ts_->getId()));
        const DateTag* bDateTag = dynamic_cast<const DateTag*>(getTagByTagSetId(b, ts_->getId()));

        const TimeTag* aTimeTag = dynamic_cast<const TimeTag*>(getTagByTagSetId(a, ts2_->getId()));
        const TimeTag* bTimeTag = dynamic_cast<const TimeTag*>(getTagByTagSetId(b, ts2_->getId()));

        if( aDateTag == NULL || aTimeTag == NULL )
        {
            return false;
        }

        if( bDateTag == NULL || bTimeTag == NULL )
        {
            return true;
        }

        // TODO: Waage fix this to use the compare functions!
        // Doesn't work now due to them having an exit result
        if( aDateTag->getYear() != bDateTag->getYear() )
        {
            return aDateTag->getYear() < bDateTag->getYear();
        }

        if( aDateTag->getMonth() != bDateTag->getMonth() )
        {
            return aDateTag->getMonth() < bDateTag->getMonth();
        }

        if( aDateTag->getDayOfMonth() != bDateTag->getDayOfMonth() )
        {
            return aDateTag->getDayOfMonth() < bDateTag->getDayOfMonth();
        }

        if( aTimeTag->getHours() != bTimeTag->getHours() )
        {
            return aTimeTag->getHours() < bTimeTag->getHours();
        }

        if( aTimeTag->getMinutes() != bTimeTag->getMinutes() )
        {
            return aTimeTag->getMinutes() < bTimeTag->getMinutes();
        }

        if( aTimeTag->getSeconds() != bTimeTag->getSeconds() )
        {
            return aTimeTag->getSeconds() < bTimeTag->getSeconds();
        }

        if( aTimeTag->getMilliseconds() != bTimeTag->getMilliseconds() )
        {
            return aTimeTag->getMilliseconds() < bTimeTag->getMilliseconds();
        }

        return true;
    }
};

struct CellDateSort : public CellSort
{
    CellDateSort(TagSet* ts): CellSort(ts){}

    bool operator()( const StateObject& a, const StateObject& b )
    {
        const DateTag* aTag = dynamic_cast<const DateTag*>(getTagByTagSetId(a, ts_->getId()));
        const DateTag* bTag = dynamic_cast<const DateTag*>(getTagByTagSetId(b, ts_->getId()));

        if( aTag == NULL )
        {
            return false;
        }

        if( bTag == NULL )
        {
            return true;
        }

        return DateTag::compare( aTag, bTag );
    }
};

struct CellTimeSort : public CellSort
{
    CellTimeSort(TagSet* ts): CellSort(ts){}

    bool operator()( const StateObject& a, const StateObject& b )
    {
        const TimeTag* aTag = dynamic_cast<const TimeTag*>(getTagByTagSetId(a, ts_->getId()));
        const TimeTag* bTag = dynamic_cast<const TimeTag*>(getTagByTagSetId(b, ts_->getId()));

        if( aTag == NULL )
        {
            return true;
        }

        if( bTag == NULL )
        {
            return false;
        }

        return TimeTag::compare( aTag, bTag );
    }
};

void Cell::sort( TagSet* tagSet )
{
    if( tagSet->getTypeId() == TagCommon::DATE )
    {
        CellDateSort cds(tagSet);
        std::sort(objects_.begin(), objects_.end(), cds);
    }
    else if( tagSet->getTypeId() == TagCommon::TIME )
    {
        CellTimeSort cts(tagSet);
        std::sort(objects_.begin(), objects_.end(), cts);
    }
}

void Cell::sortTwo( TagSet* firstTagSet, TagSet* secondTagSet )
{
    if( firstTagSet->getTypeId() == TagCommon::DATE && secondTagSet->getTypeId() == TagCommon::TIME )
    {
        CellDateTimeSort cdts(firstTagSet, secondTagSet);
        std::sort(objects_.begin(), objects_.end(), cdts);
    }
}

//____________________________________________________________________________________________________________________________________________________________________________________
