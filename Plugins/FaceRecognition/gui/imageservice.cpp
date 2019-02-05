/*
Project: hsimage
File: imageservice.cpp
Developer: Hlynur Sigurþórsson (hlynursigurthorsson@gmail.com)
Timestamp: Fall, 2011.
*/

#include "imageservice.h"
#include <vector>
using namespace std;


// Global static pointer used to ensure a single instance of the class.
ImageService* ImageService::m_pInstance = NULL;


vector<Image*> ImageService::get_all_images() {
    return this->m_images;
}

void ImageService::add_image(Image* image){
    this->m_images.push_back(image);
}


ImageService* ImageService::instance() {
    if (!m_pInstance)
        m_pInstance = new ImageService();
    return m_pInstance;
}

Image* ImageService::get_image_by_name(string name) {
    
    for (unsigned int i = 0; i < this->m_images.size(); i += 1) {
        if( this->m_images.at(i)->get_name() == name )
            return this->m_images.at(i);
    }
    
    return NULL;
}

