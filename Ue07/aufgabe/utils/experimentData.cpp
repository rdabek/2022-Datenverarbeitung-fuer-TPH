#include "experimentData.hpp"

#include <cmath>

namespace experiment {

    Data::Data(const std::string& name, const std::string& unit) {
        dataName = name;
        dataUnit = unit;
        std::cout << "Mask: " << mask << "\n";
        data = new double[mask + 1];
        capacity = mask + 1;
    }

    Data::Data(const Data& other) {
        length = other.length;
        capacity = other.capacity;
        mask = other.mask;
        dataName = other.dataName;
        dataUnit = other.dataUnit;

        data = new double[mask + 1];
        for(int i=0; i<length; i++) {
            data[i] = other.data[i];
        }
    }

    auto Data::operator()(const Data& other) -> Data& {
        length = other.length;
        capacity = other.capacity;
        mask = other.mask;
        dataName = other.dataName;
        dataUnit = other.dataUnit;

        data = new double[mask + 1];
        for(int i=0; i<length; i++) {
            data[i] = other.data[i];
        }

        return *this;
    }

    Data::~Data() {
        delete[] data;                  // Don't use wrong delete operator, as behavior is then unspecified
    }

    auto Data::push_back(double d) -> void {
        if(length >= capacity)
            doubleCapacity();
        
        data[length++] = d;
    }

    auto Data::pop_back() -> void {
        if(length <= 0)
            return;
        
        if(length < capacity/2)
            halfCapacity();
        
        data[length--] = double();
    }

    auto Data::size() const -> int {
        return length;
    }

    auto Data::avg() const -> double {
        double sum = 0.0;
        if(length == 0)
            return sum;     // What else to do...
        
        for(int i=0; i<length; i++)
            sum += data[i];
        
        return sum/(double)length;
    }

    auto Data::err() const -> double {
        if(length == 0)
            return 0.0;     // What else to do...
        
        double sumSq = 0.0, sum = 0.0;

        for(int i=0; i<length; i++) {
            sumSq += data[i] * data[i];
            sum += data[i];
        }
        
        return std::sqrt(1/((double)length*(length-1))*(sumSq - sum*sum/(double)length));
    }

    auto Data::name() const -> std::string {
        return dataName;
    }

    auto Data::unit() const -> std::string {
        return dataUnit;
    }

    auto Data::toSting() const -> std::string {
        std::string ret = dataName + " [" + dataUnit + "]:\n";
        if(length == 0)
            return ret + "{ }";

        ret += "{ ";
        for(int i=0; i<length-1; i++)
            ret += std::to_string(data[i]) + ", ";
        ret += std::to_string(data[length-1]);
        ret += " }";
        return ret;
    }

    auto Data::printFormat(std::ostream& os) const -> void {
        os << dataName << "\n" << avg() << " +/- " << err() << " [" << dataUnit << "]\n";
    }

    auto Data::doubleCapacity() -> void {
        mask = (mask << 1) | 1;         //shift one left and add the missing one in the first place
        auto newData = new double[mask + 1];
        capacity = mask + 1;
        std::cout << "New capacity: " << capacity << "\n";
        for(int i=0; i<capacity; i++)
            newData[i] = data[i];
        delete[] data;
        data = newData;
    }

    auto Data::halfCapacity() -> void {
        mask = (mask >> 1);
        auto newData = new double[mask + 1];
        capacity = mask + 1;
        std::cout << "New capacity: " << capacity << "\n";
        for(int i=0; i<capacity; i++)
            newData[i] = data[i];
        delete[] data;
        data = newData;
    }

}