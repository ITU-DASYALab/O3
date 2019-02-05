/*
Project: hsimage
File: imagewidget.cpp
Developer: Hlynur Sigurþórsson (hlynursigurthorsson@gmail.com)
Timestamp: Fall, 2011.
*/

#include "imagewidget.h"
#include "imageLabel.h"

#include <iostream>
#include <string>
#include <QtGui>

using namespace std;


ImageWidget::ImageWidget(QWidget* parent) : QWidget(parent) {
    this->vbox = new QVBoxLayout(this);
    this->imageLabel = NULL;
}

void ImageWidget::show_image(Image* image){
    
    this->imageLabel = new ImageLabel(this, image);
    this->vbox->addWidget(imageLabel);
}

ImageWidget::~ImageWidget(){
    //cout << "image widget deleted" << endl;
    delete this->vbox;
    delete this->imageLabel;
    this->vbox = NULL;
    this->imageLabel = NULL;
}

void ImageWidget::clear(){
    //cout << "begin clear" << endl;
    if(this->imageLabel){

        //cout << "layout()->removeWidget(this->imageLabel);" << endl;
        layout()->removeWidget(this->imageLabel);
        
        //cout << "delete this->imageLabel;" << endl;
        delete this->imageLabel;
        this->imageLabel = NULL;
    }
    //cout << "end clear" << endl; 
}

