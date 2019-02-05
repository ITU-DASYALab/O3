/*
Project: hsimage
File: boundingbox.h
Developer: Hlynur Sigurþórsson (hlynursigurthorsson@gmail.com)
Timestamp: Fall, 2011.
*/

#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include <QtGui>
#include <vector>
#include <string>
#include "../../ObjectCube/Utils/Log.h"
#include "../../ObjectCube/Boundaries/BoundingBox.h"

using namespace std;

class Image;

namespace hsimage {
class BoundingBox : public QDialog{
    
    Q_OBJECT
    
    public:
    // variables for bounding boxes.

    bool glow;
    int dialog_result;
 
    // Constructors
    //BoundingBox(Image *image);
	BoundingBox(Image *image, double x, double y, double x_width, double y_width);
	BoundingBox(Image *image, ObjectCube::BoundingBox bb);
    
    // Public member functions
    void confirm();
    void unconfirm();
    bool isConfirmed();
    void setPersonName(string name);
    void setDbPersonName(string name);
	void addCandidate(string name);
    void addRandomCandiates();
    void show_dialog();
    bool is_deleted();
    void random_position();
    
	double get_x() { return x; };
	double get_x_width() { return x_width; };
	double get_y() { return y; };
	double get_y_width() { return y_width; };
    
    private: 
    // States if the bounding has been confirmed.
    bool confirmed;
    vector<string> candidate_names;
    string person_name, db_person_name;
    QComboBox* cmb_candidates;
	QLineEdit *lned_name;
    bool deleted;

	double x, x_width, y, y_width;

	bool isFromDB;
	void initOriginalBB();

	Image * image;
	ObjectCube::BoundingBox originalBB;
	std::unique_ptr<Utils::Log> m_log;
    
    public slots:
	void cmbCandidates(int index);
    void btnSavePress();
    void btnCancel();
    void btnDelete();
};
}
#endif
