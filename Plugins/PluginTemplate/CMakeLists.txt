set(NAME Your)

# Add the cpp files to use
file(GLOB SOURCE_FILES *.cpp)

add_library(${NAME}_Plugin SHARED ${SOURCE_FILES})

install(TARGETS ${NAME}_Plugin LIBRARY DESTINATION ObjectCube/plugin/${NAME})
