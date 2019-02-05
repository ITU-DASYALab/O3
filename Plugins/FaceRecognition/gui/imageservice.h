/*
Project: hsimage
File: imageservice.h
Developer: Hlynur Sigurþórsson (hlynursigurthorsson@gmail.com)
Timestamp: Fall, 2011.
*/

#ifndef IMAGESERVICE_H
#define IMAGESERVICE_H

#include "image.h"
#include <vector>
#include <string>

using namespace std;

// Singleton image service that stores imported images
// for later usages. Currently they are kept in memory.
class ImageService {
    
    private:
    // Where this is a singleton class we make the the
    // constructor private as hell ;)
    ImageService(){};
    
    // Copy constructor is private;
    ImageService(ImageService const&){};             
    
    // Assignment operator is private
    ImageService& operator=(ImageService const&){};  
    static ImageService* m_pInstance;
    
    // Member variables
    vector<Image*> m_images;

    
    public:
    static ImageService* instance();
    vector<Image*> get_all_images();
    Image* get_image_by_name(string name);
    void add_image(Image*);
};

#endif
