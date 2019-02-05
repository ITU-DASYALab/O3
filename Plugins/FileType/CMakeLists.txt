set(NAME FileType)

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
set( Files_CPP ${Files_CPP};../../ObjectCube/LayerShared/StringSupport.cpp )
MESSAGE(STATUS "Contents of Files_CPP: ${Files_CPP}")

add_library(${NAME}_Plugin SHARED ${Files_CPP})

install(TARGETS ${NAME}_Plugin LIBRARY DESTINATION /usr/local/lib)
