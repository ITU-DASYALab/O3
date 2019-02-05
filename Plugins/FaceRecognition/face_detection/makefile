CC = g++
CFLAGS=-Wall -arch i386
IFLAGS=-I../opencv/include/opencv2
LFLAGS=-L../opencv/lib/ -lm -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_objdetect 

all: facexcdl ofacex facexcdldy libfacexdy 

ofacex:  
	$(CC) $(CFLAGS) -shared $(IFLAGS) $(LFLAGS) RegionOfInterest.cpp FaceDetector.cpp -o facedetector.o

facexcdl: ofacex
	$(CC) $(CFLAGS) $(LFLAGS) $(IFLAGS) facedetector.o FaceExtractor.cpp -o faceextractor

libfacexdy:
	$(CC) $(CFLAGS) -dynamiclib -current_version 1.0 facedetector.o -o libfacex.dylib

facexcdldy: libfacexdy
	$(CC) $(CFLAGS) -lfacex -L. $(LFLAGS) $(IFLAGS) -I. RegionOfInterest.cpp FaceDetector.cpp FaceExtractor.cpp -o faceextractordy

clean:
	rm *.o *.dylib faceextractor faceextractordy

asclean:
	rm *~
