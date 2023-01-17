#include "atomAttributeHelpers.hpp"

#include <fstream>
#include <iostream>

namespace myproject {

    auto convertToSeconds(double num, const char format) -> std::chrono::duration<double> {
        std::chrono::duration<double> time;
        switch(format) {
            case 's':
                time = std::chrono::duration<double, std::ratio<1>>(num); break;
            case 'm':
                time = std::chrono::duration<double, std::ratio<60>>(num); break;
            case 'h':
                time = std::chrono::duration<double, std::ratio<3600>>(num); break;
            case 'd':
                time = std::chrono::duration<double, std::ratio<86400>>(num); break;
            case 'a':
                time = std::chrono::duration<double, std::ratio<31556952>>(num); break;     // Defined in std::chrono as std::chrono::year
            default:
                std::cout << "ERROR!!\n";
        }
        return time;
    }

    auto getDecayType(const std::string& decayType) -> Decay {
        Decay ret;
        if(decayType == "st\r")
            ret = Decay::st;
        else if(decayType == "bm")
            ret = Decay::bm;
        else if(decayType == "bm+n")
            ret = Decay::bm_n;
        else if(decayType == "ec")
            ret = Decay::ec;
        else {
            std::cout << "Decay Type: " << decayType << "\n";
            std::abort();
        }
        
        return ret;
    }

    auto decayToString(const Decay& decay) -> std::string {
        if(decay == Decay::st)
            return "st";
        else if(decay == Decay::bm)
            return "bm";
        else if(decay == Decay::bm_n)
            return "bm+n";
        else if(decay == Decay::ec)
            return "ec";
        return "ERROR";
    }

    auto loadAtomAttributes(const std::filesystem::path& fileName) -> std::map<AtomicNumbers, AtomicProperties> {
        std::map<AtomicNumbers, AtomicProperties> retAtomProperties;

        std::ifstream in(std::filesystem::weakly_canonical(fileName));
        if(in.is_open())
            std::cout << "Succesfully opened '" << std::filesystem::weakly_canonical(fileName) << "' file!\n";
        else {
            std::cerr << "Could not open '" << std::filesystem::weakly_canonical(fileName) << "' file!\n";
            std::abort();
        }

        std::string line;
        while(std::getline(in, line)) {
            std::vector<std::string> splitLine;
            std::string part;
            std::stringstream lineStream(line);
            // Split the line by the tab delimiter/character
            // Notice this changes the lineStream variable, as the read data is
            // being erased from the stringstream buffer
            while(std::getline(lineStream, part, ' ')) {
                //std::cout << part << "\n";
                splitLine.push_back(part);
            }

            std::vector<std::string> atomNumbers;
            std::string tmpAtom;
            std::stringstream atom(splitLine.at(0));
            while(std::getline(atom, tmpAtom, '-')) {
                atomNumbers.push_back(tmpAtom);
            }

            auto num = AtomicNumbers{std::atoi(atomNumbers.at(0).c_str()), std::atoi(atomNumbers.at(2).c_str())};
            AtomicProperties props = retAtomProperties[num];
            props.name = atomNumbers.at(1);

            if(splitLine.size() == 2) {
                props.decays[getDecayType(splitLine.at(1))] = 1;
            }
            if(splitLine.size() > 2) {
                auto timeUnconverted = std::atof(splitLine.at(2).c_str());
                auto format = std::string(splitLine.at(3)).at(0);

                auto timeSec = convertToSeconds(timeUnconverted, format);
                props.halftime = timeSec;

                props.decays[getDecayType(splitLine.at(1))] = 1;
                
                //std::cout << "Unconverted: " << splitLine.at(2) << ", converted to double: " << timeUnconverted << ", format: " <<  format
                //    << ", converted to s: " << convertToSeconds(timeUnconverted, format).count() << "\n";
            }
            if(splitLine.size() >= 5) {
                auto probability = std::atof(splitLine.at(4).c_str())/100.0;
                //std::cout << probability << "\n";
                props.decays[getDecayType(splitLine.at(1))] = probability;
            }

            retAtomProperties[num] = props;
        }

        return retAtomProperties;
    }

    auto loadUraniumDecayAtoms(const std::filesystem::path& fileName) -> std::map<AtomicNumbers, AtomicProbability> {
        std::map<AtomicNumbers, AtomicProbability> retUraniumDecay;

        std::ifstream in(std::filesystem::weakly_canonical(fileName));
        if(in.is_open())
            std::cout << "Succesfully opened '" << std::filesystem::weakly_canonical(fileName) << "' file!\n";
        else {
            std::cerr << "Could not open '" << std::filesystem::weakly_canonical(fileName) << "' file!\n";
            std::abort();
        }

        std::string line;
        std::getline(in, line);
        while(std::getline(in, line)) {
            std::vector<std::string> splitLine;
            std::string part;
            std::stringstream lineStream(line);
            // Split the line by the tab delimiter/character
            // Notice this changes the lineStream variable, as the read data is
            // being erased from the stringstream buffer
            while(std::getline(lineStream, part, ' ')) {
                //std::cout << part << "\n";
                splitLine.push_back(part);
            }

            std::vector<std::string> atomNumbers;
            std::string tmpAtom;
            std::stringstream atom(splitLine.at(0));
            while(std::getline(atom, tmpAtom, '-')) {
                atomNumbers.push_back(tmpAtom);
            }

            auto num = AtomicNumbers{std::atoi(atomNumbers.at(0).c_str()), std::atoi(atomNumbers.at(2).c_str())};
            auto prob = AtomicProbability{atomNumbers.at(1), std::atof(splitLine.at(1).c_str())/100.0};

            retUraniumDecay[num] = prob;
        }

        return retUraniumDecay;
    }

}