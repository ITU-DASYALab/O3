cd SetupObjectCubePostgreSQL

g++ main.cpp -lpqxx -lpq

./a.out

cd ../PhotoCube/

python laugavegur_hierarchy_creation_en.py

python createLaugavegurPresentationDatabase.py

cd ../SetupObjectCubePostgreSQL/Materlizedview/

g++ main.cpp -lpqxx -lpq

./a.out
