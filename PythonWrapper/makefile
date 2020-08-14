# http://www.gnu.org/software/make/manual/make.html

SHELL = /bin/sh

OS = $(shell uname)

#Database support:  1 = yes, comment out = no
#SUPPORT_SQLITE = 1
#SUPPORT_MONETDB = 1
#SUPPORT_ORACLE = 1
SUPPORT_POSTGRESQL = 1

# 32 or 64 bit (or anything other than those two for default behaviour)
ARCH = 64

TARGET_NAME =
LIB_DIR = ../ObjectCube
PHOTOCUB_DIR = ../PhotoCube

PYTHON_VERSION = 2.7
PYTHON_INCLUDE = /usr/lib/python2.7 
PYTHON_LIB = .

BOOST_INCLUDE = 
CDEBUG =
CXXFLAGS =

#The following line should be added to CDEBUG for extra info
#-v -p -n 
# add -c to debug to stop linking

ifeq ($(OS), Linux)
	TARGET_NAME = ObjectCubePython.so
	LIB_DIR = /usr/lib
	PYTHON_INCLUDE = /usr/include/python$(PYTHON_VERSION)
	BOOST_INCLUDE =
	CDEBUG = -o -g
	CXXFLAGS = $(CDEBUG) -fPIC -I. -I$(srcdir) $(DEFS) -I/Developer/SDKs/MacOSX10.7.sdk/usr/include/ -I/opt/local/include/sdk/include -I/opt/local/include -I$(PYTHON_INCLUDE) -I$(BOOST_INCLUDE) -L/usr/local/lib -L/usr/lib -std=c++17

else ifeq ($(OS), Darwin)
	TARGET_NAME = ObjectCubePython.so
	LIB_DIR = /usr/local/lib
	PYTHON_INCLUDE = /System/Library/Frameworks/Python.framework/Versions/$(PYTHON_VERSION)/include/python$(PYTHON_VERSION)
	#PYTHON_LIB = /Developer/SDKs/MacOSX10.7.sdk/usr/lib/
	#BOOST_INCLUDE = /Library/Boost/boost_1_41_0/boost
	BOOST_INCLUDE = /usr/local/include/boost
	CDEBUG = -o -g -std=c++11
	CXXFLAGS = $(CDEBUG) -fPIC -I. -I$(srcdir) $(DEFS) -I/usr/local/include -I$(PYTHON_INCLUDE) -I$(BOOST_INCLUDE)
endif

LDFLAGS = -fPIC -fvisibility=default -ldl
#-L$(PYTHON_LIB)

ifeq ($(OS), Linux)
	CXXFLAGS += -shared -DLINUX=1 
	LDFLAGS += -L/usr/lib -L/opt/local/lib -shared -Wl,-soname,$(TARGET_NAME).1 -Wl,--export-dynamic
else ifeq ($(OS), Darwin)
	LDFLAGS += -dynamiclib -L/usr/local/lib -current_version 1.0 -compatibility_version 1.0 -install_name $(LIB_DIR)/$(TARGET_NAME)
	ifeq ($(ARCH), 32)
		CXXFLAGS += -arch i386
		LDFLAGS += -arch i386
	else ifeq ($(ARCH), 64)
		CXXFLAGS += -arch x86_64
		LDFLAGS += -arch x86_64
	endif

endif

#-arch x86_64

#### Start of system configuration section. ####
 
srcdir = .
CC = g++ -fPIC -O3
#CXX = clang++ -fPIC -O3
DEFS =  
LIBS =
ifeq ($(OS), Linux)
	LIBS = -lpython$(PYTHON_VERSION) -lboost_regex -lboost_python -L/opt/local/lib 
else ifeq ($(OS), Darwin)
	LIBS = -lpython$(PYTHON_VERSION) -lboost_regex-mt -lboost_python27-mt -L/usr/local/lib 
endif




VPATH = ../ObjectCube/LayerShared ../ObjectCube/DataAccess/Root ../ObjectCube/DataAccess/Canned ../ObjectCube/DataAccess/SQLite ../ObjectCube/DataAccess/MonetDB ../ObjectCube/DataAccess/Oracle ../ObjectCube/DataAccess/PostgreSQL ../ObjectCube/DataAccess/Factories ../ObjectCube/Converters ../ObjectCube/Tag ../ObjectCube/Hierarchy ../ObjectCube/TagSet ../ObjectCube/Filters ../ObjectCube/State ../ObjectCube/Plugin ../ObjectCube/UnitTests  ../ObjectCube/Boundaries /usr/local/include /usr/local/lib

#### End of system configuration section. ####

# --------------------------------------------------------   SHARED OBJECTS   --------------------------------------------------------

SHARED_OBJECTS = \
Exception.o TestIds.o DateSupport.o TimeSupport.o HubCommon.o RegExSupport.o LanguageCommon.o Parameters.o DebugInfo.o StringSupport.o


# --------------------------------------------------------   DATA ACCESS   --------------------------------------------------------

DATA_ACCESS_ROOT = \
TagDataAccess.o AlphanumericalTagDataAccess.o NumericalTagDataAccess.o DateTagDataAccess.o TimeTagDataAccess.o \
TagSetDataAccess.o ObjectDataAccess.o HierarchyNodeDataAccess.o DimensionDataAccess.o \
StateDataAccess.o StateTagDataAccess.o StateObjectDataAccess.o HubDataAccess.o \
PluginTagSetDataAccess.o PluginDataAccess.o LanguageDataAccess.o \
FilterDataAccess.o TagFilterDataAccess.o DimensionFilterDataAccess.o NumericalRangeFilterDataAccess.o \
DateRangeFilterDataAccess.o TimeRangeFilterDataAccess.o ObjectTagDataAccess.o Coordinate2DDataAccess.o BoundingBoxDataAccess.o \
SearchDataAccess.o RGBTagDataAccess.o

DATA_ACCESS_POSTGRESQL = \
CommonPostgreSQL.o TagPostgreSQL.o AlphanumericalTagPostgreSQL.o NumericalTagPostgreSQL.o DateTagPostgreSQL.o TimeTagPostgreSQL.o \
HierarchyNodePostgreSQL.o DimensionPostgreSQL.o ObjectPostgreSQL.o TagSetPostgreSQL.o HubPostgreSQL.o PluginTagSetPostgreSQL.o \
PluginPostgreSQL.o LanguagePostgreSQL.o TagFilterPostgreSQL.o DimensionFilterPostgreSQL.o NumericalRangeFilterPostgreSQL.o \
DateRangeFilterPostgreSQL.o TimeRangeFilterPostgreSQL.o ObjectTagPostgreSQL.o SearchPostgreSQL.o RGBTagPostgreSQL.o

DATA_ACCESS_FACTORIES = \
DimensionDataAccessFactory.o HierarchyNodeDataAccessFactory.o ObjectDataAccessFactory.o \
AlphanumericalTagDataAccessFactory.o NumericalTagDataAccessFactory.o TimeTagDataAccessFactory.o \
DateTagDataAccessFactory.o TagDataAccessFactory.o TagSetDataAccessFactory.o HubDataAccessFactory.o \
PluginTagSetDataAccessFactory.o PluginDataAccessFactory.o LanguageDataAccessFactory.o \
FilterDataAccessFactory.o TagFilterDataAccessFactory.o DimensionFilterDataAccessFactory.o \
NumericalRangeFilterDataAccessFactory.o DateRangeFilterDataAccessFactory.o TimeRangeFilterDataAccessFactory.o ObjectTagDataAccessFactory.o \
SearchDataAccessFactory.o RGBTagDataAccessFactory.o


# --------------------------------------------------------   CONVERTERS   --------------------------------------------------------

CONVERTERS = \
AlphanumericalTagConverter.o NumericalTagConverter.o TimeTagConverter.o DateTagConverter.o RGBTagConverter.o TagConverter.o \
TagConverterFactory.o HierarchyNodeConverter.o DimensionConverter.o ObjectConverter.o TagSetConverter.o \
StateTagConverter.o StateObjectConverter.o PluginConverter.o PluginTagSetConverter.o \
FilterConverterFactory.o FilterConverter.o TagFilterConverter.o DimensionFilterConverter.o NumericalRangeFilterConverter.o \
DateRangeFilterConverter.o TimeRangeFilterConverter.o Coordinate2DConverter.o BoundingBoxConverter.o ObjectTagConverter.o


# --------------------------------------------------------   LOGIC   --------------------------------------------------------

LOGIC = \
Tag.o AlphanumericalTag.o NumericalTag.o TimeTag.o DateTag.o RGBTag.o TagFactory.o \
HierarchyNode.o PersistentHierarchyNode.o VirtualHierarchyNode.o HierarchyNodeFactory.o \
TagBasedHierarchyNode.o DefaultHierarchyNode.o DefaultDimension.o \
Dimension.o PersistentDimension.o VirtualDimension.o DimensionFactory.o ../ObjectCube/Object.o ../ObjectCube/ObjectTag.o \
TagSet.o AlphanumericalTagSet.o NumericalTagSet.o TimeTagSet.o DateTagSet.o RGBTagSet.o TagSetFactory.o \
Filter.o TagFilter.o DimensionFilter.o NumericalRangeFilter.o DateRangeFilter.o TimeRangeFilter.o FilterFactory.o \
StateTag.o StateObject.o StateDimensionNode.o StateDimension.o State.o MultiDimensionalView.o Cell.o \
../ObjectCube/Hub.o ../ObjectCube/Search.o ../ObjectCube/Language.o Coordinate2D.o BoundingBox.o

# --------------------------------------------------------   PLUGIN   --------------------------------------------------------

PLUGIN = \
Plugin.o PluginTagSet.o ProcessObjectServer.o PluginLibrary.o PluginServer.o PluginObject.o PluginCommon.o PluginTagging.o PluginTaggingProcessed.o PluginReply.o

# --------------------------------------------------------   MAIN   --------------------------------------------------------

MAIN = ObjectCube_boost.o

DATA_ACCESS_DB = 

ifdef SUPPORT_SQLITE
	CXXFLAGS += -DOC_SQLITE
	LIBS += -lsqlite3 
	DATA_ACCESS_DB += $(DATA_ACCESS_SQLITE)
endif
ifdef SUPPORT_MONETDB
	CXXFLAGS += -DOC_MONETDB
	LIBS += -lmapi
	DATA_ACCESS_DB += $(DATA_ACCESS_MONETDB)
endif
ifdef SUPPORT_ORACLE
CXXFLAGS += -DOC_ORACLE
	LIBS += -locci -lclntsh
	DATA_ACCESS_DB += $(DATA_ACCESS_ORACLE)
endif
ifdef SUPPORT_POSTGRESQL
	CXXFLAGS += -DOC_POSTGRESQL
	LIBS += -lpqxx -lpq
	#LIBS += -lpq
	DATA_ACCESS_DB += $(DATA_ACCESS_POSTGRESQL)
endif


OBJS = $(SHARED_OBJECTS) $(DATA_ACCESS_ROOT) $(DATA_ACCESS_DB) $(DATA_ACCESS_FACTORIES) $(CONVERTERS) $(LOGIC) $(PLUGIN) $(MAIN)
#OBJS = $(MAIN)

.PHONY: all
all: $(TARGET_NAME)

.PHONY: $(TARGET_NAME)
$(TARGET_NAME) : $(OBJS) 
		$(CC) $(CXXFLAGS) $(LDFLAGS) -o $@ $(OBJS) $(LIBS) 
		sudo cp $(TARGET_NAME) $(LIB_DIR)
		sudo cp $(TARGET_NAME) $(PHOTOCUB_DIR)

.PHONY: clean
clean: 
	rm -f *.o $(TARGET_NAME)



