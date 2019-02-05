/*
* Snorri Gíslason - 2018
*/

#ifdef OC_POSTGRESQL

#include "DateRangeFilterPostgreSQL.h"

#include <sstream>

#include "../../LayerShared/SharedDefinitions.h"
#include "../../LayerShared/Exception.h"
#include "../../LayerShared/DateSupport.h"
#include "../../LayerShared/FilterCommon.h"
#include "CommonPostgreSQL.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

string DateRangeFilterPostgreSQL::getSelectionPredicate_()
{
	stringstream stringStream;
	stringStream << "select o.id, o.qualified_name, ot.tag_id, " << getId() << " as filter_id, " << INVALID_VALUE << " as dimension_node_id, ot.upper_left_x, ot.upper_left_y, ot.lower_right_x, ot.lower_right_y " 
	<< "from object o, object_tag ot, date_tag dt "
	<< "where o.id = ot.object_id and dt.id = ot.tag_id and "
	<< getSelectionPostfix_();
	return stringStream.str();
}
//____________________________________________________________________________________________________________________________________________________________________________________

string DateRangeFilterPostgreSQL::getFiltrationPredicate_()
{
	stringstream stringStream;
	stringStream << "select distinct( ot.object_id ) as id " 
	<< "from object_tag ot, date_tag dt "
	<< "where dt.id = ot.tag_id and "
	<< getSelectionPostfix_();
	return stringStream.str();
}
//____________________________________________________________________________________________________________________________________________________________________________________

string DateRangeFilterPostgreSQL::getSelectionPostfix_()
{
	stringstream stringStream;
	
	stringStream << "dt.tag_date between " 
	<< CommonPostgreSQL::dateToSQLString( getYearFrom(), getMonthFrom(), getDayOfMonthFrom() )
	<< " and " 
	<< CommonPostgreSQL::dateToSQLString( getYearTo(), getMonthTo(), getDayOfMonthTo() )
	<< " and dt.tag_set_id = " << getTagSetId();
	return stringStream.str();	
}
//____________________________________________________________________________________________________________________________________________________________________________________


#endif