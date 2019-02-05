/*
* Snorri Gíslason - 2018
*/


#ifdef OC_POSTGRESQL

#include "NumericalRangeFilterPostgreSQL.h"

#include <sstream>

#include "../../LayerShared/SharedDefinitions.h"

using namespace ObjectCube;


//____________________________________________________________________________________________________________________________________________________________________________________

string NumericalRangeFilterPostgreSQL::getSelectionPredicate_()
{	
	stringstream stringStream;
	stringStream << "select o.id, o.qualified_name, ot.tag_id, " << getId() << " as filter_id, " << INVALID_VALUE << " as dimension_node_id, ot.upper_left_x, ot.upper_left_y, ot.lower_right_x, ot.lower_right_y " 
	<< "from object o, object_tag ot, numerical_tag nt where o.id = ot.object_id and  ot.tag_id = nt.id and "
	<< getSelectionPostfix_();
	
	return stringStream.str();
}
//____________________________________________________________________________________________________________________________________________________________________________________

string NumericalRangeFilterPostgreSQL::getFiltrationPredicate_()
{
	stringstream stringStream;
	stringStream << " select distinct( ot.object_id ) as id from object_tag ot, numerical_tag nt where ot.tag_id = nt.id and " << getSelectionPostfix_();
	
	return stringStream.str();
}
//____________________________________________________________________________________________________________________________________________________________________________________

string NumericalRangeFilterPostgreSQL::getSelectionPostfix_()
{
	stringstream stringStream;
	stringStream << "nt.number between " << getNumberFrom() << " and " << getNumberTo() << " and nt.tag_set_id = " << getTagSetId();
	return stringStream.str();
}
//____________________________________________________________________________________________________________________________________________________________________________________


#endif