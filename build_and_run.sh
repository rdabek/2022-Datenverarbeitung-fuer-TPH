rm -r ueXX/build
mkdir -p ueXX/build
cd ueXX/build
cmake -G "Unix Makefiles" ..
cmake --build .
echo
echo "Program output:"
./aufgabe