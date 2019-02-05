#include "Recognizer.h"
#include <algorithm>

vector<RecognizerResult> Recognizer::nearestNeighbor(const vector<Mat> &projTrFaces, const Mat &unkProjected, unsigned int retain)
{
	vector<RecognizerResult> results;

	double closestFaceDist = DBL_MAX;
	string closestFaceID = "Unknown";

	for(unsigned int i = 0; i < projTrFaces.size(); i++) 
	{
		// Given two vectors and the NORM_L2 type ID the norm function computes the Euclidean distance:
		//     dist(SRC1,SRC2) = SQRT(SUM(SRC1(I) - SRC2(I))^2)
		// between the projections of the current training face and unknown.
		Mat src1 = projTrFaces[i];
		Mat src2 = unkProjected;
		double dist = norm(src1, src2, NORM_L2);

		// Every time I find somebody with a shorter distance I save the distance, map his
		// index number to his actual ID in the set of traing images and save the actual ID.

		if(dist <= closestFaceDist) {
			closestFaceDist = dist;
			closestFaceID = imageList.getSubjectNameByIndex(i);

			RecognizerResult tmpRes;
			tmpRes.subjectName = closestFaceID;
			tmpRes.distance = closestFaceDist;

			// We know this is the best match yet, if we previously got the same subject name we
			// must remove it from the results because we now have a better match for the subject
			// with that name.
			vector<int> deleteList;
			for(unsigned int j=0; j<results.size(); j++)
			{
				if(results[j].subjectName.compare(tmpRes.subjectName) == 0)
				{
					deleteList.push_back(j);
				}
			}

			for(unsigned j=0; j<deleteList.size(); j++)
			{
				results.erase(results.begin() + deleteList[j]);	
			}

			// The new match goes to the back of the vector.
			results.push_back(tmpRes);

			// If the number of matches exceeds the number we want to retain, remove the element
			// at the front of the vector.
			if(results.size() > retain)
			{
				results.erase(results.begin());
			}
		}
	}

	// The distances were added in descending order, the smallest is last so we must reverse
	// the vector.
	reverse(results.begin(), results.end());

	return results;
}
