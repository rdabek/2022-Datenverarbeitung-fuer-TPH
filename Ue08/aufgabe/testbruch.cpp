#include <iostream>
#include <stdexcept>
#include "utils/bruch.hpp"

int main()
{
  bruch p, q, r, s;

  try
  {
    q = bruch(3, 2);
    s = bruch("1/4");
    r = bruch(1, 0);
  }

  catch (const std::runtime_error &err)
  {
    std::cout << err.what() << std::endl;
  }

  p = q*3;
  std::cout << "p = " << p << " = " << p.get_x() << std::endl;

  try
  {
    p.set_n(0);
  }
  catch (const std::runtime_error &err)
  {
    std::cout << err.what() << std::endl;
  }

  p += s;
  std::cout << "pneu:\n";
  p.show(std::cout);

  q = p + s;
  std::cout << "qneu:\n";
  q.show(std::cout);

  std::cout << "Gekürzt:\n";
  std::cout << "p = " << p.reduce() << '\n';
  std::cout << "q = " << q.reduce() << std::endl;
 
  p = bruch(1, 3);
  q = bruch(1, 6);
  s = p + q;
  std::cout << p << " + " << q << " = " << s << " = ";
  std::cout << s.reduce() << std::endl;

  return 0;
}
