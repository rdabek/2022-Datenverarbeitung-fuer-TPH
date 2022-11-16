set terminal png size 600*1.61803, 600

# Plot the Avg values
set output 'CalculatedAvg.png'
set title 'Average in cumulative blocks of 50 values'
set grid
plot    "~/Ue04/plots/calculated.dat" using 1:2 w lines

# Plot the StdDev values
set output 'CalculatedStdDev.png'
set title 'Standard Deviation in cumulative blocks of 50 values'
set grid
plot    "~/Ue04/plots/calculated.dat" using 1:3 w lines

# Plot the AvgError values
set output 'CalculatedAvgError.png'
set title 'Average Error in cumulative blocks of 50 values'
set grid
plot    "~/Ue04/plots/calculated.dat" using 1:4 w lines