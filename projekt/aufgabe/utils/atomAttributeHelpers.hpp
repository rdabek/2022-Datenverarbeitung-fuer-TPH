#pragma once

#include <chrono>
#include <filesystem>
#include <optional>
#include <map>
#include <string>

namespace myAtomic {

    enum Decay {
        st,
        bm,
        bm_n,
        ec
    };

    using AtomicNumbers = std::pair<int, int>;

    using AtomicProbability = std::pair<std::string, double>;

    struct AtomicProperties {
        std::string name;
        std::map<Decay, double> decays{};   // Possible decay outcomes with their probabilities
        std::optional<std::chrono::duration<double>> halftime;
    };

    auto convertToSeconds(double num, const char format) -> std::chrono::duration<double>;

    auto getDecayType(const std::string& decayType) -> Decay;

    auto decayToString(const Decay& decay) -> std::string;

    auto loadAtomAttributes(const std::filesystem::path& fileName) -> std::map<AtomicNumbers, AtomicProperties>;

    auto loadUraniumDecayAtoms(const std::filesystem::path& fileName) -> std::map<AtomicNumbers, AtomicProbability>;

    auto atomToString(const AtomicNumbers& atom, const std::map<AtomicNumbers, AtomicProperties>& atomAttributes) -> std::string;

}