#include "utils/myPolynomial.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace mypolyops;

int main() {
    constexpr auto infile = "/YourHomePath/Ue05/vertikal.dat";
    constexpr auto outfileEnd = "/YourHomePath/Ue05/plots/endpunkt.dat";
    constexpr auto outfilePoly = "/YourHomePath/Ue05/plots/Polynominterpol.dat";
    double epsilon = 1e-10;
    std::cout << "Epsilon: " << epsilon << "\n";

    std::ifstream in(infile);

    // Try opening file
    if(in.is_open())
        std::cout << "Succesfully opened '" << infile << "'!\n";
    else {
        std::cout << "Could not open '" << infile << "'!\n";
        return 1;
    }

    // Read data from file and save to vector of numbers
    std::vector<std::vector<double>> numbers;
    std::string line;
    // Read line by line until eof. Notice this changes the in variable,
    // as the read data is being erased from the ifstream buffer
    while(std::getline(in, line)) {
        std::vector<double> triplet;
        std::string number;
        std::stringstream lineStream(line);
        // Split the line by the tab delimiter/character
        // Notice this changes the lineStream variable, as the read data is
        // being erased from the stringstream buffer
        while(std::getline(lineStream, number, ' ')) {
            triplet.push_back(std::atof(number.c_str()));
        }
        //std::cout << "\n";
        numbers.push_back(triplet);
    }

    // Create std::vectors for t, x, z
    std::vector<double> tm;
    std::vector<double> xm;
    std::vector<double> zm;
    for(size_t i=0; i<numbers.size(); i++) {
        std::cout << "Triple " << i << ": ";        // (ti, zi, xi)
        tm.push_back(numbers[i][0]);
        xm.push_back(numbers[i][2]);
        zm.push_back(numbers[i][1]);
        std::cout << tm[i] << " " << xm[i] << " " << zm[i] << "\n";
    }

    // All Calculations:
    // Interpolations
    std::vector<double> tauM = Stuetzstellen(tm[0], tm[tm.size()-1], 1000);
    std::ofstream out(outfilePoly);
    for(const auto& tau : tauM) {
        out << tau << " " << Polynom(tau, tm, zm) << " " << Polynom(tau, tm, xm) << "\n";
    }
    out.close();
    
    // Searching 0
    double t0 = Nullstelle(tm, zm, epsilon);
    std::ofstream outE(outfileEnd);
    std::cout << "Endpoint: " << t0 << " " << Polynom(t0, tm, zm) << " " << Polynom(t0, tm, xm) << "\n";
    outE << t0 << " " << Polynom(t0, tm, zm) << " " << Polynom(t0, tm, xm) << "\n";
    outE.close();
    
    return 0;
}