#pragma once

#include <string>

namespace mystringops {

    auto removeCharacter(const std::string& str, const char& character) -> std::string;

    auto toLower(const std::string& str) -> std::string;

    auto sortAscending(const std::string& str) -> std::string;
}