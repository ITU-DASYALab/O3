#include <sstream>

#include "RegionOfInterest.h"


RegionOfInterest::RegionOfInterest()
{
	isRoot=true;
	this->init("", 0, 0, 0, 0);
}

/* Creates a root node.*/
RegionOfInterest::RegionOfInterest(string name, int width, int height){
	isRoot = true;
	this->parent=this;
	this->root=this;
	this->px=0;
	this->py=0;
	this->init(name, 0, 0, width, height);
}

/* Creates a child node */
RegionOfInterest::RegionOfInterest(string name, int x, int y, int width, int height)
{
	isRoot=false;
	this->name  = name;
	this->parent = 0;
	this->root = 0;
	this->px=0;
	this->py=0;
	this->init(name, x, y, width, height);
}

/* Creates a child node.*/
RegionOfInterest::RegionOfInterest(string name, RegionOfInterest *root, RegionOfInterest *parent, int x, int y, int width, int height)
{
	isRoot=false;
	this->name  = name;
	this->parent = parent;
	this->root = root;
	this->px=0;
	this->py=0;
	this->init(name, x, y, width, height);
}

/*
RegionOfInterest::RegionOfInterest(const RegionOfInterest &region)
{
	cout << "Copy constructor" << endl;
	cout << "Parent: " << region.parent << endl;;
	this->isRoot = region.isRoot;
	this->parent = region.parent;
	this->root = region.root;
	this->init(region.name, region.x, region.y, region.width, region.height);
}
*/

/*
RegionOfInterest &RegionOfInterest::operator=(const RegionOfInterest &r)
{
	RegionOfInterest *roi = new RegionOfInterest(r.name, r.x, r.y, r.width, r.height);
	roi->setParent(this);
	roi->setRoot(this->root);	
	roi->px = this->px + this->x;
	roi->py = this->py + this->y;
	return *roi;
}
*/

	
void RegionOfInterest::init(string name, int x, int y, int width, int height)
{
	this->name = name;
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
}

RegionOfInterest* RegionOfInterest::addSubRegion(RegionOfInterest r)
{
	//RegionOfInterest *roi = new RegionOfInterest(r.name, r.x, r.y, r.width, r.height);
	//roi->setParent(this);
	//roi->setRoot(this->root);	
	RegionOfInterest *roi = new RegionOfInterest(r.name, root, this, r.x, r.y, r.width, r.height);
	//roi->setParent(this);
	//roi->setRoot(this->root);	
	roi->px = this->px + this->x;
	roi->py = this->py + this->y;
	subRegions.push_back(roi);

	return roi;
}

RegionOfInterest::~RegionOfInterest(){
	for(unsigned int i=0; i<subRegions.size(); i++){
		delete subRegions[i];
	}
}

bool RegionOfInterest::hasSubRegions()
{
	return subRegions.size() > 0;
}

/* Set this node's parent node.
 */
 /*
void RegionOfInterest::setParent(RegionOfInterest *parent){
	this->parent = parent;
}
*/

/* Set the root node of the tree this ROI is part of.
 */
 /*
void RegionOfInterest::setRoot(RegionOfInterest *root){
	this->root = root;
}
*/

/* Name of the root ROI of this tree.
 */
string RegionOfInterest::getRootName(){
	return this->root->name;
}
/* A ROI can have search regions. A face has ROIs to search for eyes in, 
 * those ROIs in turn can have sub ROIs for each eye that was found.
 */
vector<RegionOfInterest*> &RegionOfInterest::getSubRegions(){
	return subRegions;
}

/* Name of this ROI.
 */
string RegionOfInterest::getName(){
	return this->name;
}

/* Name of the parent ROI.
 */
string RegionOfInterest::getParentName(){
	return this->parent->getName();
}

/* The x component of the ROI's location relative to the parent ROI in pixels.
 */
int RegionOfInterest::getX(){
	return this->x;
}

/* The x component of the ROI's location relative to the parent ROI in pixels.
 */
int RegionOfInterest::getY(){
	return this->y;
}

/* Height of this ROI in pixels.
 */
int RegionOfInterest::getHeight(){
	return this->height;
}

/* Width of this ROI in pixels.
 */
int RegionOfInterest::getWidth(){
	return this->width;
}
				
/* The x component of the ROI's location relative to the root ROI.
 */
int RegionOfInterest::getAbsoluteX()
{
	if(isRoot){
		return 0;
	}

	return getX() + parent->getAbsoluteX();
}

/* The y component of the ROI's location relative to the root ROI.
 */
int RegionOfInterest::getAbsoluteY()
{

	if(isRoot){
		return 0;
	}
	return getY() + parent->getAbsoluteY();
}

/* Rectangle with location relative to the parent ROI.
 */
Rect RegionOfInterest::getRect()
{
	return Rect(getX(), getY(), getWidth(), getHeight());
}

/* Rectangle with location relative to the root ROI.
 */
Rect RegionOfInterest::getAbsoluteRect()
{
	return Rect(getAbsoluteX(), 
				getAbsoluteY(), 
				getWidth(), getHeight());
}

/* Location relative to parent.
 */
Point2d RegionOfInterest::getLocation()
{
	Point2d location((double)x, (double)y);
	return location;
}

/* Center relative to parent.
 */
Point2d RegionOfInterest::getCenter()
{
	Point2d center((double)x+((double)width/2.0), (double)y+((double)height/2.0));
	return center;
}



string RegionOfInterest::toOcString()
{
	stringstream ocString;
	ocString << name;
	ocString << "[";
	ocString << this->x << "," << this->y;
	ocString << ":";
	ocString << this->width << "," << this->height;
	ocString << "]";
	return ocString.str();
}
