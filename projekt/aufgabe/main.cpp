#include "utils/atomAttributeHelpers.hpp"
#include "utils/decay.hpp"
#include "utils/gnuplot-iostream.h"

#include <cmath>
#include <fstream>
#include <iostream>
#include <map>
#include <random>

using namespace myAtomic;
using namespace myDecay;

auto printDecayChain(const AtomicNumbers& aNum, const std::map<AtomicNumbers, AtomicProperties>& atomAttributes, std::mt19937& gen) -> void {
    auto iteratingAtom = aNum;
    std::cout << "Decay chain of " << atomToString(iteratingAtom, atomAttributes) << ":\n";
    while(!isStable(iteratingAtom, atomAttributes)) {
        iteratingAtom = decayAtom(iteratingAtom, atomAttributes, gen);
        std::cout << atomToString(iteratingAtom, atomAttributes) << "\n";
    }
    std::cout << "\n";
}

auto poissonProcess(std::mt19937& gen, double lambda, int numberOfIntervals) -> int {
    std::bernoulli_distribution bernoulliDist(lambda);
    int retTimeIntervals=0;

    for(int i=0; i<numberOfIntervals; i++, retTimeIntervals++)
        if(bernoulliDist(gen))
            break;

    return retTimeIntervals;
}

auto calcLambda(double halftime) -> double {
    return log(2.0)/halftime;
}

auto poissonOfAtom(const AtomicNumbers& aNum, const std::map<AtomicNumbers, AtomicProperties>& atomAttributes, std::mt19937& gen) -> void {
    // Poisson on 10000 particles of 34-Se-86
    std::map<AtomicNumbers, std::map<int, int>> histoDecayTime;
    for(int i=0; i<10000; i++) {
        auto iteratingAtom = aNum;
        while(!isStable(iteratingAtom, atomAttributes)) {
            auto histo = histoDecayTime[iteratingAtom];
            if(atomAttributes.at(iteratingAtom).halftime.has_value()) {
                auto lambda = calcLambda(atomAttributes.at(iteratingAtom).halftime.value().count());
                auto decayAfterSec = poissonProcess(gen, lambda, 10000);
                ++histo[decayAfterSec];
                histoDecayTime[iteratingAtom] = histo;
            }
            iteratingAtom = decayAtom(iteratingAtom, atomAttributes, gen);
        }
    }

    // Write poisson to file
    std::cout << "Writing poisson decay times to files.\n";
    std::vector<std::string> paths;
    for(const auto& [aNum, histo] : histoDecayTime) {
        std::filesystem::path outFilePath = "../../plots/" + atomToString(aNum, atomAttributes) + ".dat";
        paths.push_back(std::filesystem::weakly_canonical("../../plots/" + atomToString(aNum, atomAttributes)).c_str());

        std::ofstream output(std::filesystem::weakly_canonical(outFilePath));
        for(const auto& [decayTime, count] : histo) {
            output << decayTime << " " << count << "\n";
        }
        output.close();
    }
    std::cout << "Done writing to files.\n\n";

    // Gnuplot poisson histogram
    std::cout << "Creating gnuplots.\n";
    for(const auto& outFilePath : paths) {
        int width = 1200, height = width/1.618;
        Gnuplot gp;
        gp << "set terminal png size " << width << ", " << height << " enhanced font \"Helvetica,20\"\n";
        gp << "set output '" << outFilePath << ".png'\n";
        gp << "set xlabel 'decay in s'\n";
        gp << "set ylabel 'amount of decays'\n";
        gp << "plot '" << outFilePath << ".dat' using 1:2 smooth freq with boxes title 'decay from data file'\n";
    }
    std::cout << "Done creating gnuplots.\n";
}

auto main() -> int {
    std::mt19937 gen(0);

    // Read files
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
    std::vector<double> probabilities;
    for(const auto& [aNum, aProb] : uraniumDecay) {
        // Print atom name and atomic numbers
        atoms.push_back(aNum);
        probabilities.push_back(std::get<1>(aProb));
        std::cout << std::get<0>(aNum) << "-" << std::get<0>(aProb) << "-" << std::get<1>(aNum)
            << " " << std::get<1>(aProb) << "\n";
    }
    std::cout << "\n";

    // Calculate random decay chains
    for(int i=0; i<10; i++) {
        std::discrete_distribution atom(probabilities.begin(), probabilities.end());
        printDecayChain(atoms.at(atom(gen)), atomAttributes, gen);
    }

    // Simulate atomic decay with poisson
    poissonOfAtom(AtomicNumbers(34, 86), atomAttributes, gen);
    std::cout << "\n";
    poissonOfAtom(AtomicNumbers(41, 104), atomAttributes, gen);

    return 0;
}