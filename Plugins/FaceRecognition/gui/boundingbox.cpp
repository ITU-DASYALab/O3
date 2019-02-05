/*
Project: hsimage
File: boundingbox.h
Developer: Hlynur Sigurþórsson (hlynursigurthorsson@gmail.com)
Timestamp: Fall, 2011.
*/

#include "boundingbox.h"
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <fstream>

#include <math.h>

#include "PluginWrapper.h"
#include "image.h"

using namespace std;
namespace hsimage{
// Constructor for BoundingBox.
// Parameters: None.
// Functionality: Markes the bounding initially as "unconfirmed".
// Disables glowing initially (which might be set on mouseover).
// Marks the object as not deleted.
BoundingBox::BoundingBox(Image *image, double x, double y, double x_width, double y_width) {

	//Logging
	m_log = std::unique_ptr<Utils::Log>( new Utils::Log("face_recognition_ui.log") );
	m_log->writeEnter() << __PRETTY_FUNCTION__ << std::endl;

    this->unconfirm();
    this->glow = false;
    this->deleted = false;
	this->lned_name = NULL;

    this->image = image;
	
	this->x = x;
	this->x_width = x_width;
	this->y = y;
	this->y_width = y_width;

	this->initOriginalBB();
}

void BoundingBox::initOriginalBB()
{
	m_log->writeEnter() << __PRETTY_FUNCTION__ << std::endl;
	this->isFromDB = false;
	double imageWidth, imageHeight;
	imageWidth = this->image->get_image_width();
	imageHeight = this->image->get_image_height();

	double uleftx = floor( (this->x/100.0) * imageWidth );
	double ulefty = floor( (this->y/100.0) * imageHeight ) ;
	double lrightx = floor( ((this->x_width)/100.0) * imageWidth );
	double lrighty = floor( ((this->y_width)/100.0) * imageHeight );

	//cout << "new boundingBox: " << uleftx << " " << ulefty << " " << lrightx << " " << lrighty << endl;

	ObjectCube::Coordinate2D upperLeft(uleftx, ulefty);
	ObjectCube::Coordinate2D lowerRight(lrightx, lrighty);

	this->originalBB = ObjectCube::BoundingBox();
	this->originalBB.setUpperLeftCorner(upperLeft);
	this->originalBB.setLowerRightCorner(lowerRight);
}

BoundingBox::BoundingBox(Image *image, ObjectCube::BoundingBox bb) {

	m_log->writeEnter() << __PRETTY_FUNCTION__ << std::endl;

	this->isFromDB = true;
    this->unconfirm();
    this->glow = false;
    this->deleted = false;
	this->lned_name = NULL;

	this->image = image;

	//cout << "setting image width: " << this->image->get_image_width() << " x " << this->image->get_image_height() << endl;

	double imageWidth, imageHeight;
	imageWidth = this->image->get_image_width();
	imageHeight = this->image->get_image_height();

	this->x = ( bb.getUpperLeftCorner().getX() / imageWidth ) * 100.0;
	this->y = ( bb.getUpperLeftCorner().getY() / imageHeight ) * 100.0;

	this->x_width = ( bb.getLowerRightCorner().getX() / imageWidth ) * 100.0;
	this->y_width = ( bb.getLowerRightCorner().getY() / imageHeight ) * 100.0;

	//cout << "db boundingBox: " << x << " " << y << " " << x_width << " " << y_width << endl;

	this->originalBB = bb;
}

void BoundingBox::random_position(){
	m_log->writeEnter() << __PRETTY_FUNCTION__ << std::endl;

    // Create random bounding box values.
    this->x = 50;
    this->x_width = 60;
    this->y = 10;
    this->y_width = 20;
}


void BoundingBox::confirm() {
	m_log->writeEnter() << __PRETTY_FUNCTION__ << std::endl;
    this->confirmed = true;
}

void BoundingBox::unconfirm() {
	m_log->writeEnter() << __PRETTY_FUNCTION__ << std::endl;
    this->confirmed = false;
}

bool BoundingBox::isConfirmed() {
	m_log->writeEnter() << __PRETTY_FUNCTION__ << std::endl;
    return this->confirmed;
}

void BoundingBox::setPersonName(string name){
	m_log->writeEnter() << __PRETTY_FUNCTION__ << std::endl;
    this->person_name = name;
}

void BoundingBox::setDbPersonName(string name){
	m_log->writeEnter() << __PRETTY_FUNCTION__ << std::endl;
    this->db_person_name = name;
}

void BoundingBox::addCandidate(string name) {
	m_log->writeEnter() << __PRETTY_FUNCTION__ << std::endl;
	this->candidate_names.push_back(name);
}

void BoundingBox::addRandomCandiates(){
	m_log->writeEnter() << __PRETTY_FUNCTION__ << std::endl;
    //cout << "boundingbox: created random names: " << this << endl; 
    this->candidate_names.push_back("Hlynur");
    candidate_names.push_back("Thelma");
    candidate_names.push_back("Bjorn");
}


void BoundingBox::show_dialog(){
	m_log->writeEnter() << __PRETTY_FUNCTION__ << std::endl;
    setWindowTitle(tr("Bounding box edit"));
    
    // create label for drop down box.
    QLabel* l_box = new QLabel("Select person", this);
    
    // create drop down list with all the candidates.
    this->cmb_candidates = new QComboBox(this);
    QObject::connect(cmb_candidates, SIGNAL(currentIndexChanged(int)), this, SLOT(cmbCandidates(int)));
    

    cout  << "Size of cmb_candidates: " << cmb_candidates->size() << endl;

    // place the candidates into the combobox.
    for (unsigned int i = 0; i < this->candidate_names.size(); i += 1)
        cmb_candidates->addItem( this->candidate_names.at(i).c_str() );
    
    // If the bounding box has not been confirmed.
    if(!this->isConfirmed())
        cmb_candidates->setCurrentIndex(-1);
    
	lned_name = new QLineEdit("Name", this);
	lned_name->setText(QString(this->person_name.c_str()));

    // Create buttons.
    QPushButton *btn_save = new QPushButton("Save", this);
    QObject::connect(btn_save, SIGNAL(clicked()), this, SLOT(btnSavePress()));
    
    QPushButton *btn_cancel = new QPushButton("Cancel", this);
    QObject::connect(btn_cancel, SIGNAL(clicked()),this, SLOT(btnCancel()));
    
    QPushButton *btn_delete = new QPushButton("Delete", this);
    QObject::connect(btn_delete, SIGNAL(clicked()),this, SLOT(btnDelete()));

    // resize the dialog.
    this->resize(310, 150);
    
    // position the widgets on the screen.
    cmb_candidates->setGeometry(140, 20, 158, 30);
    l_box->setGeometry(20, 20, 270, 30);
	lned_name->setGeometry(20, 60, 150, 30);
    btn_save->setGeometry(20, 110, 80, 30);
    btn_cancel->setGeometry(105, 110, 80, 30);
    btn_delete->setGeometry(190, 110, 80, 30);
    this->exec();
}

	void BoundingBox::cmbCandidates(int index) {
		m_log->writeEnter() << __PRETTY_FUNCTION__ << std::endl;

		if(this->lned_name == NULL)
			return;
		QString text = cmb_candidates->itemText(index);
		
		if(index != -1){
			lned_name->setText(text);
		}
	}

    void BoundingBox::btnSavePress(){

    	m_log->writeEnter() << __PRETTY_FUNCTION__ << std::endl;

		ObjectCube::BoundingBox();

		double imageWidth, imageHeight;
		imageWidth = this->image->get_image_width();
		imageHeight = this->image->get_image_height();

/*
		double uleftx = floor( (this->x/100.0) * imageWidth ); 
		double ulefty = floor( (this->y/100.0) * imageHeight ) ;
		double lrightx = floor( ((this->x_width)/100.0) * imageWidth );
		double lrighty = floor( ((this->y_width)/100.0) * imageHeight );

		ObjectCube::Coordinate2D upperLeft(uleftx, ulefty);
        ObjectCube::Coordinate2D lowerRight(lrightx, lrighty);

        ObjectCube::BoundingBox boundingBox;
        boundingBox.setUpperLeftCorner(upperLeft);
        boundingBox.setLowerRightCorner(lowerRight);
*/

		PluginWrapper* wrapper = PluginWrapper::instance();
		FaceRecognitionPlugin *frp =  wrapper->pluginInstance();

		this->person_name = lned_name->text().toStdString();

		string image_location = this->image->get_image_location();
		int image_size = this->image->get_image_size();

		//-------------------------------------
		fstream raw_image(image_location.c_str());

		raw_image.seekg(0,ios::end);
		image_size = raw_image.tellg();
		raw_image.seekg(ios::beg);

		char* image_data = new char[image_size];
		raw_image.read(image_data, image_size);
		//-------------------------------------

		int image_id = this->image->get_image_id();

		ObjectCube::PluginObject pluginObject = ObjectCube::PluginObject(image_id, image_location, image_data, image_size);

		//cout << "original BB: ";
		//cout << originalBB.getUpperLeftCorner().getX()<< " ";
		//cout << originalBB.getUpperLeftCorner().getY() << " ";
        //cout << originalBB.getLowerRightCorner().getX() << " ";
        //cout << originalBB.getLowerRightCorner().getY() << endl;

		frp->confirmTagging( pluginObject, "persons", this->originalBB, this->person_name );

        this->confirm();

		raw_image.close();
		//delete image_data;

        close();

        m_log->writeExit() << __PRETTY_FUNCTION__ << std::endl;
    }
    
    void BoundingBox::btnCancel(){
    	m_log->writeEnter() << __PRETTY_FUNCTION__ << std::endl;
        close();
    }
    
    void BoundingBox::btnDelete(){

    	m_log->writeEnter() << __PRETTY_FUNCTION__ << std::endl;
        this->deleted = true;
		PluginWrapper* wrapper = PluginWrapper::instance();

		FaceRecognitionPlugin *frp =  wrapper->pluginInstance();

		
		if(isFromDB)
		{
			m_log->writeInfo() << " isFromDB, db delete " << std::endl;
			frp->deleteTagging( this->image->get_image_id(), "persons", originalBB, db_person_name );
		}

        close();
    }
    
    bool BoundingBox::is_deleted(){
    	m_log->writeEnter() << __PRETTY_FUNCTION__ << std::endl;
        return this->deleted;
    }
}



