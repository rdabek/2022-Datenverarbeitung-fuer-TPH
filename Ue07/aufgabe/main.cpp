#include "utils/experimentData.hpp"

#include <iostream>
#include <fstream>

using namespace experiment;

auto getDataFromFile(const std::string& fileName) -> Data {
    std::ifstream in(fileName);
    if(in.is_open())
        std::cout << "Succesfully opened '" << fileName << "' file!\n";
    else {
        std::cerr << "Could not open '" << fileName << "' file!\n";
        std::abort();
    }

    // First and second line are well defined:
    std::string name, unit, n;
    std::getline(in, name, ' ');
    std::getline(in, unit);
    std::getline(in, n);

    auto ret = Data(name, unit);

    // For all other lines:
    std::string line;
    while(std::getline(in, line)) {
        ret.push_back(std::atof(line.c_str()));
    }

    int size = std::atoi(n.c_str());

    if(size != ret.size()) {
        std::cerr << "Size is wrong!\n";
        std::abort();
    }
    
    std::cout << "Data size: " << ret.size() << ", size from file field: " << size << "\n";

    return ret;
}

int main() {
    constexpr auto mFile = "/YourHomePath/Ue07/m001.dat";
    constexpr auto pFile = "/YourHomePath/Ue07/p001.dat";
    constexpr auto tFile = "/YourHomePath/Ue07/t001.dat";

    auto mData = getDataFromFile(mFile);
    auto pData = getDataFromFile(pFile);
    auto tData = getDataFromFile(tFile);

    std::cout << mData << "\n";
    std::cout << pData << "\n";
    std::cout << tData << "\n";

    std::cout << "\nActual program output:\n";

    mData.printFormat(std::cout);
    pData.printFormat(std::cout);
    tData.printFormat(std::cout);

    return 0;
}