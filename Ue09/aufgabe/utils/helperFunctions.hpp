#pragma once

namespace experiments {

    template <typename T>
    auto max(const T &a, const T &b) -> T {
        return a > b ? a : b;
    }

    template <typename T>
    auto min(const T &a, const T &b) -> T {
        return a < b ? a : b;
    }
}