#!/bin/sh



#delete products
echo Cleaning
make clean

#build
echo Building
make all

#Copy .so 
echo Copying .so
cp -f *.so ../ObjectCube
