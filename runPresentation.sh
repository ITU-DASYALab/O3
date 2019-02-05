cd SetupObjectCubePostgreSQL

g++ main.cpp -lpqxx -lpq

./a.out

cd ../PhotoCube/

python presentation_hierarchy_creation.py

python createPresentationDatabase.py

cd ../SetupObjectCubePostgreSQL/Materlizedview/

g++ main.cpp -lpqxx -lpq

./a.out
