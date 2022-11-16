#include "utils/myVectorOps.hpp"

#include <iostream>
#include <cmath>

using namespace myvectorops;

int main() {
    auto r = Scalar(10);
    auto a = Angle(45);

    auto ang = a*M_PI/180.0;
    auto vecA = Vector3d{Point3d{r*sin(ang), 0.0, -r*cos(ang)}};

    std::cout << "vec0->A: " << vecA << ", length: " << vecA.length() << "\n\n";

    std::cout << "Expected value: " << std::pow(vecA.length(), 3)*std::sqrt(2.0)/12.0
        << ", Calculated value:\n" << calculateTetraederVolume(r, a) << "\n\n";
    
    std::cout << "Expected value: " << std::pow(vecA.length(), 2)*std::sqrt(3.0)
        << ", Calculated value:\n" << calculateTetraederSurface(r, a) << "\n";

    return 0;
}