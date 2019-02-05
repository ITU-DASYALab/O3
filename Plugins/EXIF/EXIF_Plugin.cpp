/*
 *  EXIF_Plugin.cp
 *  EXIF_Plugin
 *
 *  Created by Grímur Tómasson on 15.3.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */

#include <iostream>
#include <fstream>
#include <exiv2/image.hpp>
#include <exiv2/exif.hpp>
#include <iomanip>
#include <cassert>

#include "EXIF_Plugin.h"

#include "../../ObjectCube/Plugin/PluginServer.h"
#include "../../ObjectCube/Plugin/PluginObject.h"

#define EXPORT __attribute__((visibility("default")))

using namespace std;



EXIF_Plugin::EXIF_Plugin( const int id )
:	ProcessObjectPlugin( id )
{
	init_();
}


//A neccessary part of all plugins
PluginReply EXIF_Plugin::process( const PluginObject& /*object*/, const vector<BoundingBox>& /*boundingBoxes*/ ) { return {}; }
void EXIF_Plugin::renameTag( const string& /*tagSetName*/, const string& /*oldTagName*/, const string& /*newTagName*/ ) {}
void EXIF_Plugin::mergeTags(	const string& /*tagSetName*/, const string& /*oldTagName*/, const string& /*newTagName*/ ) {}
void EXIF_Plugin::confirmTagging( int /*objectId*/, const string& /*tagSetName*/, const BoundingBox& /*boundingBox*/, const string& /*tag*/ ) {}
void EXIF_Plugin::deleteTagging(	int /*objectId*/,const string& /*tagSetName*/, const BoundingBox& /*boundingBox*/, const string& /*tag*/ ) {}
void EXIF_Plugin::updateTagging(	int /*objectId*/, const string& /*tagSetName*/, const BoundingBox& /*boundingBox*/, const string& /*oldTag*/, const string& /*newTag*/) {}
void EXIF_Plugin::taggingNotification( int /*objectId*/, const string& /*tagSetName*/, const BoundingBox& /*boundingBox*/, const string& /*tag*/ ) {}

PluginReply EXIF_Plugin::process( const PluginObject& object )
{
	PluginReply reply( object.getId() );
	try 
	{
		Exiv2::Image::AutoPtr image = Exiv2::ImageFactory::open( reinterpret_cast<const Exiv2::byte*>( object.getBinaryData() ), object.getDataSizeInBytes() );
		image->readMetadata();

		Exiv2::ExifData exifData = image->exifData();
		if( exifData.empty() ) 
		{
			return reply; //No error, just a lack of data
		}
		
		for( Exiv2::ExifData::const_iterator itr = exifData.begin(); itr != exifData.end(); ++itr )
		{
			processMetaDatum_( *itr, reply );
		}
		
	}
	catch (Exiv2::AnyError& e) 
	{
		//Log error or return an error list too?
		std::cerr << "Error caught: " << e << std::endl;
	}
	catch(...)
	{
		std::cerr << "Unknown error in EXIF_Plugin::process" << std::endl;
	}
	
	return reply;
}


void EXIF_Plugin::processMetaDatum_( const Exiv2::Metadatum& metaDatum, PluginReply& reply )
{
	//We will only pick out a few keys, most of the exif data is of little interest, see init_() for the set of tags.
	if( !tagsToProcess_.count( metaDatum.key() ) )
	{
		return; //Not a tag we're interested in
	}
	/*
	std::cout	<< "key: " << metaDatum.key() 
				<< " value: " << metaDatum.toString() 
				<< " label: " << metaDatum.tagLabel() 
				<< " type(s): " << metaDatum.typeName() 
				<< " type: " << metaDatum.typeId() << std::endl;
	*/
	
	std::string value;
	switch ( metaDatum.typeId() ) 
	{
		case Exiv2::asciiString :
			if( extractDateAndTime_.count( metaDatum.key() ) )
			{
				std::string time = extractTime_( metaDatum.toString() );
				if( time.length() )
				{
					//tagMap.insert( pair<string, string>( metaDatum.key() + " - TIME", time ) );
					reply.addTagging( toTagging_( metaDatum.key() + " - TIME", time ) );
				}
				std::string date = extractDate_( metaDatum.toString() );
				if( date.length() )
				{
					//tagMap.insert( pair<string, string>( metaDatum.key() + " - DATE", date ) );
					reply.addTagging( toTagging_( metaDatum.key() + " - DATE", date ) );
				}
				return;
			}
			value = metaDatum.toString();  
			break;
		case Exiv2::unsignedRational :
		case Exiv2::unsignedShort : 
		case Exiv2::signedRational :
		case Exiv2::unsignedLong : 
			value = metaDatum.toString();  // Supported formats are:  "integer/integer" or "integer".  Both can be prefixed with -.  Neither can contain any other symbols, such as . and ,
			break;
		default:
			throw Exiv2::Error( 1, "Unknown data type in formatValue_" );
	}
	
	if( value.length() )
	{
		//tagMap.insert( pair<string, string>( metaDatum.key(), value ) );
		reply.addTagging( toTagging_( metaDatum.key(), value ) );
	}
}

										  
PluginTagging EXIF_Plugin::toTagging_( const string& tagSetName, const string& tag )
{
	Coordinate2D upperLeftCorner( 0.0, 100.0 );
	Coordinate2D lowerRightCorner( 100.0, 0.0 );
	BoundingBox boundingBox( upperLeftCorner, lowerRightCorner );
	
	return PluginTagging( tagSetName, tag, boundingBox, true ); //All taggings from this plugin are confirmed (true) and for the whole image
}

										  
std::string EXIF_Plugin::extractDate_( const std::string& value )
{
	//This should be done using regular expressions, but for simplicities sake we will not add boost or other regex libraries for now.
	
	//The only allowed format is YYYY-MM-DD (numerical year, numerical month, numerical day of month)
	
	std::string date;
	if( value.find( " " ) != std::string::npos )
	{
		date = value.substr( 0, value.find( " " ) );
	}
	else
	{
		date = value;
	}
	
	if( date.length() != 10 )
	{
		return "";
	}
	
	while( date.find(':') != std::string::npos )
	{
		date.replace( date.find(':'), 1, "-" );
	}
	
	if( date.substr( 4, 1 ) != "-"  || date.substr( 7, 1 ) != "-" )
	{
		return "";
	}
	
	int temp;
	try 
	{
		if( atoi( date.substr( 0, 4 ).data() ) < 1 )
		{
			return "";
		}
		temp = atoi( date.substr( 5, 2 ).data() );
		if( temp < 1 || temp > 12 )
		{
			return "";
		}
		temp = atoi( date.substr( 8, 2 ).data() );
		if ( temp < 1 || temp > 31 ) //Simplistic
		{
			return "";
		}
	}
	catch (...) 
	{
		return "";
	}
	return date;
}

										  
std::string EXIF_Plugin::extractTime_( const std::string& value )
{
	//This should be done using regular expressions, but for simplicities sake we will not add boost or other regex libraries for now.
	
	//The only allowed format is HH:MM:SS(.mmm)?	(hours (24):minutes:seconds.milliseconds)
	
	std::string time;
	if( value.find( " " ) != std::string::npos )
	{
		time = value.substr( value.find( " " ) + 1, value.length() - value.find( " ") );
	}
	else
	{
		time = value;
	}
	
	if( time.length() != 8 )
	{
		return "";
	}
	
	if( time.substr( 2, 1 ) != ":"  || time.substr( 5, 1 ) != ":" )
	{
		return "";
	}
	
	int temp;
	try 
	{
		if( atoi( time.substr( 0, 2 ).data() ) < 0 )
		{
			return "";
		}
		temp = atoi( time.substr( 3, 2 ).data() );
		if( temp < 0 || temp > 59 )
		{
			return "";
		}
		temp = atoi( time.substr( 6, 2 ).data() );
		if ( temp < 0 || temp > 59 ) 
		{
			return "";
		}
	}
	catch (...) 
	{
		return "";
	}
	return time;
	
}

										  
void EXIF_Plugin::init_()
{
	tagsToProcess_.insert( "Exif.Image.Make" );
	tagsToProcess_.insert( "Exif.Image.Model" );
	tagsToProcess_.insert( "Exif.Image.Software" );
	tagsToProcess_.insert( "Exif.Image.DateTime" );
	tagsToProcess_.insert( "Exif.Image.Artist" );
	tagsToProcess_.insert( "Exif.Photo.ExposureTime" );
	tagsToProcess_.insert( "Exif.Photo.FNumber" );
	tagsToProcess_.insert( "Exif.Photo.ISOSpeedRatings" );
	tagsToProcess_.insert( "Exif.Photo.DateTimeOriginal" );
	tagsToProcess_.insert( "Exif.Photo.ShutterSpeedValue" );
	tagsToProcess_.insert( "Exif.Photo.ApertureValue" );
	tagsToProcess_.insert( "Exif.Photo.FocalLength" );
	tagsToProcess_.insert( "Exif.Photo.PixelXDimension" );
	tagsToProcess_.insert( "Exif.Photo.PixelYDimension" );
	tagsToProcess_.insert( "Exif.Iop.RelatedImageWidth" );
	tagsToProcess_.insert( "Exif.Iop.RelatedImageLength" );
	
	//Special handling since we have to split date & time into two separate tags
	extractDateAndTime_.insert( "Exif.Image.DateTime" );
	extractDateAndTime_.insert( "Exif.Photo.DateTimeOriginal" ); 
}
										  

//A neccessary part of all plugins
extern "C" EXPORT double getPluginInterfaceVersion()
{
	return PLUGIN_INTERFACE_VERSION;
}


//A neccessary part of all plugins
extern "C" EXPORT void registerPlugin( const int id, PluginServer& pluginServer )
{
	//std::cout << "----Trying to register plugin (in plugin code)" << std::endl;
	pluginServer.addProcessObjectPlugin( new EXIF_Plugin( id ) );
}

										  


