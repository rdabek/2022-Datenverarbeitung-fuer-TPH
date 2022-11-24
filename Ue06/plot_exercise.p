set terminal png size 600*1.61803, 600

# Plot the probability values
set output 'Probability.png'
set title 'The probability of having a birthsday on the same day'
set grid
plot    "~/Ue06/plots/GebParadoxon.dat" u 1:2 w l