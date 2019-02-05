/*
Project: hsimage
File: main.cpp
Developer: Hlynur Sigurþórsson (hlynursigurthorsson@gmail.com)
Timestamp: Fall, 2011.
*/



#include "PluginWrapper.h"
#include "maindialog.h"
#include <QtGui>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
    
    
    // Create QApplication.
    QApplication app(argc, argv);
   

    PluginWrapper* test = PluginWrapper::instance();
	test->get_unique_id(); 
    // Create instance of the main dialog
    MainDialog window;
    window.setWindowTitle("hsfaces");
    
    // Show the main window.
    window.show();

    // Start event loop.
    return app.exec();
}
