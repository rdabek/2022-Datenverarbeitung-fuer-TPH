#include "figures.hpp"

#include <cmath>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace geometric {
    Kreis::Kreis(const std::string& name, double x, double y, double r)
        : name(name), x(x), y(y), r(r) { }

    auto Kreis::cloneFigure() const -> std::unique_ptr<Figure> {
        return std::make_unique<Kreis>(*this);
    }

    auto Kreis::setName(const std::string& name) -> void {
        this->name = name;
    }

    auto Kreis::getName() -> std::string {
        return name;
    }

    auto Kreis::move(double dx, double dy) -> void {
        x += dx;
        y += dy;
    }

    auto Kreis::show() -> void {
        std::filesystem::path outpath("../../plots/" + name);
        std::ofstream outfile(std::filesystem::weakly_canonical(outpath));

        auto n = 1000;
        auto dphi = 2.0*M_PI / (double)n;
        for(int i=0; i<=n; i++) {
            outfile << x+r*std::cos(i*dphi) << " " << x+r*std::sin(i*dphi) << "\n";
        }
    }

    Stern::Stern(const std::string& name, double x, double y, double d)
        : name(name), x(x), y(y), d(d) { }
    
    auto Stern::cloneFigure() const -> std::unique_ptr<Figure> {
        return std::make_unique<Stern>(*this);
    }

    auto Stern::setName(const std::string& name) -> void {
        this->name = name;
    }

    auto Stern::getName() -> std::string {
        return name;
    }

    auto Stern::move(double dx, double dy) -> void {
        x += dx;
        y += dy;
    }

    auto Stern::show() -> void {
        std::filesystem::path outpath("../../plots/" + name);
        std::ofstream outfile(std::filesystem::weakly_canonical(outpath));

        auto n = 16;
        auto dphi = 2.0*M_PI / (double)n;
        for(int i=0; i<n; i++) {
            outfile << x << " " << y << "\n";
            outfile << x + d/2.0*std::cos(i*dphi) << " " << y + d/2.0*std::sin(i*dphi) << "\n";
        }
    }

    nEck::nEck(const std::string& name, const std::vector<std::pair<double, double>>& vec) {
        this->name = name;
        this->coords = vec;
    }

    auto nEck::cloneFigure() const -> std::unique_ptr<Figure> {
        return std::make_unique<nEck>(*this);
    }

    auto nEck::setName(const std::string& name) -> void {
        this->name = name;
    }

    auto nEck::getName() -> std::string {
        return name;
    }

    auto nEck::move(const double dx, const double dy) -> void {
        coords[0] = {std::get<0>(coords[0]) + dx, std::get<1>(coords[0]) + dy};
    }

    auto nEck::show() -> void {
        std::filesystem::path outpath("../../plots/" + name);
        std::ofstream outfile(std::filesystem::weakly_canonical(outpath));
    
        for(int i=1; i<(int)coords.size(); i++) {
            outfile << std::get<0>(coords[0]) + std::get<0>(coords[i]) << " " 
                << std::get<1>(coords[0]) + std::get<1>(coords[i]) << "\n";
        }
        outfile << std::get<0>(coords[0]) + std::get<0>(coords[1]) << " " 
                << std::get<1>(coords[0]) + std::get<1>(coords[1]) << "\n";
    }
}