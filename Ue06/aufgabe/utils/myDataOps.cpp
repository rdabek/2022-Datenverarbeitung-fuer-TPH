#include "myDataOps.hpp"

#include <iostream>
#include <cassert>

namespace mydataops {

    Name::Name(const std::string& name, const std::string& surname) {
        this->name = name;
        this->surname = surname;
    }

    Name::Name(const Name& other) {
        this->name = other.name;
        this->surname = other.surname;
    }

    auto Name::operator()(const Name& other) -> Name& {
        this->name = other.name;
        this->surname = other.surname;
        return *this;
    }

    auto Name::toString() const -> std::string {
        return std::string(name) + std::string(" ") + std::string(surname);
    }
    
    Date::Date(const int& year, const int& month, const int& day) {
        // Make sure Date can only be a valid date whenever it exists
        assert(month >=1 && month <= 12);
        assert(day >= 1);

        if((month % 2 != 0 && month <= 7) || (month > 7 && month % 2 == 0))
            assert(day <= 31);
        else if(month == 2) {
            assert(day <= (this->isLeap() ? 29 : 28));
        }
        else if((month % 2 == 0 && month <= 6) || (month > 7 && month % 2 != 0))
            assert(day <= 30);
        else {
            std::cerr << "Date is non-existent!\n";
            std::abort();
        }

        this->year = year;
        this->month = month;
        this->day = day;
    }

    Date::Date(const Date& other) {
        this->day = other.day;
        this->month = other.month;
        this->year = other.year;
    }

    auto Date::operator()(const Date& other) -> Date& {
        this->day = other.day;
        this->month = other.month;
        this->year = other.year;
        return *this;
    }

    auto Date::isLeap() const -> bool {
        return (year % 4 == 0) && ((year % 100 != 0) || (year % 400 == 0));
    }

    auto Date::toString() const -> std::string {
        return formatNumber(year, 4) + "-" + formatNumber(month, 2) + "-" + formatNumber(day, 2);
    }

    auto mod(const int& a, const int& b) -> int {
        return (a%b + b)%b;             // Hack to make mod always positive and correct
    }

    auto Date::getWeekday() const -> std::string {
        auto d = day;
        auto m = month;
        auto Y = year;
        if(m == 1 || m == 2) {
            m+=12;
            Y = year-1;
        }
        auto c = (int)std::floor((double)Y/(double)100.00);
        auto y = Y-100*c;
        
        auto w = mod((
            (int)std::floor((double)(13.0*((double)m + (double)1.0))/((double)5.0))
            + (int)std::floor(((double)y)/((double)4.0))
            + (int)std::floor(((double)c)/((double)4.0))
            + (int)d
            + (int)y
            - (int)2*c
        ), 7);      // Oida... % is not modulo but the rest of the divisor... Thus it can be negative...
                    // Hacked that with the mod function
        
        const std::string weekday[] = {
            "Samstag",
            "Sunday",
            "Montag",
            "Dienstag",
            "Mittwoch",
            "Donnerstag",
            "Freitag"
        };

        return weekday[w];
    }

    auto countLeap(const Date& a, const Date& b) -> int {
        int leap = 0;
        int min, max;   // Years

        bool isSmaller = a < b;

        if(isSmaller) {
            min = a.year;
            max = b.year;
        }
        else {
            min = b.year;
            max = a.year;
        }

        for(int i = min; i<=max; i++)
            if((i % 4 == 0) && ((i % 100 != 0) || (i % 400 == 0)))
                leap++;

        if(isSmaller)
            return -leap;
        
        return leap;
    }

    auto findDaysInYear(const Date& date) -> int {
        int days = 0;
        for(int i=0; i<date.month-1; i++)
            days += numDaysInMonth[i];
        if(date.isLeap() && date.month > 2)
            days += 1;
        return days + date.day;
    }

    auto Date::operator-(const Date& other) const -> double {
        // Find out number of leap years:
        int daysInYearA = findDaysInYear(*this);
        int daysInYearB = findDaysInYear(other);

        return 365*(year - other.year) + daysInYearA - daysInYearB + countLeap(*this, other);
    }

}