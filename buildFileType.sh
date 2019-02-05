#!/bin/bash 
    
cd Plugins/FileType/
cmake .
make
sudo cp -i libFileType_Plugin.so /usr/local/lib/

