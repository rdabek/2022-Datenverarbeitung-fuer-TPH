#include "decay.hpp"

#include <functional>
#include <random>

namespace myDecay {

    auto betaDecay(const myAtomic::AtomicNumbers& aNum) -> myAtomic::AtomicNumbers {
        return {std::get<0>(aNum) + 1, std::get<1>(aNum)};
    }

    auto betaNeutronDecay(const myAtomic::AtomicNumbers& aNum) -> myAtomic::AtomicNumbers {
        return {std::get<0>(aNum) + 1, std::get<1>(aNum) - 1};
    }

    auto electronCapture(const myAtomic::AtomicNumbers& aNum) -> myAtomic::AtomicNumbers {
        return {std::get<0>(aNum) - 1, std::get<1>(aNum)};
    }

    auto atomCorrectDecay(const myAtomic::AtomicNumbers& aNum, const myAtomic::Decay& decay) -> myAtomic::AtomicNumbers {
        switch(decay) {
            case myAtomic::Decay::st:
                return aNum;
            case myAtomic::Decay::bm:
                return betaDecay(aNum);
            case myAtomic::Decay::bm_n:
                return betaNeutronDecay(aNum);
            case myAtomic::Decay::ec:
                return electronCapture(aNum);
        }
        std::abort();
        return aNum;
    }

    auto isStable(const myAtomic::AtomicNumbers& aNum, const std::map<myAtomic::AtomicNumbers, myAtomic::AtomicProperties>& atomAttributes) -> bool {
        for(const auto &[decay, prob] : atomAttributes.at(aNum).decays) {
            if(decay == myAtomic::Decay::st)
                return true;
        }
        return false;
    }

    auto decayAtom(const myAtomic::AtomicNumbers& aNum, const std::map<myAtomic::AtomicNumbers, myAtomic::AtomicProperties>& atomAttributes,
            std::mt19937& gen) -> myAtomic::AtomicNumbers {
        try{
            auto aProp = atomAttributes.at(aNum);

            std::vector<myAtomic::Decay> decays;
            std::vector<double> probabilities;
            for(const auto& [decay, prob] : aProp.decays) {
                decays.push_back(decay);
                probabilities.push_back(prob);
            }

            std::discrete_distribution decayType(probabilities.begin(), probabilities.end());
            auto ret = decayType(gen);

            return atomCorrectDecay(aNum, decays.at(ret));
        }
        catch(const std::exception& e) {
            std::abort();
        }
    }

}