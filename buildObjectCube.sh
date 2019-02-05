#!/bin/bash 
 
function setupPostgresUbuntu16()
{
    echo "---- Start Install PostgresSQL 10 ----"
 
    wget --quiet -O - https://www.postgresql.org/media/keys/ACCC4CF8.asc | sudo apt-key add -
 
    echo "deb http://apt.postgresql.org/pub/repos/apt/ xenial-pgdg main" | sudo tee /etc/apt/sources.list.d/pgdg.list
 
    apt update
 
    apt install -y postgresql-10
 	
    apt-get install -y postgresql-10-postgis-2.4
 
    wget http://pqxx.org/download/software/libpqxx/libpqxx-4.0.tar.gz
    tar xvfz libpqxx-4.0.tar.gz
    cd libpqxx-4.0
    ./configure
    make
    make install
 
    apt-get install -y libpq-dev
    apt-get install -y libpqxx-dev
 
    echo "---- Done Install PostgresSQL 10 ----"   
}
 
function setupPostgresUbuntu18()
{
echo "---- Start Install PostgresSQL 10 ----"
 
    wget --quiet -O - https://www.postgresql.org/media/keys/ACCC4CF8.asc | sudo apt-key add -
 
    echo "deb http://apt.postgresql.org/pub/repos/apt/ bionic-pgdg main" | sudo tee /etc/apt/sources.list.d/pgdg.list
 
    apt update
 
    apt install -y postgresql-10
 
    apt-get install -y postgis
 
    wget http://pqxx.org/download/software/libpqxx/libpqxx-4.0.tar.gz
    tar xvfz libpqxx-4.0.tar.gz
    cd libpqxx-4.0
    ./configure
    make
    make install
 
    apt-get install -y libpq-dev
    apt-get install -y libpqxx-dev
 
    echo "---- Done Install PostgresSQL 10 ----"   
}

function setupObjectCubeUbuntu()
{
    echo "---- Start Create PostgresSQL user and database ----"
      
    sudo adduser object --gecos "First Last,RoomNumber,WorkPhone,HomePhone" --disabled-password
      
    sudo -u postgres psql -c "CREATE USER object WITH PASSWORD 'object';"
 
    sudo -u postgres psql -c "ALTER USER object WITH SUPERUSER;"
 
    sudo -u postgres createdb objectcube
      
    echo "---- Done Create PostgresSQL user and database ----"
 
    echo "---- Start Build ObjectCube ----"
 
    cd ObjectCube
 
    apt-get install -y cmake
    apt install -y g++
    apt-get install -y cxxtest
 
    cmake .
    make

    sudo apt-get install imagemagick
    
    sudo apt-get install libmagick++-dev  

 
    echo "---- End Build ObjectCube ----"
 
    echo "---- Start Install Python Wrapper ----"
 
    apt-get install -y python
 
    apt-get install -y libboost-all-dev
 
    cd ../PythonWrapper
    make
 
    echo "---- Done Install Python Wrapper ----"
 
    echo "---- Start Build PhotoCube ----"
 
    sudo apt install -y nvidia-cg-toolkit 
 
    apt install -y python-pip
 
    apt install -y python-pil 
 
    pip2 install panda3d==1.9.4
 
    -H pip install pillow
 
    apt install -y python-wand libmagickwand-dev
 
    -H pip install Wand
 
    echo "---- Done Build PhotoCube ----"
}

function setupPluginUbuntu()
{
    sudo apt-get install libexiv2-dev
    
    cd ../Plugins/Color/
    cmake .
    make
    sudo cp -i libColor_Plugin.so /usr/local/lib/
	
    cd ../EXIF/ 
    cmake .  
    make
    sudo cp -i libEXIF_Plugin.so /usr/local/lib/

    cd ../FileType/
    cmake .
    make
    sudo cp -i libFileType_Plugin.so /usr/local/lib/

    cd ../Text/
    cmake .
    make
    sudo cp -i libText_Plugin.so /usr/local/lib/
    
}

function setupPostgresMac()
{
    echo "---- Start Install PostgresSQL 10 ----"
    
    sudo ruby -e "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/master/install)" < /dev/null 2> /dev/null
    brew install postgresql
    brew install postgis
    
    
    brew install libpqxx
    brew install libpq
    
    pg_ctl -D /usr/local/var/postgres -l /usr/local/var/postgres/server.log start

    echo "---- Done Install PostgresSQL 10 ----" 
}

function setupObjectCubeMac()
{
    echo "---- Start Create PostgresSQL user and database ----"
    
    sudo sysadminctl -addUser object -password
      
    psql postgres -c "CREATE USER object WITH PASSWORD 'object';"
 
    psql postgres -c "ALTER USER object WITH SUPERUSER;"

    createdb objectcube
    
    echo "---- Done Create PostgresSQL user and database ----"
}

function buildObjectCubeMac()
{
    echo "---- Start Build ObjectCube ----"
 
    cd ObjectCube
 
    brew install cmake
    brew install gcc
    brew install cxxtest

    
    sudo cmake .
    sudo make
 
    echo "---- End Build ObjectCube ----"
}

function buildPythonWrapperMac()
{
    echo "---- Start Install Python Wrapper ----"

    echo "brew install python"

    echo "brew install boost --with-python"

    echo "brew install boost-python --with-python3"
 
    cd PythonWrapper
    make clean
    make all
 
    echo "---- Done Install Python Wrapper ----"
}

function buildPhotoCubeMac()
{
    echo "---- Start Install PhotoCube ----"
 
    pip install panda3d==1.9.4
 
    pip install pillow

    brew install imagemagick@6

    ln -s /usr/local/Cellar/imagemagick@6/6.9.10-14/lib/libMagickWand-6.Q16.dylib /usr/local/lib/libMagickWand.dylib

    sudo pip install Wand
 
    echo "---- Done Install PhotoCube ----"
}

function setupDatabase()
{
	echo "---- Start Setup database ----"
	
	cd ../SetupObjectCubePostgreSQL/

	g++ main.cpp -lpqxx -lpq

	./a.out
	
	echo "---- Done Setup database ----"
}
  
function versionLinux()
{
    if [[ $EUID > 0 ]]; then # we can compare directly with this syntax.
        echo "Please run as root/sudo"
        exit 1
    fi
    version=$(lsb_release -rs)
    echo "Version $version"
    if [[ $version == "16.04" ]]; then
        setupPostgresUbuntu16
        setupObjectCubeUbuntu
	setupDatabase
	setupPluginUbuntu
    elif [[ $version == "18.04" ]]; then
        setupPostgresUbuntu18
        setupObjectCubeUbuntu
	setupDatabase
	setupPluginUbuntu
    else
        echo "Only supported for Ubuntu 16.04 and Ubuntu18.04"
        exit 1
    fi
}

function Mac()
{
    echo "Mac"
    setupPostgresMac
    setupObjectCubeMac
    buildObjectCubeMac
    buildPythonWrapperMac
    buildPhotoCubeMac
    setupPluginUbuntu
} 
 
OS=$(uname)
 
echo "OS $OS"
 


    if [[ $OS == "Linux" ]]; then
        versionLinux
    elif [[ $OS == "Darwin" ]]; then
	Mac
    else
        echo "Only supported for Linux"
        exit 1
    fi
