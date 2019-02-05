/*
Project: hsimage
File: imagewidget.h
Developer: Hlynur Sigurþórsson (hlynursigurthorsson@gmail.com)
Timestamp: Fall, 2011.
*/

#ifndef IMAGEWIDGET_H
#define IMAGEWIDGET_H

#include "image.h"
#include "imageLabel.h"
#include <QtGui>

#include <string>
using namespace std;

class ImageWidget : public QWidget {

    Q_OBJECT
    
    public:
    ImageWidget( QWidget* parent );
    ~ImageWidget();
    void show_image(Image* image);
    void clear();

    private:
    QVBoxLayout *vbox;
    ImageLabel* imageLabel;
};

#endif
