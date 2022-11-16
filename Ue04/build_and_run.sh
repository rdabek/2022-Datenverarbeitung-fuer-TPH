mkdir -p aufgabe/build
cd aufgabe/build
cmake -G "Unix Makefiles" ..
cmake --build .
echo
echo "Program output:"
./aufgabe
cd ~/Ue04/plots
gnuplot ~/Ue04/plot_exercise.p