set(NAME Color)

find_package(ImageMagick COMPONENTS Magick++ REQUIRED)

if(${ImageMagick_Magick++_FOUND})
	message(STATUS "Found Image Magick C++\n\tinclude dir.:${ImageMagick_INCLUDE_DIRS}\n\tlibrary path: ${ImageMagick_LIBRARIES} ")
endif(${ImageMagick_Magick++_FOUND})

include_directories(${ImageMagick_INCLUDE_DIRS})

# mandatory options for newer ImageMagick versions, these probably match the old defaults
add_definitions(-DMAGICKCORE_QUANTUM_DEPTH=16 -DMAGICKCORE_HDRI_ENABLE=0)

# Add the cpp files to use
file(GLOB SOURCE_FILES *.cpp)

add_library(${NAME}_Plugin SHARED ${SOURCE_FILES})

target_link_libraries(${NAME}_Plugin ${ImageMagick_LIBRARIES})

install(TARGETS ${NAME}_Plugin LIBRARY DESTINATION /usr/local/lib/)
