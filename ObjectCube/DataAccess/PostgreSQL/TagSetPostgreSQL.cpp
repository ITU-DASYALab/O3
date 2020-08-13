/*
* ObjectPostgreSQL.h
* Snorri Gíslason - 2018
*/

#ifdef OC_POSTGRESQL

#include "TagSetPostgreSQL.h"

#include <iostream>
#include <sstream>

#ifdef __APPLE__
#include <memory>
using std::shared_ptr;
#else
#include <memory>
#include <tr1/memory>
using std::shared_ptr;
#endif

#include "CommonPostgreSQL.h"
#include "../Factories/TagDataAccessFactory.h"
#include "../Root/TagDataAccess.h"
#include "../Root/AlphanumericalTagDataAccess.h"
#include "../Root/NumericalTagDataAccess.h"
#include "../Root/TimeTagDataAccess.h"
#include "../Root/RGBTagDataAccess.h"
#include "TimeTagPostgreSQL.h"
#include "../Root/DateTagDataAccess.h"
#include "DateTagPostgreSQL.h"
#include "../../LayerShared/Exception.h"
#include "../../LayerShared/TagCommon.h"

using namespace ObjectCube;
using namespace std;

//____________________________________________________________________________________________________________________________________________________________________________________

TagSetDataAccess* TagSetPostgreSQL::create()
{
	CommonPostgreSQL db;
	stringstream stringStream;
	stringStream << "insert into tag_set ( name, description, type_id, access_id ) values( " << "'" << getName() << "', " << "'" << getDescription() << "', " << getTypeId() << ", " << getAccessId() << ") returning id;";
	string sql = stringStream.str();
	
	setId( db.executeSQLReturningAnInteger( sql ) );
	
	return this;
}
//____________________________________________________________________________________________________________________________________________________________________________________

TagSetDataAccess* TagSetPostgreSQL::fetch( int id )
{
	CommonPostgreSQL db;

	stringstream stringStream;
	stringStream << "select d.name, d.description, d.type_id, d.access_id from tag_set d where d.id = " << id;
	string sql = stringStream.str();

	pqxx::result resultsHandle = db.executeSQL( sql );

	if( resultsHandle.empty() )
	{
		throw Exception("TagSetMonetDB::fetch", "No tag-set retrieved" );
	}

	setId( id );
	setName( resultsHandle[0][0].as<string>() );
	
	if( !resultsHandle[0][1].is_null() )
	{
		setDescription( resultsHandle[0][1].as<string>() );
	}

	setTypeId( resultsHandle[0][2].as<int>() );
	setAccessId( resultsHandle[0][3].as<int>() );
		
	tags_ = fetchTags_();
	return this;
}
//____________________________________________________________________________________________________________________________________________________________________________________

vector<TagDataAccess*> TagSetPostgreSQL::fetchTags_()
{	
	CommonPostgreSQL db;
	/*
	 select t.id, t.tag_set_id, t.type_id, at.tag_string, -1 as number, current_date() as tag_date, current_time() as tag_time
	 from tag t, alphanumerical_tag at where t.id = at.id and t.tag_set_id = 11
	 UNION ALL
	 select t.id, t.tag_set_id, t.type_id, null as tag_string, nt.number, current_date() as tag_date, current_time() as tag_time
	 from tag t, numerical_tag nt where t.id = nt.id and t.tag_set_id = 11
	 UNION ALL
	 select t.id, t.tag_set_id, t.type_id, null as tag_string, -1 as number, dt.tag_date, current_time() as tag_time
	 from tag t, date_tag dt where t.id = dt.id and t.tag_set_id = 11
	 UNION ALL
	 select t.id, t.tag_set_id, t.type_id, null as tag_string, -1 as number, current_date() as tag_date, tt.tag_time
	 from tag t, time_tag tt where t.id = tt.id and t.tag_set_id = 11
	 */	
												
	stringstream stringStream;
	stringStream << " select t.id, t.tag_set_id, t.type_id, at.tag_string, -1 as number, null as tag_date, null as tag_time, cube(array[0,0,0]) as tag_rgb from tag t, alphanumerical_tag at where t.id = at.id and t.tag_set_id = " << id_ << " \
						UNION ALL \
						select t.id, t.tag_set_id, t.type_id, null as tag_string, nt.number, null as tag_date, null as tag_time, cube(array[0,0,0]) as tag_rgb from tag t, numerical_tag nt where t.id = nt.id and t.tag_set_id = " << id_ << " \
						UNION ALL \
						select t.id, t.tag_set_id, t.type_id, null as tag_string, -1 as number, dt.tag_date, null as tag_time, cube(array[0,0,0]) as tag_rgb from tag t, date_tag dt where t.id = dt.id and t.tag_set_id = " << id_ << " \
						UNION ALL \
						select t.id, t.tag_set_id, t.type_id, null as tag_string, -1 as number, null as tag_date, tt.tag_time, cube(array[0,0,0]) as tag_rgb from tag t, time_tag tt where t.id = tt.id and t.tag_set_id = " << id_ << " \
						UNION ALL \
						select t.id, t.tag_set_id, t.type_id, null as tag_string, -1 as number, null as tag_date, null as tag_time, rt.rgb as tag_rgb from tag t, rgb_tag rt where t.id = rt.id and t.tag_set_id = " << id_;
	string sql = stringStream.str();

	pqxx::result resultsHandle = db.executeSQL( sql );
	
	vector<TagDataAccess*> tags;
	
	for(pqxx::result::const_iterator c = resultsHandle.begin(); c != resultsHandle.end(); ++c)
	{
		TagDataAccess* tag = TagDataAccessFactory::create( c[2].as<int>() );
		tag->setId( c[0].as<int>() );
		tag->setTagSetId( c[1].as<int>() );
		
		switch ( tag->getTypeId() ) 
		{
			case TagCommon::ALPHANUMERICAL :
				dynamic_cast<AlphanumericalTagDataAccess*>( tag )->setName( c[3].c_str() );
				break;
			case TagCommon::NUMERICAL :
				dynamic_cast<NumericalTagDataAccess*>( tag )->setNumber( c[4].as<int>() );
				break;
			case TagCommon::DATE :
				DateTagPostgreSQL::sqlDateToTag( dynamic_cast<DateTagDataAccess*>( tag ), c[5].c_str() ); 
				break;
			case TagCommon::TIME :
				TimeTagPostgreSQL::sqlTimeToTag( dynamic_cast<TimeTagDataAccess*>( tag ), c[6].c_str() );
				break;
			case TagCommon::RGB :
				dynamic_cast<RGBTagDataAccess*>( tag )->setName( c[7].c_str() );
				break;
			default:
				throw new Exception( "TagSetPostgreSQL::fetchTags_", "Unknown tag type", tag->getTypeId() );
		}
		tags.push_back( tag );
	}

	return tags;
}
//____________________________________________________________________________________________________________________________________________________________________________________

vector<int> TagSetPostgreSQL::fetchDimensionIds()
{
	CommonPostgreSQL db;

	stringstream stringStream;
	stringStream << "select distinct(d.id) from dimension d where d.tag_set_id = " << getId();
	string sql = stringStream.str();

	pqxx::result resultsHandle = db.executeSQL( sql );
	
	vector<int> dimensionIds;
	for( pqxx::result::const_iterator c = resultsHandle.begin(); c != resultsHandle.end(); ++c )
	{
		dimensionIds.push_back( c[0].as<int>() );
	}

	return dimensionIds;
}
//____________________________________________________________________________________________________________________________________________________________________________________

void TagSetPostgreSQL::erase()
{
	CommonPostgreSQL db;
	db.beginTransaction();
	
	try 
	{
		stringstream stringStream;
		string sql;
		stringStream << "delete from dimension_tag_object where tag_id in (select t.id from tag t where t.tag_set_id =  " << getId() << ")";  
		sql = stringStream.str();
		db.executeSQLNoResults( sql );
		
		stringstream stringStream2;
		string sql2;
		stringStream2 << "delete from object_tag where tag_id in (select t.id from tag t where t.tag_set_id = " << getId() << ")";  
		sql2 = stringStream2.str();
		db.executeSQLNoResults( sql2 );
		
		stringstream stringStream3;
		string sql3;
		stringStream3 << "delete from dimension where tag_set_id = " << getId();  
		sql3 = stringStream3.str();
		db.executeSQLNoResults( sql3 );
		
		stringstream stringStream4;
		string sql4;
		stringStream4 << "delete from alphanumerical_tag where tag_set_id = " << getId();  
		sql4 = stringStream4.str();
		db.executeSQLNoResults( sql4 );
		
		stringstream stringStream5;
		string sql5;
		stringStream5 << "delete from numerical_tag where tag_set_id = " << getId();  
		sql5 = stringStream5.str();
		db.executeSQLNoResults( sql5 );
		
		stringstream stringStream6;
		string sql6;
		stringStream6 << "delete from date_tag where tag_set_id = " << getId();  
		sql6 = stringStream6.str();
		db.executeSQLNoResults( sql6 );
		
		stringstream stringStream7;
		string sql7;
		stringStream7 << "delete from time_tag where tag_set_id = " << getId();  
		sql7 = stringStream7.str();
		db.executeSQLNoResults( sql7 );
		
		stringstream stringStream8;
		string sql8;
		stringStream8 << "delete from tag where tag_set_id = " << getId();  
		sql8 = stringStream8.str();
		db.executeSQLNoResults( sql8 );
		
		stringstream stringStream9;
		string sql9;
		stringStream9 << "delete from tag_set where id = " << getId();  
		sql9 = stringStream9.str();
		db.executeSQLNoResults( sql9 );
	
		db.commitTransaction();
	}
	catch( ... ) 
	{
		db.rollbackTransaction();
		throw;
	}
	
}
//____________________________________________________________________________________________________________________________________________________________________________________


#endif