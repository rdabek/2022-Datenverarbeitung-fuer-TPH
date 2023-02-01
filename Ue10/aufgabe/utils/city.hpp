#pragma once

#include <string>

namespace mycity {

    inline double EARTH_RADIUS = 6370.0;

    enum Direction {
        N,
        S,
        O,
        W
    };

    struct Coords {
        public:
            double deg;
            double min;
            Direction dir;
    };

    struct City {
        public:
            City() = default;

            City(const std::string& name);

            City(const std::string& name, const Coords& longitude, const Coords& latitude);

            auto getName() const -> std::string;

            auto getLatitude() const -> Coords;

            auto getLongitude() const -> Coords;

            inline auto operator<(const City& other) -> bool {
                return this->name < other.name;
            }

        private:
            Coords latitude;
            Coords longitude;

            std::string name;
    };

    auto getAngleGrad(const Coords& coord) -> double;

    auto operator-(const City& a, const City& b) -> double;
    
    inline auto operator==(const City& a, const City& b) -> bool {
        return a.getName() == b.getName();
    }
}