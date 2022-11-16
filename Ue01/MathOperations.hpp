#pragma once

// Overcomplicate Much
namespace myMathOperations {
    class Math {
        public:

        template <typename T>
        inline static T divide(T zaehler, T nenner) {
            return (T)zaehler/nenner;
        }
    };
}