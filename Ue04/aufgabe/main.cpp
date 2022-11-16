#include "utils/myStatisticOps.hpp"

#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

// Global variables are not the best idea...
// I don't really like to use them but in this case
// I think it's better than a #define ...
constexpr char _TAB_CHAR = 9;       // ASCII value for tab character

using namespace mystatisticops;

int main() {
    constexpr auto infile = "/YourHomePath/Ue04/Daten.dat";
    constexpr auto outfile = "/YourHomePath/Ue04/plots/calculated.dat";

    std::ifstream in(infile);

    // Try opening file
    if(in.is_open())
        std::cout << "Succesfully opened '" << infile << "'!\n";
    else {
        std::cout << "Could not open '" << infile << "'!\n";
        return 1;
    }

    // Read data from file and save to vector of numbers
    std::vector<double> numbers;
    std::string line;
    // Read line by line until eof. Notice this changes the in variable,
    // as the read data is being erased from the ifstream buffer
    while(std::getline(in, line)) {
        std::string number;
        std::stringstream lineStream(line);
        // Split the line by the tab delimiter/character
        // Notice this changes the lineStream variable, as the read data is
        // being erased from the stringstream buffer
        while(std::getline(lineStream, number, _TAB_CHAR)) {        
            numbers.push_back(std::atof(number.c_str()));
        }
    }
    
    std::cout << "Vector length: " << numbers.size() << "\n";

    std::ofstream out(outfile);
    // Calculations
    for(size_t i=0; i<numbers.size()/50; i++) {
        auto tmpVec = std::vector(numbers.begin(), numbers.begin()+50*(i+1));       // Not saving sums to make the program faster
                                                                                    // This is just a very simple solution

        // Write to file 'calculated.dat'
        out << i+1 << " " << avg(tmpVec) << " " << stdDev(tmpVec) << " " << avgErr(tmpVec) << "\n";     // Notice that there will be another
                                                                                                        // empty line at the end of the file
    }
    out.close();

    std::cout << "Avg: " << avg(numbers) << ", StdDev: " << stdDev(numbers) << ", Error in Avg: " << avgErr(numbers) << "\n";
    
    return 0;
}