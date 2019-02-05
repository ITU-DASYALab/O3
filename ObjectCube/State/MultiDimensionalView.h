/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/

#ifndef ObjectCube_MULTI_DIMENSIONAL_VIEW_
#define ObjectCube_MULTI_DIMENSIONAL_VIEW_

#include <vector>
#include <map>
#include <stdint.h>

#include "StateObject.h"
#include "StateDimensionNode.h"
#include "Cell.h"

using namespace std;

namespace ObjectCube
{
	class StateDimension;
	class TagSet;
	
	class MultiDimensionalView
	{
	public:
		MultiDimensionalView( const vector<StateObject>& objects, bool withEmptySlices = false );
		~MultiDimensionalView() {;}
		
		enum AXES
		{
			AXIS_1 = 0,
			AXIS_2 = 1,
			AXIS_3 = 2,
			AXIS_4 = 3,
			AXIS_5 = 4,
			AXIS_6 = 5
		};
		
		static void setAxis( unsigned int axis, StateDimensionNode stateDimensionNode, int viewDepth = 0 );
		static void setAxis( unsigned int axis, TagSet* tagSet );
				
		static void clearAxis( unsigned int axis );
		static void clearAxes();

		static int numberOfDimensions();
		
		const map<string, Cell> getCells(unsigned int maxObjects = 999999, unsigned int maxObjectsPerCell = 999999 ) const;
		
		int getAxisCellCount( unsigned int axis );
		int getObjectCount() const { return noObjects_; }
		int getUniqueObjectCount() const { return noUniqueObjects_; }
		
		bool getWithEmptySlices() const { return withEmptySlices_; }
		
	public:
		enum DIMENSION_TYPE
		{	INVALID = -1,
			TAG_SET = 1,
			HIERARCHY_NODE = 2
		};
		
	private:
		class Axis
		{
		public:
			Axis();
			Axis( TagSet* tagSet );
			Axis( StateDimensionNode node, int viewDepth );
			
			TagSet* getTagSet();
			StateDimensionNode getNode();
			int getType() const { return type_;}
			int getCellCount() const ;
			int getViewDepth() const { return viewDepth_; }
			
			bool operator==( Axis const& x ) const;
			
		private:
			TagSet* tagSet_;
			StateDimensionNode node_;
			int type_;
			int viewDepth_;
			vector<vector<Tag*> > tags_; // The tags for each dimension, 2-dimensional for hierarchies
			vector<string> displayLabels_;
			
			friend class MultiDimensionalView;
		};		
		
	protected:
		void getTagsForAxis_( Axis& axis, const vector<StateObject>& objects );
		MultiDimensionalView::Axis getAxis_( unsigned int axis );
		
		void addObjectsToCells_( const vector<StateObject>& objects );
		void processCell_( const vector<StateObject>& objects, Cell& cell, const string& key );
		
		void setObjectCount_( int count ) { noObjects_ = count; }
		void setUniqueObjectCount_( int count ) { noUniqueObjects_ = count; }
		
		void setWithEmptySlices_( bool withEmpty ) { withEmptySlices_ = withEmpty; }
		
	private:
		void construct_( const vector<StateObject>& objects );
		bool generateKey_( string& key, const vector<unsigned int>& dimensionCellCounts, vector<unsigned int>& currCounts, unsigned int& currDimension );
		
		bool inUse_( int tagId, const vector<StateObject>& objects );
		bool inUse_( map<int, int>& tagIdNodeId, const vector<StateObject>& objects );
		
		bool withEmptySlices_;
		int noObjects_;
		int noUniqueObjects_; // The object count of the state 
		
		map<string, Cell> dimensionalCellMap_; 
		
			
		
		
		static vector<Axis> axes_;
	};

}

#endif
