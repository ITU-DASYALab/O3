#ifndef REGION_OF_INTEREST_H
#define REGION_OF_INTEREST_H

#include <vector>
#include <deque>
#include <iostream>
//#include <opencv2/imgproc/imgproc.hpp>

#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

class RegionOfInterest {
	private:
		vector<RegionOfInterest*> subRegions;
		//deque<RegionOfInterest*> subRegions;
		int x, y, width, height;
		string name;
		void init(string name, int x, int y, int width, int height);
		bool isRoot;
		int type;
		int px, py;

		RegionOfInterest *parent;
		RegionOfInterest *root;

		RegionOfInterest(string name, RegionOfInterest *root, RegionOfInterest *parent, int x, int y, int width, int height);
	
	public:

		RegionOfInterest();
		RegionOfInterest(string name, int width, int height);
		RegionOfInterest(string name, int x, int y, int width, int height);
		//RegionOfInterest(const RegionOfInterest &region);
		//RegionOfInterest &operator=(const RegionOfInterest &region);
		~RegionOfInterest();
		
		void addSubRegion(RegionOfInterest *region);
		bool hasSubRegions();

		RegionOfInterest* addSubRegion(RegionOfInterest r);
		
		//void setParent(RegionOfInterest *parent);
		//void setRoot(RegionOfInterest *root);

		vector<RegionOfInterest*> &getSubRegions();
			
		bool hasSubregions();

		int getX();
		int getY();
		int getHeight();
		int getWidth();
		
		string getName();
		string getRootName();
		string getParentName();
		string toOcString();
		
		Rect getRect();
		Rect getAbsoluteRect();

		Point2d getLocation();
		Point2d getCenter();
		
		int getAbsoluteX();
		int getAbsoluteY();
};

#endif
