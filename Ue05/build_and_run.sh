mkdir -p aufgabe/build
mkdir -p ~/Ue05/plots
cd aufgabe/build
cmake -G "Unix Makefiles" ..
cmake --build .
echo
echo "Program output:"
./aufgabe
cd ~/Ue05/plots
gnuplot ~/Ue05/plot_exercise.p