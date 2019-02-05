/*
Project: hsimage
File: maindialog.cpp
Developer: Hlynur Sigurþórsson (hlynursigurthorsson@gmail.com)
Timestamp: Fall, 2011.
*/

#ifndef IMAGE_H
#define IMAGE_H

#include "boundingbox.h"
#include <QtGui>
#include <string>
#include <vector>

using namespace std;
//using namespace hsimage;

class Image : public QDialog {

    
    public:
        Image(string image_location);
        ~Image();
        string get_name();
        int search_for_faces();
        vector<hsimage::BoundingBox*>& get_bounding_boxes();
        void add_bounding_box(hsimage::BoundingBox* bb);
        int show_in_edit_dialog();

		int get_image_width(){ return image_width; };
		int get_image_height(){ return image_height; };
		int get_image_size() { return image_size; };
		char* get_image_data() { return image_data; };
		string get_image_location() { return image_location; };
		int get_image_id(){ return image_id; };
    
    private:
        string image_location;
        char* image_data;
		int image_size;
		int image_width, image_height;
		int image_id;
        vector<hsimage::BoundingBox*> boundingBoxes;
        QVBoxLayout *vbox;
        
};

#endif
