/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/


#ifndef COLOR_PROCESSING
#define COLOR_PROCESSING

#include <map>
#include <Magick++.h>

#include "ColorData.h"
#include "../../ObjectCube/Plugin/ProcessObjectPlugin.h"

using namespace std;
using namespace Magick;
using namespace ObjectCube;

class ColorProcessing
{
public:
	ColorProcessing( int maxSampleSizePercentage, int minimumSamplePixelsPerAxis );
	virtual ~ColorProcessing();
	
	void processImage(PluginReply& reply, const void *data, int size );
	
private:
	void processImage_( Image& img, ColorData& colorData);
	void processPixel_( const ColorRGB& color, ColorData& colorData );
	void processColor_( double color, int& min, int& max, double& avg );
	
	PluginTagging toTagging_( const string& tagSetName, const string& tag );
	
private:
	int maxSampleSizePercentage_;
	int minimumSamplePixelsPerAxis_;
	
	
};

#endif
