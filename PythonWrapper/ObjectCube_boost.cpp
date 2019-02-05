#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#include <boost/python.hpp>
#include <boost/python/suite/indexing/vector_indexing_suite.hpp>

#include <algorithm>


#include "../ObjectCube/Tag/Tag.h"
#include "../ObjectCube/Tag/AlphanumericalTag.h"
#include "../ObjectCube/Tag/NumericalTag.h"
#include "../ObjectCube/Tag/TimeTag.h"
#include "../ObjectCube/Tag/DateTag.h"
#include "../ObjectCube/Tag/RGBTag.h"

#include "../ObjectCube/Object.h"
#include "../ObjectCube/ObjectTag.h"

#include "../ObjectCube/Hierarchy/HierarchyNode.h"
#include "../ObjectCube/Hierarchy/Dimension.h"
#include "../ObjectCube/Hierarchy/PersistentDimension.h"
#include "../ObjectCube/Hierarchy/PersistentHierarchyNode.h"
#include "../ObjectCube/Hierarchy/VirtualDimension.h"
#include "../ObjectCube/Hierarchy/VirtualHierarchyNode.h"
#include "../ObjectCube/Hierarchy/DefaultDimension.h"
#include "../ObjectCube/Hierarchy/DefaultHierarchyNode.h"

#include "../ObjectCube/Filters/Filter.h"
#include "../ObjectCube/Filters/TagFilter.h"
#include "../ObjectCube/Filters/NumericalRangeFilter.h"
#include "../ObjectCube/Filters/TimeRangeFilter.h"
#include "../ObjectCube/Filters/DateRangeFilter.h"
#include "../ObjectCube/Filters/DimensionFilter.h"

#include "../ObjectCube/TagSet/TagSet.h"
#include "../ObjectCube/TagSet/AlphanumericalTagSet.h"
#include "../ObjectCube/TagSet/NumericalTagSet.h"
#include "../ObjectCube/TagSet/DateTagSet.h"
#include "../ObjectCube/TagSet/TimeTagSet.h"
#include "../ObjectCube/TagSet/RGBTagSet.h"

#include "../ObjectCube/State/State.h"
#include "../ObjectCube/State/StateTag.h"
#include "../ObjectCube/State/StateObject.h"
#include "../ObjectCube/State/StateDimension.h"
#include "../ObjectCube/State/StateDimensionNode.h"
#include "../ObjectCube/State/Cell.h"
#include "../ObjectCube/State/MultiDimensionalView.h"

#include "../ObjectCube/Hub.h"
#include "../ObjectCube/Language.h"
#include "../ObjectCube/LayerShared/Parameters.h"

#include "../ObjectCube/Boundaries/Coordinate2D.h"
#include "../ObjectCube/Boundaries/BoundingBox.h"


using namespace std;
using namespace ObjectCube;
using namespace boost::python;
//___________________________________________________________________________________________________________________________________________________________________________________


//BOOST_PYTHON_MEMBER_FUNCTION_OVERLOADS( tag_id, Tag::id, 0, 1)

/*
class DimensionWrap : public Dimension, public wrapper<Dimension>
{
public:
    	
	Tag addTag( Tag tag)
    {
        if (override addTag = this->get_override("addTag"))
            return addTag( tag ); // *note*
        return Dimension::addTag( tag );
    }
	
    Tag default_addTag( Tag tag) { return this->Dimension::addTag( tag ); }
	
};
*/
//.def("create", make_function( &Tag::create, return_value_policy<default_call_policies>(),  boost::mpl::vector<void, string>() ) );

/*
 Return value policies
 
 * reference_existing_object: naive (dangerous) approach
 * copy_const_reference: Boost.Python v1 approach
 * copy_non_const_reference:
 * manage_new_object: Adopt a pointer and hold the instance
 
 */

//C++ code


// This STL Container wrapping code originates from: http://wiki.python.org/moin/boost.python/StlContainers
//It has been modified from the original
template<class T>
struct std_item
{
    typedef typename T::value_type V;  //Added typename for gcc compatability
	typedef typename T::const_iterator Itr; 
   
	static V get( T const& x, int i )
    {
        if( i < 0 ) 
		{
			i += x.size();
		}
        if( i >= 0 && i < x.size() ) 
		{
			return x[i];
		}
        IndexError();
		//throw PyExc_IndexError;
    }
    
	static void set( T& x, int i, V const v )
    {
        if( i < 0 ) 
		{
			i += x.size();
		}
        if( i >= 0 && i < x.size() ) 
		{
			x[i] = v;
			return;
		}
		IndexError();
	//	throw PyExc_IndexError;
    }
    
	static void del( T& x, int i )
    {
        if( i < 0 ) 
		{
			i += x.size();
		}
        if( i >= 0 && i< x.size() ) 
		{
			x.erase( x.begin() + i );
			return;
		}
		IndexError();
		//throw PyExc_IndexError;
    }
    
	static void add( T& x, V const v )
    {
        x.push_back( v );
    }
	
	static bool in( T const& x, V const v )
	{
		return count( x.begin(), x.end(), v ) > 0;
	}
	
	static int index( T const& x, V const v )
	{
		int i = 0;
		for( Itr it = x.begin(); it != x.end(); ++it, ++i )
		{
			if( *it == v ) 
			{
				return i;
			}
		}
		return -1;
	}
	
	static void IndexError() 
	{ 
		PyErr_SetString( PyExc_IndexError, "Index out of range" ); 
	}
};

// This STL Container wrapping code originates from: http://wiki.python.org/moin/boost.python/StlContainers
//It has been modified from the original
template<class T>
struct map_item
{
    typedef typename T::key_type K;
    typedef typename T::mapped_type V;
	typedef typename T::const_iterator Itr;
    
	static V get( T const& x, K const& i )
    {
		Itr it = x.find( i );
        if( it != x.end() ) 
		{
			return  it->second;
		}
        KeyError();
	//	throw PyExc_LookupError;
    }
	
    static void set( T& x, K const& i, V const& v )
    {
        x[i] = v; // use map autocreation feature
    }
	
    static void del( T& x, K const& i )
    {
        if( x.find( i ) != x.end() )
		{
			x.erase(i);
		}
		KeyError();
		//throw PyExc_LookupError;
    }
	
	static bool in( T const& x, K const& i )
	{
        return x.find( i ) != x.end();
	}
	
	static boost::python::list keys( T const& x )
	{
        boost::python::list t;
        for( Itr it = x.begin(); it != x.end(); ++it )
		{
			t.append( it->first );
		}
        return t;
	}
	
	static boost::python::list values( T const& x )
	{
        boost::python::list t;
        for( Itr it = x.begin(); it != x.end(); ++it )
		{
			t.append( it->second );
		}
        return t;
	}
	
	static boost::python::list items( T const& x )
	{
        boost::python::list t;
        for( Itr it = x.begin(); it != x.end(); ++it )
		{
			t.append( make_tuple( it->first, it->second ) );
		}
        return t;
	}
	
	static int index( T const& x, K const& k )
	{
        int i=0;
        for( Itr it = x.begin(); it != x.end(); ++it, ++i )
		{
			if( it->first == k )
			{
				return i;
			}
		}
        return -1;
	}
	
	static void KeyError() 
	{	
		PyErr_SetString( PyExc_LookupError, "Key supplied was not found in the map!" ); 
	}
};



//End of STL Container wrapping code


BOOST_PYTHON_MODULE(ObjectCubePython)
{
	
//==================================================================================================================================================
	
	//															Tag
	
	//Overload support
	const string (Tag::*tag_type_as_string_no_params)() const = &Tag::typeAsString;
	const string (*tag_type_as_string_id)(int) = &Tag::typeAsString;
	{
		scope in_Tag = 
		class_<Tag, boost::noncopyable>("Tag", no_init)
			
			.def( "valueAsString", &Tag::valueAsString )
			.def( "inUse", &Tag::inUse )
			.def( "typeAsString", tag_type_as_string_no_params )
			.def( "typeAsStringStatic", tag_type_as_string_id ) //Due to limitation in boost python we can't declare static with but name 
			.staticmethod( "typeAsStringStatic" )
	
			.add_property( "id", &Tag::getId )
			.add_property( "typeId", &Tag::getTypeId )
			.add_property( "tagSetId", &Tag::getTagSetId )
		;
	
		//Tag enums
		enum_<Tag::TYPE>("TYPE")
			.value("ALPHANUMERICAL", Tag::ALPHANUMERICAL)
			.value("NUMERICAL", Tag::NUMERICAL)
			.value("DATE", Tag::DATE)
			.value("TIME", Tag::TIME)
			.value("TIME", Tag::RGB)
		;
	}
	
	
	//															AlphanumericalTag
	
	//Overload support
	AlphanumericalTag* (*alphanumerical_tag_fetch_id)(int) = &AlphanumericalTag::fetch;
	AlphanumericalTag* (*alphanumerical_tag_fetch_tag_set_id_and_name)( int, const string& ) = &AlphanumericalTag::fetch;
	
	class_<AlphanumericalTag, bases<Tag> >("AlphanumericalTag")
		.def( init<string>() )
	
		.def( "fetch", alphanumerical_tag_fetch_id, return_value_policy<manage_new_object>() )  
		.def( "fetch", alphanumerical_tag_fetch_tag_set_id_and_name, return_value_policy<manage_new_object>() )  
		.staticmethod( "fetch" )
	
		.add_property( "name", &AlphanumericalTag::getName, &AlphanumericalTag::setName )
	;
	
	
	//															NumericalTag
	
	//Overload support
	NumericalTag* (*numerical_tag_fetch_id)(int) = &NumericalTag::fetch;
	NumericalTag* (*numerical_tag_fetch_tag_set_id_and_number)(int, long) = &NumericalTag::fetch; 
	
	class_<NumericalTag, bases<Tag> >("NumericalTag")
		.def( init<long>() )
	
		.def( "fetch", numerical_tag_fetch_id, return_value_policy<manage_new_object>() )
		.def( "fetch", numerical_tag_fetch_tag_set_id_and_number, return_value_policy<manage_new_object>() )
		.staticmethod( "fetch" )
	
		.add_property( "number", &NumericalTag::getNumber, &NumericalTag::setNumber )
		.add_property( "isNull", &NumericalTag::isNull )
	;
	
	
	//															TimeTag
	
	//Overload support
	TimeTag* (*time_tag_fetch_id)(int) = &TimeTag::fetch;
	TimeTag* (*time_tag_fetch_tag_set_id_and_time)(int, int, int, int, int) = &TimeTag::fetch; 
	
	class_<TimeTag, bases<Tag> >("TimeTag")
	.def( init<int, int, int, int>() )
	
	.def( "fetch", time_tag_fetch_id, return_value_policy<manage_new_object>() )
	.def( "fetch", time_tag_fetch_tag_set_id_and_time, return_value_policy<manage_new_object>() )
	.staticmethod( "fetch" )
	
	.add_property( "hours", &TimeTag::getHours, &TimeTag::setHours )
	.add_property( "minutes", &TimeTag::getMinutes, &TimeTag::setMinutes )
	.add_property( "seconds", &TimeTag::getSeconds, &TimeTag::setSeconds )
	.add_property( "milliseconds", &TimeTag::getMilliseconds, &TimeTag::setMilliseconds )
	
	.add_property( "isNull", &NumericalTag::isNull )
	;
	
	
	//															DateTag
	
	//Overload support
	DateTag* (*date_tag_fetch_id)(int) = &DateTag::fetch;
	DateTag* (*date_tag_fetch_tag_set_id_and_date)(int, int, int, int) = &DateTag::fetch; 
	
	class_<DateTag, bases<Tag> >("DateTag")
	.def( init<int, int, int>() )
	
	.def( "fetch", date_tag_fetch_id, return_value_policy<manage_new_object>() )
	.def( "fetch", date_tag_fetch_tag_set_id_and_date, return_value_policy<manage_new_object>() )
	.staticmethod( "fetch" )
	
	.add_property( "year", &DateTag::getYear, &DateTag::setYear )
	.add_property( "month", &DateTag::getMonth, &DateTag::setMonth )
	.add_property( "dayOfMonth", &DateTag::getDayOfMonth, &DateTag::setDayOfMonth )
	
	.add_property( "isNull", &NumericalTag::isNull )
	;
	
	//															RGBTag
	
	//Overload support
	RGBTag* (*RGB_tag_fetch_id)(int) = &RGBTag::fetch;
	RGBTag* (*RGB_tag_fetch_tag_set_id_and_name)( int, const string& ) = &RGBTag::fetch;
	
	class_<RGBTag, bases<Tag> >("RGBTag")
		.def( init<string>() )
	
		.def( "fetch", RGB_tag_fetch_id, return_value_policy<manage_new_object>() )  
		.def( "fetch", RGB_tag_fetch_tag_set_id_and_name, return_value_policy<manage_new_object>() )  
		.staticmethod( "fetch" )
	
		.add_property( "name", &RGBTag::getName, &RGBTag::setName )
	;
	
//==================================================================================================================================================	
	
	//															Coordinate2D
	
	class_<Coordinate2D>("Coordinate2D")
		.def( init<int, int>() )
	
		.add_property( "X", &Coordinate2D::getX, &Coordinate2D::setX )
		.add_property( "Y", &Coordinate2D::getY, &Coordinate2D::setY )
	;
	
	
//==================================================================================================================================================	
	
	//															BoundingBox
	
	class_<BoundingBox>("BoundingBox")
		.def( init<Coordinate2D, Coordinate2D>() )
	
		.def( "setUpperLeftCorner", &BoundingBox::setUpperLeftCorner )
		.def( "setLowerRightCorner", &BoundingBox::setLowerRightCorner )
		.def( "getUpperLeftCorner", &BoundingBox::getUpperLeftCorner )
		.def( "getLowerRightCorner", &BoundingBox::getLowerRightCorner )
		//.add_property( "UpperLeftCorner", &BoundingBox::getUpperLeftCorner, &BoundingBox::setUpperLeftCorner )
		//.add_property( "LowerRightCorner", &BoundingBox::getLowerRightCorner, &BoundingBox::setLowerRightCorner )
	
	;
	
//==================================================================================================================================================	
	
	//															ObjectTag
	
	class_<ObjectTag>("ObjectTag", init<Tag*>() )
	.def( init<const Tag*>() )
	.def( init<Tag*, BoundingBox>() )
	.def( init<const Tag*, BoundingBox>() )
	
	.def( "getTag", &ObjectTag::getTag, return_value_policy<reference_existing_object>() )
	.def( "getBoundingBox", &ObjectTag::getBoundingBox )
	.def( "getConfirmed", &ObjectTag::getConfirmed )
	.def( "setBoundingBox", &ObjectTag::setBoundingBox )
	.def( "setConfirmed", &ObjectTag::setConfirmed )
	
	.def( "confirmTagging", &ObjectTag::confirmTagging )
	
	;
	
//==================================================================================================================================================
	
	//															Object
	
	//Overload support
	Object& (Object::*create_no_arg)() = &Object::create;
	Object& (Object::*create_string)(const string&) = &Object::create;
	
	Object (*fetch_id)(int) = &Object::fetch;
	Object (*fetch_qualified_name)(const string&) = &Object::fetch;
	
	class_<Object>("Object")
	.def( init<const string&>() )
	
	.def( "create", create_no_arg, return_value_policy<reference_existing_object>() )
	.def( "create", create_string, return_value_policy<reference_existing_object>() )
	
	.def( "fetch", fetch_id )
	.def( "fetch", fetch_qualified_name )
	.staticmethod( "fetch" )
	
	.def( "update", &Object::update )
	.def( "erase", &Object::erase )
	
	.def( "addTag", &Object::addTag )
	.def( "removeTag", &Object::removeTag )
	.def( "hasUserTags", &Object::hasUserTags )
	.def( "hasTag", &Object::hasTag ) 
	.def( "getTag", &Object::getTag )
	.def( "getTags", &Object::getTags )
	
	.add_property( "name", &Object::getName, &Object::setName )
	.add_property( "thumbnail", &Object::getThumbnail, &Object::setThumbnail )
	.add_property( "fileType", &Object::getFileType, &Object::setFileType )
	.add_property( "id", &Object::getId )
	;
	
	
//==================================================================================================================================================	
	
	//															HierarchyNode
	
	//Overload support
	HierarchyNode* (HierarchyNode::*hierarchy_node_get_branch_id)( int ) = &HierarchyNode::getBranch;
	{
		scope in_HierarchyNode = 
		class_<HierarchyNode, boost::noncopyable>("HierarchyNode", no_init)
			.def( "getBranch", hierarchy_node_get_branch_id, return_value_policy<reference_existing_object>() )
			.def( "getBranches", &HierarchyNode::getBranches )
		
			.add_property( "id", &HierarchyNode::getId )
			.add_property( "tagSetId", &HierarchyNode::getTagSetId )
			.add_property( "dimensionId", &HierarchyNode::getDimensionId )
			.add_property( "leftBorder", &HierarchyNode::getLeftBorder )
			.add_property( "rightBorder", &HierarchyNode::getRightBorder )
			.add_property( "name", &HierarchyNode::getName )
			.add_property( "childCategoryTitle", &HierarchyNode::getChildCategoryTitle )
			.add_property( "typeId", &HierarchyNode::getTypeId )
		;
		
		enum_<HierarchyNode::STATUS>("STATUS")
			.value( "INVALID", HierarchyNode::INVALID )
		;
		
		enum_<HierarchyNode::TYPE>("TYPE")
			.value( "PERSISTENT", HierarchyNode::PERSISTENT )
			.value( "VIRTUAL", HierarchyNode::VIRTUAL )
		;
	}
	
	
	//															Dimension	
	
	//Overload support
	HierarchyNode* (Dimension::*dimension_get_root_not_const)() = &Dimension::getRoot;
	
	{
		scope in_Dimension = 
		class_<Dimension, boost::noncopyable>("Dimension", no_init)
			//.def( "getNode", &Dimension::getNode, return_value_policy<reference_existing_object>() )
			.def( "getRoot", dimension_get_root_not_const, return_value_policy<reference_existing_object>() )
		
			.add_property( "id", &Dimension::getId )
			.add_property( "typeId", &Dimension::getTypeId )
			.add_property( "tagSetId", &Dimension::getTagSetId )
		;
		
		enum_<Dimension::TYPE>("TYPE")
			.value( "PERSISTENT", Dimension::PERSISTENT )
			.value( "VIRTUAL", Dimension::VIRTUAL )
		;
	}
	
	
	//															TagBasedHierarchyNode
	
	class_<TagBasedHierarchyNode, bases<HierarchyNode>, boost::noncopyable >("TagBasedHierarchyNode", no_init )
		
		.add_property( "tagId", &TagBasedHierarchyNode::getTagId )
	;
	
	
	//															PersistentHierarchyNode	
	
	class_<PersistentHierarchyNode, bases<TagBasedHierarchyNode> >("PersistentHierarchyNode")
		.def( init<const Tag* const>() )
		.def( init<const Tag* const, int, int>() )
		.def( init<const Tag* const, int, int, const string&>() )
	;
	

	//															PersistentDimension
	
	//Overload support
	PersistentHierarchyNode* (PersistentDimension::*persistent_dimension_add_node)(int, const Tag* const) = &PersistentDimension::addNode;
	PersistentHierarchyNode* (PersistentDimension::*persistent_dimension_add_node_child_category_title)(int, const Tag* const, const string&) = &PersistentDimension::addNode;
	PersistentHierarchyNode* (PersistentDimension::*persistent_dimension_get_root)() = &PersistentDimension::getPersistentRoot;
	
	class_<PersistentDimension, bases<Dimension> >("PersistentDimension")
		.def( init<int, const Tag* const>() )
		.def( init<int, const Tag* const, const string&>() )
	
		.def( "addNode", persistent_dimension_add_node, return_value_policy<reference_existing_object>() )
		.def( "addNode", persistent_dimension_add_node_child_category_title, return_value_policy<reference_existing_object>() )
		.def( "removeBranch", &PersistentDimension::removeBranch )
		.def( "getNode", &PersistentDimension::getNode, return_value_policy<reference_existing_object>() )
		.def( "getRoot", persistent_dimension_get_root, return_value_policy<reference_existing_object>() )
	;
	
	
	//															VirtualHierarchyNode
	
	class_<VirtualHierarchyNode, bases<HierarchyNode> >("VirtualHierarchyNode")
		.def( init<int, const string&, int, int, const string&, const string&>() )
		.def( init<int, const string&, int, int, const string&, const string&, const string&>() )
	//The function pointer constructor is not exposed
	;
	
	
	//															VirtualDimension
	
	//Overload support
	VirtualHierarchyNode* (VirtualDimension::*virtual_dimension_add_node)( int, const string& ) = &VirtualDimension::addNode;
	VirtualHierarchyNode* (VirtualDimension::*virtual_dimension_add_node_child_category_title)( int, const string&, const string& ) = &VirtualDimension::addNode;
	VirtualHierarchyNode* (VirtualDimension::*virtual_dimension_get_virtual_root)() = &VirtualDimension::getVirtualRoot;
	{
		scope in_VirtualDimension =
		class_<VirtualDimension, bases<Dimension> >("VirtualDimension", init<int, const string&, const string&, const string&>() )
			.def( init<int, const string&, const string&, const string&, const string&>() )
	
			.def( "addNode", virtual_dimension_add_node, return_value_policy<reference_existing_object>() )
			.def( "addNode", virtual_dimension_add_node_child_category_title, return_value_policy<reference_existing_object>() )
			.def( "getVirtualRoot", virtual_dimension_get_virtual_root, return_value_policy<reference_existing_object>() )
		
			.add_property( "outerAttributePattern", &VirtualDimension::getOuterAttributePattern )
			.add_property( "innerAttributePattern", &VirtualDimension::getInnerAttributePattern )
			.add_property( "type", &VirtualDimension::getType )
		;
			
		enum_<VirtualDimension::TYPE>("TYPE")
			.value( "PATTERN_MATCHING", VirtualDimension::PATTERN_MATCHING )
			.value( "EXTRACTION_FUNCTION", VirtualDimension::EXTRACTION_FUNCTION )
		;
	}
	
	
	//															DefaultHierarchyNode
	
	class_<DefaultHierarchyNode, bases<TagBasedHierarchyNode> >("DefaultHierarchyNode")
		.def( init<const Tag* const>() )
		.def( init<const Tag* const, int, int>() )
		.def( init<const Tag* const, int, int, const string&>() )
	;
	
	
	//															DefaultDimension
	
	//Overload support
	DefaultHierarchyNode* (DefaultDimension::*default_dimension_get_default_root)() = &DefaultDimension::getDefaultRoot;
	
	class_<DefaultDimension, bases<Dimension> >("DefaultDimension")
		.def( init<int, const vector<Tag*>&>() )
		.def( "getNode", &DefaultDimension::getNode, return_value_policy<reference_existing_object>() )
		.def( "getDefaultRoot", default_dimension_get_default_root, return_value_policy<reference_existing_object>() )
		.def( "getRootName", &DefaultDimension::getRootName )
		.staticmethod( "getRootName" )
	;
	
//==================================================================================================================================================
	
	//															Filter
	
	//Overload support
	const string (Filter::*filter_type_as_string_no_params)() const = &Filter::typeAsString;
	const string (*filter_type_as_string_id)( int ) = &Filter::typeAsString;
	{
		scope in_Filter = 
		class_<Filter, boost::noncopyable>("Filter", no_init)
		
			.def( "typeAsString", filter_type_as_string_no_params )
			.def( "typeAsStringStatic", filter_type_as_string_id )
			.staticmethod( "typeAsStringStatic" )
		
			.add_property( "id", &Filter::getId )
			.add_property( "typeId", &Filter::getTypeId )
			.add_property( "tagSetId", &Filter::getTagSetId )
			.add_property( "isNull", &Filter::isNull )
		;
		
		//Tag enums
		enum_<Filter::TYPE>("TYPE")
			.value("TAG_FILTER", Filter::TAG_FILTER )
			.value("DIMENSION_FILTER", Filter::DIMENSION_FILTER )
			.value("NUMERICAL_RANGE_FILTER", Filter::NUMERICAL_RANGE_FILTER )
			.value("TIME_RANGE_FILTER", Filter::TIME_RANGE_FILTER )
			.value("DATE_RANGE_FILTER", Filter::DATE_RANGE_FILTER )
		;
	}
	
	
	//															TagFilter

	class_<TagFilter, bases<Filter> >("TagFilter", init<const Tag* const, int>() )
		.add_property( "tagId", &TagFilter::getTagId )
	;

	
	//															DimensionFilter
	
	class_<DimensionFilter, bases<Filter> >("DimensionFilter", init<const HierarchyNode&, int>() )
		.add_property( "dimensionId", &DimensionFilter::getDimensionId )
	;
	
	
	//															NumericalRangeFilter
	
	class_<NumericalRangeFilter, bases<Filter> >("NumericalRangeFilter", init<long, long, int>() )
		.add_property("numberFrom", &NumericalRangeFilter::getNumberFrom)
		.add_property("numberTo", &NumericalRangeFilter::getNumberTo)
	;
	
			
	//															TimeRangeFilter

	class_<TimeRangeFilter, bases<Filter> >("TimeRangeFilter", init<int>() )
		.def( init<int, int, int>() )
		
		.add_property("hoursFrom", &TimeRangeFilter::getHoursFrom, &TimeRangeFilter::setHoursFrom )
		.add_property("minutesFrom", &TimeRangeFilter::getMinutesFrom, &TimeRangeFilter::setMinutesFrom )
		.add_property("secondsFrom", &TimeRangeFilter::getSecondsFrom, &TimeRangeFilter::setSecondsFrom )
		.add_property("millisecondsFrom", &TimeRangeFilter::getMillisecondsFrom, &TimeRangeFilter::setMillisecondsFrom )
	
		.add_property("hoursTo", &TimeRangeFilter::getHoursTo, &TimeRangeFilter::setHoursTo )
		.add_property("minutesTo", &TimeRangeFilter::getMinutesTo, &TimeRangeFilter::setMinutesTo )
		.add_property("secondsTo", &TimeRangeFilter::getSecondsTo, &TimeRangeFilter::setSecondsTo )
		.add_property("millisecondsTo", &TimeRangeFilter::getMillisecondsTo, &TimeRangeFilter::setMillisecondsTo )
	;
	
	
	//															DateRangeFilter
	
	class_<DateRangeFilter, bases<Filter> >("DateRangeFilter", init<int>() )
		.def( init<int, int>() )
		.def( init<int, int, int>() )
		.def( init<int, int, int, int, int>() )
		.def( init<int, int, int, int, int, int, int>() )

		.add_property("yearFrom", &DateRangeFilter::getYearFrom, &DateRangeFilter::setYearFrom )
		.add_property("monthFrom", &DateRangeFilter::getMonthFrom, &DateRangeFilter::setMonthFrom )
		.add_property("dayOfMonthFrom", &DateRangeFilter::getDayOfMonthFrom, &DateRangeFilter::setDayOfMonthFrom )
	
		.add_property("yearTo", &DateRangeFilter::getYearTo, &DateRangeFilter::setYearTo )
		.add_property("monthTo", &DateRangeFilter::getMonthTo, &DateRangeFilter::setMonthTo )
		.add_property("dayOfMonthTo", &DateRangeFilter::getDayOfMonthTo, &DateRangeFilter::setDayOfMonthTo )
	;
	
	
//==================================================================================================================================================
	
	//															TagSet

	//Overload support
	const vector<Tag*> (TagSet::*tag_set_get_tags_no_params)() const = &TagSet::getTags;
	const vector<Tag*> (TagSet::*tag_set_get_tags_tag_ids)( const vector<int>& ) const = &TagSet::getTags;
	
	PersistentDimension* (TagSet::*tag_set_get_persistent_dimension_id)( int ) = &TagSet::getPersistentDimension;
	PersistentDimension* (TagSet::*tag_set_get_persistent_dimension_name)( const string& ) = &TagSet::getPersistentDimension;
	
	const VirtualDimension* (TagSet::*tag_set_get_virtual_dimension_id)( int ) const = &TagSet::getVirtualDimension;
	const VirtualDimension* (TagSet::*tag_set_get_virtual_dimension_name)( const string&  ) const = &TagSet::getVirtualDimension;
	
	Dimension* (TagSet::*tag_set_get_dimension_id)( int ) = &TagSet::getDimension;
	Dimension* (TagSet::*tag_set_get_dimension_name)( const string& ) = &TagSet::getDimension;
	
	const string (TagSet::*tag_set_type_as_string_no_params)() const = &TagSet::typeAsString;
	const string (*tag_set_type_as_string_id)( int ) = &TagSet::typeAsString;
	
	const string (TagSet::*tag_set_access_type_as_string_no_params)() const = &TagSet::accessTypeAsString;
	const string (*tag_set_access_type_as_string_id)( int ) = &TagSet::accessTypeAsString; //Static
	
	{
		scope in_TagSet =
		class_<TagSet, boost::noncopyable>("TagSet", no_init)
			
			.add_property( "id", &TagSet::getId )
			.add_property( "name", &TagSet::getName, &TagSet::setName )
			.add_property( "description", &TagSet::getDescription, &TagSet::setDescription )
			.add_property( "typeId", &TagSet::getTypeId )
			.add_property( "accessId", &TagSet::getAccessId )
		
			.def( "addTag", &TagSet::addTag, return_value_policy<reference_existing_object>() )
			.def( "deleteTag", &TagSet::deleteTag )
			.def( "createPersistentDimension", &TagSet::createPersistentDimension, return_value_policy<reference_existing_object>() )
			.def( "deleteDimension", &TagSet::deleteDimension )
			.def( "getTag", &TagSet::getTag, return_value_policy<reference_existing_object>() )
			.def( "getTags", tag_set_get_tags_no_params )
			.def( "getTags", tag_set_get_tags_tag_ids )
			.def( "getFilters", &TagSet::getFilters )
		
			.def( "getDimension", tag_set_get_dimension_id, return_value_policy<reference_existing_object>() )
			.def( "getDimension", tag_set_get_dimension_name, return_value_policy<reference_existing_object>() )
			.def( "getDimensions", &TagSet::getDimensions )
			.def( "getPersistentDimension", tag_set_get_persistent_dimension_id, return_value_policy<reference_existing_object>() )
			.def( "getPersistentDimension", tag_set_get_persistent_dimension_name, return_value_policy<reference_existing_object>() )
			.def( "getPersistentDimensions", &TagSet::getPersistentDimensions )
			.def( "getVirtualDimension", tag_set_get_virtual_dimension_id, return_value_policy<reference_existing_object>() )
			.def( "getVirtualDimension", tag_set_get_virtual_dimension_name, return_value_policy<reference_existing_object>() )
			.def( "getVirtualDimensions", &TagSet::getVirtualDimensions )
			.def( "getDefaultDimension", &TagSet::getDefaultDimension, return_value_policy<reference_existing_object>() )
			
			.def( "erase", &TagSet::erase )
			.def( "typeAsString", tag_set_type_as_string_no_params )
			.def( "typeAsStringStatic", tag_set_type_as_string_id )
			.staticmethod( "typeAsStringStatic" )
			.def( "accessTypeAsString", tag_set_access_type_as_string_no_params )
			.def( "accessTypeAsStringStatic", tag_set_access_type_as_string_id )
			.staticmethod( "accessTypeAsStringStatic" )
		;
		
		enum_<TagSet::TYPE>("TYPE")
			.value( "ALPHANUMERICAL", TagSet::ALPHANUMERICAL )
			.value( "NUMERICAL", TagSet::NUMERICAL )
			.value( "DATE", TagSet::DATE )
			.value( "TIME", TagSet::TIME )
			.value( "RGB", TagSet::RGB )
		;
		
		enum_<TagSet::ACCESS_TYPE>("ACCESS_TYPE")
			.value( "SYSTEM", TagSet::SYSTEM )
			.value( "USER", TagSet::USER )
		;
	}
	
	
	//															AlphanumericalTagSet
	
	class_<AlphanumericalTagSet, bases<TagSet> >("AlphanumericalTagSet")
		.def( init< const string& >() )
		.def( init< const string&, const string& >() )
	
		.def( "create", &AlphanumericalTagSet::create, return_value_policy<reference_existing_object>() )
		.def( "getAlphanumericalTag", &AlphanumericalTagSet::getAlphanumericalTag, return_value_policy<reference_existing_object>() )
		.def( "fetchOrAddTag", &TagSet::fetchOrAddTag, return_value_policy<reference_existing_object>() )
	;
	
	
	//															NumericalTagSet	
	
	class_<NumericalTagSet, bases<TagSet> >("NumericalTagSet")
		.def( init< const string& >() )
		.def( init< const string&, const string& >() )
	
		.def( "create", &NumericalTagSet::create, return_value_policy<reference_existing_object>() )
		.def( "getNumericalTag", &NumericalTagSet::getNumericalTag, return_value_policy<reference_existing_object>() )
	;
	
	
	//															TimeTagSet
	
	class_<TimeTagSet, bases<TagSet> >("TimeTagSet")
		.def( init< const string& >() )
		.def( init< const string&, const string& >() )
	
		.def( "create", &TimeTagSet::create, return_value_policy<reference_existing_object>() )
		.def( "getTimeTag", &TimeTagSet::getTimeTag, return_value_policy<reference_existing_object>() ) 
	;
	
	
	//															DateTagSet
	
	class_<DateTagSet, bases<TagSet> >("DateTagSet")
		.def( init< const string& >() )
		.def( init< const string&, const string& >() )
	
		.def( "create", &DateTagSet::create, return_value_policy<reference_existing_object>() )
		.def( "getDateTag", &DateTagSet::getDateTag, return_value_policy<reference_existing_object>() )
	;

	//															RGBTagSet
	
	class_<RGBTagSet, bases<TagSet> >("RGBTagSet")
		.def( init< const string& >() )
		.def( init< const string&, const string& >() )
	
		.def( "create", &RGBTagSet::create, return_value_policy<reference_existing_object>() )
		.def( "getRGBTag", &RGBTagSet::getRGBTag, return_value_policy<reference_existing_object>() )
		.def( "fetchOrAddTag", &TagSet::fetchOrAddTag, return_value_policy<reference_existing_object>() )
	;
	
//==================================================================================================================================================
	
	//															StateTag
	
	class_<StateTag>("StateTag", init<Tag*>() )
		.def( "ledToInclusion", &StateTag::ledToInclusion )
		.def( "getFilterAndDimensionNodeIds", &StateTag::getFilterAndDimensionNodeIds )
		.def( "getTag", &StateTag::getTag, return_value_policy<reference_existing_object>() )
		.def( "getBoundingBox", &StateTag::getBoundingBox )
	
		.add_property( "hasBoundingBox", &StateTag::hasBoundingBox )
	;
	
	
	//															StateObject
	
	const vector<StateTag> (StateObject::*state_object_get_tags_by_tag_set_id)(int) const = &StateObject::getTags;
	const vector<StateTag> (StateObject::*state_object_get_all_tags)() const = &StateObject::getTags;
	
	class_<StateObject>("StateObject")
		.def( "hasUserTags", &StateObject::hasUserTags )
		.def( "hasTag", &StateObject::hasTag )
		.def( "getTags", state_object_get_tags_by_tag_set_id )
	
		.add_property( "id", &StateObject::getId )
		.add_property( "name", &StateObject::getName )
		.add_property( "tags", state_object_get_all_tags )
		.add_property( "tag", &StateObject::getTag )
	;

	
	//															StateDimensionNode
	
	class_<StateDimensionNode>("StateDimensionNode", init< const HierarchyNode*, int, map<int, map<int, vector<int> > >& /*const vector<StateObject>&*/ >() )
	.def( "getNode", &StateDimensionNode::getNode, return_value_policy<reference_existing_object>() )
	.def( "getBranches", &StateDimensionNode::getBranches )
	.def( "getObjectIds", &StateDimensionNode::getObjectIds )	
	;
	
	
	//															StateDimension
	
	class_<StateDimension>("StateDimension", init<const Dimension* const, int, map<int, map<int, vector<int> > >& /*const vector<StateObject>&*/ >() )
		.def( "getRoot", &StateDimension::getRoot )
		.def( "getParentNode", &StateDimension::getParentNode )
		.def( "getNode", &StateDimension::getNode )
		.add_property( "id", &StateDimension::getId )
		.add_property( "typeId", &StateDimension::getTypeId )
		.add_property( "tagSetId", &StateDimension::getTagSetId )
		.add_property( "filterId", &StateDimension::getFilterId )
	;
	
	
	//															State
	
	const vector<StateObject> (State::*state_get_objects_no_params)() const = &State::getObjects;
	const vector<StateObject> (State::*state_get_objects_object_ids)( const vector<int>& ) const = &State::getObjects;
	
	class_<State>("State")
		
		.def( "addFilter", &State::addFilter )
		.staticmethod( "addFilter" )
	
		.def( "removeFilter", &State::removeFilter )
		.staticmethod( "removeFilter" )
		
		.def( "removeAllFilters", &State::removeAllFilters )
		.staticmethod( "removeAllFilters" )
	
		.def( "getFilters", &State::getFilters )
		.staticmethod( "getFilters" )
		
		.def( "getState", &State::getState )
		.staticmethod( "getState" )
	
		.def( "getObjects", state_get_objects_no_params )
		.def( "getDimensions", &State::getDimensions )
		.def( "getDimension", &State::getDimension )
		.def( "getObjects", state_get_objects_object_ids )
		.def( "getMultiDimensionalView", &State::getMultiDimensionalView )
	;
	
	//															Cell
	
	class_<Cell>("Cell")
	
		.def( "belongs", &Cell::belongs ) 
		.def( "getAxisLabel", &Cell::getAxisLabel )
		.def( "getObjects", &Cell::getObjects )
        .def( "getObjectCount", &Cell::getObjectCount )
        .def( "sort", &Cell::sort )
        .def( "sortTwo", &Cell::sortTwo )
	;
	
	//															MultiDimensionalView
	
	void (*setAxis_state_dimension)( unsigned int, StateDimensionNode, int ) = &MultiDimensionalView::setAxis;
	void(*setAxis_tag_set)( unsigned int, TagSet* ) = &MultiDimensionalView::setAxis; 

	class_<MultiDimensionalView>("MultiDimensionalView", init<const vector<StateObject>&, bool>())
		
		.add_property( "getObjectCount", &MultiDimensionalView::getObjectCount )
		.add_property( "getUniqueObjectCount", &MultiDimensionalView::getUniqueObjectCount )
		.add_property( "getWithEmptySlices", &MultiDimensionalView::getWithEmptySlices )
	
		.def( "getCells", &MultiDimensionalView::getCells )
	
		.def( "setAxis", setAxis_state_dimension )
		.def( "setAxis", setAxis_tag_set )
		.staticmethod( "setAxis" )
	
		.def( "getAxisCellCount", &MultiDimensionalView::getAxisCellCount )
	
		.def( "clearAxis", &MultiDimensionalView::clearAxis )
		.staticmethod( "clearAxis" )
		.def( "clearAxes", &MultiDimensionalView::clearAxes )
		.staticmethod( "clearAxes" )
		
		.def( "getNumberOfDimensions", &MultiDimensionalView::numberOfDimensions )
		.staticmethod( "getNumberOfDimensions" )
	
	/*
	.def( "", &MultiDimensionalView:: )
	*/	
	;
	
	enum_<MultiDimensionalView::DIMENSION_TYPE>("DIMENSION_TYPE")
		.value( "INVALID", MultiDimensionalView::INVALID )
		.value( "TAG_SET",  MultiDimensionalView::TAG_SET )
		.value( "HIERARCHY_NODE",  MultiDimensionalView::HIERARCHY_NODE )
	;
	
	enum_<MultiDimensionalView::AXES>("AXES")
		.value( "AXIS_1", MultiDimensionalView::AXIS_1 )
		.value( "AXIS_2",  MultiDimensionalView::AXIS_2 )
		.value( "AXIS_3",  MultiDimensionalView::AXIS_3 )
		.value( "AXIS_4",  MultiDimensionalView::AXIS_4 )
		.value( "AXIS_5",  MultiDimensionalView::AXIS_5 )
		.value( "AXIS_6",  MultiDimensionalView::AXIS_6 )
	;
	
	
//==================================================================================================================================================	
	
	//															Hub
	
	//Overload support
	int (Hub::*hub_process_all_objects_int)(int) = &Hub::processAllObjects;
	
	const vector<int> (*search_text)( const string&) = &Hub::searchText;
	const vector<int> (*search_rgb)( const string&) = &Hub::searchRGB;

	const vector<Filter*> (Hub::*hub_get_filters_no_params)() const = &Hub::getFilters;
	const vector<Filter*> (Hub::*hub_get_filters_filter_type)(int) const = &Hub::getFilters;
	
	TagSet* (Hub::*hub_get_tag_set_by_id)(int) = &Hub::getTagSet;
	TagSet* (Hub::*hub_get_tag_set_by_name)(const string&) = &Hub::getTagSet;
	
	{ scope in_Hub = 
	class_<Hub, boost::noncopyable>("Hub", no_init)
		.def( "getHub", &Hub::getHub, return_value_policy<reference_existing_object>() )
		.staticmethod( "getHub" )
	
		.def( "processAllObjects", hub_process_all_objects_int )
		.def( "getParentTagSetsAccessType", &Hub::getParentTagSetsAccessType )
		.def( "getFilters", hub_get_filters_no_params )
		.def( "getFilters", hub_get_filters_filter_type )
		.def( "getTagSets", &Hub::getTagSets )
        .def( "getObjectCount", &Hub::getObjectCount )
		.def( "getAllTags", &Hub::getAllTags )
		.def( "getDimensions", &Hub::getDimensions )
		.def( "getPersistentDimensions", &Hub::getPersistentDimensions )
		.def( "getVirtualDimensions", &Hub::getVirtualDimensions )
		.def( "getTagSet", hub_get_tag_set_by_id, return_value_policy<reference_existing_object>() )
		.def( "getTagSet", hub_get_tag_set_by_name, return_value_policy<reference_existing_object>() )
        .def( "addTagSet", &Hub::addTagSet, return_value_policy<reference_existing_object>() )
        .def( "getDataAccessType", &Hub::getDataAccessType)
		.def( "getLastObjectsQueryAsString", &Hub::getLastObjectsQueryAsString)
        .staticmethod( "getDataAccessType" )
        .def( "setDataAccessType", &Hub::setDataAccessType)
        .staticmethod( "setDataAccessType" )
		.def( "getLanguageId", &Hub::getLanguageId )
		.staticmethod( "getLanguageId" )
		.def( "setLanguageId", &Hub::setLanguageId )
		.staticmethod( "setLanguageId" )
		.def( "refreshMaterializedViews", &Hub::refreshMaterializedViews )
		.def("destroy", &Hub::destroy )
		.def( "searchText", search_text )
		.staticmethod( "searchText" )
		.def( "searchRGB", search_rgb )
		.staticmethod( "searchRGB" )

	;
		//Tag enums
	enum_<Hub::DATA_ACCESS_TYPE>("DATA_ACCESS_TYPE")
			.value("CANNED", Hub::CANNED)
			.value("SQLITE", Hub::SQLITE)
			.value("MONETDB", Hub::MONETDB)
			.value("ORACLE", Hub::ORACLE)
			.value("POSTGRESQL", Hub::POSTGRESQL)
		;
    }
	
//==================================================================================================================================================		
	
	//															Language
	
	{
	scope in_Language =
	
	class_<Language>( "Language" )
	;
		
		enum_<Language::LANGUAGE>("LANGUAGE")
			.value("ICELANDIC", Language::ICELANDIC )
			.value( "ENGLISH", Language::ENGLISH )
		;
	}
		
//==================================================================================================================================================		
	
	//															Parameters
	
	//Overload support
	void (Parameters::*parameters_process_string)( const string&, const string&, const string& ) = &Parameters::process;
	void (Parameters::*parameters_process_main_input)( int, char* const*, const string&, const string& ) = &Parameters::process;
	
	class_<Parameters, boost::noncopyable>( "Parameters", no_init )
		.def( "getParameters", &Parameters::getParameters, return_value_policy<reference_existing_object>() )
		.staticmethod( "getParameters" )
	
		.def( "process", parameters_process_string )
		.def( "process", parameters_process_main_input )
		.def( "add", &Parameters::add )
		.def( "remove", &Parameters::remove )
		.def( "update", &Parameters::update )
	
		.def( "contains", &Parameters::contains )
		.def( "getValue", &Parameters::getValue )
		.def( "getValueAsInt", &Parameters::getValueAsInt )
	;
	 
	
//==================================================================================================================================================		
	
	//															STL Container Support
	
	class_<vector<Tag*> >("TagPVecWrapper")
		.def( "__len__", &vector<Tag*>::size )
		.def( "clear", &vector<Tag*>::clear)
		.def( "append", &std_item<vector<Tag*> >::add, with_custodian_and_ward<1,2>() ) // to let container keep value
		.def( "__getitem__", &std_item<vector<Tag*> >::get, return_value_policy<reference_existing_object>() )
		.def( "__setitem__", &std_item<vector<Tag*> >::set, with_custodian_and_ward<1,2>()) // to let container keep value
		.def( "__delitem__", &std_item<vector<Tag*> >::del)
		.def( "__contains__", &std_item<vector<Tag*> >::in )
		.def( "__iter__", boost::python::iterator< vector<Tag*>, return_internal_reference<> >() )
		.def( "index", &std_item<vector<Tag*> >::index )
	;
	
	class_<vector<TagSet*> >("TagSetPVecWrapper")
		.def( "__len__", &vector<TagSet*>::size )
		.def( "clear", &vector<TagSet*>::clear)
		.def( "append", &std_item<vector<TagSet*> >::add, with_custodian_and_ward<1,2>() ) // to let container keep value
		.def( "__getitem__", &std_item<vector<TagSet*> >::get, return_value_policy<reference_existing_object>() )
		.def( "__setitem__", &std_item<vector<TagSet*> >::set, with_custodian_and_ward<1,2>()) // to let container keep value
		.def( "__delitem__", &std_item<vector<TagSet*> >::del)
		.def( "__contains__", &std_item<vector<TagSet*> >::in )
		.def( "__iter__", boost::python::iterator< vector<TagSet*>, return_internal_reference<> >() )
		.def( "index", &std_item<vector<TagSet*> >::index )
	;
	 
	class_<vector<Object> >("ObjectVecWrapper")
		.def( "__len__", &vector<Object>::size )
		.def( "clear", &vector<Object>::clear)
		.def( "append", &std_item<vector<Object> >::add, with_custodian_and_ward<1,2>() ) // to let container keep value
		.def( "__getitem__", &std_item<vector<Object> >::get )
		.def( "__setitem__", &std_item<vector<Object> >::set, with_custodian_and_ward<1,2>()) // to let container keep value
		.def( "__delitem__", &std_item<vector<Object> >::del)
		.def( "__contains__", &std_item<vector<Object> >::in )
		.def( "__iter__", boost::python::iterator< vector<Object> >() )
		.def( "index", &std_item<vector<Object> >::index )    
	;
	
	class_<vector<ObjectTag> >("ObjectTagVecWrapper")
	.def( "__len__", &vector<ObjectTag>::size )
	.def( "clear", &vector<ObjectTag>::clear)
	.def( "append", &std_item<vector<ObjectTag> >::add, with_custodian_and_ward<1,2>() ) // to let container keep value
	.def( "__getitem__", &std_item<vector<ObjectTag> >::get )
	.def( "__setitem__", &std_item<vector<ObjectTag> >::set, with_custodian_and_ward<1,2>()) // to let container keep value
	.def( "__delitem__", &std_item<vector<ObjectTag> >::del)
	.def( "__contains__", &std_item<vector<ObjectTag> >::in )
	.def( "__iter__", boost::python::iterator< vector<ObjectTag> >() )
	.def( "index", &std_item<vector<ObjectTag> >::index )  
	;
	
	class_<vector<Filter*> >("FilterPVecWrapper")
		.def( "__len__", &vector<Filter*>::size )
		.def( "clear", &vector<Filter*>::clear)
		.def( "append", &std_item<vector<Filter*> >::add, with_custodian_and_ward<1,2>() ) // to let container keep value
		.def( "__getitem__", &std_item<vector<Filter*> >::get, return_value_policy<reference_existing_object>() )
		.def( "__setitem__", &std_item<vector<Filter*> >::set, with_custodian_and_ward<1,2>()) // to let container keep value
		.def( "__delitem__", &std_item<vector<Filter*> >::del)
		.def( "__contains__", &std_item<vector<Filter*> >::in )
		.def( "__iter__", boost::python::iterator< vector<Filter*>, return_internal_reference<> >() )
		.def( "index", &std_item<vector<Filter*> >::index )
    ;
	
	class_<vector<HierarchyNode*> >("HierarchyNodePVecWrapper")
	.def( "__len__", &vector<HierarchyNode*>::size )
	.def( "clear", &vector<HierarchyNode*>::clear)
	.def( "append", &std_item<vector<HierarchyNode*> >::add, with_custodian_and_ward<1,2>() ) // to let container keep value
	.def( "__getitem__", &std_item<vector<HierarchyNode*> >::get, return_value_policy<reference_existing_object>() )
	.def( "__setitem__", &std_item<vector<HierarchyNode*> >::set, with_custodian_and_ward<1,2>()) // to let container keep value
	.def( "__delitem__", &std_item<vector<HierarchyNode*> >::del)
	.def( "__contains__", &std_item<vector<HierarchyNode*> >::in )
	.def( "__iter__", boost::python::iterator< vector<HierarchyNode*>, return_internal_reference<> >() )
	.def( "index", &std_item<vector<HierarchyNode*> >::index ) 
    ;	
	
	class_<vector<PersistentDimension*> >("PersistentDimensionPVecWrapper")
	.def( "__len__", &vector<PersistentDimension*>::size )
	.def( "clear", &vector<PersistentDimension*>::clear)
	.def( "append", &std_item<vector<PersistentDimension*> >::add, with_custodian_and_ward<1,2>() ) // to let container keep value
	.def( "__getitem__", &std_item<vector<PersistentDimension*> >::get, return_value_policy<reference_existing_object>() )
	.def( "__setitem__", &std_item<vector<PersistentDimension*> >::set, with_custodian_and_ward<1,2>()) // to let container keep value
	.def( "__delitem__", &std_item<vector<PersistentDimension*> >::del)
	.def( "__contains__", &std_item<vector<PersistentDimension*> >::in )
	.def( "__iter__", boost::python::iterator< vector<PersistentDimension*>, return_internal_reference<> >() )
	.def( "index", &std_item<vector<PersistentDimension*> >::index ) 
	;
	
	class_<vector<VirtualDimension*> >("VirtualDimensionPVecWrapper")
	.def( "__len__", &vector<VirtualDimension*>::size )
	.def( "clear", &vector<VirtualDimension*>::clear)
	.def( "append", &std_item<vector<VirtualDimension*> >::add, with_custodian_and_ward<1,2>() ) // to let container keep value
	.def( "__getitem__", &std_item<vector<VirtualDimension*> >::get, return_value_policy<reference_existing_object>() )
	.def( "__setitem__", &std_item<vector<VirtualDimension*> >::set, with_custodian_and_ward<1,2>()) // to let container keep value
	.def( "__delitem__", &std_item<vector<VirtualDimension*> >::del)
	.def( "__contains__", &std_item<vector<VirtualDimension*> >::in )
	.def( "__iter__", boost::python::iterator< vector<VirtualDimension*>, return_internal_reference<> >() )
	.def( "index", &std_item<vector<VirtualDimension*> >::index ) 
	;
	
	class_<vector<StateTag> >("StateTagVecWrapper")
		.def( "__len__", &vector<StateTag>::size )
		.def( "clear", &vector<StateTag>::clear)
		.def( "append", &std_item<vector<StateTag> >::add, with_custodian_and_ward<1,2>() ) // to let container keep value
		.def( "__getitem__", &std_item<vector<StateTag> >::get )
		.def( "__setitem__", &std_item<vector<StateTag> >::set, with_custodian_and_ward<1,2>()) // to let container keep value
		.def( "__delitem__", &std_item<vector<StateTag> >::del)
		.def( "__contains__", &std_item<vector<StateTag> >::in )
		.def( "__iter__", boost::python::iterator< vector<StateTag> >() )
		.def( "index", &std_item<vector<StateTag> >::index ) 
    ;
	
	class_<vector<StateObject> >("StateObjectVecWrapper")
		.def( "__len__", &vector<StateObject>::size )
		.def( "clear", &vector<StateObject>::clear)
		.def( "append", &std_item<vector<StateObject> >::add, with_custodian_and_ward<1,2>() ) // to let container keep value
		.def( "__getitem__", &std_item<vector<StateObject> >::get )
		.def( "__setitem__", &std_item<vector<StateObject> >::set, with_custodian_and_ward<1,2>()) // to let container keep value
		.def( "__delitem__", &std_item<vector<StateObject> >::del)
		.def( "__contains__", &std_item<vector<StateObject> >::in )
		.def( "__iter__", boost::python::iterator< vector<StateObject> >() )
		.def( "index", &std_item<vector<StateObject> >::index ) 
    ;
	
	class_<vector<StateObject*> >("StateObjectPVecWrapper")
	.def( "__len__", &vector<StateObject*>::size )
	.def( "clear", &vector<StateObject*>::clear)
	.def( "append", &std_item<vector<StateObject*> >::add, with_custodian_and_ward<1,2>() ) // to let container keep value
	.def( "__getitem__", &std_item<vector<StateObject*> >::get, return_value_policy<reference_existing_object>() )
	.def( "__setitem__", &std_item<vector<StateObject*> >::set, with_custodian_and_ward<1,2>()) // to let container keep value
	.def( "__delitem__", &std_item<vector<StateObject*> >::del)
	.def( "__contains__", &std_item<vector<StateObject*> >::in )
	.def( "__iter__", boost::python::iterator< vector<StateObject*>, return_internal_reference<> >() )
	.def( "index", &std_item<vector<StateObject*> >::index ) 
	;

	class_<vector<StateDimensionNode> >("StateDimensionNodeVecWrapper")
		.def( "__len__", &vector<StateDimensionNode>::size )
		.def( "clear", &vector<StateDimensionNode>::clear)
		.def( "append", &std_item<vector<StateDimensionNode> >::add, with_custodian_and_ward<1,2>() ) // to let container keep value
		.def( "__getitem__", &std_item<vector<StateDimensionNode> >::get )
		.def( "__setitem__", &std_item<vector<StateDimensionNode> >::set, with_custodian_and_ward<1,2>()) // to let container keep value
		.def( "__delitem__", &std_item<vector<StateDimensionNode> >::del)
		.def( "__contains__", &std_item<vector<StateDimensionNode> >::in )
		.def( "__iter__", boost::python::iterator< vector<StateDimensionNode> >() )
		.def( "index", &std_item<vector<StateDimensionNode> >::index ) 
    ;
	
	class_<vector<StateDimension> >("StateDimensionVecWrapper")
		.def( "__len__", &vector<StateDimension>::size )
		.def( "clear", &vector<StateDimension>::clear)
		.def( "append", &std_item<vector<StateDimension> >::add, with_custodian_and_ward<1,2>() ) // to let container keep value
		.def( "__getitem__", &std_item<vector<StateDimension> >::get )
		.def( "__setitem__", &std_item<vector<StateDimension> >::set, with_custodian_and_ward<1,2>()) // to let container keep value
		.def( "__delitem__", &std_item<vector<StateDimension> >::del)
		.def( "__contains__", &std_item<vector<StateDimension> >::in )
		.def( "__iter__", boost::python::iterator< vector<StateDimension> >() )
		.def( "index", &std_item<vector<StateDimension> >::index ) 
	;

	class_<vector<int> >("intVecWrapper")
	.def( "__len__", &vector<int>::size )
	.def( "clear", &vector<int>::clear)
	.def( "append", &std_item<vector<int> >::add, with_custodian_and_ward<1,2>() ) // to let container keep value
	.def( "__getitem__", &std_item<vector<int> >::get )
	.def( "__setitem__", &std_item<vector<int> >::set, with_custodian_and_ward<1,2>()) // to let container keep value
	.def( "__delitem__", &std_item<vector<int> >::del)
	.def( "__contains__", &std_item<vector<int> >::in )
	.def( "__iter__", boost::python::iterator< vector<int> >() )
	.def( "index", &std_item<vector<int> >::index ) 
	;
	
	class_<vector<Cell> >("CellVecWrapper")
	.def( "__len__", &vector<Cell>::size )
	.def( "clear", &vector<Cell>::clear)
	.def( "append", &std_item<vector<Cell> >::add, with_custodian_and_ward<1,2>() ) // to let container keep value
	.def( "__getitem__", &std_item<vector<Cell> >::get )
	.def( "__setitem__", &std_item<vector<Cell> >::set, with_custodian_and_ward<1,2>()) // to let container keep value
	.def( "__delitem__", &std_item<vector<Cell> >::del)
	.def( "__contains__", &std_item<vector<Cell> >::in )
	.def( "__iter__", boost::python::iterator< vector<Cell> >() )
	.def( "index", &std_item<vector<Cell> >::index ) 
	;
	
	/*
	class_<vector<vector<Cell> > >("CellVecVecWrapper")
	.def( "__len__", &vector<vector<Cell> >::size )
	.def( "clear", &vector<vector<Cell> >::clear)
	.def( "append", &std_item<vector<vector<Cell> > >::add, with_custodian_and_ward<1,2>() ) // to let container keep value
	.def( "__getitem__", &std_item<vector<vector<Cell> > >::get )
	.def( "__setitem__", &std_item<vector<vector>Cell> > >::set, with_custodian_and_ward<1,2>()) // to let container keep value
	.def( "__delitem__", &std_item<vector<vector<Cell> > >::del)
	.def( "__contains__", &std_item<vector<vector<Cell> > >::in )
	.def( "__iter__", boost::python::iterator< vector<vector<Cell> > >() )
	.def( "index", &std_item<vector<vector<Cell> > >::index ) 
	*/
	
	class_<map<int, int> >("IntIntMapWrapper")
		.def("__len__", &map<int, int>::size)
		.def("clear", &map<int, int>::clear)
		.def("__getitem__", &map_item<map<int, int> >::get )
		.def("__setitem__", &map_item<map<int, int> >::set, with_custodian_and_ward<1,2>()) // to let container keep value
		.def("__delitem__", &map_item<map<int, int> >::del)
		.def( "__contains__", &map_item<map<int, int> >::in )
		.def( "keys", &map_item<map<int, int> >::keys )
		.def( "values", &map_item<map<int, int> >::values )
		.def( "items", &map_item<map<int, int> >::items )
		.def( "index", &map_item<map<int, int> >::index )
	;
	
	class_<map<string, Cell> >("StringCellMapWrapper")
	.def("__len__", &map<string, Cell>::size)
	.def("clear", &map<string, Cell>::clear)
	.def("__getitem__", &map_item<map<string, Cell> >::get )
	.def("__setitem__", &map_item<map<string, Cell> >::set, with_custodian_and_ward<1,2>()) // to let container keep value
	.def("__delitem__", &map_item<map<string, Cell> >::del)
	.def( "__contains__", &map_item<map<string, Cell> >::in )
	.def( "keys", &map_item<map<string, Cell> >::keys )
	.def( "values", &map_item<map<string, Cell> >::values )
	.def( "items", &map_item<map<string, Cell> >::items )
	.def( "index", &map_item<map<string, Cell> >::index )
	;
	
	 
    
	
//==================================================================================================================================================	
	 
}


