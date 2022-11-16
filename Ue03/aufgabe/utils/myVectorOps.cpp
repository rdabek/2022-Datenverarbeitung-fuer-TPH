#include "myVectorOps.hpp"

#include <cmath>
#include <iostream>

namespace myvectorops {

    auto Vector3d::toString() -> std::string {
        using namespace std;
        auto ret = std::string();
        ret += "[ "
            + to_string(p[0]) + ", "
            + to_string(p[1]) + ", "
            + to_string(p[2])
            + " ]";
        return ret;
    }

    auto Vector3d::operator+(Vector3d other) -> Vector3d {
        auto ret = p;
        ret[0] += other.p[0];
        ret[1] += other.p[1];
        ret[2] += other.p[2];
        return ret;
    }

    auto Vector3d::operator-(Vector3d other) -> Vector3d {
        auto ret = p;
        ret[0] -= other.p[0];
        ret[1] -= other.p[1];
        ret[2] -= other.p[2];
        return ret;
    }

    auto Vector3d::operator*(Scalar s) -> Vector3d {
        auto ret = p;
        ret[0] *= s;
        ret[1] *= s;
        ret[2] *= s;
        return ret;
    }

    auto Vector3d::operator*(Vector3d other) -> Scalar {
        return p[0] * other.p[0]
            + p[1] * other.p[1]
            + p[2] * other.p[2];
    }

    auto Vector3d::x(Vector3d other) -> Vector3d {
        auto ret = p;
        ret[0] = p[1]*other.p[2]-p[2]*other.p[1];
        ret[1] = p[2]*other.p[0]-p[0]*other.p[2];
        ret[2] = p[0]*other.p[1]-p[1]*other.p[0];
        return ret;
    }

    auto Vector3d::length() -> Scalar {
        using namespace std;
        return sqrt(
            p[0] * p[0]
            + p[1] * p[1]
            + p[2] * p[2]
        );
    }

    auto calculateTetraederVolume(Scalar r, Angle a) -> Scalar {
        using namespace std;
        auto ang = a*M_PI/180.0;
        auto vecA = Vector3d{Point3d{r*sin(ang), 0.0, -r*cos(ang)}};
        auto vecB = Vector3d{Point3d{r*cos(ang), r*sin(ang), 0.0}};
        auto vecC = Vector3d{Point3d{0.0, r*cos(ang), -r*sin(ang)}};

        cout << "vec0->A: " << vecA << ", length: " << vecA.length() << "\n";
        cout << "vec0->B: " << vecB << ", length: " << vecB.length() << "\n";
        cout << "vec0->C: " << vecC << ", length: " << vecC.length() << "\n";

        return 1.0/6.0*(abs((vecA.x(vecB))*vecC));
    }

    auto calculateTetraederSurface(Scalar r, Angle a) -> Scalar {
        using namespace std;
        auto ang = a*M_PI/180.0;
        auto vecA = Vector3d{Point3d{r*sin(ang), 0.0, -r*cos(ang)}};
        auto vecB = Vector3d{Point3d{r*cos(ang), r*sin(ang), 0.0}};
        auto vecC = Vector3d{Point3d{0.0, r*cos(ang), -r*sin(ang)}};
        auto vecAB = vecB - vecA;
        auto vecAC = vecC - vecA;

        cout << "vec0->A: " << vecA << ", length: " << vecA.length() << "\n";
        cout << "vec0->B: " << vecB << ", length: " << vecB.length() << "\n";
        cout << "vec0->C: " << vecC << ", length: " << vecC.length() << "\n";
        cout << "vecA->B: " << vecAB << ", length: " << vecAB.length() << "\n";
        cout << "vecA->C: " << vecAC << ", length: " << vecAC.length() << "\n";

        return 1.0/2.0*vecA.x(vecB).length()
            + 1.0/2.0*vecA.x(vecC).length()
            + 1.0/2.0*vecB.x(vecC).length()
            + 1.0/2.0*vecAB.x(vecAC).length();
    }

}