#pragma once

#include <iostream>
#include <string>
#include <regex>

class bruch {
    public:
        bruch() = default;

        bruch(const bruch& other);

        auto operator=(const bruch& other) -> bruch&;

        bruch(auto, auto) = delete;                             // Delete implicit conversion constructor -> allow only specified types

        bruch(int num, int denum);                              // Allow int values

        bruch(const std::string& division);                     // Allow strings with specified regex

        auto operator+(const bruch& other) -> bruch;

        auto operator*(int multiplicator) -> bruch;

        auto operator+=(const bruch& other) -> bruch&;

        auto set_n(auto) -> void = delete;                      // Delete implicit conversion

        auto set_n(int numerator) -> void;

        auto set_d(int denumerator) -> void;

        auto get_x() -> double;

        auto reduce() -> bruch&;

        auto toString() const -> std::string;

        auto show(std::ostream& os) const -> std::ostream&;

    private:
        auto num() -> double;

        const std::regex divisionRegex = std::regex("^[0-9]+\\/[0-9]+$");    // Match specified format -> e.g. 234/234 and nothing else
                                                                                // Some fancy black magic
        int numerator, denumerator;
        double number;
};

inline auto operator<<(std::ostream& os, const bruch& b) -> std::ostream& {
    os << b.toString();
    return os;
}