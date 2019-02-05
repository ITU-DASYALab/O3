/*
Project: hsimage
File: PluginWrapper.h
Developer: Hlynur Sigurþórsson (hlynursigurthorsson@gmail.com)
Timestamp: Fall, 2011.
*/

#ifndef PLUGINWRAPPER_H
#define PLUGINWRAPPER_H

#include "../FaceRecognitionPlugin.h"

#include "../../ObjectCube/Plugin/PluginObject.h"
#include "../../ObjectCube/Plugin/PluginTagging.h"


// Singleton image service that stores imported images
// for later usages. Currently they are kept in memory.
class PluginWrapper {
    
    private:
    // Private member variables 
	FaceRecognitionPlugin* m_frp;

	// private member functions
	
	// Where this is a singleton class we make the the
    // constructor private as hell ;)
    PluginWrapper(){
    	this->m_frp = new FaceRecognitionPlugin(1);
    };
    
    // Copy constructor is private;
    PluginWrapper(PluginWrapper const&){};             
    
    // Assignment operator is private
    //PluginWrapper& operator=(PluginWrapper const&){};  
    static PluginWrapper* m_pInstance;
    
    public:
    static PluginWrapper* instance();
    FaceRecognitionPlugin* pluginInstance() { return m_frp; };
	int get_unique_id();
};

#endif
