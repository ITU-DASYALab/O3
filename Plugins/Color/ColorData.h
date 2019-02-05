/***********************************************************************
 ** Reykjavik University
 ** Grímur Tómasson
 ** Copyright (c) 2010. All rights reserved.
 **********************************************************************/

#ifndef COLOR_DATA
#define COLOR_DATA

struct ColorData
{
	double totalRed, totalGreen, totalBlue; //Total color value used to calculate AVG
	//	int minRed, minGreen, minBlue; //MIN
	int avgRed, avgGreen, avgBlue; //Calculate final AVG
	//	int maxRed, maxGreen, maxBlue; //MAX	
};

#endif