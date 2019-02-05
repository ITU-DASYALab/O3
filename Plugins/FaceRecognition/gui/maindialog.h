/*
Project: hsimage
File: maindialog.cpp
Developer: Hlynur Sigurþórsson (hlynursigurthorsson@gmail.com)
Timestamp: Fall, 2011.
*/

#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include "imagewidget.h"
#include <QtGui>

class MainDialog : public QMainWindow {
    Q_OBJECT
    
    private:
        // private member variables
        QWidget* centralwidget;
        QHBoxLayout* horizontalLayout;
        QListWidget* listView;
        ImageWidget* imageWidget;
        
        // private member functions.
        void initialize_menu();
        void LoadImages();
    
    public:
        MainDialog(QWidget *parent = 0);
        

    private slots:
        void eventMenuClickAbout();
        void eventMenuClickImport();
        void eventImageListViewSelectionChanged();
};
#endif
