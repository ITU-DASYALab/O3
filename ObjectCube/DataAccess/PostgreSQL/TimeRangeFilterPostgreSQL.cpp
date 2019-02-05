/*
* Snorri Gíslason - 2018
*/

#ifdef OC_POSTGRESQL

#include "TimeRangeFilterPostgreSQL.h"

#include <sstream>

#include "../../LayerShared/SharedDefinitions.h"
#include "../../LayerShared/Exception.h"
#include "CommonPostgreSQL.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

string TimeRangeFilterPostgreSQL::getSelectionPredicate_()
{
	stringstream stringStream;	
	stringStream << "select o.id, o.qualified_name, ot.tag_id, " << getId() << " as filter_id, " << INVALID_VALUE << " as dimension_node_id, ot.upper_left_x, ot.upper_left_y, ot.lower_right_x, ot.lower_right_y " 
	<< "from object o, object_tag ot, time_tag tt "
	<< "where o.id = ot.object_id and tt.id = ot.tag_id and "
	<< getSelectionPostfix_();
	return stringStream.str();
}
//____________________________________________________________________________________________________________________________________________________________________________________

string TimeRangeFilterPostgreSQL::getFiltrationPredicate_()
{
	stringstream stringStream;
	stringStream << "select distinct( ot.object_id ) as id " 
	<< "from object_tag ot, time_tag tt "
	<< "where tt.id = ot.tag_id and "
	<< getSelectionPostfix_();
	return stringStream.str();
}
//____________________________________________________________________________________________________________________________________________________________________________________

string TimeRangeFilterPostgreSQL::getSelectionPostfix_()
{
	stringstream stringStream;
	stringStream << "tt.tag_time between " 
	<< CommonPostgreSQL::timeToSQLString( getHoursFrom(), getMinutesFrom(), getSecondsFrom(), getMillisecondsFrom() )
	<< " and " 
	<< CommonPostgreSQL::timeToSQLString( getHoursTo(), getMinutesTo(), getSecondsTo(), getMillisecondsTo() )
	<< " and tt.tag_set_id = " << getTagSetId();
	
	return stringStream.str();
}
//____________________________________________________________________________________________________________________________________________________________________________________


#endif