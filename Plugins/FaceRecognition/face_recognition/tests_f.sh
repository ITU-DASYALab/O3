#!/bin/sh

# File name: tests.sh
# Date:      2011-09-09 13:43
# Author:    Kristján Rúnarsson


./facerectest -f -t file_lists/train_all_1-9.txt -r file_lists/test_all_5-5.txt
./facerectest -f -t file_lists/train_all_2-8.txt -r file_lists/test_all_5-5.txt
./facerectest -f -t file_lists/train_all_3-7.txt -r file_lists/test_all_5-5.txt
./facerectest -f -t file_lists/train_all_4-6.txt -r file_lists/test_all_5-5.txt
./facerectest -f -t file_lists/train_all_5-5.txt -r file_lists/test_all_5-5.txt
