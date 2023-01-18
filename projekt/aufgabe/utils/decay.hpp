#pragma once

#include "atomAttributeHelpers.hpp"

#include <random>

namespace myDecay {

    auto betaDecay(const myAtomic::AtomicNumbers& aNum) -> myAtomic::AtomicNumbers;

    auto betaNeutronDecay(const myAtomic::AtomicNumbers& aNum) -> myAtomic::AtomicNumbers;

    auto electronCapture(const myAtomic::AtomicNumbers& aNum) -> myAtomic::AtomicNumbers;

    auto isStable(const myAtomic::AtomicNumbers& aNum, const std::map<myAtomic::AtomicNumbers, myAtomic::AtomicProperties>& atomAttributes) -> bool;

    auto decayAtom(const myAtomic::AtomicNumbers& aNum, const std::map<myAtomic::AtomicNumbers, myAtomic::AtomicProperties>& atomAttributes,
            std::mt19937& gen) -> myAtomic::AtomicNumbers;

}