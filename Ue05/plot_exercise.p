set terminal png size 600*1.61803, 600

# Plot the x interpolation values
set output 'InterpolationX.png'
set title 'The interpolation of x'
set grid
plot    "~/Ue05/plots/Polynominterpol.dat" u 1:3 w l, \
        "~/Ue05/vertikal.dat" u 1:3 w p pt 7 ps 1.5

# Plot the z interpolation values
set output 'InterpolationZ.png'
set title 'The interpolation of z'
set grid
plot    "~/Ue05/plots/Polynominterpol.dat" u 1:2 w l, \
        "~/Ue05/vertikal.dat" u 1:2 w p pt 7 ps 1.5

# Plot the 3d path
set output '3dpath.png'
set title 'The interpolated path in 3d'
set xlabel "t[s]" offset 0, -1, 1
set ylabel "x[m]" offset 0, -1, 0
set zlabel "z[m]" offset -3, 0, 0
splot   "~/Ue05/plots/Polynominterpol.dat" using 1:3:2 w lines, \
        "~/Ue05/plots/endpunkt.dat" using 1:3:2 w p pt 7 ps 1.5