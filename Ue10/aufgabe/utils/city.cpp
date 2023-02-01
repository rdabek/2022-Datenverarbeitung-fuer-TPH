#include "city.hpp"

#include <cmath>

namespace mycity {
    City::City(const std::string& name) {
        this->name = name;
    }

    City::City(const std::string& name, const Coords& longitude, const Coords& latitude) {
        this->name = name;
        this->latitude = latitude;
        this->longitude = longitude;
    }

    auto City::getName() const -> std::string {
        return name;
    }

    auto City::getLatitude() const -> Coords {
        return latitude;
    }
            
    auto City::getLongitude() const -> Coords {
        return longitude;
    }

    auto getAngleGrad(const Coords& coord) -> double {
        if(coord.dir == Direction::W || coord.dir == Direction::S)
            return -(coord.deg + coord.min/60.0);
        return coord.deg + coord.min/60.0;
    }

    auto getAngle(const Coords& coord) -> double {
        return getAngleGrad(coord) * M_PI / 180.0;
    }

    auto operator-(const City& a, const City& b) -> double {
        return EARTH_RADIUS * std::acos(
            std::sin(getAngle(a.getLongitude())) * std::sin(getAngle(b.getLongitude()))
            + std::cos(getAngle(a.getLongitude())) * std::cos(getAngle(b.getLongitude()))
            * cos(getAngle(b.getLatitude()) - getAngle(a.getLatitude()))
        );
    }
}