/*
 *  PhotoSet.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 25.10.2009.
 *  Copyright 2009 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_STATE_
#define ObjectCube_STATE_

#include <vector>
#include <map>
#include "StateObject.h"
#include "StateDimension.h"
#include "MultiDimensionalView.h"

using namespace std;

namespace ObjectCube
{
	class Filter;
	
	class State
	{
	public:
		~State() {;}
		
		static void addFilter( Filter* /*const*/ filter ); //Each filter is on a single dimension
		static void removeFilter( Filter* filter );
		static void removeAllFilters();
		static const vector<Filter*> getFilters();
		static const State getState(); 
		
		const vector<StateObject> getObjects() const { return objects_; }
		const vector<StateObject> getObjects( const vector<int>& objectIds ) const;
		const vector<StateDimension> getDimensions() const { return dimensions_; }
		const StateDimension getDimension( int dimensionId ) const;
		
		const MultiDimensionalView getMultiDimensionalView( bool withEmptySlices = true) const;
		
	protected:
		void setObjects_( const vector<StateObject>& objects ) { objects_ = objects; }
		void setDimensions_( const vector<StateDimension>& dimensions ) { dimensions_ = dimensions; }
		map<int, map<int, vector<int> > >& getFilterIdNodeIdObjectIds() { return filterIdNodeIdObjectIds_; } 
		
	private:
		vector<StateObject> objects_;
		vector<StateDimension> dimensions_;
		map<int, map<int, vector<int> > > filterIdNodeIdObjectIds_;  //Used to add object_id's to hierarchies efficiently


		friend class Hub;
	};
	
}

#endif