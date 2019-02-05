/*
 *  memoryManagement.h
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 27.4.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */
#include <algorithm>

#ifndef ObjectCube_MEMORY_MANAGEMENT_
#define ObjectCube_MEMORY_MANAGEMENT_

//____________________________________________________________________________________________________________________________________________________________________________________

struct delete_object 
{
	template <typename T>
	void operator()( T* object )
	{ 
		if( object != 0 )
		{
			delete object;
			object = 0;
		}
	}
};
//____________________________________________________________________________________________________________________________________________________________________________________

template <class T>
void clearAndDestroy( vector<T*>& vec )
{
	for_each( vec.begin(), vec.end(), delete_object() );
	vec.clear();
}
//____________________________________________________________________________________________________________________________________________________________________________________

//This is from: http://www.gamedev.net/community/forums/topic.asp?topic_id=555248
template<typename T>
class dereference_t
{
    T* pointer;
	
public:
	
    dereference_t(T* p) : pointer(p) {}
	
    bool operator()(T* p)
    {
        return *p == *pointer;
    }
};
//____________________________________________________________________________________________________________________________________________________________________________________

template<typename T>
dereference_t<T> dereference(T* p)
{
    return dereference_t<T>(p);
}
//____________________________________________________________________________________________________________________________________________________________________________________

template<typename T>
T* clone(const T* original)
{
	T* clone = new T();
	*clone = *original;
	return clone;
}

#endif
