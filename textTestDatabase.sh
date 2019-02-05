cd PhotoCube

rm -f ObjectCubePython.so

cd ../PythonWrapper/

make

cd ../Plugins/Text

cmake . 

make

cd ../../SetupObjectCubePostgreSQL

g++ main.cpp -lpqxx -lpq

./a.out

cd ../PhotoCube/

python createTextPluginDatabase.py

#cd ../SetupObjectCubePostgreSQL/Materlizedview/

#g++ main.cpp -lpqxx -lpq

#./a.out
