#include "utils/helperFunctions.hpp"
#include "utils/gnuplot-iostream.h"

#include <functional>
#include <map>
#include <random>
#include <iostream>
#include <fstream>
#include <filesystem>

using namespace experiments;

auto diceThrow(std::function<int()>& dice) -> int {
    auto throw1 = dice();
    auto throw2 = dice();
    auto throw3 = dice();
    return throw1 + min(throw2, throw3) - max(throw2, throw3);
}

auto diceExperiment(std::mt19937& gen) -> void {
    auto uintDistribution = std::uniform_int_distribution<>(1, 6);
    std::function<int()> dice = std::bind(uintDistribution, gen);
    std::map<int, int> histo;
    constexpr auto gameN = 100000;

    for(int i=0; i<gameN; i++)
        ++histo[diceThrow(dice)];

    std::filesystem::path outFilePath = "../../plots/dice.dat";
    std::ofstream outFile(std::filesystem::weakly_canonical(outFilePath));
    if(!outFile)
        std::cerr << "Cannot open " << outFilePath << "\n";
    
    double avg = 0.0;
    double allPi = 0.0;
    for(const auto& [key, value] : histo) {
        allPi += value / (double)gameN;
        std::cout << "i: " << key << ", ni: " << value << ", pi: " <<  value / (double)gameN << "\n";
        outFile << key << " " << value / (double)gameN << "\n";
        avg += key * (double)(value/(double)gameN);
    }
    outFile.close();
    std::cout << "Average: " << avg << "\n";

    auto height = 400;
    auto width = height*1.61803;
    Gnuplot gp;
    gp << "set terminal png size " << width << ", " << height << " enhanced font \"Helvetica,20\"\n";
    gp << "set output '~/Ue09/plots/output.png'\n";
    gp << "set xrange [-6:8]\n";
    gp << "set yrange [0:0.2]\n";
    gp << "plot " << std::filesystem::weakly_canonical(outFilePath) << " using 1:2 smooth freq with boxes\n";
}

auto poissonProcess(std::mt19937& gen, double probability, int numberOfIntervals) -> int {
    std::bernoulli_distribution bernoulliDist(probability);
    std::map<bool, int> process;
    
    for(int i=0; i<numberOfIntervals; i++)
        ++process[bernoulliDist(gen)];

    return process[true];
}

auto poissonExperiment(std::mt19937& gen) -> void {
    std::map<int, int> histo;
    for(int i=0; i<10000; i++)
        ++histo[poissonProcess(gen, 0.01, 360)];

    for(const auto& [key, value] : histo) {
        std::cout << "Anzahl gelungener Versuche: " << key << ", wie oft: " << value << "\n";
    }
}

auto main() -> int {
    std::mt19937 gen(0);
    
    diceExperiment(gen);
    poissonExperiment(gen);

    return 0;
}