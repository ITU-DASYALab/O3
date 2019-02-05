/*
Project: hsimage
File: maindialog.cpp
Developer: Hlynur Sigurþórsson (hlynursigurthorsson@gmail.com)
Timestamp: Fall, 2011.
*/

#include "maindialog.h"
#include "image.h"
#include "imageservice.h"
#include "imagewidget.h"
#include <QtGui>
#include <iostream>
#include <fstream>
#include <dirent.h>
#include <sys/stat.h>
using namespace std;

MainDialog::MainDialog(QWidget *parent) : QMainWindow(parent) {
    this->initialize_menu();
    this->resize(605, 398);
    
    // Create central widget.
    this->centralwidget = new QWidget(this);
    
    // Create layout.
    this->horizontalLayout = new QHBoxLayout(this->centralwidget); 
    
    // Create image listview.    
    this->listView = new QListWidget();
    
    // Create size polizy for the listview.
    QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(listView->sizePolicy().hasHeightForWidth());
    listView->setSizePolicy(sizePolicy);
    listView->setMaximumSize(QSize(200, 16777215));
    
    // Load the all stored images into the listwidget.
    this->LoadImages(); 


    // Create image widget to the main dialog.
    this->imageWidget = new ImageWidget(this);
   
    // Add the widgets to the layout
    horizontalLayout->addWidget(imageWidget);
    horizontalLayout->addWidget(listView);    
    
    // do stuff with listview slot.
    connect(this->listView, SIGNAL(itemSelectionChanged()), this, SLOT(eventImageListViewSelectionChanged())); 
    this->setCentralWidget(centralwidget);
}


void MainDialog::LoadImages(){
    this->listView->clear();
    //cout << "adding images to list view" << endl;
    // Get all images from Image service.
    vector<Image*> images = ImageService::instance()->get_all_images();
    
    //add all the images into the listbox.
    for(unsigned int i=0; i<images.size(); i++) {
        Image* image = images.at(i);
        //cout << image->get_name() << endl;
        this->listView->addItem(QString(image->get_name().c_str()));
    }
}



void MainDialog::initialize_menu(){
    QAction *quit = new QAction("&Quit", this);
    QAction *import = new QAction("&Import", this);
    QMenu *file;
    file = menuBar()->addMenu("&File");
    file->addAction(quit);
    file->addAction(import);

    connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(import, SIGNAL(triggered()), this, SLOT(eventMenuClickImport()));
}


void MainDialog::eventImageListViewSelectionChanged() {

    QListWidgetItem* selectedItem = this->listView->currentItem();
    QString qs = selectedItem->text();

    string image_name = qs.toUtf8().constData();
    Image* selected_image = ImageService::instance()->get_image_by_name(image_name);
    //cout << "select image " << selected_image << endl;
    
    this->imageWidget->clear();
    
    
    //cout << "after clear!" << endl;
    
    this->imageWidget->show_image(selected_image);
}


void MainDialog::eventMenuClickAbout() {
    //cout << "we are doing about" << endl;
}


// SLOT Function for Import action.
// Opens up dialog for select folder. Images within that folder
// are then imported and taken through person tagging process.
void MainDialog::eventMenuClickImport()
{
    // Create File Dialog to select import folder location.
    QFileDialog* fd = new QFileDialog( this, "Select folder to import");
    fd->setFileMode( QFileDialog::Directory );
    fd->setFilter(QDir::Dirs);
    
    if(fd->exec()) {
        string selected_folder = fd->selectedFiles().at(0).toLocal8Bit().constData();
        //cout << selected_folder << endl;
    
        ifstream inn;
        struct dirent *dirp;
        struct stat st;
        
        // open the directory.
        DIR* d_fd = opendir( selected_folder.c_str() );
        
        if(!d_fd)
            cout << "Error: unable to read directory '" << selected_folder << "'" << endl;
        else{
            while ((dirp = readdir( d_fd ))){
                string file_name = dirp->d_name;
                
                // Get rid of back directories "." and ".."
                if(file_name.compare(".") == 0 || file_name.compare("..") == 0) continue;
                
                // Create string for the full path.
                string file_full_path = selected_folder + "/" + file_name;
                
                // check if is folder, if so we skip them.
                lstat(file_full_path.c_str(), &st);
                if (S_ISDIR(st.st_mode))
                    continue;
                
				// Skip everything that does not end on png or jpg.
				string f_ext = file_full_path.substr(file_full_path.length()-3,file_full_path.length());

				if( !(f_ext.compare("JPG")==0 || f_ext.compare("jpg")==0 || f_ext.compare("PNG")==0 || f_ext.compare("png")==0) ) 
				{
					//cout << "Not a supported file type." << endl;
					continue;
				}

                // debug output the fullpath.
                //cout << "+ " << file_full_path << endl;
                
                // Create image object for the image.
                Image* image = new Image(file_full_path);
                image->search_for_faces();
                
                // show the image in a modal dialog for face managment.
                image->show_in_edit_dialog();
                
                // remove deleted bounding boxes.
                vector<hsimage::BoundingBox*> bb = image->get_bounding_boxes();
                //cout << "image label working with bbs " << bb << endl;
                
                
                for ( vector<hsimage::BoundingBox*>::iterator iter = bb.begin(); iter != bb.end(); ) { 
                    hsimage::BoundingBox* b = &(**iter);
                    if ( !b->is_deleted() ) {
                        ++iter;
                    } 
                    else {
                        iter = bb.erase( iter );
                        //cout << "removed bounding box" << endl;
                    }
                }
              
                // add the image to the image service.
                ImageService::instance()->add_image(image);
                //cout << "image has " << image->get_bounding_boxes().size() << " boxes" << endl; 
                
                
            }
        }
        
        delete d_fd; 
        
        // reload the listview images.
        this->LoadImages();   
    }   
    
    // clean up.
    delete fd;
}
