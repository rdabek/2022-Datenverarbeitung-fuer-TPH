#pragma once

#include <vector>

namespace mypolyops {

    auto Basispolynom(const int& i, const double& x, const std::vector<double>& xm) -> double;

    auto Stuetzstellen(const double& x0, const double& xm, const int& n) -> std::vector<double>;

    auto Polynom(const double& x, const std::vector<double>& xm, const std::vector<double>& ym) -> double;

    auto Nullstelle(const std::vector<double>& xm, const std::vector<double>& ym, const double& epsilon) -> double;
}