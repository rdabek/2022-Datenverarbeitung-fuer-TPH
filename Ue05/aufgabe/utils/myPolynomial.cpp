#include "myPolynomial.hpp"
#include <cassert>
#include <cmath>
#include <iostream>

namespace mypolyops {

    auto Basispolynom(const int& i, const double& x, const std::vector<double>& xm) -> double {
        double ret = 1.0;
        for(int j=0; j<(int)xm.size(); j++) {
            if(i==j)
                continue;
            ret *= (x - xm[j])/(xm[i]-xm[j]);
        }
        return ret;
    }

    auto Stuetzstellen(const double& x0, const double& xm, const int& n) -> std::vector<double> {
        std::vector<double> ret;
        auto h = (xm-x0)/(double)n;
        for(int i=0; i<=n; i++)
            ret.push_back(x0 + i*h);
        return ret;
    }

    auto Polynom(const double& x, const std::vector<double>& xm, const std::vector<double>& ym) -> double {
        assert(xm.size() == ym.size());
        double ret = 0.0;
        for(int i=0; i<(int)xm.size(); i++) {
            ret += ym[i] * Basispolynom(i, x, xm);
        }
        return ret;
    }

    auto Nullstelle(const std::vector<double>& xm, const std::vector<double>& ym, const double& epsilon) -> double {
        // Searching z=0
        double xMin = xm[0], xMax;
        for(xMax=xMin; ; xMax+=1.0)
            if(Polynom(xMax, xm, ym)<0.0)           // Find y(x) < 0
                break;
        
        // Bisection Algorithm
        double x0;
        while(std::abs(xMax - xMin) > epsilon) {
            x0 = xMin + (xMax-xMin)/2;              // Notice (xMax+xMin)/2 can lead to a overflow bug,
                                                    // it's known, because it happened in java history...
                                                    // (here it won't be the case because the numbers are too small but still...)
            if(Polynom(xMin, xm, ym)*Polynom(x0, xm, ym) < 0)
                xMax = x0;
            else
                xMin = x0;
        }
        return x0;
    }

}