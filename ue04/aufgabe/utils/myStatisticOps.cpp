#include "myStatisticOps.hpp"
#include <cmath>

namespace mystatisticops {

    auto avg(const std::vector<double> &data) -> double {
        double sum = 0.0;
        for(const auto& x : data)
            sum += x;
        return sum/data.size();
    }

    auto stdDev(const std::vector<double> &data) -> double {
        const double average = avg(data);
        double sum = 0.0;
        for(const auto &x : data) {
            double diff = x - average;
            sum += diff * diff;
        }
        return std::sqrt(sum/(data.size() - 1));
    }

    auto avgErr(const std::vector<double> &data) -> double {
        return stdDev(data)/std::sqrt(data.size());
    }

}