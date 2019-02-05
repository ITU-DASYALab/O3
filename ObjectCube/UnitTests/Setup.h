/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/


#ifndef ObjectCube_SETUP_
#define ObjectCube_SETUP_

namespace ObjectCube
{	
	
    class Setup
	{
	public:
		virtual void setup() = 0;
		virtual void cleanup() = 0;
	
	};

}

#endif