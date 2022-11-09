#include "myStringOps.hpp"

namespace mystringops {

    auto removeCharacter(const std::string& str, const char& character) -> std::string {
        std::string ret;
        for(auto itr : str) {
            if(itr == character) {
                //do nothing
            }
            else
                ret += itr;
        }
        return ret;
    }

    auto toLower(const std::string& str) -> std::string {
        std::string ret;
        for(auto itr : str) {
            if(itr >= 'A' && itr <= 'Z')
                itr -= 'A'-'a';
            ret += itr;
        }
        return ret;
    }

    auto swap(char& a, char&b) -> void {
        auto tmp = a;
        a = b;
        b = tmp;
    }

    auto sortAscending(const std::string& str) -> std::string {
        auto ret = str;
        // Use bubble sort
        int i, j;
        for (i = 0; i < static_cast<int>(ret.length()) - 1; i++) {          // Note: I am assuming that the conversion
                                                                            // from size_t to int will not overflow, there is no guarantee though
            for (j = 0; j < static_cast<int>(ret.length()) - 1 - i; j++) {
                if (ret.at(j) > ret.at(j + 1))
                    swap(ret.at(j), ret.at(j + 1));
            }
        }
        return ret;
    }

}