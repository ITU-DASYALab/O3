#include "FaceDetector.h"

FaceDetector::FaceDetector(string trFileFace, string trFileRightEye, string trFileLeftEye)
{

	this->flags = 0;

	this->upScale = 1;
	this->downScale = 1;

	this->haarFlags = 0;

	eyeRoiPropUpperBound = 0.1;
	eyeRoiPropLowerBound = 0.5;
	eyeRoiPropWidth = 0.6;

	this->faceFrontCasPars.scaleFactor = 1.20;
	this->faceFrontCasPars.minNeighbors = 3;
	this->faceFrontCasPars.flags = CV_HAAR_DO_CANNY_PRUNING;
	this->faceFrontCasPars.minWidth = 5;
	this->faceFrontCasPars.minHeight = 5;

	this->eyeCasPars.scaleFactor = 1.05;
	this->eyeCasPars.minNeighbors = 3;
	this->eyeCasPars.flags = CV_HAAR_DO_CANNY_PRUNING;
	this->eyeCasPars.minWidth = 5;
	this->eyeCasPars.minHeight = 5;

	// TODO: runtime exceptions here.

	if(!casFaceFrontal.load(trFileFace)){
		cerr << "Failed to load frontal cascade training data: " << trFileFace << endl;
		exit(1);
	}

	if(!casLeftEye.load(trFileLeftEye)){
		cerr << "Failed to load left eye cascade training data: " << trFileLeftEye << endl;
		exit(1);
	}

	if(!casRightEye.load(trFileRightEye)){
		cerr << "Failed to load right eye cascade training data: " << trFileRightEye << endl;
		exit(1);
	}

}

void FaceDetector::setScale(int scale){
upScale = 100.0/scale;
downScale = scale/100.0;
}

void FaceDetector::setFlags(int flags){
this->flags = flags;
}

void FaceDetector::detect(CascadeClassifier &cascade, Mat &image, vector<Rect> &resRois, CascadeParams casPars)
{
cascade.detectMultiScale(
		image,
		resRois,
		casPars.scaleFactor,
		casPars.minNeighbors,
		casPars.flags,
		Size( casPars.minWidth, casPars.minHeight) );

}


/* Simple face detection. Once the detection is done the ROIs found by OpenCV
 * are inserted into a tree like region of interest structure where the root
 * ROI is the original image it self, it's sub regions are the ROIs for the
 * faces within it.
 */
void FaceDetector::detectFaces(Mat &originalImage, RegionOfInterest &faceRois)
{	
	this->scaledSearchImage = Mat(originalImage);

	// To increase detection speed we downsize the image and then search for faces.
	CvSize searchSize =  Size(originalImage.cols*downScale,originalImage.rows*downScale);
	resize(originalImage,scaledSearchImage, searchSize, 0, 0, INTER_LINEAR);

//		Mat gray, norm_img(img.rows, img.cols, CV_8UC1 );
//		cvtColor(img, gray, CV_BGR2GRAY);
//		resize(gray, norm_img, norm_img.size(), 0, 0, INTER_LINEAR);
//		equalizeHist(norm_img, norm_img);


	double detTime;
    if(flags & TIME_DETECTION){
        detTime = (double)cvGetTickCount();
    }

	// Face detection can be done on very small images. Scaling an imag down cuts 
	// executiont time considerably when the original image is very large. 
	// However, the down scaling should be capped at a certain minimum size or 
	// skipped if the original image was smaller than or equally large as this 
	// minimum size.

	vector<Rect> faces;
	this->detect(casFaceFrontal, scaledSearchImage, faces, faceFrontCasPars);

	for(unsigned int i=0; i < faces.size(); i++){
		RegionOfInterest face("face",
					faces[i].x * upScale,
					faces[i].y * upScale,
					faces[i].width * upScale,
					faces[i].height * upScale);
		
		faceRois.addSubRegion(face);					
	}
	
    if(flags & TIME_DETECTION){
        detTime = (double)cvGetTickCount() - detTime;
		faceTime =  detTime/((double)cvGetTickFrequency()*1000.0);

        //cout << "Detected faces in: " << detTime/((double)cvGetTickFrequency()*1000.) 
		//	<< " ms" << endl;
    }
    

	int i = 0;
	if(flags & SAVE_ROI)
	{
		for( vector<Rect>::const_iterator face  = faces.begin(); face != faces.end(); face++, i++){
			stringstream saveName;
			saveName << "roi_face_" << i <<  ".png";
			Mat faceRoi = scaledSearchImage(*face);
			imwrite(saveName.str(), faceRoi);
		}
	}
}

void FaceDetector::markFaces(Mat &image, RegionOfInterest &root, CvScalar color)
{
    // For each face found, draw a box.
	vector<RegionOfInterest*> &faces = root.getSubRegions();
	for(unsigned int i=0; i<faces.size(); i++)
	{
		Rect abs =  faces[i]->getAbsoluteRect();
        rectangle(image, abs, color, 3, 8, 0 );
        //rectangle(image, faces[i]->getAbsoluteRect(), color, 3, 8, 0 );
    }
}


/* During the face search procedure the regions of interest for each face
 * are inserted into a tree like ROI structure where the root ROI is the 
 * original image it self, it's sub regions are the ROIs for the
 * faces within it.
 * 
 * Given a ROoi tree loaded with face ROIs this method calculates the search 
 * regions for the right and left eyes and processes them.  The eye search 
 * ROIs are added as sub regions of the relavant face and the eyes found 
 * within each region are added as sub regons of the eye search ROI in which 
 * they were found.
 *
 * Since the face cascade focuses on frontal faces one can estimate the 
 * location of the eyes and define two separate regions of interest were the 
 * cascade should search for eyes. This speeds up the search and reduces false 
 * positives.
 * 
 *    The left eye search       The right eye search.
 *	  Region of Interest.       Region of Interest 
 *    --------------------      ------------------------
 *
 *    1 - eyeRoiWidth              eyeRoiWidth
 *        |                           |
 *        v                           v
 *    +-------+                 +----------+
 *    |       |                 |          |
 *    --------------------      ----------------------+--+
 *    |xx  irrelevant  xx|      |xx  irrelevant  xx|  |<-|-- eyeRoiUpperBound
 *    |------------------|      |------------------|--+  |
 *    |x I/R x| Left eye |      | Right eye|x I/R x|     |<- eyeRoiLowerBound
 *    |x I/R x| search   |      | search   |x I/R x|     |
 *    |x I/R x| ROI      |      | ROI      |x I/R x|     |
 *    |------------------|      |------------------|-----+
 *    |xx  irrelevant  xx|      |xx  irrelevant  xx|
 *    |xx  irrelevant  xx|      |xx  irrelevant  xx|
 *    |xx  irrelevant  xx|      |xx  irrelevant  xx|
 *    |xx  irrelevant  xx|      |xx  irrelevant  xx|
 *    --------------------      -------------------- 
 */
void FaceDetector::detectEyes(Mat &originalImage, RegionOfInterest &root)
{

	//Mat gray, norm_img(img.rows, img.cols, CV_8UC1 );
	//cvtColor(img, gray, CV_BGR2GRAY);
	//resize(gray, norm_img, norm_img.size(), 0, 0, INTER_LINEAR);
	//equalizeHist(norm_img, norm_img);
	
	double detTime;
	if(flags & TIME_DETECTION){
		detTime = (double)cvGetTickCount();
	}

	vector<RegionOfInterest*> &faces = root.getSubRegions();
	// Iterate over all the faces previously found in this picture.
	for(unsigned int i = 0; i < faces.size(); i++)
	//for( int i = 0; i < root.getSubRegions().size(); i++)
	{

		Rect lEyeSearchRoi, rEyeSearchRoi;
		Mat lEyeSearchMat, rEyeSearchMat;

		// Exctract the face region from the original full sized photo. Eye detection 
		// is done on the largest possible ROI since an eye is a rather small feature.
		Mat faceRoiMat = originalImage(faces[i]->getRect());

		// Now calcualte the positon of the eye ROIs within the face.
		setEyeSearchRois(lEyeSearchRoi, rEyeSearchRoi, faces[i]->getRect());

		// Discard anything smaller than 10% of the eye seach roi.
		this->eyeCasPars.minWidth = lEyeSearchRoi.width * 0.2;
		this->eyeCasPars.minHeight = lEyeSearchRoi.height * 0.2;

		rEyeSearchMat = faceRoiMat(rEyeSearchRoi);
		lEyeSearchMat = faceRoiMat(lEyeSearchRoi);

		vector<Rect> rightEyes;
		detect(casRightEye, rEyeSearchMat, rightEyes, eyeCasPars);
		
		RegionOfInterest rightEyeSearchRegion("rightEyeSearchRegion", 
							rEyeSearchRoi.x, rEyeSearchRoi.y,
							rEyeSearchRoi.width, rEyeSearchRoi.height);

		// To each face add it's right eye search region.
		faces[i]->addSubRegion(rightEyeSearchRegion);

		RegionOfInterest *rightEyeSearchSubRegion = faces[i]->getSubRegions()[0];

		// To this search region add the eyes found within it.
		for(unsigned int j=0; j < rightEyes.size(); j++)
		{
			RegionOfInterest rightEye("rightEye", 
							rightEyes[j].x,
							rightEyes[j].y,
							rightEyes[j].width,
							rightEyes[j].height); 

			rightEyeSearchSubRegion->addSubRegion(rightEye);	

		}

		vector<Rect> leftEyes;
		detect(casLeftEye, lEyeSearchMat, leftEyes, eyeCasPars);

		RegionOfInterest leftEyeSearchRegion("leftEyeSearchRegion", 
							lEyeSearchRoi.x, lEyeSearchRoi.y,
							lEyeSearchRoi.width, lEyeSearchRoi.height);

		// To each face add it's left eye search region.
		faces[i]->addSubRegion(leftEyeSearchRegion);

		RegionOfInterest *leftEyeSearchSubRegion = faces[i]->getSubRegions()[1];

		// To this search region add the eyes found within it.
		for(unsigned int j=0; j < leftEyes.size(); j++)
		{
			RegionOfInterest leftEye("leftEye", 
							leftEyes[j].x,
							leftEyes[j].y,
							leftEyes[j].width,
							leftEyes[j].height);
							
			leftEyeSearchSubRegion->addSubRegion(leftEye); 

		}

		if(flags & SAVE_ROI)
		{
			string fType = ".png";
			stringstream saveName;
			saveName << "roi_face_" << i << "_left_eye" << fType;

			imwrite(saveName.str(), lEyeSearchMat);

			saveName.str("");

			saveName << "roi_face_" << i << "_right_eye" << fType;

			imwrite(saveName.str(), rEyeSearchMat);
		}
	}

	if(flags & TIME_DETECTION){
		detTime = (double)cvGetTickCount() - detTime;
		eyeTime =  (double)detTime/((double)cvGetTickFrequency()*1000.0);
	
		//cout << "Detected eyes in: " << detTime/((double)cvGetTickFrequency()*1000.) 
		//	<< " ms" << endl;
	}
}


// Calculates the left eye region of interest
void FaceDetector::setEyeSearchRois(Rect &leftRoi, Rect &rightRoi, Rect face)
{
	int upperLeftX  = (int)(face.width * (1-eyeRoiPropWidth));
	int upperLeftY = (int)(face.height * eyeRoiPropUpperBound);

	int width = (int)(face.width * eyeRoiPropWidth);
	int height = (int)(face.height * eyeRoiPropLowerBound);

	leftRoi= Rect(upperLeftX, upperLeftY, width, height);

	upperLeftX  = 0; 
	upperLeftY = (int)(face.width * eyeRoiPropUpperBound);

	width = (int)(face.width * eyeRoiPropWidth);
	height = (int)(face.height * eyeRoiPropLowerBound);

	rightRoi = Rect(upperLeftX, upperLeftY, width, height);
}

void FaceDetector::markEyes(Mat &originalImage, RegionOfInterest &root, CvScalar leftColor, CvScalar rightColor)
{
	Point center;
	int radius;
	
	vector<RegionOfInterest*> &faces = root.getSubRegions();
	for(unsigned int i=0; i<faces.size(); i++)
	{
		vector<RegionOfInterest*> &eyeSearchSubRegions = faces[i]->getSubRegions();
		for(unsigned int j=0; j<eyeSearchSubRegions.size(); j++)
		{
			vector<RegionOfInterest*> &eyes = eyeSearchSubRegions[j]->getSubRegions();
			for(unsigned int k=0; k<eyes.size(); k++)
			{
				RegionOfInterest *eye = eyes[k];

				Rect rect = eye->getAbsoluteRect();
				
				center.x = cvRound(rect.x + rect.width*0.5);
				center.y = cvRound(rect.y + rect.height*0.5);
				radius = cvRound((rect.width + rect.height)*0.25);			
				
				if (eye->getName() == "leftEye"){
					circle( originalImage, center, radius, leftColor, 3, 8, 0 );
				}else{
					circle( originalImage, center, radius, rightColor, 3, 8, 0 );
				}
			}
		}
	}
}


/** Given an original image, a RegionOfInterest object corresponding to a face and a Size object this function 
 * will return a recognition image that has been resized donw to the specified size. If the provided face 
 * RegionOfInterest object has both left and right eye sub regions the face will be rotated and repositioned
 * such that the eyes are level and the nasal root is positioned at a fixed point in the image. The face will
 * then be grayscaled, histogram equalized and the face will be surrounded by an elliptical mask.
 * 
 * Flags:
 *  NO_MASK - Turn off the mask.
 *  NO_ROTATION - Do not attempt to rotate the face if both eyes are present.
 *  NO_NORMALIZATION - Do not histogram equalize and grayscale the image. Normalized images are type CV_8UC1 
 *                     otherwise the image type is CV_8UC3.
 */


void calculateEyeAngle(RegionOfInterest &roi, Point optimalNasalRoot, Point &eyeCenterShift, double &angle);
void rotateFace(Mat &source, Mat &destination, Point &sourceBuffer, Rect faceRect, Point optimalNasalRoot, double angle);
void applyMask(Mat &source, Mat &destination, Size maskSize, MaskParams mp, int flags);
void normalize(Mat &source);

void FaceDetector::extractFace(Mat &original, Mat& face, RegionOfInterest &roi, Size recSize, MaskParams mp, int flags, int interpolation)
{
	double detTime;
	detTime = (double)cvGetTickCount();

	// FIXME: Throw runtime exceptions.
	assert(0 <= mp.optNasalRootPos && mp.optNasalRootPos <= 1);
	assert(recSize.width <= recSize.height);
	assert(roi.getName().compare("face") == 0);

	Rect faceRect = roi.getAbsoluteRect();

	// ROI adjustment factors:
	// scaleFactor  -> Make the face ROI bigger than the region returned by the detector.
	// shiftFactor  -> If the ROI is increased it must be repositioned.
	// aspectFactor -> Correct the aspect ratio because the detector sometimes slices off
	//                 the chin and throat.
	Size scaleFactor(faceRect.width * 0.1, faceRect.height * 0.1); 
	Point shiftFactor(scaleFactor.width / 2.0, scaleFactor.height / 2.0);
	Size aspectFactor(0, faceRect.height * 0.2);

	// Set a fixed point in an image where the nasal root should be. This is good for 
	// faces where eyes were found but not so good if no eyes were found in the image.
	// This could lead to problems. Optimally we wold like to improve eye detection to
	// the point where eyes can be found in the vast majority of faces.
	Point optimalNasalRoot(faceRect.width/2, faceRect.height * mp.optNasalRootPos);

	// If both of the eye search regions have at least one eye.  We must determine if 
	// the eyes are level.
	RegionOfInterest *rightEyeSearchRoi = roi.getSubRegions()[0];
	RegionOfInterest *leftEyeSearchRoi = roi.getSubRegions()[1];

	double angle = 0;
	bool canRotate = leftEyeSearchRoi->hasSubRegions() && rightEyeSearchRoi->hasSubRegions();
	if(canRotate)
	{
		Point eyeCenterShift;

		calculateEyeAngle(roi, optimalNasalRoot, eyeCenterShift, angle);

		faceRect = faceRect - eyeCenterShift;
	}

	// Resize the face rect.
	faceRect=faceRect + scaleFactor;

	// Reposition the origin and adjust the optimal nasal root point to account for scaling.
	faceRect = faceRect - shiftFactor;
	optimalNasalRoot += shiftFactor;

	// Correct the aspect ratio of the ROI if required.
	faceRect = faceRect + aspectFactor;

	// Extract a copy of the face from the original image and rotate it around the
	// optimal nasal root point.
	Mat tmpFace;

	int padFactor = 200;
	Mat bufferedOriginal(Size(original.cols+padFactor*2,original.rows+padFactor*2),original.type());
	copyMakeBorder(original, bufferedOriginal, padFactor, padFactor, padFactor, padFactor, BORDER_CONSTANT, mp.color);
	Point buffer(padFactor,padFactor);

	if(!(flags & NO_ROTATION) && canRotate)
	{
		rotateFace(bufferedOriginal, tmpFace, buffer, faceRect, optimalNasalRoot, angle);

	}
	else
	{
		Rect tmpFaceRect = faceRect + buffer;
		tmpFace = Mat(bufferedOriginal, tmpFaceRect);
	}

	if(flags & MARK_OPTIMAL_NASAL)
		circle(tmpFace, optimalNasalRoot, 6, CV_RGB(255,150,0), 4);

	// Resize the image to the required recognition size.
	Mat tmpFaceScaled;
	resize(tmpFace, tmpFaceScaled, recSize , 0, 0, interpolation);
	tmpFace = tmpFaceScaled;

	// Normalize: Light, Histogram... 
	if(!(flags & NO_NORMALIZATION))
	{
		normalize(tmpFace);
	}

	// Masking: Create an ellptical mask in memory, copy face to output param.
	if(flags & NO_MASK)
	{
		tmpFace.copyTo(face);
	}
	else
	{
		applyMask(tmpFace, face, recSize, mp, flags);
	}

	detTime = (double)cvGetTickCount() - detTime;
	//cout << "Extracted face in: " << detTime/((double)cvGetTickFrequency()*1000.) << " ms"<< endl;
}

void FaceDetector::extractFace(Mat &original, Mat& face, RegionOfInterest &roi, Size recSize, int flags, int interpolation )
{
	MaskParams mp;
	FaceDetector::extractFace(original, face, roi, recSize, mp, flags, interpolation);
}

void calculateEyeAngle(RegionOfInterest &roi, Point optimalNasalRoot, Point &eyeCenterShift, double &angle)
{

	RegionOfInterest *rightEyeSearchRoi = roi.getSubRegions()[0];
	RegionOfInterest *leftEyeSearchRoi = roi.getSubRegions()[1];

	RegionOfInterest *rightEye = rightEyeSearchRoi->getSubRegions()[0]; 
	RegionOfInterest *leftEye = leftEyeSearchRoi->getSubRegions()[0];

	Point2d rightEyeCenter = rightEye->getCenter()+rightEyeSearchRoi->getLocation();
	Point2d leftEyeCenter = leftEye->getCenter()+leftEyeSearchRoi->getLocation();

	Point2d hypotenuse = rightEyeCenter - leftEyeCenter;
	Point2d adjacent(hypotenuse.x, 0);

	double hypNorm = norm(hypotenuse);
	double adjNorm = norm(adjacent);

	angle = acos(adjNorm/hypNorm) * 180/M_PI;

	if(hypotenuse.y > 0)
	{
		angle = -angle;
	}

	Point actualNasalRoot(hypotenuse.x/2, hypotenuse.y/2);

	Point foo = rightEye->getCenter()+rightEyeSearchRoi->getLocation();
	actualNasalRoot = foo - actualNasalRoot;
	eyeCenterShift = optimalNasalRoot-actualNasalRoot;

}

void rotateFace(Mat &source, Mat &destination, Point &sourceBuffer, Rect faceRect, Point optimalNasalRoot, double angle)
{
	// Start by extracting an oversized ROI, thust creating a buffer that ensures
	// as little of the face as possible is lost on rotation.

	Rect rotFaceRect = faceRect;
	Size cutoffBuffer = Size(faceRect.width*0.15,faceRect.height*0.15);
	Point cutoffBufferShift = Point(cutoffBuffer.width/2, cutoffBuffer.height/2);

	// Adjust face ROI for buffer zone.
	rotFaceRect = rotFaceRect + cutoffBuffer;
	rotFaceRect = rotFaceRect - cutoffBufferShift;

	// Take into accout that the original image has a buffer zone as well.
	rotFaceRect += sourceBuffer;
	Mat tmpFace = Mat(source, rotFaceRect);

	// Adjust the optimal nasal position to accout for the cutoff buffer.
	optimalNasalRoot = optimalNasalRoot + cutoffBufferShift;
	
	// Rotate the image the image to make sure the eyes are level.  This is a 
	// time expensive operation it would be better to only do this if the eye
	// angle is above a certain level. One can also save time by scaling the
	// face down first but then one loses a bit of precision.
	Mat rotMat = getRotationMatrix2D(optimalNasalRoot, angle, 1.0);
	Mat tmpFaceRot;

	warpAffine(tmpFace, tmpFaceRot, rotMat, tmpFace.size());

	destination = Mat(tmpFaceRot, Rect(cutoffBufferShift, faceRect.size()));
}

void applyMask(Mat &source, Mat &destination, Size maskSize, MaskParams mp, int flags)
{
		// Mask the recognition image and copy it.
		Point eCenter(maskSize.width, maskSize.height);
		Size eAxes = Size((maskSize.width)*0.85, (maskSize.height)*0.85);

		Mat mask(maskSize, CV_8UC1);

		if(flags & NO_NORMALIZATION) {
			destination = Mat(maskSize, CV_8UC3);
		} else {
			destination = Mat(maskSize, CV_8UC1);
		}

		rectangle(mask, Point(0,0), maskSize, CV_RGB(0,0,0), CV_FILLED);
		ellipse(mask, eCenter, eAxes, 0, 0, 360, CV_RGB(255,255,255), CV_FILLED, 0, 1);
		rectangle(destination, Point(0,0), maskSize, mp.color, CV_FILLED);

		// Overwrite everything in the 'maskColor' rectange we drew into the face matrix with 
		// pixels from the temporary face image. Only pixels from the temporary face image that 
		// correspond to non zero elements in the face mask will be copied
		source.copyTo(destination, mask); 
}

void normalize(Mat &source)
{
	Mat tmpFaceGray, tmpFaceNorm(source.rows, source.cols, CV_8UC1 );
	cvtColor(source, tmpFaceGray, CV_RGB2GRAY);
	equalizeHist(tmpFaceGray, tmpFaceNorm);

	source = tmpFaceNorm;
}

double FaceDetector::getFaceTime()
{
	return faceTime;
}

double FaceDetector::getEyeTime()
{
	return eyeTime;
}
