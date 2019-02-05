/*
* Snorri Gíslason - 2018
*/

#ifdef OC_POSTGRESQL

#include "DimensionFilterPostgreSQL.h"

#include <sstream>

#include "../../LayerShared/SharedDefinitions.h"
#include "../../LayerShared/Parameters.h"
#include "../../LayerShared/DimensionCommon.h"

using namespace ObjectCube;

//____________________________________________________________________________________________________________________________________________________________________________________

string DimensionFilterPostgreSQL::dimensionFilterVersion2Parameter_ = "DimensionFilterV2";

//____________________________________________________________________________________________________________________________________________________________________________________

string DimensionFilterPostgreSQL::getSelectionPredicate_()
{	
	if( Parameters::getParameters()->contains( dimensionFilterVersion2Parameter_ ) && getDimensionTypeId() != DimensionCommon::VIRTUAL ) //We have no Materialized Views for virtual hierarchies
	{
		return getSelectionPredicateMV_();
	}
	return getSelectionPredicateUnions_();

}
//____________________________________________________________________________________________________________________________________________________________________________________

string DimensionFilterPostgreSQL::getSelectionPredicateUnions_()
{
	stringstream stringStream;
	for( map<int, int>::const_iterator itr = tagAndDimensionNodeIds_.begin(); itr != tagAndDimensionNodeIds_.end(); ++itr )
	{
		if( itr != tagAndDimensionNodeIds_.begin() )
		{
			stringStream << "\nUNION ALL\n";
		}
		stringStream << "select o.id, o.qualified_name, ot.tag_id, " << getId() << " as filter_id, " << (*itr).second << " as dimension_node_id, ot.upper_left_x, ot.upper_left_y, ot.lower_right_x, ot.lower_right_y "
		<< " from object o, object_tag ot "
		<< "where o.id = ot.object_id and ot.tag_id = " << (*itr).first;
	}
	
	if( tagAndDimensionNodeIds_.size() == 0 ) 
	{
		stringStream << "select o.id, o.qualified_name, ot.tag_id, " << INVALID_VALUE << " as filter_id, " << INVALID_VALUE << " as dimension_node_id, ot.upper_left_x, ot.upper_left_y, ot.lower_right_x, ot.lower_right_y "
		<< " from object o, object_tag ot "
		<< " where o.id = ot.object_id and 0=1";
	}
	return stringStream.str();
}
//____________________________________________________________________________________________________________________________________________________________________________________

string DimensionFilterPostgreSQL::getSelectionPredicateMV_()
{
	stringstream stringStream;
	stringStream << "select o.id, o.qualified_name, dto.tag_id, " << getId() << " as filter_id, dto.node_id as dimension_node_id, dto.upper_left_x, dto.upper_left_y, dto.lower_right_x, dto.lower_right_y "
	<< "from object o, dimension_tag_object dto "
	<< "where o.id = dto.object_id and dto.dimension_id = " << getDimensionId() 
	<< " and dto.left_border >= " << getLeftBorder() << " and dto.right_border <= " << getRightBorder();
	return stringStream.str();
}
//____________________________________________________________________________________________________________________________________________________________________________________

string DimensionFilterPostgreSQL::getFiltrationPredicate_()
{	
	
	if( Parameters::getParameters()->contains( dimensionFilterVersion2Parameter_ )  && getDimensionTypeId() != DimensionCommon::VIRTUAL )
	{
		return getFiltrationPredicateMV_();
	}
	return getFiltrationPredicateIn_();	
}
//____________________________________________________________________________________________________________________________________________________________________________________

string DimensionFilterPostgreSQL::getFiltrationPredicateIn_()
{
	stringstream stringStream;
	stringStream << "select distinct( ot.object_id ) as id from object_tag ot where ot.tag_id in( ";
	
	for( map<int, int>::const_iterator itr = tagAndDimensionNodeIds_.begin(); itr != tagAndDimensionNodeIds_.end(); ++itr )
	{
		if( itr != tagAndDimensionNodeIds_.begin() )
		{
			stringStream << ", ";
		}
		stringStream << (*itr).first;
	}
	
	if( tagAndDimensionNodeIds_.size() == 0 ) 
	{
		stringStream << INVALID_VALUE;
	}
	
	stringStream << " )";	
	return stringStream.str();	
}
//____________________________________________________________________________________________________________________________________________________________________________________

string DimensionFilterPostgreSQL::getFiltrationPredicateMV_()
{

	stringstream stringStream;
	stringStream << "select distinct( dto.object_id ) as id "
	<< "from dimension_tag_object dto "
	<< "where dto.dimension_id = " << getDimensionId() << " and dto.left_border >= " << getLeftBorder() << " and dto.right_border <= " << getRightBorder();
	return stringStream.str();
}
//____________________________________________________________________________________________________________________________________________________________________________________

#endif