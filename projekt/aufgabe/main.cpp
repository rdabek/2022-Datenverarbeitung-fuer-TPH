#include "utils/atomAttributeHelpers.hpp"
#include "utils/decay.hpp"
#include "utils/gnuplot-iostream.h"

#include <iostream>
#include <map>
#include <random>

using namespace myAtomic;
using namespace myDecay;

auto main() -> int {
    const auto atomAttributes = loadAtomAttributes("../../Nuklide.txt");
    const auto uraniumDecay = loadUraniumDecayAtoms("../../U235nf_fp.txt");

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

    std::vector<AtomicNumbers> atoms;
    for(const auto& [aNum, aProb] : uraniumDecay) {
        // Print atom name and atomic numbers
        atoms.push_back(aNum);
        std::cout << std::get<0>(aNum) << "-" << std::get<0>(aProb) << "-" << std::get<1>(aNum)
            << " " << std::get<1>(aProb) << "\n";
    }

    // Fission
    std::mt19937 gen(0);
    auto iteratingAtom = AtomicNumbers(34, 86);
    std::cout << "\nDecay chain of " << atomToString(iteratingAtom, atomAttributes) << ":\n";
    while(!isStable(iteratingAtom, atomAttributes)) {
        iteratingAtom = decayAtom(iteratingAtom, atomAttributes, gen);
        std::cout << atomToString(iteratingAtom, atomAttributes) << "\n";
    }

    return 0;
}