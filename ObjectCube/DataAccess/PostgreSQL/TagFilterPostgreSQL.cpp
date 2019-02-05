/*
* Snorri Gíslason - 2018
*/

#ifdef OC_POSTGRESQL

#include "TagFilterPostgreSQL.h"

#include <sstream>

#include "../../LayerShared/SharedDefinitions.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

string TagFilterPostgreSQL::getSelectionPredicate_()
{	
	stringstream stringStream;
	stringStream << "select	o.id, o.qualified_name, ot.tag_id,  " << getId() << " as filter_id, " << INVALID_VALUE << " as dimension_node_id, ot.upper_left_x, ot.upper_left_y, ot.lower_right_x, ot.lower_right_y " 
	<< "from object o, object_tag ot "	
	<< "where o.id = ot.object_id " 
	<< "and " << getSelectionPostfix_();
	return stringStream.str();
}
//____________________________________________________________________________________________________________________________________________________________________________________

string TagFilterPostgreSQL::getFiltrationPredicate_()
{
	stringstream stringStream;
	stringStream << "select	distinct( ot.object_id ) as id  " 
	<< "from object_tag ot "	
	<< "where " << getSelectionPostfix_();
	return stringStream.str();
}
//____________________________________________________________________________________________________________________________________________________________________________________

string TagFilterPostgreSQL::getSelectionPostfix_()
{
	stringstream stringStream;
	stringStream << "ot.tag_id = " << getTagId();
	return stringStream.str();
}
//____________________________________________________________________________________________________________________________________________________________________________________


#endif