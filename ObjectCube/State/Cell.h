/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/

#ifndef ObjectCube_CELL_
#define ObjectCube_CELL_

#include <vector>
#include <string>

#include "../LayerShared/TagCommon.h"

using namespace std;

namespace ObjectCube
{
	class Tag;
	class TagSet;
	class StateObject;
	
	class Cell
	{
	public:
		Cell();
		~Cell() {;}
		Cell( vector<vector<Tag*> > dimensionTags, vector<string> displayLabels );
		
		bool belongs( const StateObject& object );
		
		string getAxisLabel( unsigned int axisNo ) const;
		
		const vector<StateObject> getObjects() const { return objects_; }
		unsigned int getObjectCount() const { return objects_.size(); }
		const vector<vector<Tag*> > getDimensionTags() const { return dimensionTags_; }

		// Sorts the objects list by the value the object has of the tag type given
		// If object does not have tag type, then it is at the end of the list in any order
		void sort( TagSet* tagSet );

		// Currently only set to work for Date first and Time second. Will be fixed soon.
		void sortTwo( TagSet* firstTagSet, TagSet* secondTagSet );

	protected:
		void setAxisLabel_( int axisNo, const string& label );
	
	private:
		vector<vector<Tag*> > dimensionTags_;	
		vector<string> displayLabels_;
		vector<StateObject> objects_;
		
		friend class MultiDimensionalView;
		
	public:
			bool operator==( Cell const& x) const { return x.getDimensionTags() == getDimensionTags(); }
	};
	
}

#endif
