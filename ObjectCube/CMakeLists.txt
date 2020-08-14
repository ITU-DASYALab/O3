CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
ADD_DEFINITIONS( -DOC_POSTGRESQL )
SET( CMAKE_OSX_ARCHITECTURES x86_64 )

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
	SET (CMAKE_CXX_STANDARD 17)
endif()
SET (CMAKE_CXX_STANDARD 17)

#SET( LIBRARY_OUTPUT_PATH /usr/lib )

MESSAGE( STATUS ${CMAKE_CXX_COMPILER} )

file(MAKE_DIRECTORY /usr/local/ObjectCube )
file(MAKE_DIRECTORY /usr/local/ObjectCube/plugin )

FILE (GLOB_RECURSE Files_CPP *.cpp )
FILE(GLOB_RECURSE IgnoreFiles_CPP "UnitTests/*.cpp")
FILE(GLOB main_CPP "main*.cpp")

LIST(REMOVE_ITEM Files_CPP ${IgnoreFiles_CPP})
LIST(REMOVE_ITEM Files_CPP ${main_CPP})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC -lpqxx -lpq")

#MESSAGE(STATUS "Contents of IgnoreFiles_CPP: ${IgnoreFiles_CPP}")
#MESSAGE(STATUS "Contents of Files_CPP: ${Files_CPP}")

set(CMAKE_FIND_LIBRARY_SUFFIXES ".a;.so;.dylib")

ADD_LIBRARY(ObjectCube SHARED ${Files_CPP})

INSTALL(TARGETS ObjectCube LIBRARY DESTINATION /usr/lib )


