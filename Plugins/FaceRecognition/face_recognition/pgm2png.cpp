/*
 * File name: foo.cpp
 * Date:      2011-09-16 17:06
 * Author:    Kristján Rúnarsson
 */

#include <iostream>
#include <string>
#include "ImageList.h"
using namespace std;

int main(int argc, char *argv[]){
	
	cout << argv[1] << endl;
	ImageList il(argv[1]);

	string newSuffix = "png";
	for(unsigned int i=0; i<il.size(); i++)
	{
		string path = il.getPathByIndex(i);
		size_t found = path.find("pgm");
		if(found != string::npos){
			path.replace(found, newSuffix.size(), newSuffix);
		}

		imwrite(path, il.getImageByIndex(i));
		cout << path << endl;	
	}
	
    return 0;
} // end main()
