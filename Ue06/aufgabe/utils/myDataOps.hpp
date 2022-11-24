#pragma once

#include <cmath>

#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>

#include <functional>
#include <unordered_set>

namespace mydataops {

    constexpr int numDaysInMonth[] = {      // Not a leap year
        31,     // January
        28,     // February
        31,     // March
        30,     // April
        31,     // May
        30,     // June
        31,     // July
        31,     // August
        30,     // September
        31,     // October
        30,     // November
        31      // December
    };

    struct Name {
        public:
            // Explicit Constructor
            Name(const std::string& name, const std::string& surname);

            ~Name() = default;

            // Copy Constructor
            Name(const Name& other);        // Rule of three

            // Copy assignment operator
            auto operator()(const Name& other) -> Name&;

            auto toString() const -> std::string;

        public:
            std::string name{};
            std::string surname{};
    };

    inline auto operator<(const Name& a, const Name& b) -> bool {
        return a.name < b.name;
    }

    inline auto operator<<(std::ostream& os, const Name& name) -> std::ostream&
    {
        os << name.toString();
        return os;
    }

    struct Date {
        public:
            // Explicit Constructor
            Date(const int& year, const int& month, const int& day);

            ~Date() = default;

            // Copy Constructor
            Date(const Date& other);        // Rule of three

            // Copy assignment operator
            auto operator()(const Date& other) -> Date&;

            auto isLeap() const -> bool;

            auto toString() const -> std::string;

            auto getWeekday() const -> std::string;

            auto operator-(const Date& other) const -> double;

        public:
            int year{};
            int month{};
            int day{};
    };

    inline auto operator<(const Date& a, const Date& b) -> bool {
        if(a.year < b.year)
            return true;
        else if(a.year > b.year)
            return false;
        // Else a.year == b.year, continue
        
        if(a.month < b.month)
            return true;
        else if(a.month > b.month)
            return false;
        // Else year == year, continue

        if(a.day < b.day)
            return true;
        // Else if a.day > b.day is false
        // Else a.day == b.day it's still false
        
        return false;
    }

    inline auto operator<<(std::ostream& os, const Date& date) -> std::ostream& {
        os << date.toString();
        return os;
    }

    struct Person {
        public:
            Person(const Name& name, const Date& date)
                : date(date), name(name) { /* Nothing to do here */ }

        public:
            Date date;
            Name name;
            
    };

    inline auto formatNumber(int num, int fields) -> std::string {
        std::stringstream oss;
        oss << std::setfill('0') << std::setw(fields) << num;
        return oss.str();
    }

}