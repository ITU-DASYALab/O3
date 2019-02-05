CC = g++
CFLAGS=-Wall -arch i386
IFLAGS=-I/usr/local/include/opencv -I /opt/local/include
LFLAGS=-lm -lopencv_core -lopencv_highgui -lopencv_imgproc -lopencv_objdetect -larmadillo

all:  frtest

recimage:
	$(CC) $(CFLAGS) -shared $(IFLAGS) $(LFLAGS) RecImage.cpp -o recimage.o

imagelist: recimage
	$(CC) $(CFLAGS) -shared $(IFLAGS) $(LFLAGS) recimage.o ImageList.cpp -o imagelist.o

recognizer:
	$(CC) $(CFLAGS) -shared $(IFLAGS) $(LFLAGS) imagelist.o Recognizer.cpp -o recognizer.o

eigenfaces: imagelist recognizer
	$(CC) $(CFLAGS) -shared $(IFLAGS) $(LFLAGS) recimage.o imagelist.o recognizer.o Eigenfaces.cpp -o eigenfaces.o

lda: imagelist
	$(CC) -framework Accelerate $(CFLAGS) -shared $(IFLAGS) $(LFLAGS) recimage.o imagelist.o LDA.cpp -o lda.o

ldatest: lda 
	$(CC) $(CFLAGS) $(IFLAGS) $(LFLAGS) recimage.o imagelist.o lda.o ldatest.cpp -o ldatest 

fisherfaces: lda imagelist recognizer
	$(CC) $(CFLAGS) -shared $(IFLAGS) $(LFLAGS) recimage.o imagelist.o recognizer.o Fisherfaces.cpp lda.o -o fisherfaces.o

frtest: eigenfaces fisherfaces
	$(CC) $(CFLAGS) $(LFLAGS) $(IFLAGS) recimage.o imagelist.o eigenfaces.o fisherfaces.o FaceRecTest.cpp -o facerectest

conv: imagelist
	$(CC) $(CFLAGS) $(LFLAGS) $(IFLAGS) recimage.o imagelist.o pgm2png.cpp -o pgm2png

clean:
	rm *.o facerectest ldatest pgm2png
