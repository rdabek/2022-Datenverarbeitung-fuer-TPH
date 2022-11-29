#pragma once

#include <string>
#include <iostream>

namespace experiment {
    
    class Data {
        public:
            Data(const std::string& name, const std::string& unit);

            Data(const Data& other);        // Rule of three
                                            // Avoid shallow copy, which would result in a double free
                                            // by implementing a deep-copy copy constructor and copy assignment operator...

            auto operator()(const Data& other) -> Data&;

            ~Data();

            auto push_back(double d) -> void;

            auto pop_back() -> void;

            auto size() const -> int;

            auto avg() const -> double;

            auto err() const -> double;

            auto name() const -> std::string;

            auto unit() const -> std::string;

            auto toSting() const -> std::string;

            auto printFormat(std::ostream& os) const -> void;

        private:

            auto doubleCapacity() -> void;

            auto halfCapacity() -> void;

            double* data;
            std::string dataName;
            std::string dataUnit;
            
            int mask = (1 << 2) - 1;
            int length = 0;
            int capacity = 0;
    };

    inline auto operator<<(std::ostream& os, Data data) -> std::ostream& {
        os << data.toSting();
        return os;
    }
}