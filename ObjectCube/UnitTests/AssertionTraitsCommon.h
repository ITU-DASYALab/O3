/*
 *  AssertionTraitsCommon.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 25.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#ifndef ObjectCube_ASSERTION_TRAITS_COMMON_
#define ObjectCube_ASSERTION_TRAITS_COMMON_

#include <algorithm>

namespace CppUnit 
{
	template <typename T>
	struct PointerLessThan
	{
		const bool operator()(const T* a, const T* b) const 
		{
			// check for 0
			if (a == 0) 
			{
				return b != 0; // if b is also 0, then they are equal, hence a is not < than b
			} 
			else if (b == 0) 
			{
				return false;
			} 
			return *a < *b;
		}
	};
	
	class AssertionTraitsCommon
	{
	public:
		
		//Value version
		template <class T>
		static bool equalLists( const vector<T>& x, const vector<T>& y )
		{
			if ( x.size() != y.size() ) 
			{
				return false;
			}
			
			vector<T> xSorted = x;
			vector<T> ySorted = y;
			sort( xSorted.begin(), xSorted.end() );
			sort( ySorted.begin(), ySorted.end() );
			
			for (int i = 0; i < xSorted.size(); i++) 
			{
				if(	!assertion_traits<T>::equal( xSorted[i], ySorted[i] ) )
				{
					return false;
				}
			}
			return true;	
		}		
		
		//Pointer version
		template <class T>
		static bool equalLists( const vector<T*>& x, const vector<T*>& y )
		{
			if ( x.size() != y.size() ) 
			{
				return false;
			}
			
			vector<T*> xSorted = x;
			vector<T*> ySorted = y;
			sort( xSorted.begin(), xSorted.end(), PointerLessThan<T>() );
			sort( ySorted.begin(), ySorted.end(), PointerLessThan<T>() );
			for (int i = 0; i < xSorted.size(); i++) 
			{
				if(	!assertion_traits<T>::equal( *xSorted[i], *ySorted[i] ) )
				{
					return false;
				}
			}
			return true;	
		}
		
		
		template <class T>
		bool pointerComparisonFunction( T* x, T* y )
		{
			return *x < *y;
		}
		
	};
	
}

#endif
