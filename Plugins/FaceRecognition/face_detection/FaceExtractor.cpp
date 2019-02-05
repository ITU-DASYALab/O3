#include "FaceDetector.h"
#include <sys/stat.h>
#include <unistd.h>

void usage();
void printRoiTree(RegionOfInterest &roiRoot);

int main( int argc, char** argv )
{
	bool doScale = false;
    string casFaceFrontalName = "resources/haarcascade_frontalface_alt.xml";
	string casRightEyeName = "resources/haarcascade_righteye_2splits.xml";
	string casLeftEyeName = "resources/haarcascade_lefteye_2splits.xml";

 	if (argc < 2){
		usage();
	}

	float scale = 1.0;
	int pixels = 1024;
	int index = 0;
	bool saveRois = false;
	bool printArgs = false;
	bool isVerbose = false;
	bool doTiming = false;
	bool doMark = false;
	string recImgSavePrefix = "rec_img_";
	string saveDirPath = ".";

	string imageName, imagePath;

	char c;
	while ( (c = getopt(argc, argv, ":aps:vthi:f:md:")) != -1) {
		switch (c) {
			case 's':
				pixels = atoi(optarg);
				doScale = true;
				break;
			case 'p':
				saveRois = true;
				break;
			case 'a':
				printArgs = true;
				break;
			case 'v':
				isVerbose = true;
				break;
			case 't':
				doTiming = true;
				break;
			case 'h':
				usage();
				break;
			case 'i':
				index=atoi(optarg);
				break;
			case 'f':
				recImgSavePrefix = optarg;
				break;
			case 'd':
				saveDirPath = optarg;
				break;
			case 'm':
				doMark = true;
				break;
			case '?':
				cout << "Invalid option: '-" << (char)optopt << "'" << endl;
				usage();
				break;
			case ':':
				cout << "Missing argument value for: '-" << (char)optopt << "'" << endl;
				usage();
				break;
			default:
				cerr << "getopt returned character code 0%o" << c << endl;
				usage();
		}
	}

	struct stat st;
	if(stat(saveDirPath.c_str(),&st) != 0)
	{
		cerr << "Directory '" << saveDirPath.c_str() << "' does not exist or cannot be accessed." << endl;
		exit(1);
	}

	if(saveDirPath.find_last_of("/") != saveDirPath.size())
	{
			saveDirPath.append("/");
	}

	if(printArgs){
		for(int i=0; i < argc; i++)
		{
			cout << "argc[" << i << "]: " << argv[i] << endl;
		}

	}

	if (optind < argc)
	{
		imagePath = argv[optind];
		
		if(int pos = imagePath.find_last_of("/"))
		{
			imageName = imagePath.substr(pos+1,imagePath.size());
		}
	} 
	else 
	{
		cerr << "You must provide an image path." << endl;
		usage();
	}

	if(isVerbose){
		cout << endl;
		cout << "Classifier training sets." << endl;
		cout << "    " << casFaceFrontalName << endl;
		cout << "    " << casRightEyeName << endl;
		cout << "    " << casLeftEyeName << endl;
	}
 

	Mat matImage = imread( imagePath, CV_LOAD_IMAGE_COLOR );

	if(matImage.empty()){
		cerr << "Unable to read file: " << imagePath << endl;
		exit(1);
	}

	scale = (float)pixels/(float)matImage.cols*100;
	
	//FIXME do this check in detector and throw runtime exception?
	if(matImage.cols < pixels && doScale){
		cerr << "Image width must be greater than scaling width." << endl;
		exit(0);
	}

	FaceDetector *fdet = new FaceDetector(casFaceFrontalName, casRightEyeName, casLeftEyeName);

	int flags=0;

	if(doTiming){
		flags = flags|TIME_DETECTION;
	}

	if(saveRois){
		flags = flags|SAVE_ROI;
	}
	
	fdet->setFlags(flags);
	fdet->setScale(scale);

	RegionOfInterest roiRoot(imageName, matImage.cols, matImage.rows);
	fdet->detectFaces(matImage, roiRoot);
	
	fdet->detectEyes(matImage, roiRoot);

	if(isVerbose){
		cout << "Scaling images down to " << pixels << " pixels for searching." << endl;
		cout << endl;
		printRoiTree(roiRoot);
	}


	if(doTiming)
	{
		cout << "Detected faces in: " << fdet->getFaceTime() << "ms" << endl;
		cout << "Detected eyes in: " << fdet->getEyeTime() << "ms" << endl;
	}
	
	if(doMark)
	{
		fdet->markFaces(matImage, roiRoot, CV_RGB(255, 0, 0));

		fdet->markEyes(matImage, roiRoot, CV_RGB(0, 0, 255), CV_RGB(0, 255, 0));
	}

		stringstream markedImgName; 
		markedImgName << saveDirPath << recImgSavePrefix << index << "_original.jpg";

		cout << endl;
		cout << "Saving copy of original as: " << markedImgName.str() << endl;

		imwrite(markedImgName.str(),matImage);
	
	cout << "Processing: " << imageName << endl;
	for(unsigned int i=0; i<roiRoot.getSubRegions().size(); i++){

		Mat recFace;
		FaceDetector::extractFace(matImage, recFace, *roiRoot.getSubRegions()[i], Size(100,120), 0, INTER_LINEAR);

		stringstream recFaceName;
		recFaceName << saveDirPath << recImgSavePrefix << index << "." << i << ".png";
		cout << "Saved as: " << recFaceName.str() << endl;
		imwrite(recFaceName.str(),recFace);

		recFaceName.str("");
		recFaceName << saveDirPath << recImgSavePrefix << index << "." << i << ".pgm";
		cout << "Saved as: " << recFaceName.str() << endl;
		imwrite(recFaceName.str(),recFace);
	}

    return 0;
}

void usage()
{
	cout << "Given a single image find all faces in it, mark them with squares and the eyes with ciricles." << endl;
	cout << endl;
	cout << "Usage: faceextractor [-s <pixels>] [-p] [-a] [-h] <image_name>" << endl;
	cout << "    -s Scale the the image down to the given size before searching for faces." << endl;
	cout << "    -t Times the haarcascades for face and eye search and prints out search time im milliseconds." << endl;
	cout << "    -i An index number that is prefixed to the sequence number of a face within an image when saving" << endl; 
	cout << "       recognition images, i.e: \"rec_img_<index>.0.png\". Mainly useful when batch processing many " << endl;
	cout << "       images in a script." << endl;
	cout << "    -f Prefix added to the save name of all recognition images extracted, default: \"rec_img_\"" << endl;
	cout << "    -d Set an output directory for the extracted recognition images." << endl;
	cout << "    -h This text." << endl;
	cout << endl;
	cout << "Debug options: " << endl;
	cout << "    -p Save the regions of interest used to search for faces and eyes as PNGs. This is meant for" << endl; 
	cout << "       ebugging. Old ROIs will be overwritten unless they are copied between executions.." << endl;
	cout << "    -m Mark eyes with red squares and eyes with circles, green for right, blue for left." << endl;
	cout << "    -a Print the arguments." << endl;
	cout << "    -v Verbose mode, prints out a load of debug data." << endl;

	exit(1);
}

void printRoiTree(RegionOfInterest &roiRoot)
{
	if(!roiRoot.getName().compare("root")){
		cerr << "Not a root node." << endl;
		exit(1);
	}

	cout << "faces under root:" << endl;
	vector<RegionOfInterest*> &faces = roiRoot.getSubRegions();
	for(unsigned int i=0; i<faces.size(); i++)
	{
		cout << "f[" << i << "]->name: " << faces[i]->getName() << endl; 
		cout << "f[" << i << "]->x: " << faces[i]->getX() << endl; 
		cout << "f[" << i << "]->y: " << faces[i]->getY() << endl; 

		
		vector<RegionOfInterest*> &eyeSearchRegions = faces[i]->getSubRegions();
		for(unsigned int j=0; j<eyeSearchRegions.size(); j++)
		{
			cout << "f[" << i << "]->esr[" << j << "]->name: " << eyeSearchRegions[j]->getName() << endl; 
			cout << "f[" << i << "]->esr[" << j << "]->x: " << eyeSearchRegions[j]->getX() << endl; 
			cout << "f[" << i << "]->esr[" << j << "]->y: " << eyeSearchRegions[j]->getY() << endl; 
			cout << "f[" << i << "]->esr[" << j << "]->ax: " << eyeSearchRegions[j]->getAbsoluteX() << endl; 
			cout << "f[" << i << "]->esr[" << j << "]->ay: " << eyeSearchRegions[j]->getAbsoluteY() << endl; 

			vector<RegionOfInterest*> &eyes = eyeSearchRegions[j]->getSubRegions();
			for(unsigned int k=0; k<eyes.size(); k++)
			{
				cout << "f[" << i << "]->esr[" << j << "]->eye[" << k << "]->name: " << eyes[k]->getName() << endl; 
				cout << "f[" << i << "]->esr[" << j << "]->eye[" << k << "]->par: " << eyes[k]->getParentName() << endl;
				cout << "f[" << i << "]->esr[" << j << "]->eye[" << k << "]->w: " << eyes[k]->getWidth() << endl; 
				cout << "f[" << i << "]->esr[" << j << "]->eye[" << k << "]->h: " << eyes[k]->getHeight() << endl; 
				cout << "f[" << i << "]->esr[" << j << "]->eye[" << k << "]->x: " << eyes[k]->getX() << endl; 
				cout << "f[" << i << "]->esr[" << j << "]->eye[" << k << "]->y: " << eyes[k]->getY() << endl; 
				cout << "f[" << i << "]->esr[" << j << "]->eye[" << k << "]->ax: " << eyes[k]->getAbsoluteX() << endl; 
				cout << "f[" << i << "]->esr[" << j << "]->eye[" << k << "]->ay: " << eyes[k]->getAbsoluteY() << endl; 
			}
		}
		cout << endl;
	}
}

