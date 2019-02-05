#include <iostream>
#include <fstream>
#include <iomanip>

#include "FaceRecognitionPlugin.h"
//#include "face_database/Face.h"
#include "../ObjectCube/Plugin/PluginObject.h"
#include "../ObjectCube/Plugin/PluginTagging.h"

using namespace std;

int main(int argc, char *argv[]){

	try{

		FaceRecognitionPlugin frp(1);
		
		// Reading test image 1 ----------------------------------------------------

		cout << "-----" << endl;

		string testImageName1 = "testimages/test1.jpg";

		fstream testImage1(testImageName1.c_str());
	
		testImage1.seekg(0,ios::end);
		int dataSize = testImage1.tellg();
		testImage1.seekg(ios::beg);
	
		string name=testImageName1;
	
		char *data1 = new char[dataSize];
		char *data2 = new char[dataSize];
		char *data3 = new char[dataSize];

		testImage1.read(data1, dataSize);

		testImage1.seekg(ios::beg);

		testImage1.read(data2, dataSize);

		testImage1.seekg(ios::beg);

		testImage1.read(data3, dataSize);

	
		// Process Test 1 ----------------------------------------------------------

		cout << "-----" << endl;

		PluginObject pluginObject1 = PluginObject(20,name,data1,dataSize);
	
		PluginReply pluginReply1 = frp.process( pluginObject1 );

		vector<PluginTagging> taggings1 = pluginReply1.getTaggings();

		for(unsigned int i=0; i<taggings1.size(); i++)
		{
			cout << "reply1: " << taggings1[i].getTag() << endl;
			cout << "reply1: " << taggings1[i].getSuggestedTags().size() << endl;
		}
		
		// Process Test 2 ----------------------------------------------------------

		cout << "-----" << endl;
	
		PluginObject pluginObject2 = PluginObject(21,name,data2,dataSize);
	
		PluginReply pluginReply2 = frp.process( pluginObject2 );

		vector<PluginTagging> taggings2 = pluginReply2.getTaggings();

		for(unsigned int i=0; i<taggings2.size(); i++)
		{
			cout << "reply2: " << taggings2[i].getTag() << endl;
			cout << "reply2: " << taggings2[i].getSuggestedTags().size() << endl;
		}

		// Confirm test 1 ----------------------------------------------------------

		cout << "-----" << endl;

		Coordinate2D upperLeft(1461.0,715.0);
		Coordinate2D lowerRight(2377.0, 1631.0);
		BoundingBox boundingBox;
		boundingBox.setUpperLeftCorner(upperLeft);
		boundingBox.setLowerRightCorner(lowerRight);

		frp.confirmTagging(20, "people", boundingBox, "Unknown1");

		// Confirm test 2 ----------------------------------------------------------

		cout << "-----" << endl;

		frp.confirmTagging(21, "people", boundingBox, "Unknown2");

		// -------------------------------------------------------------------------
		// Two confirmed images, there should be a retraining now.
		// -------------------------------------------------------------------------

		// Process Test 3 ----------------------------------------------------------

		cout << "-----" << endl;

		PluginObject pluginObject3 = PluginObject(22,name,data3,dataSize);
	
		PluginReply pluginReply3 = frp.process( pluginObject3 );
	
		vector<PluginTagging> taggings3 = pluginReply3.getTaggings();

		for(unsigned int i=0; i<taggings3.size(); i++)
		{
			cout << "reply3: " << taggings3[i].getTag() << endl;
			cout << "reply3: " << taggings3[i].getSuggestedTags().size() << endl;
		}

		// Confirm test 2 ----------------------------------------------------------

		cout << "-----" << endl;

		frp.confirmTagging(22, "people", boundingBox, taggings3[0].getTag());

		frp.deleteTagging(21, "people" , boundingBox, "Unknown2");

		char *data4 = new char[dataSize];

		testImage1.seekg(ios::beg);

		testImage1.read(data4, dataSize);

		PluginObject pluginObject4 = PluginObject(23, name, data4, dataSize);
	
		upperLeft = Coordinate2D (1461.0,715.0);
		lowerRight = Coordinate2D(2377.0, 1631.0);

		//BoundingBox boundingBox;
		boundingBox.setUpperLeftCorner(upperLeft);
		boundingBox.setLowerRightCorner(lowerRight);

		vector<BoundingBox> boundingBoxes;
		boundingBoxes.push_back(boundingBox);

		PluginReply pluginReply4 = frp.process( pluginObject4 , boundingBoxes);

		frp.confirmTagging(23, "people", boundingBox, "Jonas");

		// Reading test image 5 ----------------------------------------------------

		cout << "-----" << endl;

		string testImageName5 = "testimages/test3.jpg";

		fstream testImage5(testImageName5.c_str());
	
		testImage5.seekg(0,ios::end);
		dataSize = testImage5.tellg();
		testImage5.seekg(ios::beg);
	
		name=testImageName5;
	
		char *data5 = new char[dataSize];

		testImage5.read(data5, dataSize);

		// Process Test 5 ----------------------------------------------------------

		cout << "-----" << endl;

		PluginObject pluginObject5 = PluginObject(24,name,data5,dataSize);
	
		PluginReply pluginReply5 = frp.process( pluginObject5 );

		vector<PluginTagging> taggings5 = pluginReply5.getTaggings();

		cout << "Faces in landscape image: " << taggings5.size() << endl;

		for(unsigned int i=0; i<taggings5.size(); i++)
		{
			cout << "reply5: " << taggings5[i].getTag() << endl;
			cout << "reply5: " << taggings5[i].getSuggestedTags().size() << endl;
		}

		cout << "Done testing..." << endl;

	}
	catch (runtime_error e)
	{
		cout << "What: " << e.what() << endl;
	}
	catch (exception e)
	{
		cout << "What: " << e.what() << endl;
	}
	catch (...)
	{
		cout << "Blah" << endl;
	}
    return 0;
}
