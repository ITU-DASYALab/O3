/*
Project: hsimage
File: image.cpp
Developer: Hlynur Sigurþórsson (hlynursigurthorsson@gmail.com)
Timestamp: Fall, 2011.
*/

#include "image.h"
#include "imagewidget.h"
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "PluginWrapper.h"
#include "../FaceRecognitionPlugin.h"
#include "../../ObjectCube/Plugin/PluginObject.h"
#include "../../ObjectCube/Plugin/PluginTagging.h"
#include "../../ObjectCube/Plugin/PluginReply.h"

#include <opencv2/opencv.hpp>
#include <fstream>

using namespace std;

Image::Image(string image_location){
    this->image_location = image_location;

    fstream raw_image(image_location.c_str());

    raw_image.seekg(0,ios::end);
    image_size = raw_image.tellg();
    raw_image.seekg(ios::beg);

    image_data = new char[image_size];
	raw_image.read(image_data, image_size);

	Mat img = imread(image_location,CV_LOAD_IMAGE_COLOR);

	image_height = img.rows;
	image_width = img.cols;
}

Image::~Image(){   
	if(image_data != NULL)
	{
		delete image_data;
	}
	
}

string Image::get_name() {
    return this->image_location;
}

int Image::search_for_faces(){
    // Create some random bounding boxes for the image.
    srand ( time(NULL) );    

	PluginWrapper* wrapper = PluginWrapper::instance();

	int objectCubeID = wrapper->get_unique_id(); 

	this->image_id = objectCubeID;

	ObjectCube::PluginObject pluginObject = ObjectCube::PluginObject(objectCubeID, image_location, image_data, image_size);

	FaceRecognitionPlugin *frp =  wrapper->pluginInstance();
	
    ObjectCube::PluginReply pluginReply = frp->process( pluginObject );
	
    vector<ObjectCube::PluginTagging> taggings = pluginReply.getTaggings();

	int num_bounding_boxes = taggings.size();

    for (int i = 0; i < num_bounding_boxes; i += 1) {

        hsimage::BoundingBox* b = new hsimage::BoundingBox(this, taggings[i].getBoundingBox());

		b->setPersonName(taggings[i].getSuggestedTags()[0]);

	    for(unsigned int j=0; j<taggings[i].getSuggestedTags().size(); j++)
   		{
    		b->addCandidate(taggings[i].getSuggestedTags()[j]);
   		}

        this->add_bounding_box(b);   
    }
    
    // Return the number of bounding box found.
    return num_bounding_boxes;
}

vector<hsimage::BoundingBox*>& Image::get_bounding_boxes(){
    return this->boundingBoxes;
}

void Image::add_bounding_box(hsimage::BoundingBox* bb){
    this->boundingBoxes.push_back(bb);  
}

int Image::show_in_edit_dialog(){
    setWindowTitle(tr(this->image_location.c_str()));
    QVBoxLayout *vbox = new QVBoxLayout(this);
    ImageWidget* iw = new ImageWidget(this);
    iw->show_image(this);
    vbox->addWidget(iw);
    setLayout(vbox);
    this->resize(800, 600);
    
    this->exec();
    delete iw;
    delete vbox;
    return 0;
}
