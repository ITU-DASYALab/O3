## O3

This page details the steps required to build O3.  

Note: This text assumes the Ubuntu 16.04 operating system. You will, at times, need super-user credentials.

## Step 0: Get the Code

Clone the source, for example by pressing "Clone" above and copy-pasting the link, or using the commands below:

	git clone https://github.itu.dk/sngi/ObjectCubeMaster.git

## Step 1: Install 03

	cd ObjectCubeMaster
	bash buildObjectCube.sh

## Step 2: Run P3

	cd PhotoCube
	python Runner.py

## Step 3: Install test database

	bash runPresentation.sh

To reset the database run:

	bash setupDatabase.sh
