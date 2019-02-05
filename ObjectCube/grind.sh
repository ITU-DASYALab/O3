#!/bin/sh

valgrind --tool=memcheck -v --leak-check=full --show-reachable=yes --num-callers=15 --show-reachable=yes --track-fds=yes --track-origins=yes --read-var-info=yes ~/temp/trunk/trunk/ObjectCube/ObjectCubeMakeGenerated -language 2 -dataAccessType 3 -unitTestObjectPath /Users/grimurtomasson/Dropbox/SQLite/UnitTest/ -outputDebugInfo 1 -SQLite /Users/grimurtomasson/temp/trunk/trunk/ObjectCube/Database/ObjectCubeDB
