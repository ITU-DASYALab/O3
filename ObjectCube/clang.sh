rm -rf CMakeCache* CMakeFiles*;
scan-build --use-c++=clang++ make -j 16;
