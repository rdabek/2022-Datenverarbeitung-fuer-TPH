#include "utils/figures.hpp"
#include "utils/gnuplot-iostream.h"

#include <iostream>
#include <fstream>
#include <filesystem>
#include <regex>

using namespace geometric;

auto splitString(const std::string& str, char delimiter) -> std::vector<std::string> {
    std::vector<std::string> splitString;
    std::string part;
    std::stringstream lineStream(str);
    while(std::getline(lineStream, part, delimiter)) {
        splitString.push_back(part);
    }

    return splitString;
}

auto parseEck(std::ifstream& in, int n, const std::string& name) -> std::pair<std::unique_ptr<Figure>, std::pair<double, double>> {
    std::string line;
    std::smatch match;

    std::vector<std::pair<double, double>> input;
    std::pair<double, double> delta;

    int count = 0;
    while(std::getline(in, line)) {
        if(!std::regex_match(line, match, std::regex("^[+-]?([0-9]+([.][0-9]*)?|[.][0-9]+) [+-]?([0-9]+([.][0-9]*)?|[.][0-9]+)$")))
            break;
        
        std::cout << line << "\n";
        
        auto numbers = splitString(line, ' ');
        delta = {std::atof(numbers.at(0).c_str()), std::atof(numbers.at(1).c_str())};
        input.push_back(delta);

        if(count++ > n)
            break;
    }
    input.pop_back();

    auto fig = std::unique_ptr<Figure>(new nEck(name, input));

    return {std::move(fig), delta};
}

auto parseKreis(std::ifstream& in, const std::string& name) -> std::pair<std::unique_ptr<Figure>, std::pair<double, double>> {
    double x, y, z;
    in >> x >> y >> z;
    double dx, dy;
    in >> dx >> dy;

    std::cout << "x: " << x << ", y: " << y << ", z: " << z << "\n";

    auto fig = std::unique_ptr<Figure>(new Kreis(name, x, y, z));

    return {std::move(fig), {dx, dy}};
}

auto parseStern(std::ifstream& in, const std::string& name) -> std::pair<std::unique_ptr<Figure>, std::pair<double, double>> {
    double x, y, z;
    in >> x >> y >> z;
    double dx, dy;
    in >> dx >> dy;

    std::cout << "x: " << x << ", y: " << y << ", z: " << z << "\n";

    auto fig = std::unique_ptr<Figure>(new Stern(name, x, y, z));

    return {std::move(fig), {dx, dy}};
}

auto loadShapes(const std::filesystem::path& fileName) -> std::vector<std::pair<std::unique_ptr<Figure>, std::pair<double, double>>> {
        std::vector<std::pair<std::unique_ptr<Figure>, std::pair<double, double>>> retLoadedFigures;

        std::ifstream in(std::filesystem::weakly_canonical(fileName));
        if(in.is_open())
            std::cout << "Succesfully opened '" << std::filesystem::weakly_canonical(fileName) << "' file!\n";
        else {
            std::cerr << "Could not open '" << std::filesystem::weakly_canonical(fileName) << "' file!\n";
            std::abort();
        }

        std::smatch match;
        std::string line;
        while(std::getline(in, line)) {
            auto words = splitString(line, ' ');

            if(words.size() <= 0)
                continue;

            int n = std::atoi(words.at(0).c_str());
            std::string name = words.at(1);

            if(std::regex_match(words.at(0), match, std::regex("^\\d+eck$"))) {
                std::cout << "Match " << n << "Eck " << name << "\n";
                auto eckPair = parseEck(in, n, name);

                retLoadedFigures.push_back({std::move(std::get<0>(eckPair)), std::get<1>(eckPair)});
            }
            else if(std::regex_match(words.at(0), match, std::regex("^(Kreis)$"))) {
                std::cout << "Match Kreis " << name << "\n";
                auto kreis = parseKreis(in, name);
            
                retLoadedFigures.push_back({std::move(std::get<0>(kreis)), std::get<1>(kreis)});
            }
            else if(std::regex_match(words.at(0), match, std::regex("^(Stern)$"))) {
                std::cout << "Match Stern " << name << "\n";
                auto stern = parseStern(in, name);
            
                retLoadedFigures.push_back({std::move(std::get<0>(stern)), std::get<1>(stern)});
            }

            std::cout << "\n";
        }

        return retLoadedFigures;
    }

auto main() -> int {
    auto figures = loadShapes("../../figuren.dat");

    for(const auto& [figure, delta] : figures) {
        auto movefigure = figure->cloneFigure();
        movefigure->setName(movefigure->getName() + "Move");
        movefigure->move(std::get<0>(delta), std::get<1>(delta));

        std::cout << "Show " << figure->getName() << "\n";
        std::cout << "Show " << movefigure->getName() << "\n";

        figure->show();
        movefigure->show();
    }

    return 0;
}