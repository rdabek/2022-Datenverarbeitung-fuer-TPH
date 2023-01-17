#include "utils/atomAttributeHelpers.hpp"
#include "utils/gnuplot-iostream.h"

#include <iostream>
#include <map>

using namespace myproject;

auto main() -> int {
    auto atomAttributes = loadAtomAttributes("../../Nuklide.txt");
    auto uraniumDecay = loadUraniumDecayAtoms("../../U235nf_fp.txt");

    std::cout << "Printing nuclei properties:\n";

    for(const auto& [aNum, aProp] : atomAttributes) {
        // Print atom name and atomic numbers
        std::cout << std::get<0>(aNum) << "-" << aProp.name << "-" << std::get<1>(aNum);

        for(const auto& [decay, prob] : aProp.decays)
            std::cout << " " << decayToString(decay) << " " << prob;

        // Stable nuclei have no halftime
        if(aProp.halftime.has_value())
            std::cout << " " << aProp.halftime.value().count() << "s";

        std::cout << "\n";
    }

    std::cout << "\nPrinting uranium decay with probabilities:\n";

    for(const auto& [aNum, aProb] : uraniumDecay) {
        // Print atom name and atomic numbers
        std::cout << std::get<0>(aNum) << "-" << std::get<0>(aProb) << "-" << std::get<1>(aNum)
            << " " << std::get<1>(aProb) << "\n";
    }

    return 0;
}