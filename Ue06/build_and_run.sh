rm -r aufgabe/build
mkdir -p aufgabe/build
mkdir -p ~/Ue06/plots
cd aufgabe/build
cmake -DCMAKE_BUILD_TYPE=Debug -G "Unix Makefiles" ..
cmake --build .
echo
echo "Program output:"
./aufgabe
cd ~/Ue06/plots
gnuplot ~/Ue06/plot_exercise.p