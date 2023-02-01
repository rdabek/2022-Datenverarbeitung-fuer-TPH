#include "utils/city.hpp"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <regex>
#include <set>
#include <string>

using namespace mycity;

auto convertStrToDir(const std::string& dir) -> Direction {
    if(dir == "N")
        return Direction::N;
    else if(dir == "S")
        return Direction::S;
    else if(dir == "O")
        return Direction::O;
    else if(dir == "W")
        return Direction::W;
    else
        std::abort();
}

auto convertDirToStr(const Direction& dir) -> std::string {
    if(dir == Direction::N)
        return "N";
    else if(dir == Direction::S)
        return "S";
    else if(dir == Direction::O)
        return "O";
    else if(dir == Direction::W)
        return "W";
    else
        std::abort();
}

auto cmp(City a, City b) -> bool {
    return a < b;
}

auto loadCities(std::filesystem::path infile) -> std::set<City, decltype(&cmp)> {
    std::set<City, decltype(&cmp)> cities(cmp);

    std::ifstream input(std::filesystem::weakly_canonical(infile));
    if(input)
        std::cout << "Sucessfully loaded file: '" << std::filesystem::weakly_canonical(infile).c_str() << "'!\n";
    else
        std::cout << "Couldn't load file: '" << std::filesystem::weakly_canonical(infile).c_str() << "'!\n";

    std::string line;
    while(std::getline(input, line)) {
        std::string name;

        name = line.c_str();

        if(!std::getline(input, line))
            break;
        std::stringstream stream1(line);
        

        double latDeg, latMin;
        std::string latDir;
        stream1 >> latDeg >> latMin >> latDir;
        auto latitude = Coords{latDeg, latMin, convertStrToDir(latDir)};

        if(!std::getline(input, line))
            break;
        std::stringstream stream2(line);
        
        double longDeg, longMin;
        std::string longDir;
        stream2 >> longDeg >> longMin >> longDir;
        auto longitude = Coords{longDeg, longMin, convertStrToDir(longDir)};

        auto city = City(name, latitude, longitude);
        cities.emplace(city);
    }

    return cities;
}

auto main() -> int {
    auto cities = loadCities("../../staedte.dat");

    auto wienItr = cities.find({"Wien"});
    if(wienItr == cities.end()) {
        std::cout << "Didn't find Wien!\n";
        std::abort();
    }
    auto wien = (*wienItr);

    for(const auto& city : cities) {
        if(city == wien)
            continue;
        std::cout << (wien - city) << " km - " << city.getName() << " (" << getAngleGrad(city.getLongitude()) << "° " << convertDirToStr(city.getLongitude().dir)
            << " / "  << getAngleGrad(city.getLatitude()) << "° " << convertDirToStr(city.getLatitude().dir) << ")\n";
    }

    auto itrCity = (*cities.find({"Wien"}));
    std::vector<City> aroundTheWorld = {
        {"Shanghai"},
        {"Tokio"},
        {"Sydney"},
        {"Honolulu"},
        {"New York City"},
        {"Santiago de Chile"},
        {"Buenos Aires"},
        {"Kapstadt"},
        {"Kairo"},
        {"Wien"}
    };

    double distance = 0.0;
    for(const auto& city : aroundTheWorld) {
        auto newCity = (*cities.find(city));
        distance += itrCity - newCity;
        itrCity = newCity;
    }
    
    std::cout << "Distance trip: " << distance << " km\n";

    return 0;
}