#include "utils/myStringOps.hpp"

#include <iostream>

using namespace mystringops;

int main() {
    constexpr auto name = "Surname Name";

    // Note this is very ineficient, as the functions have to be called multiple times for nothing,
    // but not using variables in this case is very compact
    std::cout << name << "\n";
    std::cout << removeCharacter(name, ' ') << "\n";
    std::cout << toLower(removeCharacter(name, ' ')) << "\n";
    std::cout << sortAscending(toLower(removeCharacter(name, ' '))) << "\n";

    return 0;
}