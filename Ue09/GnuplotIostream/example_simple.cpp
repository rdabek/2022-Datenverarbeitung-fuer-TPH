// Simple test of C++/gnuplot interface

#include <iostream>
#include <cmath>
#include "gnuplot-iostream.h" //gnuplot interface

int main()
{
  Gnuplot gp;   //gnuplot object

  // commmands are simply parsed to Gnuplot object via <<
  gp << "plot sin(x)/x \n"; //dont forget newline

  //  pause_if_needed();

  return 0;
}

