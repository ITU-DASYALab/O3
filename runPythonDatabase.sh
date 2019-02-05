cd PhotoCube

rm -f ObjectCubePython.so

cd ../PythonWrapper/

make clean

make

cd ../SetupObjectCubePostgreSQL/

g++ main.cpp -lpqxx -lpq

./a.out

cd ../PhotoCube/

python laugavegur_hierarchy_creation.py

python createDatabase.py

cd ../SetupObjectCubePostgreSQL/Materlizedview/

g++ main.cpp -lpqxx -lpq

./a.out