/*
 * File name: testfacedb.cpp
 * Date:      2011-07-27 16:06
 * Author:    Kristján Rúnarsson
 */

#include <iostream>
#include <string>
#include <stdexcept>

#include "Person.h"
#include "Face.h"

using namespace std;

int main() {
	
	try{

		Person p1("Tom");
		p1.persist();

		Person p2("Dick");
		p2.persist();

		Person p3("Harry");
		p3.persist();

		p1.setRealName("Pom");
		p1.persist();

		p2.setRealName("Prick");
		p2.persist();

		p3.setRealName("Parry");
		p3.persist();

		Person p4("Tom");
		p4.persist();

		Person p5("Dick");
		p5.persist();

		Person p6("Harry");
		p6.persist();

		Person p7 = Person::personFromSeq(2);
		cout << p7.getPersonSeqNum() << " is " << p7.getRealName() << endl; 
		cout << "isUnknown: " << p7.isUnknown() << endl;

		Person p8 = Person::personByRealName("Parry");
		cout << p8.getPersonSeqNum() << " is " << p8.getRealName() << endl; 

		Face f1("original.jpg", Point(10,10), Point(20,20), Mat(Size(100,120), CV_8UC1)); 
		f1.setTraining(true);
		f1.persist();

		Face f2("original.jpg", Point(10,10), Point(20,20), Mat(Size(100,120), CV_8UC1)); 
		f2.setTraining(true);
		f2.persist();

		Face f3("original.jpg", Point(10,10), Point(20,20), Mat(Size(100,120), CV_8UC1));
		f3.persist();

		Person unknown = Person::personByRealName("Unknown");
		cout << "facecount for 'Unknown': " << unknown.getFaces().size() << endl;

		Person parry = Person::personByRealName("Parry");
		cout << "facecount for 'Parry': " << parry.getFaces().size() << endl;

		parry.addFace(f1);
		parry.addFace(f2);
		parry.addFace(f3);
		parry.persist();

		Face f4("original.jpg", Point(10,10), Point(20,20), Mat(Size(100,120), CV_8UC1));
		f4.persist();
		

		parry = Person::personByRealName("Parry");
		cout << "facecount for 'Parry': " << parry.getFaces().size() << endl;

		MySQLite::closeDB();

/*
		Mat i1 = imread("rec_img_11.12.png", CV_LOAD_IMAGE_GRAYSCALE);
*/

		//Mat boo = Mat(Size(100,100), CV_8UC1); 
		//fdb.getTrainingMat(boo);

		//cout << boo.cols << "," << boo.rows << endl;

	}catch(runtime_error e){
		cout << "Exception: " << e.what() << endl;
	}
    return 0;
}
