#include "MathOperations.hpp"

#include <iostream>
#include <typeinfo>

using namespace myMathOperations;

// Overcomplicate Much
int main() {
    {
        using MyType = int;
        std::cout << "Aufgabe 1, " << typeid(MyType).name() << "\n";
        MyType nenner = 2;
        for(MyType zaehler=4; zaehler>=1; zaehler--)
            std::cout << "Zaehler: " << zaehler << ", Vergleich: " << Math::divide<MyType>(zaehler, nenner) * nenner << "\n";
    }

    {
        using MyType = float;
        std::cout << "Aufgabe 1, " << typeid(MyType).name() << "\n";
        MyType nenner = 2;
        for(MyType zaehler=4; zaehler>=1; zaehler--)
            std::cout << "Zaehler: " << zaehler << ", Vergleich: " << Math::divide<MyType>(zaehler, nenner) * nenner << "\n";
    }

    {
        using MyType = double;
        std::cout << "Aufgabe 1, " << typeid(MyType).name() << "\n";
        MyType nenner = 2;
        for(MyType zaehler=4; zaehler>=1; zaehler--)
            std::cout << "Zaehler: " << zaehler << ", Vergleich: " << Math::divide<MyType>(zaehler, nenner) * nenner << "\n";
    }


    return 0;
}