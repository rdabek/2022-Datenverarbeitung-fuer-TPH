#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace myvectorops {

    using Point3d = std::vector<double>;

    using Scalar = double;

    using Angle = double;

    class Vector3d {
        public:
            Vector3d() {
                p = Point3d{0.0, 0.0, 0.0};
            }

            Vector3d(Point3d p) {
                this->p = p;
            }

            auto toString() -> std::string;           // Scalar multiplication

            auto operator+(Vector3d other) -> Vector3d;     // Vector addition
            
            auto operator-(Vector3d other) -> Vector3d;     // Vector subtraction

            auto operator*(Scalar scalar) -> Vector3d;      // Scalar multiplication
            
            auto operator*(Vector3d other) -> Scalar;       // Scalar multiplication

            auto x(Vector3d other) -> Vector3d;             // Crossproduct

            auto length() -> Scalar;                        // Vector Length

        private:
            Point3d p;
    };

    inline auto operator<<(std::ostream& os, Vector3d v) -> std::ostream&
    {
        os << v.toString();
        return os;
    }
    
    auto calculateTetraederVolume(Scalar r, Angle a) -> Scalar;

    auto calculateTetraederSurface(Scalar r, Angle a) -> Scalar;

}