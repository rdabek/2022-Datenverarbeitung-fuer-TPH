#pragma once

#include <vector>

namespace mystatisticops {

    auto avg(const std::vector<double> &data) -> double;

    auto stdDev(const std::vector<double> &data) -> double;

    auto avgErr(const std::vector<double> &data) -> double;
}