rm -r aufgabe/build
mkdir -p aufgabe/build
cd aufgabe/build
cmake -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles" ..
cmake --build .
echo
echo "Program output:"
./aufgabe
cd ~/Ue11/plots
gnuplot ~/Ue11/figspdf.gp