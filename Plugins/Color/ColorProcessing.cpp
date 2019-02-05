/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/

#include "ColorProcessing.h"

#include <iostream>
#include <sstream>
#include <math.h>

const int RGB_SCALING = 255;

ColorProcessing::ColorProcessing( int maxSampleSizePercentage, int minimumSamplePixelsPerAxis )
{
	maxSampleSizePercentage_ = maxSampleSizePercentage;
	minimumSamplePixelsPerAxis_ = minimumSamplePixelsPerAxis;
}

ColorProcessing::~ColorProcessing()
{

}

std::string IntToString ( int number )
{
  std::ostringstream oss;

  // Works just like cout
  oss<< number;

  // Return the underlying string
  return oss.str();
}

void ColorProcessing::processImage( PluginReply& reply, const void* data, int size )
{
	try 
	{
		Blob imBlob( (void*) data, size );
		Image img( imBlob );
		ColorData colorData = { 0,0,0,0,0,0 }; //Slightly nasty
		
		processImage_( img, colorData );

		stringstream stringStream;
		stringStream << IntToString( colorData.avgRed ) << ";" << IntToString( colorData.avgGreen ) << ";" << IntToString( colorData.avgBlue );
		string rgb = stringStream.str();

		reply.addTagging( toTagging_("Average.Red", IntToString( colorData.avgRed )) );
		reply.addTagging( toTagging_("Average.Blue", IntToString( colorData.avgBlue )) );
		reply.addTagging( toTagging_("Average.Green", IntToString( colorData.avgGreen )) );
		reply.addTagging( toTagging_("RGB", rgb));
	}
	catch( exception e ) 
	{
		cerr << "Execption in ColorProcessing::processImage, error: " << e.what() << endl;
	}
}

PluginTagging ColorProcessing::toTagging_( const string& tagSetName, const string& tag )
{
	Coordinate2D upperLeftCorner( 0.0, 100.0 );
	Coordinate2D lowerRightCorner( 100.0, 0.0 );
	BoundingBox boundingBox( upperLeftCorner, lowerRightCorner );

	//All taggings from this plugin are confirmed (true) and for the whole image
	return PluginTagging( tagSetName, tag, boundingBox, true );
}

void ColorProcessing::processImage_( Image& img, ColorData& colorData)
{
	img.colorSpace( RGBColorspace );
	
	int width = img.columns();
	int height = img.rows();
	
	int samplesPerAxis = pow( (double)( width * height ) * ( maxSampleSizePercentage_ / 100 ), 0.5 );
	if( samplesPerAxis < minimumSamplePixelsPerAxis_ )
	{
		samplesPerAxis = minimumSamplePixelsPerAxis_;
	}
	
	double intervalWidth = (double)width / ( samplesPerAxis - 1 );
	double intervalHeight = (double)height / ( samplesPerAxis -1 );
	if( intervalWidth < 1 ) //picture is smaller than maximum pixel samples
	{
		intervalWidth = 1; //All the pixels
	}
	if( intervalHeight < 1 )
	{
		intervalHeight = 1;
	}
	
	//We always want to sample the first and last pixel in both dimensions, for the whole grid
	//In other words, the grid starts at the edges
	
	double comparisonWidth = (double)width + 0.99;
	double comparisonHeight = (double)height + 0.99;
	for( double widthIndex = 0; widthIndex <= comparisonWidth; widthIndex += intervalWidth )
	{
		for( double heightIndex = 0; heightIndex <= comparisonHeight; heightIndex += intervalHeight )
		{
			ColorRGB rgbColor( img.pixelColor( widthIndex, heightIndex ) );
			processPixel_( rgbColor, colorData );
		}
	}
	
	int sampleCount = (int) pow( samplesPerAxis, 2 );
	
	colorData.avgRed = ( colorData.totalRed * RGB_SCALING ) / sampleCount;
	colorData.avgGreen = ( colorData.totalGreen * RGB_SCALING ) / sampleCount;
	colorData.avgBlue = ( colorData.totalBlue * RGB_SCALING ) / sampleCount;
}

void ColorProcessing::processPixel_( const ColorRGB& color, ColorData& colorData )
{
	colorData.totalRed += color.red();
	colorData.totalGreen += color.green();
	colorData.totalBlue += color.blue();
}

void ColorProcessing::processColor_( double color, int& min, int& max, double& avg )
{
	avg += color;
	
	int iColor = color * RGB_SCALING;
	if( iColor < min )
	{
		min = iColor;
		return;
	}
	if( iColor > max )
	{
		max = iColor;
		return;
	}	
}
