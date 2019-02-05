/*
Project: hsimage
File: imageLabel.cpp
Developer: Hlynur Sigurþórsson (hlynursigurthorsson@gmail.com)
Timestamp: Fall, 2011.
*/

#include "imageLabel.h"
#include "image.h"
#include <iostream>
#include <QtGui>
#include <boundingbox.h>
using namespace std;

ImageLabel::ImageLabel( QWidget* parent, Image* image ) : QLabel(parent) {


	this->mouse_x = 0;
	this->mouse_y = 0;
	this->mouse_x_move = 0;
	this->mouse_y_move = 0;
    this->image = image;
    this->setMouseTracking(true);
    this->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    this->setScaledContents(true);
    this->setMouseTracking(true);
    this->boundingbox_in_focus = NULL;
    this->mouse_down = false;
    // Store pointer to the image.
    this->qimage = new QImage(this->image->get_name().c_str());
}


ImageLabel::~ImageLabel(){
    delete this->qimage;
}

// Slot for mouse down event.
//
void ImageLabel::mousePressEvent(QMouseEvent *event) {
    if(this->boundingbox_in_focus){
        this->boundingbox_in_focus->show_dialog();

    }
    // draw new bounding box.
    else {
        this->mouse_down = true;
        mouse_x = event->x();
        mouse_y = event->y();
        mouse_x_move = mouse_x;
        mouse_y_move = mouse_y;
        //BoundingBox* b = new BoundingBox();
        //this->image->add_bounding_box(b);
        
    }
}


// Slot for mouse release.
void ImageLabel::mouseReleaseEvent(QMouseEvent *){
    
    if(this->mouse_down){
        this->mouse_down = false;
        //cout << "mouse UP!" << endl;
        
         //create new bounding box for the drawing.
        if(mouse_x_move < mouse_x){
            int temp = mouse_x_move;
            mouse_x_move = mouse_x;
            mouse_x = temp;
        }
        if(mouse_y_move < mouse_y){
            int temp = mouse_y_move;
            mouse_y_move = mouse_y;
            mouse_y = temp;
        }
        
        double x_begin_per = (mouse_x / (this->width()+0.01))*100;    
        double x_width_per = (mouse_x_move / (this->width()+0.01))*100;
        double y_begin_per = (mouse_y / (this->height()+0.01))*100;
        double y_width_per = (mouse_y_move / (this->height()+0.01))*100;
        
        //hsimage::BoundingBox* b = new hsimage::BoundingBox(this->image);
		if( (x_width_per - x_begin_per < 1) || (y_width_per - y_begin_per < 1))
		{
			//cout << "Too small" << endl;
			return;
		}

		//cout << x_begin_per << " " << x_width_per << " " << y_begin_per << " " << y_width_per << endl;
        hsimage::BoundingBox* b = new hsimage::BoundingBox(this->image, x_begin_per, y_begin_per, x_width_per, y_width_per);

/*
        b->x = x_begin_percentage;
        b->x_width = x_width_percentage;
        
        b->y = y_begin_percentage;
        b->y_width = y_width_percentage;
*/
        
        this->image->add_bounding_box(b);
        
        if(boundingbox_in_focus){
            boundingbox_in_focus->glow=false;
        }
        boundingbox_in_focus = b;
        
        
        update();
    }
}


// Slot function for mouse movement.
// Checks if we are hovering any bounding boxes on the image.
// If there is a bounding box in scope we store a pointer to it.
void ImageLabel::mouseMoveEvent(QMouseEvent* event){
    
    if(this->mouse_down){
        mouse_x_move = event->x(); 
        mouse_y_move = event->y();
        update();
        return;
    }
    
    bool hover = false;
    
    //cout <<this->image->get_bounding_boxes().size() << endl;
    
    for (unsigned int i = 0; i < this->image->get_bounding_boxes().size(); i += 1)
    {
        hsimage::BoundingBox* b = this->image->get_bounding_boxes().at(i);
        
        if(b->is_deleted()){
            //cout << "DELETED" << endl;
            continue;
        }
        
        // check on x level.
        if(
            ((event->x()+0.0001) / (this->width()+0.0001)) >= (b->get_x() / 100.0) && 
            ((event->x()+0.0001) / (this->width()+0.0001)) <= (b->get_x_width()/100.0)
        )

        {
            //cout << "nice" << endl;
            if( 
            ( (event->y()+0.00001) / (this->height() + 0.0001)) >= (b->get_y() / 100.0) && 
            (event->y()+0.0001) / (this->height() + 0.0001) <= (b->get_y_width() /100.0)
            )
             {
                if(boundingbox_in_focus) {
                    boundingbox_in_focus->glow = false;
                }

                //cout << "hovering " << b << endl;
                
                boundingbox_in_focus = b;
                hover = true;
                // boundingbox_in_focus->glow = true;
                update();
                break;
            }
        }
    }
    
    if(!hover){
        //todo: facerec: clear all glows!
        if(boundingbox_in_focus){
            boundingbox_in_focus->glow = false;
            boundingbox_in_focus = NULL;
            update();
        }
    }
}



void ImageLabel::paintEvent(QPaintEvent *event) {
    //cout << this << endl;
    if(!this->qimage)
        return;
        
    QPainter paint(this);
    paint.drawImage(0, 0, this->qimage->scaled ( this->width(), this->height(), Qt::IgnoreAspectRatio, Qt::FastTransformation ));

    QPen pen(qRgb(0,0,0));
    pen.setWidth(2);
 
    for (unsigned int i = 0; i < this->image->get_bounding_boxes().size(); i += 1) { 

        hsimage::BoundingBox* b = this->image->get_bounding_boxes().at(i);
        if(!b){
            cout << "b2 is null!" << endl;
        }
        
        if(b->is_deleted())
            continue;
        
        
        if( !b->isConfirmed() ){
            pen.setColor(Qt::red);
        }
        
        else{
            pen.setColor(Qt::blue);
        }
        
        if(b->glow){
            pen.setColor(Qt::yellow);
        }
        
        paint.setPen(pen);
        
        // Paint the box.
        paint.drawRect(QRect( 
        (this->width() * (b->get_x()/100.0)), 
        (this->height()* (b->get_y()/100.0)), 
        (this->width() * ( (b->get_x_width() - b->get_x()) /100.0)), 
        (this->height() * ( (b->get_y_width()-b->get_y()) /100.0))));
        
        // check if mouse is down, then we should draw a bounding box
        if(this->mouse_down){
            paint.drawRect(QRect( mouse_x , mouse_y, (mouse_x_move - mouse_x), (mouse_y_move-mouse_y)));
            //cout << "DD" << endl;
        }
        
        
    }
}

