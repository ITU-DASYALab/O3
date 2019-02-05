set(NAME FaceRecognition)

#This could be recursed (GLOB), but then we'd have to remove the test files.
set( SOURCE_FILES
	FaceRecognitionPlugin.cpp
	face_detection/FaceDetector.cpp
	face_detection/RegionOfInterest.cpp
	face_database/MySQLite.cpp
	face_database/Person.cpp
	face_database/Face.cpp
	face_recognition/Eigenfaces.cpp
	face_recognition/ImageList.cpp
	face_recognition/RecImage.cpp
	face_recognition/Recognizer.cpp
)

#  OpenCV library support
	find_library( OPENCV_LIBRARY_CORE NAMES opencv_core  PATHS /usr/lib /usr/lib64 /usr/local/lib /usr/local/lib64 )
	find_library( OPENCV_LIBRARY_HIGHGUI NAMES opencv_highgui PATHS /usr/lib /usr/lib64 /usr/local/lib /usr/local/lib64 )
	find_library( OPENCV_LIBRARY_IMGPROC NAMES opencv_imgproc PATHS /usr/lib /usr/lib64 /usr/local/lib /usr/local/lib64 )
	find_library( OPENCV_LIBRARY_OBJDETECT NAMES opencv_objdetect PATHS /usr/lib /usr/lib64 /usr/local/lib /usr/local/lib64 )
	find_library( OPENCV_LIBRARY_M NAMES m PATHS /usr/lib /usr/lib64 /usr/local/lib /usr/local/lib64 )

	find_path( OPENCV_INCLUDE_DIR opencv2/opencv.hpp PATHS /usr/local/include/ )

	if( OPENCV_INCLUDE_DIR AND OPENCV_LIBRARY_CORE AND OPENCV_LIBRARY_HIGHGUI AND OPENCV_LIBRARY_IMGPROC AND OPENCV_LIBRARY_OBJDETECT AND OPENCV_LIBRARY_M ) #simplify this code, only one if statement needed.
		message( STATUS "Found OpenCV \n\tinclude dir.:${OPENCV_INCLUDE_DIR}\n\tlibrary path:\n\t\t ${OPENCV_LIBRARY_CORE}\n\t\t ${OPENCV_LIBRARY_HIGHGUI}\n\t\t ${OPENCV_LIBRARY_IMGPROC}\n\t\t ${OPENCV_LIBRARY_OBJDETECT}\n\t\t ${OPENCV_LIBRARY_M}" )
	else()
		message( FATAL_ERROR "Could not find OpenCV \n\tinclude dir.:${OPENCV_INCLUDE_DIR}\n\tlibrary path:\n\t\t ${OPENCV_LIBRARY_CORE}\n\t\t ${OPENCV_LIBRARY_HIGHGUI}\n\t\t ${OPENCV_LIBRARY_IMGPROC}\n\t\t ${OPENCV_LIBRARY_OBJDETECT}\n\t\t ${OPENCV_LIBRARY_M}" )
	endif()
# End OpenCV

# SQLite library support
	find_library( SQLITE_LIBRARY NAMES sqlite3 PATHS /usr/local/lib/ )
	find_path( SQLITE_INCLUDE_DIR sqlite3.h PATHS /usr/local/include/ )

	if( SQLITE_INCLUDE_DIR AND SQLITE_LIBRARY )
		message( STATUS "Found SQLite3 \n\tinclude dir.:${SQLITE_INCLUDE_DIR}\n\tlibrary path: ${SQLITE_LIBRARY}" )
	else()
		message( FATAL_ERROR "Could not find SQLite3 \n\tinclude dir.:${SQLITE_INCLUDE_DIR}\n\tlibrary path: ${SQLITE_LIBRARY}" )
	endif()
# End SQLite 


include_directories( ${OPENCV_INCLUDE_DIR} ${SQLITE_INCLUDE_DIR} )

add_library(${NAME}_Plugin SHARED ${SOURCE_FILES})

target_link_libraries(${NAME}_Plugin ${OPENCV_LIBRARY_CORE} ${OPENCV_LIBRARY_HIGHGUI} ${OPENCV_LIBRARY_IMGPROC} ${OPENCV_LIBRARY_OBJDETECT} ${OPENCV_LIBRARY_M} ${SQLITE_LIBRARY} )

install(TARGETS ${NAME}_Plugin LIBRARY DESTINATION ObjectCube/plugin/${NAME})

# additional installs
file(GLOB ADDITIONAL_INSTALL_FILES 
	face_detection/resources/*.xml
	face_database/faceDatabase.sqlite
)
install(FILES ${ADDITIONAL_INSTALL_FILES} DESTINATION ObjectCube/plugin/${NAME})

# create face_rec_images and have it be installed with 0777 permissions
set(IMAGE_DIRECTORY face_rec_images)
file(MAKE_DIRECTORY ${IMAGE_DIRECTORY})
install (DIRECTORY ${IMAGE_DIRECTORY} DESTINATION ObjectCube/plugin/${NAME}
	DIRECTORY_PERMISSIONS 
		OWNER_WRITE OWNER_READ OWNER_EXECUTE
		GROUP_WRITE GROUP_READ GROUP_EXECUTE
		WORLD_WRITE WORLD_READ WORLD_EXECUTE
)
