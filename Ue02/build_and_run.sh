mkdir -p aufgabe/build
cd aufgabe/build
cmake -G "Unix Makefiles" ..
cmake --build .
echo
echo "Program output:"
./aufgabe