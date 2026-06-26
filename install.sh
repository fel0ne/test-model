rm -rf build
mkdir build
cmake -S . -B build
cmake --build build -j 6
cd build
./main