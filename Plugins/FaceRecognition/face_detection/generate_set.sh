#!/bin/sh

# File name: generate_set.sh
# Date:      2011-10-11 11:25
# Author:    Kristján Rúnarsson

INDEX=1

find "/Users/kristjanr/Desktop/Test sets/Set 2" -name "*.JPG" | while read i
do 
	#./faceextractor -d blah -i $INDEX "$i"
	#echo "$i"
	./faceextractor -d extracted -i $INDEX "$i"
	INDEX=$(($INDEX+1))
done
IFS=$SAVEIFS

