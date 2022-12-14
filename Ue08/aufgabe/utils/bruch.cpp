#include "bruch.hpp"

#include <sstream>

bruch::bruch(int numerator, int denumerator) {
    if(denumerator == 0)
        throw std::runtime_error("Divide by 0 Error!");
    this->numerator = numerator;
    this->denumerator = denumerator;
    number = num();
}

bruch::bruch(const std::string& division) {
    std::smatch match;
    if(!std::regex_match(division, match, divisionRegex))
        throw std::runtime_error("Illegal format used for division!");
    
    // Legal format now...
    std::stringstream sstream(division);
    std::string num, denum;
    std::getline(sstream, num, '/');
    std::getline(sstream, denum);

    numerator = std::atoi(num.c_str());
    denumerator = std::atoi(denum.c_str());
    if(denumerator == 0)
        throw std::runtime_error("Divide by 0!");

    number = this->num();
}

bruch::bruch(const bruch& other) {
    numerator = other.numerator;
    denumerator = other.denumerator;
    number = other.number;
}

auto bruch::operator=(const bruch& other) -> bruch& {
    numerator = other.numerator;
    denumerator = other.denumerator;
    number = num();

    return *this;
}

auto bruch::operator+(const bruch& other) -> bruch {
    bruch ret(*this);
    ret.numerator = other.numerator*ret.denumerator + ret.numerator*other.denumerator;
    ret.denumerator = other.denumerator*ret.denumerator;
    ret.number = ret.num();

    return ret;
}

auto bruch::operator*(int multiplicator) -> bruch {
    bruch ret(*this);
    ret.numerator *= multiplicator;
    ret.number = ret.num();

    return ret;
}

auto bruch::operator+=(const bruch& other) -> bruch& {
    numerator = other.numerator*denumerator + numerator*other.denumerator;
    denumerator = other.denumerator*denumerator;
    number = num();

    return *this;
}

auto bruch::set_n(int denumerator) -> void {
    if(denumerator == 0)
        throw std::runtime_error("Divide by 0!");
    this->denumerator = denumerator;
    number = num();
}

auto bruch::get_x() -> double {
    return number;
}

auto bruch::num() -> double {
    return (double)numerator/(double)denumerator;
}

auto gcd(int a, int b) -> int {     // Greatest common divisor
    int r;
    while ((a % b) > 0)  {
        r = a % b;
        a = b;
        b = r;
    }
    return b;
}

auto bruch::reduce() -> bruch& {
    auto divisor = gcd(numerator, denumerator);
    numerator /= divisor;
    denumerator /= divisor;
    number = num();
    return *this;
}

auto bruch::toString() const -> std::string {
    return std::to_string(numerator) + "/" + std::to_string(denumerator);
}

auto bruch::show(std::ostream& os) const -> std::ostream& {
    os << this->toString() << "\n";
    return os;
}