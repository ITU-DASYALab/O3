/*
 *  HubCommon.cpp
 *  ObjectCube
 *
 *  Created by Grímur Tómasson on 17.2.2010.
 *  Copyright 2010 Reykjavik University. All rights reserved.
 *
 */


#include "HubCommon.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

int HubCommon::dataAccessType_ = HubCommon::POSTGRESQL;

string HubCommon::uncategorizedDimName_ = "UNCATEGORIZED";
string HubCommon::uncategorizedTagName_ = "Uncategorized";
string HubCommon::dataAccessTypeParameterName_ = "dataAccessType";

//____________________________________________________________________________________________________________________________________________________________________________________