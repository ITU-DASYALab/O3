set(NAME EXIF)

# EXIV2 libraries and include directories
find_library(EXIV2_LIBRARY NAMES exiv2 PATHS /usr/lib /usr/lib64 /usr/local/lib /usr/local/lib64)
find_path(EXIV2_INCLUDE_DIR exiv2/exv_conf.h PATHS /usr/local/exiv2/include /usr/include /usr/local)

IF(EXIV2_INCLUDE_DIR AND EXIV2_LIBRARY)
	message(STATUS "Found EXIV2\n\tinclude dir.:${EXIV2_INCLUDE_DIR}\n\tlibrary path: ${EXIV2_LIBRARY} ")
else()
	message(FATAL_ERROR "Could not find EXIV2\n\tinclude dir.:${EXIV2_INCLUDE_DIR}\n\tlibrary path: ${EXIV2_LIBRARY} ")
endif()

# Add the cpp files to use
file(GLOB Files_CPP *.cpp)
set( Files_CPP ${Files_CPP};../../ObjectCube/Plugin/PluginCommon.cpp )
set( Files_CPP ${Files_CPP};../../ObjectCube/LayerShared/HubCommon.cpp )
set( Files_CPP ${Files_CPP};../../ObjectCube/LayerShared/Exception.cpp )
set( Files_CPP ${Files_CPP};../../ObjectCube/Plugin/PluginCommon.cpp )
set( Files_CPP ${Files_CPP};../../ObjectCube/Plugin/PluginReply.cpp )
set( Files_CPP ${Files_CPP};../../ObjectCube/Plugin/PluginTagging.cpp )
set( Files_CPP ${Files_CPP};../../ObjectCube/Boundaries/Coordinate2D.cpp )
set( Files_CPP ${Files_CPP};../../ObjectCube/Boundaries/BoundingBox.cpp )
MESSAGE(STATUS "Contents of Files_CPP: ${Files_CPP}")

add_library(${NAME}_Plugin SHARED ${Files_CPP})

target_link_libraries(${NAME}_Plugin ${EXIV2_LIBRARY})

install(TARGETS ${NAME}_Plugin LIBRARY DESTINATION /usr/local/lib)
