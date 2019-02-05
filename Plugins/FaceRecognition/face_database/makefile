CC=g++ -Wall -arch i386

IFLAGS=-I /opt/local/include/ -I /usr/local/include/opencv2/ 
LFLAGS=-L /usr/local/lib/ -l sqlite3 -lopencv_core -lopencv_imgproc -lopencv_highgui  

all:
	$(CC) $(LFLAGS) $(IFLAGS) MySQLite.cpp Face.cpp Person.cpp testfacedb.cpp -o testfacedb
