/*
Project: hsimage
File: imageLabel.h
Developer: Hlynur Sigurþórsson (hlynursigurthorsson@gmail.com)
Timestamp: Fall, 2011.
*/

#ifndef IMAGELABEL_H
#define IMAGELABEL_H

#include "boundingbox.h"
#include "image.h"
#include <QtGui>
#include <string>
#include <vector>


using namespace std;


class ImageLabel : public QLabel {
    Q_OBJECT
    
    public:
    ImageLabel( QWidget* parent, Image* image );
    ~ImageLabel();
    private:
    QImage* qimage;
    hsimage::BoundingBox* boundingbox_in_focus;
    bool mouse_down;
    Image* image;
    int mouse_x; 
    int mouse_y;
    
    int mouse_x_move; 
    int mouse_y_move;
    
    public slots:
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *);
    
    protected slots:
    void paintEvent(QPaintEvent *event);
    
};
#endif
